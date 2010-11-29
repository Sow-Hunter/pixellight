/*********************************************************\
 *  File: String.h                                       *
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


#ifndef __PLGENERAL_STRING_H__
#define __PLGENERAL_STRING_H__
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


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    String class
*
*  @remarks
*    The string class uses a 'copy on change' technique - therefore copying one string
*    into another is quite performant because the internal string buffer is shared
*    as long as a string doesn't change. As result comparing strings 'can' also be very fast
*    and the internal string buffer can be ASCII OR Unicode in a quite flexible way.
*    As long as you DON'T save your source codes in an UTF8 format you can also use the ASCII
*    extension Ansi. (characters: 128-256) But with an UTF8 format, this may cause serious problems
*    and you should use Unicode instead ASCII for characters above 128 to avoid encoding troubles!
*    For best compatibility with other string techniques, this class is using pointers instead of
*    [] references, so NULL is a valid parameter.
*
*  @verbatim
*    Usage example:
*    String sS;                        // Test string instance
*    sS = "Mini";                      // Set string to 'Mini' as ASCII
*    sS += " Me";                      // Concatenate 'Me' (ASCII) to string
*    const char *pS = sS.GetASCII();   // Get pointer to ASCII string content
*    const char *pS = sS;              // Get pointer to ASCII string content (same as above)
*    sS = L"Mini";                     // Set string to 'Mini' as Unicode
*    sS = L"\u65e5\u672c\u8a9e";       // Set string to 'nihon' (= Japanese) as Unicode
*    sS = (const utf8*)"Mini";         // Set string to 'Mini' as UTF8
*  @endverbatim
*
*  @note
*    - With 'length' we mean the 'number of characters' and not the 'number of bytes'
*/
class String {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Internal string format
		*/
		enum EFormat {
			Unknown = 0,	/**< Unknown format (can indicate an empty string) */
			ASCII   = 1,	/**< ASCII, 1 byte per character (American Standard Code for Information Interchange, 0-128 defined, above undefined) */
			Unicode = 2,	/**< Unicode, (sometimes called 'multi-byte' or 'wide character') normally 2 bytes (unsigned short) per character */
			UTF8    = 3		/**< [TODO] Under construction! UTF8 (8-bit Unicode Transformation Format) with 1 to 6 bytes to encode one Unicode character */
		};


