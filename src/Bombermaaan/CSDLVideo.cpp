/************************************************************************************

    Copyright (C) 2000-2002, 2007 Thibaut Tollemer
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

///////////////////
// CSDLVideo.cpp

#include "STDAFX.H"
#include "CSDLVideo.h"
#include "BombermaaanIco.h"

static const char* GetSDLVideoError (HRESULT hRet);
static void AddDisplayMode (int width, int height, int depth, LPVOID lpContext);

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

CSDLVideo::CSDLVideo (void)
{
    m_hWnd = NULL;
//    m_pDD = NULL;
    m_pBackBuffer = NULL;
    m_pPrimary = NULL;
    m_Width = 0;
    m_Height = 0;
    m_Depth = 0;
    m_FullScreen = false;
    m_ColorKey = 0;
    m_OriginX = 0;
    m_OriginY = 0;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

CSDLVideo::~CSDLVideo (void)
{
    // Nothing to do
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

static void AddDisplayMode (int width, int height, int depth, LPVOID lpContext)
{
    // The DirectInput device that will be created
    vector<SDisplayMode>* pDisplayModes = (vector<SDisplayMode>*)lpContext;
    
    SDisplayMode DisplayMode;
    DisplayMode.Width = width;
    DisplayMode.Height = height;
    DisplayMode.Depth = depth;

    pDisplayModes->push_back(DisplayMode);

    return;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool CSDLVideo::Create (int Width, int Height, int Depth, bool FullScreen)
{
    // Set the display properties
    m_Width = Width;
    m_Height = Height;
    m_Depth = Depth;
    m_FullScreen = FullScreen;

    //m_pDD = NULL;
    m_pBackBuffer = NULL;
    m_pPrimary = NULL;
    m_ColorKey = 0;

    SDL_Rect **modes;
    
    int i;
    bool validMode = false; // is this video mode valid?

    // Enumerate all display modes (without taking refresh rates into account)
    if (!m_FullScreen) {
		modes = SDL_ListModes(NULL, SDL_HWSURFACE|SDL_DOUBLEBUF);
	}
	else {
		modes = SDL_ListModes(NULL, SDL_HWSURFACE|SDL_DOUBLEBUF);
	}
    
    // some mode available?
	if (modes == (SDL_Rect **)0) {
		// Log failure
        theLog.WriteLine ("SDLVideo      => !!! Could not find any video modes.");

        // Get out
        return false;
    }
    else if (modes == (SDL_Rect **)-1) {
		// Log success
        theLog.WriteLine ("SDLVideo      => All modes available");
        
        // so, add 240x234 (window), 320 x 240, 512 x 384, 640 x 480 in 16 bits
        AddDisplayMode(240, 234, 16, (LPVOID *)&m_AvailableDisplayModes);
        AddDisplayMode(320, 240, 16, (LPVOID *)&m_AvailableDisplayModes);
        AddDisplayMode(512, 384, 16, (LPVOID *)&m_AvailableDisplayModes);
        AddDisplayMode(640, 480, 16, (LPVOID *)&m_AvailableDisplayModes);
        
		// so this mode is possible
		validMode = true;
	}
	else {
		// enumerate modes and add certain
        for (i = 0; modes[i]; ++i) {
			if ((modes[i]->w == 240 && modes[i]->h == 234) ||
				(modes[i]->w == 320 && modes[i]->h == 240) ||
				(modes[i]->w == 512 && modes[i]->h == 384) ||
				(modes[i]->w == 640 && modes[i]->h == 480)) {
				AddDisplayMode(modes[i]->w, modes[i]->h, 16,
					(LPVOID *)&m_AvailableDisplayModes);
				
				// is our requested mode possbile?
				if (modes[i]->w == m_Width && modes[i]->h == m_Height) {
						validMode = true;
				}
			}
		}
			
	}
		
	if (!validMode) {
		// Log failure
        theLog.WriteLine ("SDLVideo      => !!! Requested video mode %dx%d not found.", m_Width, m_Height);

        // Get out
        return false;
    }
    
    // If desired mode is windowed mode
    if (!m_FullScreen)
    {
        // Log that windowed mode is being initialized
        theLog.WriteLine ("SDLVideo      => Initializing SDLVideo interface for windowed mode %dx%d.", m_Width, m_Height);

        // Get normal windowed mode
        m_pPrimary = SDL_SetVideoMode(m_Width, m_Height, m_Depth, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
        
        if (m_pPrimary == NULL) {
			// Log failure
		    theLog.WriteLine ("SDLVideo      => !!! Requested video mode could not be set. (primary surface)");
		
		    // Get out
		    return false;
		}
		    
		// create primary and back buffer surface

		// Create the primary surface
		/* Uint32 rmask, gmask, bmask, amask;
			
		// SDL interprets each pixel as a 32-bit number, so our masks must depend
		// on the endianness (byte order) of the machine
		#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			rmask = 0xff000000;
			gmask = 0x00ff0000;
			bmask = 0x0000ff00;
			amask = 0x000000ff;
		#else
			rmask = 0x000000ff;
			gmask = 0x0000ff00;
			bmask = 0x00ff0000;
			amask = 0xff000000;
		#endif
		
		// Get the backbuffer
		m_pBackBuffer = SDL_CreateRGBSurface(SDL_HWSURFACE, m_Width, m_Height,
				m_Depth, rmask, gmask, bmask, amask);
	
		// If it failed
		if (m_pBackBuffer == NULL)
		{
			// Log failure
			theLog.WriteLine ("SDLVideo      => !!! Could not create backbuffer surface.");
			theLog.WriteLine ("SDLVideo      => !!! SDLVideo error is : %s.", GetSDLVideoError(hRet));
	
			// Get out
			return false;
		}
		// If it was successful
		else
		{
			// Log success
			theLog.WriteLine ("SDLVideo      => Backbuffer surface was created.");
		}*/
	}
    // If desired mode is a fullscreen mode
    else
    {
        // Log that fullscreen mode is being initialized
        theLog.WriteLine ("SDLVideo      => Initializing SDLVideo interface for fullscreen mode %dx%dx%d.", m_Width, m_Height, m_Depth);
         
        // Get fullscreen mode
        m_pPrimary = SDL_SetVideoMode(m_Width, m_Height, m_Depth, SDL_HWSURFACE|SDL_FULLSCREEN|SDL_DOUBLEBUF);
        
        if (m_pPrimary == NULL) {
			// Log failure
		    theLog.WriteLine ("SDLVideo      => !!! Requested video mode could not be set. (primary/backbuffer)");
		
		    // Get out
		    return false;
		}
	}
					
    // Get the rects of the viewport and screen bounds
    m_rcViewport.x = 0;
    m_rcViewport.y = 0;

    m_rcViewport.w = m_Width;
    m_rcViewport.h = m_Height;
    
    memcpy (&m_rcScreen, &m_rcViewport, sizeof (SDL_Rect));
    
    // show cursor depending on windowed/fullscreen mode
    SDL_ShowCursor (!m_FullScreen);
	
	SDL_RWops *rwIcon = SDL_RWFromMem(BombermaaanIcon, sizeof(BombermaaanIcon));
    
    SDL_Surface *icon = SDL_LoadBMP_RW(rwIcon, 0);
    
	if (icon != NULL) {
		if (SDL_SetColorKey(icon, SDL_SRCCOLORKEY, SDL_MapRGB(icon->format,
			0x00, 0xff, 0x00)) == 0) {
			SDL_WM_SetIcon(icon, NULL);
		}
	}
	else {
		printf ("could not load icon.\n");
	}
	
	SDL_FreeSurface(icon);
					
    // Clear the back buffer surface
    Clear ();

    // Reset origin
    m_OriginX = 0;
    m_OriginY = 0;

    // Everything went right
    return true;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Destroys the SDLVideo interface

