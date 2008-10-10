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

#include "LevelPreview.h"

#include <iostream>
#include <string.h>

using namespace std;

#ifdef USE_32_PIXELS_PER_BLOCK
#define MINI_ARENA_TILE_SIZE                16
#define TILE_POSITION_TO_BOMBER_POSITION    -4
#else
#define MINI_ARENA_TILE_SIZE                 8
#define TILE_POSITION_TO_BOMBER_POSITION    -2
#endif

// Define the name of the DLL (where sprites and sound samples are stored)
static HMODULE m_hModule = NULL;

#ifdef WIN32
#  ifdef USE_32_PIXELS_PER_BLOCK
#    define NAME_OF_BOMBERMAN_DLL "Bombermaaan_32.dll"
#  else
#    define NAME_OF_BOMBERMAN_DLL "Bombermaaan.dll"
#  endif
#else
#  define NAME_OF_BOMBERMAN_DLL "libbombermaaan.so"
#endif


#define IMAGE_WIDTH                         (MINI_ARENA_TILE_SIZE * ARENA_WIDTH)
#define IMAGE_HEIGHT                        (MINI_ARENA_TILE_SIZE * ARENA_HEIGHT)

static vector<vector<SSprite> > m_SpriteTables; //!< Available sprite tables
static vector<SSurface>         m_Surfaces;     //!< Surfaces

#undef jmpbuf

// png error/warning functions
static void user_error_fn(png_structp, png_const_charp error_msg)
{
    cout << error_msg << endl;
}

static void user_warning_fn(png_structp, png_const_charp warning_msg)
{
    cout << warning_msg << endl;
}

// png i/o user functions (due to a bug in libpng (WIN32) which cannot use the FILE pointers
void user_write_data(png_structp write_ptr,
        png_bytep data, png_size_t length)
{
    fwrite(data, length, 1, (FILE *)png_get_io_ptr(write_ptr));
}

void user_flush_data(png_structp write_ptr)
{
    fflush((FILE *)png_get_io_ptr(write_ptr));
}

/**
 * @brief   helper function: shift color to the right with a given mask
 *          see http://www.kalytta.com/bitmap.h
 * @param   Color               color to shift
 * @param   Mask                the mask which is used to shift
 * @param   DistributeToBits    distribute the result to this number of bits
 * @return  Color shifted by Mask to the right
 */
unsigned int ShiftRightByMask(unsigned int Color, unsigned int Mask, unsigned int DistributeToBits = 8)
{
	if (Mask == 0) return 0;

	unsigned int ShiftCount = 0;
	unsigned int Test = 0x00000001;

	while (ShiftCount < 32)
    {
		if (Mask & Test) {
			break;
		}
		Test <<= 1;
		ShiftCount++;
	}
	
	unsigned int BitCount = 32;
	Test = 0x80000000;

	while (BitCount)
    {
		if ((Mask >> ShiftCount) & Test)
        {
			break;
		}
		Test >>= 1;
		BitCount--;
	}

	unsigned int BaseColor = (Color & Mask) >> ShiftCount;

	if (DistributeToBits > BitCount)
    {
		/* We have to fill lower bits */
		unsigned int BitsToFill = DistributeToBits - BitCount;
		while (BitsToFill--)
        {
			BaseColor <<= 1;
			if (BaseColor & 1)
            {
				BaseColor |= 1;
			}
		}
	}
    else if (DistributeToBits < BitCount)
    {
		BaseColor >>= (BitCount - DistributeToBits);
	}
	return BaseColor;
}

/**
 * @brief   load sprites from a bitmap
 * @param   SpriteTableWidth    width of the table in the bitmap
 * @param   SpriteTableHeight   height of the table in the bitmap
 * @param   SpriteWidth         width of the sprite to load
 * @param   SpriteHeight        height of the sprite to load
 * @param   Transparent         does this sprite use transparency?
 * @param   hBitmap             Bitmap number
 */
