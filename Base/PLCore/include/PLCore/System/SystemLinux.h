/*********************************************************\
 *  File: SystemLinux.h                                  *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


#ifndef __PLCORE_SYSTEM_LINUX_H__
#define __PLCORE_SYSTEM_LINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <sys/utsname.h>
#include "PLCore/System/ConsoleLinux.h"
#include "PLCore/System/SystemImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Linux 'System' implementation
*/
class SystemLinux : public SystemImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class System;


	//[-------------------------------------------------------]
	//[ Private structures                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Holds memory information
		*/
		struct MemoryInformation {
			uint64 nTotalPhysicalMemory;	/**< Total physical memory in bytes */
			uint64 nFreePhysicalMemory;		/**< Free physical memory in bytes */
			uint64 nTotalSwapMemory;		/**< Total swap memory in bytes */
			uint64 nFreeSwapMemory;			/**< Free swap memory in bytes */
		};


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		SystemLinux();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SystemLinux();

		/**
		*  @brief
		*    Reads memory information from the '/proc/meminfo'-file
		*
		*  @param[out] sMemoryInformation
		*    Receives the memory information
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool GetMemoryInformation(MemoryInformation &sMemoryInformation) const;


	//[-------------------------------------------------------]
	//[ Private virtual SystemImpl functions                  ]
	//[-------------------------------------------------------]
	private:
		virtual String GetPlatform() const override;
		virtual String GetOS() const override;
		virtual char GetSeparator() const override;
		virtual uint32 GetCPUMhz() const override;
		virtual String GetComputerName() const override;
		virtual String GetUserName() const override;
		virtual String GetUserHomeDir() const override;
		virtual String GetUserDataDir() const override;
		virtual String GetDataDirName(const String &sName) const override;
		virtual String GetExecutableFilename() const override;
		virtual String GetEnvironmentVariable(const String &sName) const override;
		virtual bool SetEnvironmentVariable(const String &sName, const String &sValue) const override;
		virtual void DeleteEnvironmentVariable(const String &sName) const override;
		virtual bool Execute(const String &sCommand, const String &sParameters, const String &sWorkingDir) const override;
		virtual String GetLocaleLanguage() const override;
		virtual String GetCurrentDir() const override;
		virtual bool SetCurrentDir(const String &sPath) override;
		virtual Thread *GetCurrentThread() const override;
		virtual void Exit(int nReturn) override;
		virtual const Console &GetConsole() const override;
		virtual Time GetTime() const override;
		virtual uint64 GetMilliseconds() const override;
		virtual uint64 GetMicroseconds() const override;
		virtual void Sleep(uint64 nMilliseconds) const override;
		virtual void Yield() const override;
		virtual float GetPercentageOfUsedPhysicalMemory() const override;
		virtual uint64 GetTotalPhysicalMemory() const override;
		virtual uint64 GetFreePhysicalMemory() const override;
		virtual uint64 GetTotalVirtualMemory() const override;
		virtual uint64 GetFreeVirtualMemory() const override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		ConsoleLinux   m_cConsole;		/**< Console instance */
		bool		   m_bSysInfoInit;	/**< Has 'm_sName' a valid value? */
		struct utsname m_sName;			/**< Basic system information */
		String		   m_sFilename;		/**< Application filename */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_SYSTEM_LINUX_H__