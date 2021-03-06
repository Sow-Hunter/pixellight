/*********************************************************\
 *  File: PLSceneEnumProc.cpp                            *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Xml/Xml.h>
#include <PLCore/File/Directory.h>
#include <IGame/IGame.h>
#include "PL3dsMaxSceneExport/PLSceneExportDialogs.h"
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLTools.h"
#include "PL3dsMaxSceneExport/PLScene.h"
#include "PL3dsMaxSceneExport/PLSceneEnumProc.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Global functions                                      ]
//[-------------------------------------------------------]
DWORD WINAPI fn(LPVOID arg)
{
	// All went fine
	return 0;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
PLSceneEnumProc::PLSceneEnumProc(const char szName[], Interface &cMaxInterface, DWORD nMaxOptions)
{
	{ // 3ds Max version check
		// Get the 3ds Max version of the program currently running
		int nRunning3dsMaxVersion = GET_MAX_RELEASE(Get3DSMAXVersion());

		// Get the 3ds Max version this exporter was build with
		int nBuild3dsMaxVersion   = GET_MAX_RELEASE(VERSION_3DSMAX);

		// Check version match!
		if (nRunning3dsMaxVersion < nBuild3dsMaxVersion) {
			// Show an error message box
			String sError = "Error: 3ds Max version mismatch!\nYou are using version '" + PLTools::ToString(nRunning3dsMaxVersion/1000.0f) +
				"', but this exporter was build for at least version '" + PLTools::ToString(nBuild3dsMaxVersion/1000.0f) + "'!";
			MessageBoxW(nullptr, sError.GetUnicode(), L"PixelLight scene export error", MB_OK);

			// ARGH! Get us out of here!
			return;
		}
	}

	{ // IGame version check
		// Get the IGame version of the program currently running
		float fRunningIGameVersion = GetIGameVersion();

		// Get the IGame version this exporter was build with
		float fBuildIGameVersion   = IGAMEDLLVERSION;

		// Check version match!
		if (fRunningIGameVersion < fBuildIGameVersion) {
			// Show an error message box
			String sError = "Error: 'IGame.dll' version mismatch!\nYou are using version '" + PLTools::ToString(fRunningIGameVersion) +
				"', but this exporter was build for at least version '" + PLTools::ToString(fBuildIGameVersion)+ "'!";
			MessageBoxW(nullptr, sError.GetUnicode(), L"PixelLight scene export error", MB_OK);

			// ARGH! Get us out of here!
			return;
		}
	}

	// Load options
	g_SEOptions.Load();

	// Setup export options
	cMaxInterface.ProgressStart(_T("Export"), true, fn, nullptr);
	if (!PLSceneOpenExportDialog(cMaxInterface)) {
		char szApplicationDrive[_MAX_DRIVE], szApplicationDir[_MAX_DIR];
		String sFilename;

		// Save options. Our default filename is quite long, so, there shouldn't be any conflicts with
		// configuration files of other plugins...
		g_SEOptions.Save();

		// Get filename without path
		_splitpath(szName, szApplicationDrive, szApplicationDir, nullptr, nullptr);
		const char *pszNameT = &szName[strlen(szApplicationDrive) + strlen(szApplicationDir)];
		g_SEOptions.sFilenameOnly = pszNameT;

		// Cut of '.scene' extension
		int nIndex = g_SEOptions.sFilenameOnly.LastIndexOf(".");
		if (nIndex >= 0)
			g_SEOptions.sFilenameOnly.Delete(nIndex);

		// Get filename
		if (g_SEOptions.bPLDirectories) {
			// Data
			String sDataFilename = String(szApplicationDrive) + szApplicationDir + "Data";
			CreateDirectoryW(sDataFilename.GetUnicode(), nullptr);
			// Meshes
			if (g_SEOptions.bExportMeshes) {
				sFilename = sDataFilename + "\\Meshes\\";
				CreateDirectoryW(sFilename.GetUnicode(), nullptr);
				if (g_SEOptions.bSubdirectories) {
					sFilename += g_SEOptions.sFilenameOnly;
					sFilename += '\\';
					CreateDirectoryW(sFilename.GetUnicode(), nullptr);
				}
			}
			// Misc
			sFilename = sDataFilename + "\\Misc\\";
			CreateDirectoryW(sFilename.GetUnicode(), nullptr);
			if (g_SEOptions.bSubdirectories) {
				sFilename += g_SEOptions.sFilenameOnly;
				sFilename += '\\';
				CreateDirectoryW(sFilename.GetUnicode(), nullptr);
			}
			// Scenes
			sFilename = sDataFilename + "\\Scenes\\";
			CreateDirectoryW(sFilename.GetUnicode(), nullptr);
			// Materials
			if (g_SEOptions.bExportMaterials && g_SEOptions.bCreateMaterials) {
				sFilename = sDataFilename + "\\Materials\\";
				CreateDirectoryW(sFilename.GetUnicode(), nullptr);
				if (g_SEOptions.bSubdirectories) {
					sFilename += g_SEOptions.sFilenameOnly;
					sFilename += '\\';
					CreateDirectoryW(sFilename.GetUnicode(), nullptr);
				}
			}
			sFilename = sDataFilename + "\\Scenes\\" + pszNameT;
		} else {
			sFilename = szName;
		}

		// Ensure that the filename ending is '.scene' and not '.SCENE', '.sCeNe' and so on (may cause troubles)
		nIndex = sFilename.LastIndexOf(".");
		if (nIndex >= 0) {
			sFilename.Delete(nIndex);
			sFilename += ".scene";
		}

		g_SEOptions.sFilename = szName;

		bool bSelected = (nMaxOptions & SCENE_EXPORT_SELECTED);
		cMaxInterface.ProgressUpdate(0, 0, _T("Start export..."));
		PLTextFile cFile(sFilename);
		if (cFile.IsValid()) {
			// Log
			if (g_SEOptions.bLog) {
				// Get log filename
				String sLogFilename;
				String sName = szName;
				nIndex = sName.LastIndexOf(".");
				if (nIndex >= 0)
					sName.Delete(nIndex);
				sLogFilename = sName + "Log.txt";

				// Open log
				g_pLog = new PLLog(sLogFilename);
				g_pLog->PrintFLine("Scene filename: %s", szName);
				if (bSelected)
					g_pLog->PrintLine(">> Export selected");
				else
					g_pLog->PrintLine(">> Export all");

				// Write down  the current unit display information
				LogUnitDisplayInformation(*g_pLog);

				// Write the export options into the log
				g_SEOptions.WriteIntoLog();
			} else {
				g_pLog = new PLLog("");
			}

			// Set the log flags
			g_pLog->SetFlags(g_SEOptions.nLogFlags);

			// Check the current filename of the loaded 3ds Max scene
			String sCurFilePath = cMaxInterface.GetCurFilePath();
			if (!sCurFilePath.GetLength())
				g_pLog->LogFLine(PLLog::Warning, "There's no current 3ds Max scene filename! Maybe scene was loaded using Drag'n'Drop and the scene was not dropped within a render viewport?");

			// Initialize the IGame interface
			IGameScene *pIGame = GetIGameInterface();
			if (pIGame) {
				// Setup IGame conversion manager
				IGameConversionManager *pIGameCM = GetConversionManager();
				if (pIGameCM)
					pIGameCM->SetCoordSystem(IGameConversionManager::IGAME_OGL);

				// Setup IGame
				pIGame->InitialiseIGame(bSelected);
				pIGame->SetStaticFrame(cMaxInterface.GetTime());

				// Create the PixelLight scene
				PLScene *pPLScene = new PLScene(cMaxInterface, *pIGame, 0, 60, szApplicationDrive, szApplicationDir);

				// Post process the scene
				cMaxInterface.ProgressUpdate(60, 0, _T("Post process the PixelLight scene..."));
				pPLScene->PostProcess();

				// Save the PixelLight scene right now
				cMaxInterface.ProgressUpdate(62, 0, _T("Save the PixelLight scene..."));
				g_pLog->PrintLine("\nWrite scene to file:");

				// Create XML document
				XmlDocument cDocument;

				// Write down
				pPLScene->WriteToXMLDocument(cDocument);

				// Save settings
				cFile.Close();
				cDocument.Save(sFilename);

				// Write some scene statistics into the log
				pPLScene->OutputStatistics();

				// Cleanup
				cMaxInterface.ProgressUpdate(90, 0, _T("Cleanup..."));
				delete pPLScene;

				// [TODO] Crash with 3ds Max 2010?! (but not on every system?!)
				#ifndef MAX_RELEASE_R10
					// Cleanup IGame
					pIGame->ReleaseIGame();
				#endif
			}

			// Publish?
			if (g_SEOptions.bPublish)
				Publish(String(szApplicationDrive) + szApplicationDir + String("x86"));

			// Close the log
			String sLogFilename = g_pLog->GetFilename();
			delete g_pLog;
			g_pLog = nullptr;

			// Open the log right now?
			if (g_SEOptions.bLog && g_SEOptions.bLogOpen)
				ShellExecuteW(0, L"open", sLogFilename.GetUnicode(), 0, 0, SW_SHOW);

			// Show the scene right now?
			if (g_SEOptions.bShowExportedScene && g_SEOptions.sViewer.GetLength()) {
				String sDirectory = g_SEOptions.sViewer;
				nIndex = sDirectory.LastIndexOf("/");
				if (nIndex < 0)
					nIndex = sDirectory.LastIndexOf("\\");
				if (nIndex >= 0) {
					sDirectory.Delete(nIndex);
					ShellExecuteW(0, L"open", g_SEOptions.sViewer.GetUnicode(), ("\"" + sFilename + "\"").GetUnicode(), sDirectory.GetUnicode(), SW_SHOW);
				}
			}
		} else {
			// Show an error message box
			String sError = "Error: Can't create the file \"" + sFilename + "\"";
			MessageBoxW(nullptr, sError.GetUnicode(), L"PixelLight scene export error", MB_OK);
		}
	}

	// We're done. Finish the progress bar.
	cMaxInterface.ProgressUpdate(100, 0, _T("Export finished"));
	cMaxInterface.ProgressEnd();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Writes down the current unit display information
*/
void PLSceneEnumProc::LogUnitDisplayInformation(PLLog &cLog) const
{
	// Unit display information
	DispInfo sDispInfo;
	GetUnitDisplayInfo(&sDispInfo);
	cLog.PrintSpaces();
	cLog.Print(">> Unit display type: ");
	switch (sDispInfo.dispType) {
		case UNITDISP_GENERIC:
			cLog.Print("Generic");
			break;

		case UNITDISP_METRIC:
			cLog.Print("Metric ");
			switch (sDispInfo.metricDisp) {
				case UNIT_METRIC_DISP_MM: cLog.Print("(millimeters)");    break;
				case UNIT_METRIC_DISP_CM: cLog.Print("(centimeters)");    break;
				case UNIT_METRIC_DISP_M:  cLog.Print("(meters)");         break;
				case UNIT_METRIC_DISP_KM: cLog.Print("(kilometers)");     break;
				default:                  cLog.Print("(unknown system)"); break;
			}
			break;

		case UNITDISP_US:
			cLog.Print("US ");
			switch (sDispInfo.metricDisp) {
				case UNIT_US_DISP_FRAC_IN:    cLog.Print("(fractional inches, ");        break;
				case UNIT_US_DISP_DEC_IN:     cLog.Print("(decimal inches)");            break;
				case UNIT_US_DISP_FRAC_FT:    cLog.Print("(fractional feet, ");          break;
				case UNIT_US_DISP_DEC_FT:     cLog.Print("(decimal feet)");              break;
				case UNIT_US_DISP_FT_FRAC_IN: cLog.Print("(feet w/fractional inches, "); break;
				case UNIT_US_DISP_FT_DEC_IN:  cLog.Print("(feet w/decimal inches)");     break;
				default:                      cLog.Print("(unknown system)");            break;
			}
			switch (sDispInfo.metricDisp) {
				case UNIT_US_DISP_FRAC_IN:
				case UNIT_US_DISP_FRAC_FT:
				case UNIT_US_DISP_FT_FRAC_IN:
					switch (sDispInfo.usFrac) {
						case UNIT_FRAC_1_1:   cLog.Print("1/1)");   break;
						case UNIT_FRAC_1_2:   cLog.Print("1/2)");   break;
						case UNIT_FRAC_1_4:   cLog.Print("1/4)");   break;
						case UNIT_FRAC_1_8:   cLog.Print("1/8)");   break;
						case UNIT_FRAC_1_10:  cLog.Print("1/10)");  break;
						case UNIT_FRAC_1_16:  cLog.Print("1/16)");  break;
						case UNIT_FRAC_1_32:  cLog.Print("1/32)");  break;
						case UNIT_FRAC_1_64:  cLog.Print("1/64)");  break;
						case UNIT_FRAC_1_100: cLog.Print("1/100)"); break;
					}
					break;

				default:
					cLog.Print("?)");
					break;
			}
			break;

		case UNITDISP_CUSTOM:
			cLog.PrintF("Custom: '%s' = '%g' ", sDispInfo.customName.data(), sDispInfo.customValue);
			switch (sDispInfo.customUnit) {
				case UNITS_INCHES:      cLog.Print("inches");      break;
				case UNITS_FEET:        cLog.Print("feet");        break;
				case UNITS_MILES:       cLog.Print("miles");       break;
				case UNITS_MILLIMETERS: cLog.Print("millimeters"); break;
				case UNITS_CENTIMETERS: cLog.Print("centimeters"); break;
				case UNITS_METERS:      cLog.Print("meters");      break;
				case UNITS_KILOMETERS:  cLog.Print("kilometers");  break;
				default:                cLog.Print("unknown");     break;
			}
			break;

		default:
			cLog.Print("Unknown");
			break;
	}
	cLog.Print("\n");

	// Master unit information
	int nType;
	float fScale;
	GetMasterUnitInfo(&nType, &fScale);
	cLog.PrintSpaces();
	cLog.PrintF(">> Master unit: '1 unit' = '%g' ", fScale);
	switch (nType) {
		case UNITS_INCHES:      cLog.Print("inches");      break;
		case UNITS_FEET:        cLog.Print("feet");        break;
		case UNITS_MILES:       cLog.Print("miles");       break;
		case UNITS_MILLIMETERS: cLog.Print("millimeters"); break;
		case UNITS_CENTIMETERS: cLog.Print("centimeters"); break;
		case UNITS_METERS:      cLog.Print("meters");      break;
		case UNITS_KILOMETERS:  cLog.Print("kilometers");  break;
		default:                cLog.Print("unknown");     break;
	}
	cLog.Print("\n");
}