bool LoadSprites (int SpriteTableWidth, 
                  int SpriteTableHeight, 
                  int SpriteWidth, 
                  int SpriteHeight, 
                  bool Transparent, 
                  int BMP_ID)
{
    HRSRC hResource = FindResource(m_hModule, MAKEINTRESOURCE(BMP_ID), RT_BITMAP);
    HGLOBAL hBitmap;
    LPVOID Bitmap;
    DWORD DataSize;

    if (hResource == NULL)
    {
        cout << "Could not find resource image (" << BMP_ID << ")." << endl;
        return false;
    }

    hBitmap = LoadResource (m_hModule, hResource);

    if (hBitmap == NULL)
    {
        cout << "Could not load resource image (" << BMP_ID << ")." << endl;
        return false;
    }

    Bitmap = LockResource(hBitmap);
    if (Bitmap == NULL)
    {
        cout << "Could not lock resource" << endl;
        return false;
    }

    DataSize = SizeofResource(m_hModule, hResource);
    if (DataSize == 0)
    {
        // Log failure
        cout << "Could not get the bitmap's (res id: " << hBitmap << ") attributes." << endl;

        // Get out
        return false;
    }

    SSurface Surface;
    
    unsigned int        infosize;     // Size of header information
    unsigned int offbits;
    
    BYTE *CurrentPosition = (BYTE *)Bitmap;
    
    // in WIN32 there is no file header
#ifndef WIN32
    // check if bitmap is valid
    BITMAPFILEHEADER    header;

    header.bfType      = *((WORD *)CurrentPosition);
    CurrentPosition += sizeof(WORD);

    header.bfSize      = *((unsigned int *)CurrentPosition);
    CurrentPosition += sizeof(unsigned int);
    
    header.bfReserved1 = *((WORD *)CurrentPosition);
    CurrentPosition += sizeof(WORD);
    
    header.bfReserved2 = *((WORD *)CurrentPosition);
    CurrentPosition += sizeof(WORD);
    
    header.bfOffBits   = *((unsigned int *)CurrentPosition);
    CurrentPosition += sizeof(unsigned int);

    offbits = header.bfOffBits;

    if (header.bfType != BF_TYPE) /* Check for BM reversed... */
        return false;
#endif
    infosize = *((unsigned int *)CurrentPosition);
    if ((Surface.BitmapInfo = new BITMAPINFO) == NULL)
        return false;

    Surface.BitmapInfo->bmiHeader.biSize         = infosize;
    CurrentPosition += sizeof(unsigned int);
    
    Surface.BitmapInfo->bmiHeader.biWidth         = *((int *)CurrentPosition);
    CurrentPosition += sizeof(int);
    
    Surface.BitmapInfo->bmiHeader.biHeight        = *((int *)CurrentPosition);
    CurrentPosition += sizeof(int);
    
    Surface.BitmapInfo->bmiHeader.biPlanes        = *((WORD *)CurrentPosition);
    CurrentPosition += sizeof(WORD);
    
    Surface.BitmapInfo->bmiHeader.biBitCount      = *((WORD *)CurrentPosition);
    CurrentPosition += sizeof(WORD);
    
    Surface.BitmapInfo->bmiHeader.biCompression   = *((unsigned int *)CurrentPosition);
    CurrentPosition += sizeof(unsigned int);
    
    Surface.BitmapInfo->bmiHeader.biSizeImage     = *((unsigned int *)CurrentPosition);
    CurrentPosition += sizeof(unsigned int);

    Surface.BitmapInfo->bmiHeader.biXPelsPerMeter = *((int *)CurrentPosition);
    CurrentPosition += sizeof(int);
    
    Surface.BitmapInfo->bmiHeader.biYPelsPerMeter = *((int *)CurrentPosition);
    CurrentPosition += sizeof(int);
    
    Surface.BitmapInfo->bmiHeader.biClrUsed       = *((unsigned int *)CurrentPosition);
    CurrentPosition += sizeof(unsigned int);
    
    Surface.BitmapInfo->bmiHeader.biClrImportant  = *((unsigned int *)CurrentPosition);
    CurrentPosition += sizeof(unsigned int);
    
    // there are always DWORDS following sizeof(unsigned int)
    // 14: sizeof(BITMAPFILEHEADER) in WIN32, 40: sizeof(BITMAPINFOHEADER)
    BYTE *subtrahend = (BYTE *)Bitmap + 14 - sizeof(unsigned int);
    
#ifdef WIN32
    // there is no further information in header

    // offbits
    offbits = DataSize - Surface.BitmapInfo->bmiHeader.biSizeImage;
#else
    // pseudo-while loop (for using break)
    while (CurrentPosition - subtrahend < infosize)
    {
        // we have masks
        Surface.BitmapInfo->bmiHeader.biRedMask   = *((unsigned int *)CurrentPosition);
        CurrentPosition += sizeof(unsigned int);
        if (CurrentPosition - subtrahend >= infosize) break;
        
        Surface.BitmapInfo->bmiHeader.biGreenMask = *((unsigned int *)CurrentPosition);
        CurrentPosition += sizeof(unsigned int);
        if (CurrentPosition - subtrahend >= infosize) break;
        
        Surface.BitmapInfo->bmiHeader.biBlueMask  = *((unsigned int *)CurrentPosition);
        CurrentPosition += sizeof(unsigned int);
        if (CurrentPosition - subtrahend >= infosize) break;

        Surface.BitmapInfo->bmiHeader.biAlphaMask  = *((unsigned int *)CurrentPosition);
        CurrentPosition += sizeof(unsigned int);
        if (CurrentPosition - subtrahend >= infosize) break;
        
        Surface.BitmapInfo->bmiHeader.biCSType  = *((unsigned int *)CurrentPosition);
        CurrentPosition += sizeof(unsigned int);
        if (CurrentPosition - subtrahend >= infosize) break;

        for (int i = 0; i < 9 && (CurrentPosition - subtrahend < infosize); i++)
        {
            Surface.BitmapInfo->bmiHeader.biEndpoints[i] = *((unsigned int *)CurrentPosition);
            CurrentPosition += sizeof(unsigned int);
        }
        if (CurrentPosition - subtrahend >= infosize) break;
    
        Surface.BitmapInfo->bmiHeader.biGammaRed   = *((unsigned int *)CurrentPosition);
        CurrentPosition += sizeof(unsigned int);
        if (CurrentPosition - subtrahend >= infosize) break;
    
        Surface.BitmapInfo->bmiHeader.biGammaGreen = *((unsigned int *)CurrentPosition);
        CurrentPosition += sizeof(unsigned int);
        if (CurrentPosition - subtrahend >= infosize) break;
    
        Surface.BitmapInfo->bmiHeader.biGammaBlue  = *((unsigned int *)CurrentPosition);
        CurrentPosition += sizeof(unsigned int);
        if (CurrentPosition - subtrahend + 3*sizeof(unsigned int) >= infosize) break;
    
        // ignore the rest
        CurrentPosition += sizeof(unsigned int) * 4;
        break; // exit while
    }
#endif
    
    if ((CurrentPosition - (BYTE *)Bitmap) < offbits &&
        Surface.BitmapInfo->bmiHeader.biClrUsed > 0)
    {
        // Palette
        memcpy(Surface.Palette, CurrentPosition, Surface.BitmapInfo->bmiHeader.biClrUsed * sizeof(RGBQUAD));
        CurrentPosition += Surface.BitmapInfo->bmiHeader.biClrUsed * sizeof(RGBQUAD);
    }
    else if ((CurrentPosition - (BYTE *)Bitmap) < offbits)
    {
        // set to offset where the image starts
        CurrentPosition = (BYTE *)Bitmap + offbits;
    }

    // Now that we have all the header info find out where the image begins
    // save its size and its beginning
    if ((Surface.BitSize = Surface.BitmapInfo->bmiHeader.biSizeImage) == 0)
        Surface.BitSize = (Surface.BitmapInfo->bmiHeader.biWidth *
                           Surface.BitmapInfo->bmiHeader.biBitCount + 7) / 8 *
  	                       abs(Surface.BitmapInfo->bmiHeader.biHeight);

    Surface.BitmapStart = CurrentPosition;
    
    //----------------------------------------------
    // Set the surface transparency color if needed
    //----------------------------------------------
    Surface.Transparent = Transparent;

    //-----------------------
    // Store the new surface
    //-----------------------

    // Add the surface to the surface container
    m_Surfaces.push_back(Surface);
    
    //---------------------------
    // Create the sprite table
    //---------------------------

    // Prepare a sprite table
    vector<SSprite> SpriteTable;
            
    // Variable rectangle coordinates that will be passed during sprite creations
    int ZoneX1 = 1;
    int ZoneY1 = 1;
    int ZoneX2 = 1 + SpriteWidth;
    int ZoneY2 = 1 + SpriteHeight;

    // Scan all the sprites in this surface
    for (int Y = 0 ; Y < SpriteTableHeight ; Y++)
    {
        for (int X = 0 ; X < SpriteTableWidth ; X++)
        {
            // Prepare a sprite
            SSprite Sprite;
            Sprite.SurfaceNumber = m_Surfaces.size() - 1;       // The surface we just added to the container
            Sprite.ZoneX1 = ZoneX1;
            Sprite.ZoneY1 = ZoneY1;
            Sprite.ZoneX2 = ZoneX2;
            Sprite.ZoneY2 = ZoneY2;

            // Advance the rectangle on the row
            ZoneX1 += SpriteWidth + 1;
            ZoneX2 += SpriteWidth + 1;
            
            // Add the sprite to the sprite table
            SpriteTable.push_back (Sprite);
        }

        // Back to beginning of row
        ZoneX1 = 1;
        ZoneX2 = 1 + SpriteWidth;

        // Make the rectangle go down
        ZoneY1 += SpriteHeight + 1;
        ZoneY2 += SpriteHeight + 1;
    }

    // Store the sprite table
    m_SpriteTables.push_back (SpriteTable);
    
	// Everything went right
    return true;
}

