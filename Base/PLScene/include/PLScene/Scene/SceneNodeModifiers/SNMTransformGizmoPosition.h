/*********************************************************\
 *  File: SNMTransformGizmoPosition.h                    *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLSCENE_SCENENODEMODIFIER_TRANSFORMGIZMOPOSITION_H__
#define __PLSCENE_SCENENODEMODIFIER_TRANSFORMGIZMOPOSITION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Scene/SceneNodeModifiers/SNMTransformGizmo.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract position transform gizmo scene node modifier base class
*/
class SNMTransformGizmoPosition : public SNMTransformGizmo {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMTransformGizmoPosition, "PLScene", PLScene::SNMTransformGizmo, "Abstract position transform gizmo scene node modifier base class")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cSceneNode
		*    Owner scene node
		*/
		PLS_API SNMTransformGizmoPosition(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMTransformGizmoPosition();


	//[-------------------------------------------------------]
	//[ Protected virtual SNMTransformGizmo functions         ]
	//[-------------------------------------------------------]
	protected:
		PLS_API virtual PLCore::uint32 DetermineSelected(const PLMath::Ray &cRay) const override;
		PLS_API virtual void DrawGizmo(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode) override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLMesh::MeshHandler *m_pMeshHandler;	/**< The 'cone' mesh for the axis arrow (always valid!) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODEMODIFIER_TRANSFORMGIZMOPOSITION_H__
