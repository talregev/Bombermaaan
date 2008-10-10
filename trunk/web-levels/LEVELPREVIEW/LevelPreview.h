/************************************************************************************
    Level Preview Generator
    Can be used to generate thumbnails for the web site
 
    Copyright (C) 2008 Markus Drescher

    This file is part of Bombermaaan.

    Bombermaaan is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Bombermaaan is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Bombermaaan.  If not, see <http://www.gnu.org/licenses/>.

************************************************************************************/

/// LevelPreview.h
#ifndef __LEVELPREVIEW_H__
#define __LEVELPREVIEW_H__

#include <png.h>

#include "COptions.h"
#include "STDAFX.H" // this is the STDAFX.H in the Bombermaaan directory

#define BF_TYPE 0x4D42             /* "MB" */

#ifndef WIN32
#define RT_BITMAP "BITMAP"

// BMP file header structure
typedef struct
{
    unsigned short bfType;           // Magic number for file
    unsigned int   bfSize;           // filesize
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int   bfOffBits;        // Offset to bitmap data
} BITMAPFILEHEADER;

// Bitmap Info Header V5 http://msdn.microsoft.com/en-us/library/ms532300(VS.85).aspx
typedef struct { 
  DWORD        biSize; 
  LONG         biWidth; 
  LONG         biHeight; 
  WORD         biPlanes; 
  WORD         biBitCount; 
  DWORD        biCompression; 
  DWORD        biSizeImage; 
  LONG         biXPelsPerMeter; 
  LONG         biYPelsPerMeter; 
  DWORD        biClrUsed; 
  DWORD        biClrImportant; 
  DWORD        biRedMask; 
  DWORD        biGreenMask; 
  DWORD        biBlueMask; 
  DWORD        biAlphaMask; 
  DWORD        biCSType; 
  DWORD        biEndpoints[9]; 
  DWORD        biGammaRed; 
  DWORD        biGammaGreen; 
  DWORD        biGammaBlue; 
  DWORD        biIntent; 
  DWORD        biProfileData; 
  DWORD        biProfileSize; 
  DWORD        biReserved; 
} BITMAPV5HEADER; 

// Compression types
#define BI_RGB       0              // No compression - straight BGR data
#define BI_RLE8      1              // 8-bit run-length compression
#define BI_RLE4      2              // 4-bit run-length compression
#define BI_BITFIELDS 3              // RGB bitmap with RGB masks

// Colormap entry structure
typedef struct                       
{
    unsigned char  rgbBlue;
    unsigned char  rgbGreen;
    unsigned char  rgbRed;
    unsigned char  rgbReserved;
} RGBQUAD;

// Bitmap information structure
typedef struct
{
    BITMAPV5HEADER   bmiHeader;      // Image header
    RGBQUAD          bmiColors[1]; // Image colormap
} BITMAPINFO;
#endif /* WIN32 */

struct SSprite
{
    int SurfaceNumber;          //!< Number of the surface in CDisplay that will be the source
    int ZoneX1;                 // Top-left corner in the source surface
    int ZoneY1;
    int ZoneX2;                 // Bottom-right corner in the source surface
    int ZoneY2;
};

struct SSurface
{
    BITMAPINFO *BitmapInfo;
    BYTE       *BitmapStart;
    int         BitSize;
    bool        Transparent;
    RGBQUAD     Palette[256]; // Image colormap
};

enum {
    TYPE_BITMAP = 0,
    TYPE_SOUND,
    NUM_TYPES
};

// function prototypes
bool LoadSprites      (int SpriteTableWidth, int SpriteTableHeight, int SpriteWidth, int SpriteHeight, bool Transparent, int BMP_ID);
void DrawSprite       (png_bytep *row_pointers, int PositionX, int PositionY, int SpriteTable, int Sprite, int SpriteLayer, int PriorityInLayer);

bool buildOutputImage (const char *out, COptions& options);
void printUsage       (const char *argv0);
int  main             (int argc, const char **argv);

#endif