/**
 * @brief   draw the demanded sprite to the given position
 * @biref   row_pointers    pointer to the image rows (libpng)
 * @param   PositionX       position on the x-axis on the target image
 * @param   PositionY       position on the y-axis on the target image
 * @param   pZone           ignored
 * @param   pClip           ignored
 * @param   Sprite          number of sprite use
 * @param   SpriteTable     number of sprite table to use
 * @param   SpriteLayer     ignored
 * @param   PriorityInLayer ignored
 */
void DrawSprite (png_bytep *row_pointers,
                 int PositionX, 
                 int PositionY, 
                 int SpriteTable, 
                 int Sprite, 
                 int SpriteLayer, 
                 int PriorityInLayer)
{
    // Check if the parameters are valid
    ASSERT (SpriteTable >= 0 && SpriteTable < (int)m_SpriteTables.size());
    ASSERT (Sprite >= 0 && Sprite < (int)m_SpriteTables[SpriteTable].size());
    
    int X, Y;
    
    int SpriteWidth   = m_SpriteTables[SpriteTable][Sprite].ZoneX2 -
                        m_SpriteTables[SpriteTable][Sprite].ZoneX1;
    int SpriteHeight  = m_SpriteTables[SpriteTable][Sprite].ZoneY2 -
                        m_SpriteTables[SpriteTable][Sprite].ZoneY1;
    int SurfaceNumber = m_SpriteTables[SpriteTable][Sprite].SurfaceNumber;
    
    BYTE *offset;

    unsigned short BitCount = m_Surfaces[SurfaceNumber].BitmapInfo->bmiHeader.biBitCount;
    int         BitmapWidth = m_Surfaces[SurfaceNumber].BitmapInfo->bmiHeader.biWidth;
    int        BitmapHeight = m_Surfaces[SurfaceNumber].BitmapInfo->bmiHeader.biHeight;
    unsigned int Compression= m_Surfaces[SurfaceNumber].BitmapInfo->bmiHeader.biCompression;
    
    unsigned int RedMask = 0, GreenMask = 0, BlueMask = 0;
#ifdef WIN32
    // we don't recognize compression
    if (0)
    {
    }
#else
    if (Compression == 3)
    {
        RedMask   = m_Surfaces[SurfaceNumber].BitmapInfo->bmiHeader.biRedMask;
        GreenMask = m_Surfaces[SurfaceNumber].BitmapInfo->bmiHeader.biGreenMask;
        BlueMask  = m_Surfaces[SurfaceNumber].BitmapInfo->bmiHeader.biBlueMask;
    }
#endif
    else if (BitCount == 16)
    {
        RedMask   = 0xf800;
        GreenMask = 0x7e0;
        BlueMask  = 0x1f;
    }
    else
    {
        RedMask   = 0xff;
        GreenMask = 0x00ff;
        BlueMask  = 0x0000ff;
    }

    unsigned int  LineWidth = (BitmapWidth * BitCount / 8 + 3) & ~3;
    unsigned int  LineStart = m_SpriteTables[SpriteTable][Sprite].ZoneX1 * BitCount / 8;
    
    BYTE pos;
    RGBQUAD *ColorTable = m_Surfaces[SurfaceNumber].Palette;
    
    if (Compression != 0 && Compression != 3) // no RLE Compression atm
        return;
    
    offset = m_Surfaces[SurfaceNumber].BitmapStart +
             (BitmapHeight - m_SpriteTables[SpriteTable][Sprite].ZoneY1-1) * LineWidth + LineStart;
    
    if (PositionY < 0)
        offset += PositionY * LineWidth;

    for (Y = MAX(0,PositionY); Y < MIN(IMAGE_HEIGHT, PositionY + SpriteHeight); Y++)
    {
        if (PositionX < 0)
            offset += PositionX * (-1) * BitCount / 8;
        
        // find position in this row (3 bytes per pixel)
        for (X = MAX(0,PositionX); X < MIN(IMAGE_WIDTH, PositionX + SpriteWidth); X++)
        {
            unsigned char red = 0, green = 0, blue = 0;
            unsigned int Color = 0;
            // copy pixel from bitmap
            switch (BitCount)
            {
                case 1:
                    // untested
                    pos = 128 >> (X % 8);
                    red   = (*offset & pos) ? ColorTable[1].rgbRed   : ColorTable[0].rgbRed;
                    green = (*offset & pos) ? ColorTable[1].rgbGreen : ColorTable[0].rgbGreen;
                    blue  = (*offset & pos) ? ColorTable[1].rgbBlue  : ColorTable[0].rgbBlue;
                    if (X % 8 == 7) offset++;
                    break;
                case 4:
                    // untested
                    if (X % 2 == 0)
                    {
                        red   = ColorTable[(*offset >> 4) & 0x0f].rgbRed;
                        green = ColorTable[(*offset >> 4) & 0x0f].rgbGreen;
                        blue  = ColorTable[(*offset >> 4) & 0x0f].rgbBlue;
                    }
                    else
                    {
                        red   = ColorTable[(*offset) & 0x0f].rgbRed;
                        green = ColorTable[(*offset) & 0x0f].rgbGreen;
                        blue  = ColorTable[(*offset) & 0x0f].rgbBlue;
                        offset++;
                    }
                    break;
                case 8:
                    red   = ColorTable[*offset].rgbRed;
                    green = ColorTable[*offset].rgbGreen;
                    blue  = ColorTable[*offset].rgbBlue;
                    offset++;
                    break;
                case 16:
                    Color = *((unsigned short *)offset);

                    if (Compression == 0)
                    {
                        red   = ShiftRightByMask(Color, RedMask);
                        green = ShiftRightByMask(Color, GreenMask);
                        blue  = ShiftRightByMask(Color, BlueMask);
                    }
                    else // Compression == 3
                    {
                        red   = ShiftRightByMask(Color, RedMask);
                        green = ShiftRightByMask(Color, GreenMask);
                        blue  = ShiftRightByMask(Color, BlueMask);
                    }
                    offset += 2;
                    break;
                case 24:
                    // untested
                    Color = *((unsigned int *)offset);
                    blue  = (Color >> 16)  & 0xff;
                    green = (Color >> 8)  & 0xff;
                    red   = Color & 0xff;
                    offset += 3;
                    break;
                case 32:
                    // untested
                    Color = *((unsigned int *)offset);
                    if (Compression == 0)
                    {
                        red   = (Color >> 16) & 0xff;
                        green = (Color >> 8) & 0xff;
                        blue  = Color & 0xff;
                    }
                    else // Compression == 3
                    {
                        red   = ShiftRightByMask(Color, RedMask);
                        green = ShiftRightByMask(Color, GreenMask);
                        blue  = ShiftRightByMask(Color, BlueMask);
                    }
                    offset += 4;
                    break;
                default:
                    return;
            }
            
            if (!m_Surfaces[SurfaceNumber].Transparent ||
                red != 0x00 || green != 0xff || blue != 0x00)
            {
                row_pointers[Y][3*X]   = red;
                row_pointers[Y][3*X+1] = green;
                row_pointers[Y][3*X+2] = blue;
            }
        }

        offset -= LineWidth + m_SpriteTables[SpriteTable][Sprite].ZoneX2 * BitCount / 8 - LineStart;
    }
}

