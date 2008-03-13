/************************************************************************************

    Copyright (C) 2000-2002, 2007 Thibaut Tollemer

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


///////////////////////
// CDisplay.h

#ifndef __CDISPLAY_H__
#define __CDISPLAY_H__

#include "CDirectDraw.h"

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

enum EDisplayMode
{
    DISPLAYMODE_NONE,
    DISPLAYMODE_FULL1,
    DISPLAYMODE_FULL2,
    DISPLAYMODE_FULL3,
    DISPLAYMODE_WINDOWED
};

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

class CDisplay
{
private:

    HMODULE         m_hModule;          //!< Connection to the resources
    CDirectDraw     m_DirectDraw;       //!< Object used for display
    int             m_ViewOriginX;      //!< Top left corner of the game view
    int             m_ViewOriginY;
    
    bool            Create (int Width, int Height, bool FullScreen); //!< (Re)Create the DirectDraw interface and (re)load the sprite tables given the resolution
    bool            LoadSprites (int SpriteTableWidth, int SpriteTableHeight, int SpriteWidth, int SpriteHeight, bool Transparent, int BMP_ID); //!< Load a sprite table given its bitmap data and its properties.

public:

                    CDisplay (void);    //!< Initialize some members
                    ~CDisplay (void);   //!< Does nothing
    inline void     SetWindowHandle (HWND hWnd); //!< Set the handle of the window DirectDraw has to work with
    inline void     SetModuleHandle (HMODULE hModule); //!< Set the handle of the module linked to the resources
    bool            Create (EDisplayMode DisplayMode); //!< (Re)Create the DirectDraw interface and (re)load the sprite tables given the display mode
    void            Destroy (void);     //!< Destroy the DirectDraw interface and the sprite tables
    inline void     OnWindowMove (void); //!< Has to be called when the window moves (WM_MOVE)
    inline void     OnPaint (void);     //!< Has to be called when the window has to be repainted (WM_PAINT)
    inline void     Clear (void);       //!< Make the window's client area black
    inline void     Update (void);      //!< Draw the sprites that DrawSprite recorded and update the window's client area
    inline void     SetOrigin (int OriginX, int OriginY); //!< Set the origin to draw from the game view origin
    inline void     DrawSprite (int PositionX, int PositionY, RECT *pZone, RECT *pClip, int SpriteTable, int Sprite, int SpriteLayer, int PriorityInLayer); //!< Record a drawing request that will be executed on next call to Update
    bool            IsDisplayModeAvailable (EDisplayMode DisplayMode);
};

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

inline void CDisplay::SetWindowHandle (HWND hWnd)
{
    m_DirectDraw.SetWindowHandle (hWnd);
}

inline void CDisplay::SetModuleHandle (HMODULE hModule)
{
    m_hModule = hModule;
}

inline void CDisplay::SetOrigin (int OriginX, int OriginY)
{
    m_DirectDraw.SetOrigin (m_ViewOriginX + OriginX, m_ViewOriginY + OriginY);
}

inline void CDisplay::Clear (void)
{
    m_DirectDraw.Clear ();
}

inline void CDisplay::Update (void)
{
    m_DirectDraw.UpdateAll ();
}

inline void CDisplay::OnWindowMove (void)
{
    m_DirectDraw.OnWindowMove ();
}

inline void CDisplay::OnPaint (void)
{
    //! @see CDirectDraw::UpdateScreen()
    m_DirectDraw.UpdateScreen ();
}

inline void CDisplay::DrawSprite (int PositionX, int PositionY, RECT *pZone, RECT *pClip, int SpriteTable, int Sprite, int SpriteLayer, int PriorityInLayer)
{
    m_DirectDraw.DrawSprite (PositionX, PositionY, pZone, pClip, SpriteTable, Sprite, SpriteLayer, PriorityInLayer);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#endif // __CDISPLAY_H__