/**
*  @brief
*    Packs everything 'PLViewer' requires into the exported directory
*/
void PLSceneEnumProc::Publish(const String &sTargetDirectory) const
{
	// Get get runtime directory
	char *pszBuffer = PLTools::GetPixelLightRuntimeDirectory();
	if (pszBuffer) {
		// Is there a '\' or '//' at the end?
		size_t nLength = strlen(pszBuffer);
		if (pszBuffer[nLength-1] == '\\' || pszBuffer[nLength-1] == '/') {
			pszBuffer[nLength-1] = '\0';
			nLength--;
		}
		const String &sSourceDirectory = pszBuffer;
		delete [] pszBuffer;

		// Create the executable (x86) directory
		CreateDirectoryW(sTargetDirectory.GetUnicode(), nullptr);

		// Physics support?
		bool bPhysics = (g_SEOptions.sSceneContainer == "PLPhysics::SCPhysicsWorld");

		{ // Copy runtime and data files
			const int NumOfFiles = 20;
			static const String sFiles[] =
			{
				"PLCore.dll",
				"PLMath.dll",
				"PLMath.plugin",
				"PLGraphics.dll",
				"PLGraphics.plugin",
				"PLInput.dll",
				"PLInput.plugin",
				"PLRenderer.dll",
				"PLRenderer.plugin",
				"PLMesh.dll",
				"PLMesh.plugin",
				"PLScene.dll",
				"PLScene.plugin",
				"PLPhysics.dll",
				"PLPhysics.plugin",
				"PLEngine.dll",
				"PLEngine.plugin",
				"PLFrontendOS.dll",
				"PLFrontendOS.plugin",
				"..\\Data\\Standard.zip"
			};
			for (int i=0; i<NumOfFiles; i++) {
				const String sAbsSourceFilename = sSourceDirectory + '\\' + sFiles[i];
				const String sAbsTargetFilename = sTargetDirectory + '\\' + sFiles[i];
				CopyFileW(sAbsSourceFilename.GetUnicode(), sAbsTargetFilename.GetUnicode(), false);
			}
		}

		{ // Copy PLRenderer files
			static const int NumOfFiles = 2;
			static const String sFiles[] =
			{
				"PLRendererOpenGL.dll",
				"PLRendererOpenGL.plugin"
			};
			for (int i=0; i<NumOfFiles; i++) {
				const String sAbsSourceFilename = sSourceDirectory + '\\' + sFiles[i];
				const String sAbsTargetFilename = sTargetDirectory + '\\' + sFiles[i];
				CopyFileW(sAbsSourceFilename.GetUnicode(), sAbsTargetFilename.GetUnicode(), false);
			}
		}

		{ // Copy PLScene files
			static const int NumOfFiles = 2;
			static const String sFiles[] =
			{
				"PLCompositing.dll",
				"PLCompositing.plugin"
			};
			for (int i=0; i<NumOfFiles; i++) {
				const String sAbsSourceFilename = sSourceDirectory + '\\' + sFiles[i];
				const String sAbsTargetFilename = sTargetDirectory + '\\' + sFiles[i];
				CopyFileW(sAbsSourceFilename.GetUnicode(), sAbsTargetFilename.GetUnicode(), false);
			}
		}

		// Copy PLPhysics files
		if (bPhysics) {
			static const int NumOfFiles = 3;
			static const String sFiles[] =
			{
				"PLPhysicsNewton.dll",
				"PLPhysicsNewton.plugin",
				"newton.dll"
			};
			for (int i=0; i<NumOfFiles; i++) {
				const String sAbsSourceFilename = sSourceDirectory + '\\' + sFiles[i];
				const String sAbsTargetFilename = sTargetDirectory + '\\' + sFiles[i];
				CopyFileW(sAbsSourceFilename.GetUnicode(), sAbsTargetFilename.GetUnicode(), false);
			}
		}

		// Copy 'PLViewer.exe'
		String sViewer = PLTools::GetPLViewerFilename();
		if (sViewer.GetLength()) {
			// Copy
			CopyFileW(sViewer.GetUnicode(), (sTargetDirectory + "\\PLViewer.exe").GetUnicode(), false);
		}

		{ // Copy VC2010 redistributable files
			const int NumOfFiles = 2;
			static const String sFiles[] =
			{
				"msvcr100.dll",
				"msvcp100.dll"
			};
			for (int i=0; i<NumOfFiles; i++) {
				const String sAbsSourceFilename = sSourceDirectory + "\\VC2010_Redistributable\\" + sFiles[i];
				const String sAbsTargetFilename = sTargetDirectory + '\\' + sFiles[i];
				CopyFileW(sAbsSourceFilename.GetUnicode(), sAbsTargetFilename.GetUnicode(), false);
			}
		}

		{ // Create the 'PLViewer.cfg' file
			const String sAbsFilename = sTargetDirectory + "\\..\\PLViewer.cfg";

			// Create XML document
			XmlDocument cDocument;

			// Add declaration
			XmlDeclaration *pDeclaration = new XmlDeclaration("1.0", "ISO-8859-1", "");
			cDocument.LinkEndChild(*pDeclaration);

			// Add config
			XmlElement *pConfigElement = new XmlElement("Config");
			pConfigElement->SetAttribute("Version", "1");

			{ // PLViewerConfig
				// Add the 'Group' element
				XmlElement *pGroupElement = new XmlElement("Group");
				pGroupElement->SetAttribute("Class", "PLViewerConfig");
				pGroupElement->SetAttribute("DefaultFilename", "Data\\Scenes\\" + g_SEOptions.sFilenameOnly + ".scene");

				// Link 'Group' element
				pConfigElement->LinkEndChild(*pGroupElement);
			}

			// Link 'Config' element
			cDocument.LinkEndChild(*pConfigElement);

			{ // Before we safe, we need to ensure that the target directory is there, else 'Save()' will fail!
				Url cUrl = sAbsFilename;
				Directory cDirectory(cUrl.CutFilename());
				cDirectory.CreateRecursive();
			}

			// Save settings
			cDocument.Save(sAbsFilename);
		}
	}
}


//[-------------------------------------------------------]
//[ Public virtual ITreeEnumProc functions                ]
//[-------------------------------------------------------]
int PLSceneEnumProc::callback(INode *pMaxNode)
{
	// Continue
	return TREE_CONTINUE;
}
