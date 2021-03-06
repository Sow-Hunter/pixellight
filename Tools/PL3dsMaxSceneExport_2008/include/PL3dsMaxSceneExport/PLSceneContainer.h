/*********************************************************\
 *  File: PLSceneContainer.h                             *
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


#ifndef __PL_SCENECONTAINER_H__
#define __PL_SCENECONTAINER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <map>
#include <vector>
#include "PL3dsMaxSceneExport/PLSceneNode.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class PLScene;
class IGameNode;
class PLSceneCell;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Exported PixelLight scene container
*/
class PLSceneContainer : public PLSceneNode {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class PLScene;
	friend class PLSceneCell;
	friend class PLSceneLight;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns a scene node
		*
		*  @param[in] sName
		*    Name of the scene node to return
		*
		*  @return
		*    The scene node with the given name, a null pointer if there's no scene node with the given name
		*
		*  @remarks
		*    Within Get(<Name>) you can also use 'absolute names' instead of 'relative' names. 'Root.MyScene.MyNode'
		*    for instance will return the scene node 'MyNode' within the scene container 'MyScene' with is a
		*    subnode of 'Root'. 'MyScene.MyNode' will return the node 'MyNode' of the container 'MyScene' which is
		*    an element of the current container. 'Parent.MyNode' will return the scene node 'MyNode' within the parent
		*    scene container. 'Parent' returns the parent scene container, '' returns THIS container, 'Root' will return
		*    the root scene container itself.
		*/
		PLSceneNode *Get(const PLCore::String &sName);

		/**
		*  @brief
		*    Returns the world space center of this container
		*
		*  @return
		*    The world space center of this container
		*
		*  @note
		*    - This center is calculated within PostProcess()
		*/
		const Point3 &GetWorldSpaceCenter() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pContainer
		*    Container this container is in, a null pointer if this is the root container of the scene
		*  @param[in] sName
		*    Name of this scene node
		*  @param[in] nType
		*    Scene node type
		*/
		PLSceneContainer(PLSceneContainer *pContainer, const PLCore::String &sName, EType nType = TypeContainer);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PLSceneContainer();

		/**
		*  @brief
		*    Returns a cell with the given name
		*
		*  @param[in] sName
		*    Name of the cell to return
		*  @param[in] cIGameNode
		*    IGame node the cell name comes from
		*
		*  @return
		*    Cell with the given name, a null pointer on error
		*
		*  @note
		*    - If there's no cell with this name, a new one is created
		*/
		PLSceneCell *GetCell(const PLCore::String &sName, IGameNode &cIGameNode);

		/**
		*  @brief
		*    Checks and corrects names
		*
		*  @param[in] sName
		*    Name to check and correct
		*  @param[in] szMaxNode
		*    Name of the 3ds Max node this name comes from
		*  @param[in] szType
		*    Type of the name
		*/
		void CheckAndCorrectName(PLCore::String &sName, const TCHAR szMaxNode[], const char szType[]) const;

		/**
		*  @brief
		*    Writes the scene container into a file
		*
		*  @param[in] cSceneElement
		*    Scene XML element to insert into
		*  @param[in] sApplicationDrive
		*    Application drive
		*  @param[in] sApplicationDir
		*    Application directory
		*  @param[in] sClass
		*    Name of the node class
		*/
		void WriteToFile(PLCore::XmlElement &cSceneElement, const PLCore::String &sApplicationDrive, const PLCore::String &sApplicationDir, const PLCore::String &sClass);


	//[-------------------------------------------------------]
	//[ Protected virtual PLSceneContainer functions          ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Adds an IGame node to the scene
		*
		*  @param[in] cIGameNode
		*    IGame node to add
		*
		*  @return
		*    'true' if all went fine, else 'false' (unknown node type?)
		*/
		virtual bool AddIGameNode(IGameNode &cIGameNode);

		/**
		*  @brief
		*    Post processes the scene
		*
		*  @note
		*    - This function is called before the scene is saved
		*/
		virtual void PostProcess();

		/**
		*  @brief
		*    Writes the container statistics into the log
		*/
		virtual void OutputStatistics();


	//[-------------------------------------------------------]
	//[ Private structures                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Statistics
		*/
		struct SStatistics {
			int nNumOfCells;		/**< Number of cell nodes */
			int nNumOfCellPortals;	/**< Number of cell-portal nodes */
			int nNumOfAntiPortals;	/**< Number of anti-portal nodes */
			int nNumOfCameras;		/**< Number of camera nodes */
			int nNumOfLights;		/**< Number of light nodes */
			int nNumOfObjects;		/**< Number of object nodes */
			int nNumOfHelpers;		/**< Number of helper nodes */
			int nNumOfUnknown;		/**< Number of unknown nodes */
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool									m_bFixedCenter;		/**< Do not calculate world space center of this container automatically */
		Point3									m_vCenter;			/**< World space center of this container */
		std::vector<PLSceneNode*>				m_lstSceneNodes;	/**< List of scene nodes within this container */
		SStatistics								m_sStatistics;		/**< Statistics */
		std::map<PLCore::String, PLSceneCell*>	m_mapCells;			/**< Map with scene cell references within this container */
		std::map<PLCore::String, PLSceneNode*>	m_mapNodes;			/**< Map with scene node references within this container */


	//[-------------------------------------------------------]
	//[ Protected virtual PLSceneNode functions               ]
	//[-------------------------------------------------------]
	protected:
		virtual void WriteToFile(PLCore::XmlElement &cSceneElement, const PLCore::String &sApplicationDrive, const PLCore::String &sApplicationDir) override;


};


#endif // __PL_SCENECONTAINER_H__
