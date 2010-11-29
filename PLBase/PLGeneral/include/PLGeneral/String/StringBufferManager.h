/*********************************************************\
 *  File: StringBufferManager.h                          *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLGENERAL_STRINGBUFFERMANAGER_H__
#define __PLGENERAL_STRINGBUFFERMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/PLGeneral.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class StringBuffer;
class StringBufferUTF8;
class StringBufferASCII;
class StringBufferUnicode;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    String buffer manager
*/
class StringBufferManager {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class String;
	friend class StringBuffer;
	friend class StringBufferUTF8;
	friend class StringBufferASCII;
	friend class StringBufferUnicode;


	//[-------------------------------------------------------]
	//[ Private static data                                   ]
	//[-------------------------------------------------------]
	private:
		static const uint32 NumOfReservedCharacters		= 64;	/**< Number of reserved characters for future use to add when allocating a new string buffer */
		static const uint32 MaxStringReuseLength		= 256;	/**< We don't want to keep alive long strings for later reuse... */
		static const uint32 MaxStringsPerReuseLength	= 4;	/**< Number of reusable strings per string length */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		StringBufferManager();

		/**
		*  @brief
		*    Destructor
		*/
		~StringBufferManager();

		/**
		*  @brief
		*    Returns an instance of a ASCII string buffer
		*
		*  @param[in] nLength
		*    Minimum internal length of the string buffer (excluding the terminating zero, MUST be valid!)
		*
		*  @return
		*    Instance of a ASCII string buffer, NULL on error
		*
		*  @note
		*    - The length of the string buffer is 0, but it has already reserved memory for at least "nLength" characters (+ an additional terminating zero)
		*/
		StringBufferASCII *GetStringBufferASCII(uint32 nLength);

		/**
		*  @brief
		*    Returns an instance of a unicode string buffer
		*
		*  @param[in] nLength
		*    Minimum internal length of the string buffer (excluding the terminating zero, MUST be valid!)
		*
		*  @return
		*    Instance of a unicode string buffer, NULL on error
		*
		*  @note
		*    - The length of the string buffer is 0, but it has already reserved memory for at least "nLength" characters (+ an additional terminating zero)
		*/
		StringBufferUnicode *GetStringBufferUnicode(uint32 nLength);

		/**
		*  @brief
		*    Releases an instance of a string buffer
		*
		*  @param[in] cStringBuffer
		*    String buffer instance to release
		*/
		void ReleaseStringBuffer(StringBuffer &cStringBuffer);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		StringBufferASCII   **m_pStringBufferASCII;		/**< Reusable ASCII string buffers, can be NULL */
		StringBufferUnicode **m_pStringBufferUnicode;	/**< Reusable unicode string buffers, can be NULL */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
}


#endif // __PLGENERAL_STRINGBUFFERMANAGER_H__