	//[-------------------------------------------------------]
	//[ Static functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Creates a new formatted string (like sprintf)
		*
		*  @param[in] pszFormat
		*    The format string ... -> The variable arguments (can be NULL)
		*
		*  @return
		*    New string
		*/
		PLGENERAL_API static String Format(const char *pszFormat, ...);
		PLGENERAL_API static String Format(const wchar_t *pszFormat, ...);
		PLGENERAL_API static String Format(const utf8 *pszFormat, ...);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGENERAL_API String();

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nValue
		*    Single character to put into the string
		*/
		PLGENERAL_API String(char nValue);
		PLGENERAL_API String(wchar_t nValue);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pszString
		*    String to save, can be NULL
		*  @param[in] bCopy
		*    Copy the given string or use this one directly? Do ONLY set bCopy to 'false'
		*    if you are sure there can't go anything wrong - the string class will take over
		*    control of the string buffer and also destroy it.
		*  @param[in] nLength
		*    Length of the given string, (excluding the terminating zero) if negative, the length is
		*    calculated automatically
		*  @param[in] nNumOfBytes
		*    Number of bytes of the string buffer (excluding the terminating zero, MUST be valid if not 0!)
		*/
		PLGENERAL_API String(const char *pszString, bool bCopy = true, int nLength = -1);
		PLGENERAL_API String(const wchar_t *pszString, bool bCopy = true, int nLength = -1);
		PLGENERAL_API String(const utf8 *pszString, bool bCopy = true, int nLength = -1, uint32 nNumOfBytes = 0);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] sString
		*    String
		*/
		PLGENERAL_API String(const String &sString);

		/**
		*  @brief
		*    Internal copy constructor
		*
		*  @param[in] pStringBuffer
		*    String buffer to use, can be NULL
		*
		*  @note
		*    - This constructor is ONLY used inside PLGeneral and therefore it's not exported
		*      and usable from 'outside'
		*/
		String(StringBuffer *pStringBuffer);

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API ~String();

		/**
		*  @brief
		*    Returns the length of the string
		*
		*  @return
		*    Length of the string (excluding the terminating zero)
		*/
		PLGENERAL_API uint32 GetLength() const;

		/**
		*  @brief
		*    Returns the internal string format
		*
		*  @return
		*    Internal string format
		*/
		PLGENERAL_API EFormat GetFormat() const;

		/**
		*  @brief
		*    Returns the number of bytes the string is using
		*
		*  @return
		*    The number of bytes the string is using (excluding the terminating zero)
		*
		*  @remarks
		*    Note that the number of bytes a string is using is NOT always equal to the length of it!
		*    For a pure ASCII string the number of bytes is always equal to it's length. For a UTF8 string
		*    the number of bytes 'can', but 'must not' be equal to it's length!
		*/
		PLGENERAL_API uint32 GetNumOfBytes() const;

		/**
		*  @brief
		*    Get a ASCII character of the string
		*
		*  @param[in] nIndex
		*    Position of the ASCII character to retrieve
		*
		*  @return
		*    ASCII character at the given position within the string, terminating NULL (\0) on error
		*/
		PLGENERAL_API char operator [](uint32 nIndex) const;

		/**
		*  @brief
		*    Returns the character string as ASCII
		*
		*  @return
		*    Pointer to the character string as ASCII, never NULL
		*
		*  @remarks
		*    If the internal format of this string doesn't match the requested format, an internal temp
		*    string of the requested format is created and backuped until this original string is manipulated.
		*    Then, the internal backup get's dirty/invalid - so, do NEVER backup the returned pointer by self!
		*
		*  @note
		*    - Do NOT manipulate or even mess up the memory by writing outside the given buffer!
		*/
		PLGENERAL_API const char *GetASCII() const;

		/**
		*  @brief
		*    Returns the character string as ASCII
		*
		*  @return
		*    Pointer to the character string as ASCII, never NULL
		*
		*  @see
		*    - GetASCII()
		*/
		PLGENERAL_API operator const char *() const;

		/**
		*  @brief
		*    Returns the character string as Unicode
		*
		*  @return
		*    Pointer to the character string as Unicode, never NULL
		*
		*  @see
		*    - GetASCII()
		*/
		PLGENERAL_API const wchar_t *GetUnicode() const;

		/**
		*  @brief
		*    Returns the character string as Unicode
		*
		*  @return
		*    Pointer to the character string as Unicode, never NULL
		*
		*  @see
		*    - GetASCII()
		*/
		PLGENERAL_API operator const wchar_t *() const;

		/**
		*  @brief
		*    Returns the character string as UTF8
		*
		*  @return
		*    Pointer to the character string as UTF8, never NULL
		*
		*  @see
		*    - GetASCII()
		*/
		PLGENERAL_API const utf8 *GetUTF8() const;

		/**
		*  @brief
		*    Returns the character string as UTF8
		*
		*  @return
		*    Pointer to the character string as UTF8, never NULL
		*
		*  @see
		*    - GetASCII()
		*/
		PLGENERAL_API operator const utf8 *() const;

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] sString
		*    String to copy
		*
		*  @return
		*    Reference to this string
		*/
		PLGENERAL_API String &operator =(const String &sString);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] pszString
		*    String to copy, can be NULL
		*
		*  @return
		*    Reference to this string
		*/
		PLGENERAL_API String &operator =(const char *pszString);
		PLGENERAL_API String &operator =(const wchar_t *pszString);
		PLGENERAL_API String &operator =(const utf8 *pszString);

		/**
		*  @brief
		*    Concatenate strings
		*
		*  @param[in] sString
		*    String to add
		*
		*  @return
		*    Reference to the new string
		*/
		PLGENERAL_API String operator +(const String &sString) const;

		/**
		*  @brief
		*    Concatenate strings
		*
		*  @param[in] pszString
		*    String to add, can be NULL
		*
		*  @return
		*    Reference to the new string
		*/
		PLGENERAL_API String operator +(const char *pszString) const;
		PLGENERAL_API String operator +(const wchar_t *pszString) const;
		PLGENERAL_API String operator +(const utf8 *pszString) const;

		/**
		*  @brief
		*    Concatenate strings
		*
		*  @param[in] pszString
		*    String to add, can be NULL
		*  @param[in] sString
		*    String to add
		*
		*  @return
		*    Reference to the new string
		*/
		PLGENERAL_API friend String operator +(const char *pszString, const String &sString);
		PLGENERAL_API friend String operator +(const wchar_t *pszString, const String &sString);
		PLGENERAL_API friend String operator +(const utf8 *pszString, const String &sString);

		/**
		*  @brief
		*    Concatenate strings
		*
		*  @param[in] sString
		*    String to add
		*
		*  @return
		*    Reference to this string
		*/
		PLGENERAL_API String &operator +=(const String &sString);

		/**
		*  @brief
		*    Concatenate strings
		*
		*  @param[in] pszString
		*    String to add, can be NULL
		*
		*  @return
		*    Reference to this string
		*/
		PLGENERAL_API String &operator +=(const char *pszString);
		PLGENERAL_API String &operator +=(const wchar_t *pszString);
		PLGENERAL_API String &operator +=(const utf8 *pszString);

		/**
		*  @brief
		*    Compares this string and the given one lexicographically
		*
		*  @param[in] sString
		*    String to compare with
		*
		*  @return
		*    'true' if this string is less than the given one
		*/
		PLGENERAL_API bool operator <(const String &sString) const;

		/**
		*  @brief
		*    Compares this string and the given one lexicographically
		*
		*  @param[in] pszString
		*    String to compare with, can be NULL
		*
		*  @return
		*    'true' if this string is less than the given one
		*/
		PLGENERAL_API bool operator <(const char *pszString) const;
		PLGENERAL_API bool operator <(const wchar_t *pszString) const;
		PLGENERAL_API bool operator <(const utf8 *pszString) const;

		/**
		*  @brief
		*    Compares this string and the given one lexicographically
		*
		*  @param[in] sString
		*    String to compare with
		*
		*  @return
		*    'true' if this string is greater than the given one
		*/
		PLGENERAL_API bool operator >(const String &sString) const;

		/**
		*  @brief
		*    Compares this string and the given one lexicographically
		*
		*  @param[in] pszString
		*    String to compare with, can be NULL
		*
		*  @return
		*    'true' if this string is greater than the given one
		*/
		PLGENERAL_API bool operator >(const char *pszString) const;
		PLGENERAL_API bool operator >(const wchar_t *pszString) const;
		PLGENERAL_API bool operator >(const utf8 *pszString) const;

		/**
		*  @brief
		*    Compare operator (case sensitive)
		*
		*  @param[in] sString
		*    String to compare with
		*
		*  @return
		*    'true' if the two strings are identical, else 'false'
		*/
		PLGENERAL_API bool operator ==(const String &sString) const;

		/**
		*  @brief
		*    Compare operator (case sensitive)
		*
		*  @param[in] pszString
		*    String to compare with, can be NULL
		*
		*  @return
		*    'true' if the two strings are identical, else 'false'
		*/
		PLGENERAL_API bool operator ==(const char *pszString) const;
		PLGENERAL_API bool operator ==(const wchar_t *pszString) const;
		PLGENERAL_API bool operator ==(const utf8 *pszString) const;

		/**
		*  @brief
		*    Compare operator (case sensitive)
		*
		*  @param[in] sString
		*    String to compare with
		*
		*  @return
		*    'true' if the two strings are different, else 'false'
		*/
		PLGENERAL_API bool operator !=(const String &sString) const;

		/**
		*  @brief
		*    Compare operator (case sensitive)
		*
		*  @param[in] pszString
		*    String to compare with, can be NULL
		*
		*  @return
		*    'true' if the two strings are different, else 'false'
		*/
		PLGENERAL_API bool operator !=(const char *pszString) const;
		PLGENERAL_API bool operator !=(const wchar_t *pszString) const;
		PLGENERAL_API bool operator !=(const utf8 *pszString) const;

		/**
		*  @brief
		*    Compare function (case sensitive)
		*
		*  @param[in] sString
		*    String to compare with
		*  @param[in] nPos
		*    Start position within this string
		*  @param[in] nCount
		*    Number of characters to compare, if negative compare all characters, if 0 the result is "true"
		*
		*  @return
		*    'true' if the two strings are identical, else 'false'
		*/
		PLGENERAL_API bool Compare(const String &sString, uint32 nPos = 0, int nCount = -1) const;

		/**
		*  @brief
		*    Compare function (case sensitive)
		*
		*  @param[in] pszString
		*    String to compare with, can be NULL
		*  @param[in] nPos
		*    Start position within this string
		*  @param[in] nCount
		*    Number of characters to compare, if negative compare all characters, if 0 the result is "true"
		*
		*  @return
		*    'true' if the two strings are identical, else 'false'
		*/
		PLGENERAL_API bool Compare(const char *pszString, uint32 nPos = 0, int nCount = -1) const;
		PLGENERAL_API bool Compare(const wchar_t *pszString, uint32 nPos = 0, int nCount = -1) const;
		PLGENERAL_API bool Compare(const utf8 *pszString, uint32 nPos = 0, int nCount = -1) const;

		/**
		*  @brief
		*    Compare function (case insensitive)
		*
		*  @param[in] sString
		*    String to compare with
		*  @param[in] nPos
		*    Start position within this string
		*  @param[in] nCount
		*    Number of characters to compare, if negative compare all characters, if 0 the result is "true"
		*
		*  @return
		*    'true' if the two strings are identical, else 'false'
		*/
		PLGENERAL_API bool CompareNoCase(const String &sString, uint32 nPos = 0, int nCount = -1) const;

		/**
		*  @brief
		*    Compare function (case insensitive)
		*
		*  @param[in] pszString
		*    String to compare with, can be NULL
		*  @param[in] nPos
		*    Start position within this string
		*  @param[in] nCount
		*    Number of characters to compare, if negative compare all characters, if 0 the result is "true"
		*
		*  @return
		*    'true' if the two strings are identical, else 'false'
		*/
		PLGENERAL_API bool CompareNoCase(const char *pszString, uint32 nPos = 0, int nCount = -1) const;
		PLGENERAL_API bool CompareNoCase(const wchar_t *pszString, uint32 nPos = 0, int nCount = -1) const;
		PLGENERAL_API bool CompareNoCase(const utf8 *pszString, uint32 nPos = 0, int nCount = -1) const;

		/**
		*  @brief
		*    Determines whether the string is alphabetic or not
		*
		*  @return
		*    'true' if the string is alphabetic, else 'false' (maybe the string is empty?)
		*
		*  @note
		*    - Examples: 'abc' is alphabetic while 'abc12' or 'ab-c' are not
		*/
		PLGENERAL_API bool IsAlphabetic() const;

		/**
		*  @brief
		*    Determines whether the string is alpha-numeric or not
		*
		*  @return
		*    'true' if the string is alpha-numeric, else 'false' (maybe the string is empty?)
		*
		*  @note
		*    - Examples: 'abc', '12' or 'abc12' are alpha-numeric while 'abc-12' is not
		*/
		PLGENERAL_API bool IsAlphaNumeric() const;

		/**
		*  @brief
		*    Determines whether the string is numeric
		*
		*  @return
		*    'true' if the string is numeric, else 'false' (maybe the string is empty?)
		*
		*  @note
		*    - Examples: '5' or '0' are numeric,
		*      while  '5.1', '.', 'AD', '3D', '5,5', '5.2.8' are not
		*/
		PLGENERAL_API bool IsNumeric() const;

		/**
		*  @brief
		*    Checks whether the given string is a substring of this string or not
		*
		*  @param[in] sString
		*    String to check, if empty string, 'true' will be returned
		*
		*  @return
		*    'true', if the given string is a substring of this string, (or both are empty) else 'false'
		*/
		PLGENERAL_API bool IsSubstring(const String &sString) const;

		/**
		*  @brief
		*    Checks whether the given string is a substring of this string or not
		*
		*  @param[in] pszString
		*    String to check, if NULL or empty, 'true' will be returned
		*
		*  @return
		*    'true', if the given string is a substring of this string, (or both are empty) else 'false' else 'false'
		*/
		PLGENERAL_API bool IsSubstring(const char *pszString) const;
		PLGENERAL_API bool IsSubstring(const wchar_t *pszString) const;
		PLGENERAL_API bool IsSubstring(const utf8 *pszString) const;

		/**
		*  @brief
		*    Returns the index of the substring if contained in this string
		*
		*  @param[in] sString
		*    String to check, if empty string, < 0 will be returned
		*  @param[in] nPos
		*    Start position within this string
		*
		*  @return
		*    Index of the substring if found within this string, < 0 on error
		*    (maybe the given position is invalid) or if both strings are empty
		*/
		PLGENERAL_API int IndexOf(const String &sString, uint32 nPos = 0) const;

		/**
		*  @brief
		*    Returns the index of the substring if contained in this string
		*
		*  @param[in] pszString
		*    String to check, if NULL or empty, < 0 will be returned
		*  @param[in] nPos
		*    Start position within this string
		*
		*  @return
		*    Index of the substring if found within this string, < 0 on error
		*    (maybe the given position is invalid) or if both strings are empty
		*/
		PLGENERAL_API int IndexOf(const char *pszString, uint32 nPos = 0) const;
		PLGENERAL_API int IndexOf(const wchar_t *pszString, uint32 nPos = 0) const;
		PLGENERAL_API int IndexOf(const utf8 *pszString, uint32 nPos = 0) const;

		/**
		*  @brief
		*    Searches from backwards for the index of the substring within this string
		*
		*  @param[in] sString
		*    String to check, if empty string, < 0 will be returned
		*  @param[in] nPos
		*    Start position within this string, if < 0 start at the last character
		*
		*  @return
		*    Index of the substring if found within this string, < 0 on error
		*    (maybe the given position is invalid) or if both strings are empty
		*/
		PLGENERAL_API int LastIndexOf(const String &sString, int nPos = -1) const;

		/**
		*  @brief
		*    Searches from backwards for the index of the substring within this string
		*
		*  @param[in] pszString
		*    String to check, if NULL or empty, < 0 will be returned
		*  @param[in] nPos
		*    Start position within this string, if < 0 start at the last character
		*
		*  @return
		*    Index of the substring if found within this string, < 0 on error
		*    (maybe the given position is invalid) or if both strings are empty
		*/
		PLGENERAL_API int LastIndexOf(const char *pszString, int nPos = -1) const;
		PLGENERAL_API int LastIndexOf(const wchar_t *pszString, int nPos = -1) const;
		PLGENERAL_API int LastIndexOf(const utf8 *pszString, int nPos = -1) const;

		/**
		*  @brief
		*    Get a substring from the string
		*
		*  @param[in] nPos
		*    Start position
		*  @param[in] nCount
		*    Number of characters to copy, negative for everything from nPos to the end of the string
		*
		*  @return
		*    The substring
		*/
		PLGENERAL_API String GetSubstring(uint32 nPos, int nCount = -1) const;

		/**
		*  @brief
		*    Change all characters to lower case
		*
		*  @return
		*    Reference to this string
		*/
		PLGENERAL_API String &ToLower();

		/**
		*  @brief
		*    Change all characters to upper case
		*
		*  @return
		*    Reference to this string
		*/
		PLGENERAL_API String &ToUpper();

		/**
		*  @brief
		*    Delete a substring
		*
		*  @param[in] nPos
		*    Start position of deletion
		*  @param[in] nCount
		*    Number of characters to delete, if negative delete all characters
		*
		*  @return
		*    Reference to this string
		*/
		PLGENERAL_API String &Delete(uint32 nPos = 0, int nCount = -1);

		/**
		*  @brief
		*    Insert a string at a given location
		*
		*  @param[in] sString
		*    String to insert
		*  @param[in] nPos
		*    Position at which to insert the string
		*  @param[in] nCount
		*    Number of characters to add, if negative insert the whole string
		*
		*  @return
		*    Reference to this string
		*/
		PLGENERAL_API String &Insert(const String &sString, uint32 nPos = 0, int nCount = -1);

		/**
		*  @brief
		*    Insert a string at a given location
		*
		*  @param[in] pszString
		*    String to insert, can be NULL
		*  @param[in] nPos
		*    Position at which to insert the string
		*  @param[in] nCount
		*    Number of characters to add, if negative insert the whole string
		*
		*  @return
		*    Reference to this string
		*/
		PLGENERAL_API String &Insert(const char *pszString, uint32 nPos = 0, int nCount = -1);
		PLGENERAL_API String &Insert(const wchar_t *pszString, uint32 nPos = 0, int nCount = -1);
		PLGENERAL_API String &Insert(const utf8 *pszString, uint32 nPos = 0, int nCount = -1);

		/**
		*  @brief
		*    Copies a string
		*
		*  @param[in] pszString
		*    String to copy, can be NULL
		*  @param[in] nCount
		*    Number of characters to copy, if negative copy the whole string
		*
		*  @return
		*    Reference to this string
		*/
		PLGENERAL_API String &Copy(const char *pszString, int nCount = -1);
		PLGENERAL_API String &Copy(const wchar_t *pszString, int nCount = -1);
		PLGENERAL_API String &Copy(const utf8 *pszString, int nCount = -1);

		/**
		*  @brief
		*    Replaces all occurences of a character by another character
		*
		*  @param[in] nOld
		*    Character to be replaced
		*  @param[in] nNew
		*    Character to replace whith
		*
		*  @return
		*    Number of replaced characters (0 if new = old)
		*/
		PLGENERAL_API uint32 Replace(char nOld, char nNew);
		PLGENERAL_API uint32 Replace(wchar_t nOld, wchar_t nNew);

		/**
		*  @brief
		*    Replaces all occurences of a substring by another string
		*
		*  @param[in] sOld
		*    Substring to be replaced
		*  @param[in] sNew
		*    String to replace with
		*
		*  @return
		*    Number of replaced substrings (0 if sNew = sOld or sOld is empty)
		*/
		PLGENERAL_API uint32 Replace(const String &sOld, const String &sNew);

		/**
		*  @brief
		*    Replaces all occurences of a substring by another string
		*
		*  @param[in] pszOld
		*    Substring to be replaced, can be NULL
		*  @param[in] pszNew
		*    String to replace with, can be NULL
		*
		*  @return
		*    Number of replaced substrings (0 if pszNew = pszOld or pszOld is NULL or empty)
		*/
		PLGENERAL_API uint32 Replace(const char *pszOld, const char *pszNew);
		PLGENERAL_API uint32 Replace(const wchar_t *pszOld, const wchar_t *pszNew);
		PLGENERAL_API uint32 Replace(const utf8 *pszOld, const utf8 *pszNew);

		/**
		*  @brief
		*    Sets a character at the given index
		*
		*  @param[in] nIndex
		*    Character index
		*  @param[in] nCharacter
		*    Character to set at the given index
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLGENERAL_API bool SetCharacter(uint32 nIndex, char nCharacter);
		PLGENERAL_API bool SetCharacter(uint32 nIndex, wchar_t nCharacter);
		PLGENERAL_API bool SetCharacter(uint32 nIndex, const utf8 *pnCharacter);

		/**
		*  @brief
		*    Removes all whitespace (tabs and spaces) at the beginning of the string
		*
		*  @return
		*    Reference to this string
		*/
		PLGENERAL_API String &TrimLeading();

		/**
		*  @brief
		*    Removes all whitespace (tabs and spaces) at the end of the string
		*
		*  @return
		*    Reference to this string
		*/
		PLGENERAL_API String &TrimTrailing();

		/**
		*  @brief
		*    Removes all whitespace (tabs and spaces) at the beginning and the end of the string
		*
		*  @return
		*    Reference to this string
		*/
		PLGENERAL_API String &Trim();

		/**
		*  @brief
		*    Removes line endings ("\r\n" or "\n")
		*
		*  @return
		*    Reference to this string
		*/
		PLGENERAL_API String &RemoveLineEndings();


	//[-------------------------------------------------------]
	//[ Conversion functions                                  ]
	//[-------------------------------------------------------]
	public:
		// Is valid tests
		PLGENERAL_API bool IsValidInteger() const;
		PLGENERAL_API bool IsValidFloat() const;

		// Convert from string
		PLGENERAL_API bool     GetBool()     const;
		PLGENERAL_API char     GetChar()     const;
		PLGENERAL_API wchar_t  GetWideChar() const;
		PLGENERAL_API int      GetInt()      const;
		PLGENERAL_API uint32   GetUInt32()   const;
		PLGENERAL_API uint64   GetUInt64()   const;
		PLGENERAL_API uint_ptr GetUIntPtr()  const;
		PLGENERAL_API long     GetLong()     const;
		PLGENERAL_API float    GetFloat()    const;
		PLGENERAL_API double   GetDouble()   const;

		// Convert to string
		PLGENERAL_API String &operator =(bool     bValue);
		PLGENERAL_API String &operator =(char     nValue);
		PLGENERAL_API String &operator =(wchar_t  nValue);
		PLGENERAL_API String &operator =(int      nValue);
		PLGENERAL_API String &operator =(uint32   nValue);
		PLGENERAL_API String &operator =(uint64   nValue);
		PLGENERAL_API String &operator =(float    fValue);
		PLGENERAL_API String &operator =(double   dValue);

		// Concatenation
		PLGENERAL_API String operator +(bool    bValue) const;
		PLGENERAL_API String operator +(char    nValue) const;
		PLGENERAL_API String operator +(wchar_t nValue) const;
		PLGENERAL_API String operator +(int     nValue) const;
		PLGENERAL_API String operator +(uint32  nValue) const;
		PLGENERAL_API String operator +(uint64  nValue) const;
		PLGENERAL_API String operator +(float   fValue) const;
		PLGENERAL_API String operator +(double  dValue) const;
		PLGENERAL_API friend String operator +(bool     bValue, const String &sString);
		PLGENERAL_API friend String operator +(char     nValue, const String &sString);
		PLGENERAL_API friend String operator +(wchar_t  nValue, const String &sString);
		PLGENERAL_API friend String operator +(int      nValue, const String &sString);
		PLGENERAL_API friend String operator +(uint32   nValue, const String &sString);
		PLGENERAL_API friend String operator +(uint64   nValue, const String &sString);
		PLGENERAL_API friend String operator +(float    fValue, const String &sString);
		PLGENERAL_API friend String operator +(double   dValue, const String &sString);
		PLGENERAL_API String &operator +=(bool     bValue);
		PLGENERAL_API String &operator +=(char     nValue);
		PLGENERAL_API String &operator +=(wchar_t  nValue);
		PLGENERAL_API String &operator +=(int      nValue);
		PLGENERAL_API String &operator +=(uint32   nValue);
		PLGENERAL_API String &operator +=(uint64   nValue);
		PLGENERAL_API String &operator +=(float    fValue);
		PLGENERAL_API String &operator +=(double   dValue);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Use a new string buffer
		*
		*  @param[in] pszStringBuffer
		*    New string buffer to use, can be NULL
		*  @param[in] nLength
		*    Length of the string buffer (excluding the terminating zero, MUST be valid!)
		*  @param[in] nNumOfBytes
		*    Number of bytes of the string buffer (excluding the terminating zero, MUST be valid!)
		*/
		void SetStringBuffer(utf8 *pszStringBuffer, uint32 nLength, uint32 nNumOfBytes);

		/**
		*  @brief
		*    Use a new string buffer
		*
		*  @param[in] pStringBuffer
		*    New string buffer to use, can be NULL
		*/
		void SetStringBuffer(StringBuffer *pStringBuffer);

		/**
		*  @brief
		*    Release string buffer
		*/
		void ReleaseStringBuffer();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		StringBuffer *m_pStringBuffer;	/**< Pointer to the string buffer, if NULL, string is empty */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
// Include the string buffer header if we are in debug mode so we can inspect the string in a quite comfortable way
#ifdef _DEBUG
	#include "PLGeneral/String/StringBuffer.h"
#endif


#endif // __PLGENERAL_STRING_H__