void CSDLVideo::Destroy (void)
{
    // Free drawing requests, sprite tables, surfaces...
    FreeSprites ();

    // If a SDLVideo object exists
    if (m_pPrimary != NULL)
    {
        // If we are in fullscreen mode
        if (m_FullScreen)
        {
            // Show the cursor because we are in windowed mode
            SDL_ShowCursor (true);
        }
        
        // If the back buffer surface exists
        if (m_pBackBuffer != NULL)
        {
            // Release it
            SDL_FreeSurface(m_pBackBuffer);
            m_pBackBuffer = NULL;

            // Log release
            theLog.WriteLine ("SDLVideo      => Backbuffer surface was released.");
        }
        
        // If the primary surface exists
        if (m_pPrimary != NULL)
        {
            // Release it
            SDL_FreeSurface(m_pPrimary);
            m_pPrimary = NULL;

            // Log release
            theLog.WriteLine ("SDLVideo      => Primary surface was released.");
        }
    
        // Log release
        theLog.WriteLine ("SDLVideo      => SDLVideo object was released.");
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Updates the display by blitting the back buffer
// surface on the primary surface.

void CSDLVideo::UpdateScreen (void)
{
    HRESULT hRet;

    while (true)
    {
        // If we are in windowed mode
        if (!m_FullScreen)
        {
            // Update the primary surface with by blitting the backbuffer on the primary surface
            //hRet = SDL_BlitSurface(m_pBackBuffer, &m_rcViewport, m_pPrimary, &m_rcScreen);
            //hRet = SDL_BlitSurface(m_pBackBuffer, NULL, m_pPrimary, NULL);
            hRet = SDL_Flip(m_pPrimary);
        }
        // If we are in fullscreen mode
        else
        {
            // Update the primary surface by flipping backbuffer and primary surface
            hRet = SDL_Flip(m_pPrimary);
        }

		// If it worked fine
        if (hRet == 0)
        {
            // Get out
            break;
        }

        // Log failure
        if (hRet != 0) {
	        theLog.WriteLine ("SDLVideo      => !!! Updating failed (switching primary/backbuffer).");
	        theLog.WriteLine ("SDLVideo      => !!! SDLVideo error is : %s.", GetSDLVideoError(hRet));
        }
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Updates the object : this updates the drawing zones
// in case the window moves.

void CSDLVideo::OnWindowMove ()
{
    // Update the window rect that is used when updating the screen
    /* GetClientRect (m_hWnd, &m_rcViewport);
    GetClientRect (m_hWnd, &m_rcScreen);
    ClientToScreen (m_hWnd, (POINT*)&m_rcScreen.left);
    ClientToScreen (m_hWnd, (POINT*)&m_rcScreen.right); */
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CSDLVideo::DrawSprite (int PositionX, 
                              int PositionY, 
                              RECT *pZone,
                              RECT *pClip,
                              int SpriteTable, 
                              int Sprite, 
                              int SpriteLayer, 
                              int PriorityInLayer)
{
    // Check if the parameters are valid
    ASSERT (SpriteTable >= 0 && SpriteTable < (int)m_SpriteTables.size());
    ASSERT (Sprite >= 0 && Sprite < (int)m_SpriteTables[SpriteTable].size());
        
    // Prepare a drawing request
    SDrawingRequest DrawingRequest;

    // Save the sprite pointer
    SSprite *pSprite = &m_SpriteTables[SpriteTable][Sprite];

    // If we have to take care of clipping
    if (pClip != NULL)
    {
        // Save the sprite size
        int SpriteSizeX = pSprite->ZoneX2 - pSprite->ZoneX1;
        int SpriteSizeY = pSprite->ZoneY2 - pSprite->ZoneY1;

        // If the sprite is completely out of the clip rect
        if (PositionX >= pClip->right || 
            PositionY >= pClip->bottom ||
            PositionX + SpriteSizeX < pClip->left ||
            PositionY + SpriteSizeY < pClip->top)
        {
            // Get out, don't even register the drawing request
            return;
        }
        
        // If the sprite has to be clipped on the left
        if (PositionX < pClip->left)
        {
            // Clip on the left
            DrawingRequest.PositionX = pClip->left;
            DrawingRequest.ZoneX1 = pSprite->ZoneX1 + pClip->left - PositionX;
        }
        // If no clip on the left is needed
        else
        {
            // Don't clip
            DrawingRequest.PositionX = PositionX;
            DrawingRequest.ZoneX1 = pSprite->ZoneX1;
        }

        // If the sprite has to be clipped on the top
        if (PositionY < pClip->top)
        {
            // Clip on the top
            DrawingRequest.PositionY = pClip->top;
            DrawingRequest.ZoneY1 = pSprite->ZoneY1 + pClip->top - PositionY;
        }
        // If no clip on the top is needed
        else
        {
            // Don't clip
            DrawingRequest.PositionY = PositionY;
            DrawingRequest.ZoneY1 = pSprite->ZoneY1;
        }

        // If the sprite has to be clipped on the right
        if (PositionX + SpriteSizeX >= pClip->right)
        {
            // Clip on the right
            DrawingRequest.ZoneX2 = pSprite->ZoneX1 + pClip->right - PositionX;
        }
        // If no clip on the right is needed
        else
        {
            // Don't clip
            DrawingRequest.ZoneX2 = pSprite->ZoneX2;
        }
    
        // If the sprite has to be clipped on the bottom
        if (PositionY + SpriteSizeY >= pClip->bottom)
        {
            // Clip on the bottom
            DrawingRequest.ZoneY2 = pSprite->ZoneY1 + pClip->bottom - PositionY;
        }
        // If no clip on the bottom is needed
        else
        {
            // Don't clip
            DrawingRequest.ZoneY2 = pSprite->ZoneY2;
        }
    }
    // If we don't have to care about clipping
    else
    {
        // Use the desired position
        DrawingRequest.PositionX = PositionX;
        DrawingRequest.PositionY = PositionY;
        
        // Use the zone of the sprite
        DrawingRequest.ZoneX1 = pSprite->ZoneX1;
        DrawingRequest.ZoneY1 = pSprite->ZoneY1;
        DrawingRequest.ZoneX2 = pSprite->ZoneX2;
        DrawingRequest.ZoneY2 = pSprite->ZoneY2;
    }

    // Finish preparing the drawing request
    DrawingRequest.PositionX += m_OriginX;
    DrawingRequest.PositionY += m_OriginY;
    DrawingRequest.SpriteTable = SpriteTable;
    DrawingRequest.Sprite = Sprite;
    DrawingRequest.SpriteLayer = SpriteLayer;
    DrawingRequest.PriorityInLayer = PriorityInLayer;
    
    // Store it (automatic sort)
    m_DrawingRequests.push(DrawingRequest);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Makes the display black.

void CSDLVideo::Clear ()
{
	HRESULT hRet;
    /* DDBLTFX blt = { 0 };
    blt.dwSize = sizeof (blt);
    blt.dwFillColor = 0;
    m_pBackBuffer->Blt (NULL, 0, 0, DDBLT_COLORFILL | DDBLT_WAIT, &blt); */
    hRet = SDL_FillRect(m_pPrimary, &m_rcViewport, 0);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

WORD CSDLVideo::GetNumberOfBits (DWORD dwMask)
{
    WORD wBits = 0;
    while (dwMask)
    {
        dwMask = dwMask & (dwMask - 1);  
        wBits++;
    }
    return wBits;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool CSDLVideo::SetTransparentColor (int Red, int Green, int Blue)
{
    // Get the pixel format of the primary surface
    SDL_PixelFormat *pf = m_pPrimary->format;

    // Compute how many bits for each RGB color component in a pixel data
    /* WORD wRBitCount = GetNumberOfBits (pf->Rmask);
    WORD wGBitCount = GetNumberOfBits (pf->Gmask);
    WORD wBBitCount = GetNumberOfBits (pf->Bmask);
	
	printf("numbers of bits: %d %d %d\n", wRBitCount, wGBitCount, wBBitCount);

    // Compute RGB color components to use for the color key 
    // according to transparency color RGB components
    DWORD r = (Red >> (8 - wRBitCount)) << (wGBitCount + wBBitCount);
    DWORD g = (Green >> (8 - wGBitCount)) << wBBitCount;
    DWORD b = (Blue >> (8 - wBBitCount));

    // Compute the color key to apply to the surface
    m_ColorKey = (r | g | b); */
	
	m_ColorKey = SDL_MapRGB(pf, Red, Green, Blue);

    // Everything went right
    return true;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool CSDLVideo::LoadSprites (int SpriteTableWidth, 
                             int SpriteTableHeight, 
                             int SpriteWidth, 
                             int SpriteHeight, 
                             bool Transparent, 
                             HBITMAP hBitmap)
{
    HRESULT hRet = 0;
    SDL_RWops *rwBitmap;

    LPVOID pData;
    DWORD DataSize;

    // Prepare a new surface from the BMP
    DataSize = GetObject (hBitmap, 0, &pData);
    if (DataSize == 0)
    {
        // Log failure
        theLog.WriteLine ("SDLVideo      => !!! Could not get the bitmap's (res id: %d) attributes.", hBitmap);
        theLog.LogLastError ();

        // Get out
        return false;
    }

    SSurface Surface;

    // Create a SDLVideo surface for this bitmap
    SDL_Surface *ddsd;
	
    rwBitmap = SDL_RWFromMem(pData, DataSize);
    
	ddsd = SDL_LoadBMP_RW(rwBitmap, 0);
	
    // If it failed
    if (ddsd == NULL)
    {
        // Log failure
        theLog.WriteLine ("SDLVideo      => !!! Could not create surface.");
        theLog.WriteLine ("SDLVideo      => !!! SDLVideo error is : %s.", GetSDLVideoError(hRet));

        // Get out
        return false;
    }

	/*
     * Palettized screen modes will have a default palette (a standard
     * 8*8*4 colour cube), but if the image is palettized as well we can
     * use that palette for a nicer colour matching
     */
    /* if (ddsd->format->palette && m_pPrimary->format->palette) {
    	SDL_SetColors(m_pPrimary, ddsd->format->palette->colors, 0,
                  ddsd->format->palette->ncolors);
    } */
	
	
    // Blit the bitmap onto the SDLVideo surface
	Surface.pSurface = ddsd;

    // If it fails
    /*if (SDL_BlitSurface(ddsd, NULL, Surface.pSurface, NULL) < 0)
    {
        // Log failure
        theLog.WriteLine ("SDLVideo      => !!! Could not blit the bitmap to the SDLVideo surface.");
        theLog.LogLastError ();

        // Get out
        return false;
    }
	*/

    //----------------------------------------------
    // Set the surface transparency color if needed
    //----------------------------------------------

    // If the sprite table uses transparency
    if (Transparent)
    {
        // Set parameter to use when blitting the surface : use transparency
        //Surface.BlitParameters = DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY;

        // Apply the color key to the surface
		hRet = SDL_SetColorKey(ddsd, SDL_SRCCOLORKEY,
			SDL_MapRGB(ddsd->format, 0x00, 0xff, 0x00));
		
        // If it failed
        if (hRet != 0)
        {
            // Log failure
            theLog.WriteLine ("SDLVideo      => !!! Could not set colorkey.");
            theLog.WriteLine ("SDLVideo      => !!! SDLVideo error is : %s.", GetSDLVideoError(hRet));

            // Get out
            return false;
        }
    }
    else
    {
        // Set parameter to use when blitting the surface : no transparency
        //Surface.BlitParameters = DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY;
    }


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

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CSDLVideo::FreeSprites (void)
{
    // Empty drawing requests queue
    while (!m_DrawingRequests.empty())
        m_DrawingRequests.pop();        

    // Remove all sprite tables
    m_SpriteTables.clear();
    
    // Scan all the surfaces
    for (unsigned int i = 0 ; i < m_Surfaces.size() ; i++)
    {
        // If the surface exists
        if (m_Surfaces[i].pSurface != NULL)
        {
            // Release it
            SDL_FreeSurface(m_Surfaces[i].pSurface);
            m_Surfaces[i].pSurface = NULL;
        }
    }

    // Remove all surfaces
    m_Surfaces.clear();
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CSDLVideo::UpdateAll (void)
{
    // While all the drawing requests have not been executed
    while (!m_DrawingRequests.empty())
    {   
        // Save the top drawing request
        const SDrawingRequest &DR = m_DrawingRequests.top();

        // Save the sprite as specified by this drawing request
        const SSprite *pSprite = &m_SpriteTables[DR.SpriteTable][DR.Sprite];

        // Build a RECT structure containing the zone to draw
        SDL_Rect SourceRect;
        SourceRect.x = DR.ZoneX1;
        SourceRect.y = DR.ZoneY1;
        SourceRect.w = DR.ZoneX2 - DR.ZoneX1;
        SourceRect.h = DR.ZoneY2 - DR.ZoneY1;
		
		SDL_Rect DestRect;
		DestRect.x = DR.PositionX;
		DestRect.y = DR.PositionY;
		DestRect.w = 0;
		DestRect.h = 0;

        // Blit the surface zone on the back buffer
		if (SDL_BlitSurface(m_Surfaces[pSprite->SurfaceNumber].pSurface,
			&SourceRect, m_pPrimary, &DestRect) < 0) {
			// blitting failed
		}
			
        // Pop the drawing request to go to the next
        m_DrawingRequests.pop();
    }

    UpdateScreen ();
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool CSDLVideo::IsModeAvailable (int Width, int Height, int Depth)
{
    // Scan all available display modes
    for (unsigned int i = 0 ; i < m_AvailableDisplayModes.size() ; i++)
    {
        // If this is the display mode we are looking for
        if (m_AvailableDisplayModes[i].Width == Width &&
            m_AvailableDisplayModes[i].Height == Height &&
            m_AvailableDisplayModes[i].Depth == Depth)
        {
            // Then it's available
            return true;
        }
    }

    // The display mode was not found so it's not available
    return false;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

static const char* GetSDLVideoError (HRESULT hRet)
{
    return SDL_GetError();
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************