/**
 * @brief   build the demanded image with the level thumbnail
 * @param   out the output file (png)
 * @return  true if it worked, false otherwise
 */
bool buildOutputImage(const char *out, COptions& options)
{
    png_structp write_ptr;
    png_infop info_ptr;
    unsigned char **row_pointers = NULL;

    int X, Y;

    // create write struct
    write_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, (png_voidp)out,
      user_error_fn, user_warning_fn);
    
    if (!write_ptr)
       return false;

    // and info struct
    info_ptr = png_create_info_struct(write_ptr);
    if (!info_ptr)
    {
       png_destroy_write_struct(&write_ptr,
         (png_infopp)NULL);
       return false;
    }
    
    // open png file
    FILE *fp = fopen(out, "wb");
    if (!fp)
    {
       png_destroy_write_struct(&write_ptr, &info_ptr);
       return false;
    }

    // set error handler
    if (setjmp(png_jmpbuf(write_ptr)))
    {
       png_destroy_write_struct(&write_ptr, &info_ptr);
       fclose(fp);
       return false;
    }
    
    // initialise png header
    png_set_IHDR(write_ptr, info_ptr, IMAGE_WIDTH, IMAGE_HEIGHT,
       8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
       PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    // allocate memory for the image
    row_pointers = (unsigned char **) calloc(sizeof(unsigned char*),IMAGE_HEIGHT);
    if (row_pointers == NULL) return false;
    row_pointers[0] = (unsigned char  *) calloc(sizeof(unsigned char),IMAGE_HEIGHT*IMAGE_WIDTH*3);
    if (row_pointers[0] == NULL)
    {
        free(row_pointers);
        return false;
    }

    for (int i = 1; i < IMAGE_HEIGHT; i++)
    {
      row_pointers[i] = row_pointers[i-1] + IMAGE_WIDTH*3;
      memset(row_pointers[i], 0, IMAGE_WIDTH * 3); // initialise with black
    }

    // Scan all the blocks of the arena (first the blocks, then the bombers
    for (X = 0 ; X < ARENA_WIDTH ; X++)
    {
        for (Y = 0 ; Y < ARENA_HEIGHT ; Y++)
        {            
            EBlockType BlockType = options.GetBlockType(X, Y);
            
            if (BlockType == BLOCKTYPE_HARDWALL)
            {    
                DrawSprite (row_pointers, X * MINI_ARENA_TILE_SIZE, Y * MINI_ARENA_TILE_SIZE, 
                                        0, 0, 1, 1);
            }
            else if (BlockType == BLOCKTYPE_RANDOM)
            {
                DrawSprite (row_pointers, X * MINI_ARENA_TILE_SIZE, Y * MINI_ARENA_TILE_SIZE, 0, 1, 1, 1);
            }
            else
            {
                bool Shadow = (Y - 1 >= 0 && 
                               (options.GetBlockType(X, Y - 1) == BLOCKTYPE_HARDWALL ||
                                options.GetBlockType(X, Y - 1) == BLOCKTYPE_RANDOM));

                DrawSprite (row_pointers, X * MINI_ARENA_TILE_SIZE, Y * MINI_ARENA_TILE_SIZE, 0, (Shadow ? 3 : 2), 1, 0); 
            }
        }
    }
    
    for (X = 0 ; X < ARENA_WIDTH ; X++)
    {
        for (Y = 0 ; Y < ARENA_HEIGHT ; Y++)
        {            
            // bomb movement blocks (arrows)
            int spriteNumberAction = -1;

            switch ( options.GetBlockType(X, Y) )
            {
                case BLOCKTYPE_MOVEBOMB_RIGHT:    spriteNumberAction = 4;   break;
                case BLOCKTYPE_MOVEBOMB_DOWN:     spriteNumberAction = 5;   break;
                case BLOCKTYPE_MOVEBOMB_LEFT:     spriteNumberAction = 6;   break;
                case BLOCKTYPE_MOVEBOMB_UP:       spriteNumberAction = 7;   break;
                default: break;
            }

            if ( spriteNumberAction != -1 ) 
            {
                DrawSprite (row_pointers, X * MINI_ARENA_TILE_SIZE, 
                                        Y * MINI_ARENA_TILE_SIZE, 
                                        0, 
                                        spriteNumberAction, 
                                        2, 
                                        0); 
            }
        }
    }

    // now the bombers
    for (X = 0 ; X < ARENA_WIDTH ; X++)
    {
        for (Y = 0 ; Y < ARENA_HEIGHT ; Y++)
        {            
            EBlockType BlockType = options.GetBlockType(X, Y);
            switch (BlockType)
            {
                case BLOCKTYPE_WHITEBOMBER : DrawSprite (row_pointers, X * MINI_ARENA_TILE_SIZE + TILE_POSITION_TO_BOMBER_POSITION, Y * MINI_ARENA_TILE_SIZE + TILE_POSITION_TO_BOMBER_POSITION, 1, 0, 1, 2); break;
                case BLOCKTYPE_BLACKBOMBER : DrawSprite (row_pointers, X * MINI_ARENA_TILE_SIZE + TILE_POSITION_TO_BOMBER_POSITION, Y * MINI_ARENA_TILE_SIZE + TILE_POSITION_TO_BOMBER_POSITION, 1, 1, 1, 2); break;
                case BLOCKTYPE_REDBOMBER   : DrawSprite (row_pointers, X * MINI_ARENA_TILE_SIZE + TILE_POSITION_TO_BOMBER_POSITION, Y * MINI_ARENA_TILE_SIZE + TILE_POSITION_TO_BOMBER_POSITION, 1, 2, 1, 2); break;
                case BLOCKTYPE_BLUEBOMBER  : DrawSprite (row_pointers, X * MINI_ARENA_TILE_SIZE + TILE_POSITION_TO_BOMBER_POSITION, Y * MINI_ARENA_TILE_SIZE + TILE_POSITION_TO_BOMBER_POSITION, 1, 3, 1, 2); break;
                case BLOCKTYPE_GREENBOMBER : DrawSprite (row_pointers, X * MINI_ARENA_TILE_SIZE + TILE_POSITION_TO_BOMBER_POSITION, Y * MINI_ARENA_TILE_SIZE + TILE_POSITION_TO_BOMBER_POSITION, 1, 4, 1, 2); break;
                default :                                                                                                                                                                                     break;
            }
        }
    }
    
    // set rows with image data
    png_set_rows(write_ptr, info_ptr, row_pointers);

    // initialise file pointer with libpng
    png_set_write_fn(write_ptr, fp, user_write_data, user_flush_data);
    
    png_write_info(write_ptr, info_ptr);
    png_write_image(write_ptr, row_pointers);    // write image
    png_write_end(write_ptr, info_ptr);
    
    // free rows
    free(row_pointers[0]);
    free(row_pointers);
    
    // finish & clean up
    //png_write_end(write_ptr, info_ptr);
    png_destroy_write_struct(&write_ptr, &info_ptr);

    fclose(fp);
    return true;
}

