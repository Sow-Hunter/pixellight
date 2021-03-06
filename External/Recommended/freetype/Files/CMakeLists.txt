#*********************************************************#
#*  File: CMakeLists.txt                                 *
#*
#*  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
#*
#*  This file is part of PixelLight.
#*
#*  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
#*  and associated documentation files (the "Software"), to deal in the Software without
#*  restriction, including without limitation the rights to use, copy, modify, merge, publish,
#*  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
#*  Software is furnished to do so, subject to the following conditions:
#*
#*  The above copyright notice and this permission notice shall be included in all copies or
#*  substantial portions of the Software.
#*
#*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
#*  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#*  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
#*  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#*  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#*********************************************************#


##################################################
## Project
##################################################
cmake_minimum_required(VERSION 2.8.3)
project(freetype)

##################################################
## Source files
##################################################
set(src
		# Base system
     	src/base/ftsystem.c
     	src/base/ftinit.c
      	src/base/ftdebug.c
      	src/base/ftbase.c
      	src/base/ftbbox.c       # recommended, see <freetype/ftbbox.h>
      	src/base/ftglyph.c      # recommended, see <freetype/ftglyph.h>
      	src/base/ftbdf.c        # optional, see <freetype/ftbdf.h>
      	src/base/ftbitmap.c     # optional, see <freetype/ftbitmap.h>
      	src/base/ftcid.c        # optional, see <freetype/ftcid.h>
      	src/base/ftfstype.c     # optional
      	src/base/ftgasp.c       # optional, see <freetype/ftgasp.h>
      	src/base/ftgxval.c      # optional, see <freetype/ftgxval.h>
      	src/base/ftlcdfil.c     # optional, see <freetype/ftlcdfil.h>
      	src/base/ftmm.c         # optional, see <freetype/ftmm.h>
      	src/base/ftotval.c      # optional, see <freetype/ftotval.h>
      	src/base/ftpatent.c     # optional
      	src/base/ftpfr.c        # optional, see <freetype/ftpfr.h>
      	src/base/ftstroke.c     # optional, see <freetype/ftstroke.h>
      	src/base/ftsynth.c      # optional, see <freetype/ftsynth.h>
      	src/base/fttype1.c      # optional, see <freetype/t1tables.h>
      	src/base/ftwinfnt.c     # optional, see <freetype/ftwinfnt.h>
      	src/base/ftxf86.c       # optional, see <freetype/ftxf86.h>

		# Font drivers
      	src/bdf/bdf.c           # BDF font driver
      	src/cff/cff.c           # CFF/OpenType font driver
      	src/cid/type1cid.c      # Type 1 CID-keyed font driver
      	src/pcf/pcf.c           # PCF font driver
      	src/pfr/pfr.c           # PFR/TrueDoc font driver
      	src/sfnt/sfnt.c         # SFNT files support
        src/truetype/truetype.c # TrueType font driver
      	src/type1/type1.c       # Type 1 font driver
      	src/type42/type42.c     # Type 42 font driver
      	src/winfonts/winfnt.c   # Windows FONT / FNT font driver

		# Rasterizers
      	src/raster/raster.c     # monochrome rasterizer
      	src/smooth/smooth.c     # anti-aliasing rasterizer

		# Auxiliary modules (optional)
      	src/autofit/autofit.c   # auto hinting module
      	src/cache/ftcache.c     # cache sub-system (in beta)
      	src/gzip/ftgzip.c       # support for compressed fonts (.gz)
      	src/lzw/ftlzw.c         # support for compressed fonts (.Z)
      	src/gxvalid/gxvalid.c   # TrueTypeGX/AAT table validation
      	src/otvalid/otvalid.c   # OpenType table validation
      	src/psaux/psaux.c       # PostScript Type 1 parsing
      	src/pshinter/pshinter.c # PS hinting module
      	src/psnames/psnames.c   # PostScript glyph names support
)

##################################################
## Include directories
##################################################
include_directories(
	include
)

##################################################
## Additional libraries
##################################################
#set(libs
#)

##################################################
## Compiler flags
##################################################
add_definitions(
	-DFT2_BUILD_LIBRARY
)

##################################################
## Build
##################################################
add_library(freetype ${src})
#target_link_libraries (freetype ${libs})
