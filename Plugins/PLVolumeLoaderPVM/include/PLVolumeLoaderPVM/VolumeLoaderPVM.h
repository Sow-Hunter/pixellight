/*********************************************************\
 *  File: VolumeLoaderPVM.h                              *
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


#ifndef __PLVOLUMELOADERPVM_VOLUMELOADER_PVM_H__
#define __PLVOLUMELOADERPVM_VOLUMELOADER_PVM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLVolume/Loader/VolumeLoader.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLVolume {
	class Volume;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolumeLoaderPVM {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Volume loader implementation for the "PVM"-format
*
*  @note
*    - Lookout! Due to the lack of an image file format specification, this loader is using GPL code from the V^3 volume rendering package -> Don't use this loader when you're e.g. using LGPL or another less restrictive license...
*    - The file format is part of the V^3 volume rendering package available at http://www.stereofx.org/volume.html and it appears that there's no format specification, just source code
*    - Sample data sets are available at http://www9.informatik.uni-erlangen.de/External/vollib/
*/
class VolumeLoaderPVM : public PLVolume::VolumeLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, VolumeLoaderPVM, "PLVolumeLoaderPVM", PLVolume::VolumeLoader, "Volume loader implementation for the \"PVM\"-format. The file format is part of the V^3 volume rendering package available at http://www.stereofx.org/volume.html .")
		// Properties
		pl_properties
			pl_property("Formats",	"pvm,PVM")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_2(Load,		pl_ret_type(bool),	PLVolume::Volume&,			PLCore::File&,			"Load method, by default 8 bit is enforced",																							"")
		pl_method_3(LoadParams,	pl_ret_type(bool),	PLVolume::Volume&,			PLCore::File&,	bool,	"Load method. Parameters: First 'bool' parameter determines whether or not to enforce 8 bit (may result in a visible quality loss).",	"")
		pl_method_2(Save,		pl_ret_type(bool),	const PLVolume::Volume&,	PLCore::File&,			"Save method",																															"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		bool Load(PLVolume::Volume &cVolume, PLCore::File &cFile);
		bool LoadParams(PLVolume::Volume &cVolume, PLCore::File &cFile, bool bForce8Bit);
		bool Save(const PLVolume::Volume &cVolume, PLCore::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		VolumeLoaderPVM();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~VolumeLoaderPVM();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeLoaderPVM


#endif // __PLVOLUMELOADERPVM_VOLUMELOADER_PVM_H__