/**
 * @brief   print usage of this tool and exit
 * @param   argv0   first argument of the program (from main)
 */
void printUsage(const char *argv0)
{
    cout << "Usage: " << argv0 << " <FILE> [<OUT>]" << endl;
    cout << "Generates a thumbnail as a bitmap in OUT of the level FILE" <<endl;
    cout << "If OUT is omitted, the file extension of FILE will be replaced to \"png\"." << endl;
    cout << "  -h, --help\t\tShow this screen\n";
    exit(0);
}

/**
 * @brief   main function
 * @param   argc    argument count
 * @param   argv    arguments
 * @return  0 (success) or -1 (failure)
 */
int main (int argc, const char **argv)
{
    const char *levelFileName;
    char *outFileName;
    COptions options;
    
    // correct parameters?
    if (argc < 2 ||
        strncmp(argv[1], "-h", 2) == 0 || strncmp(argv[1], "--help", 6) == 0)
        printUsage(argv[0]);

    levelFileName = argv[1];
    
    // check file extension
    if (strlen(levelFileName) < 4)
    {
        cout << "The filename " << levelFileName << " is not a valid filename. "
             << "The extension .TXT is expected." << endl;
        return 0;
    }
    
    if (argc < 3)
    {
        // build file name
        const char *dotpos = strrchr(levelFileName, '.');
        if (dotpos == NULL)
        {
            // this file does not have a extension
            outFileName = new char[strlen(levelFileName) + 5];
            if (outFileName == NULL) return 0;
            
            strncpy(outFileName, levelFileName, strlen(levelFileName));
            strcpy(outFileName + strlen(levelFileName), ".png");
        }
        else
        {
            unsigned int len = dotpos - levelFileName + 1;
            outFileName = new char[len + 4];
            if (outFileName == NULL) return 0;
            
            strncpy(outFileName, levelFileName, len);
            strcpy(outFileName + len, "png");
        }
    }
    else
    {
        outFileName = new char[strlen(argv[2])+1];
        if (outFileName == NULL) return 0;
        
        strcpy(outFileName, argv[2]);
    }

#ifdef WIN32
    // Load Library
    m_hModule = LoadLibrary ( NAME_OF_BOMBERMAN_DLL );
    
    // If it failed
    if (m_hModule == NULL)
    {
        cout << "Could not load " << NAME_OF_BOMBERMAN_DLL << endl;
        
        // Get out
        return 0;
    }
#endif
    
    // Load Sprites
    if (
#ifdef USE_32_PIXELS_PER_BLOCK
            !LoadSprites (8,      1,      16,     16,     true,     BMP_LEVEL_MINI_TILES          ) ||
            !LoadSprites (5,      1,      24,     20,     true,     BMP_LEVEL_MINI_BOMBERS        )
#else
            !LoadSprites (8,      1,       8,      8,     true,     BMP_LEVEL_MINI_TILES          ) ||
            !LoadSprites (5,      1,      12,     10,     true,     BMP_LEVEL_MINI_BOMBERS        )
#endif
    )
    {
        cout << "Could not load sprites from library." << endl;
        delete[] outFileName;
#ifdef WIN32
        FreeLibrary (m_hModule);
#endif
        return 0;
    }
    
    // If it failed
    if (!options.LoadLevel(levelFileName))
    {
        cout << "Could not load level file " << levelFileName << "." << endl;
        delete[] outFileName;
#ifdef WIN32
        FreeLibrary (m_hModule);
#endif
        return 0;
    }
    
    if (!buildOutputImage(outFileName, options))
    {
        cout << "Could not write output image " << outFileName << "." << endl;
        delete[] outFileName;
#ifdef WIN32
        FreeLibrary (m_hModule);
#endif
        return 0;
    }
    
    delete[] outFileName;

    for (unsigned int i = 0; i < m_Surfaces.size(); i++)
    {
        delete m_Surfaces[i].BitmapInfo;
    }
#ifdef WIN32
    FreeLibrary (m_hModule);
#endif
    return 1;
}
