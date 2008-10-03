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


/////////////////////////
// CMenuLevel.cpp

#include "STDAFX.H"
#include "CMenuLevel.h"
#include "CDisplay.h"
#include "CInput.h"
#include "COptions.h"
#include "CFont.h"
#include "CMenu.h"
#include "CSound.h"

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#define MENUMATCH_SPRITELAYER       1               //!< Sprite layer where to draw sprites
                                                    
#ifdef USE_32_PIXELS_PER_BLOCK
#define TITLE_TEXT_POSITION_Y       90              //!< Position Y of the title text that is centered on the X axis
#else
#define TITLE_TEXT_POSITION_Y       45              //!< Position Y of the title text that is centered on the X axis
#endif

#ifdef USE_32_PIXELS_PER_BLOCK
#define MINI_ARENA_POSITION_X   120
#define MINI_ARENA_POSITION_Y   (73+60)
#define TILE_POSITION_TO_BOMBER_POSITION    -4
#else
#define MINI_ARENA_POSITION_X   59
#define MINI_ARENA_POSITION_Y   73
#define TILE_POSITION_TO_BOMBER_POSITION    -2
#endif


//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

CMenuLevel::CMenuLevel (void) : CMenuBase ()
{
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

CMenuLevel::~CMenuLevel (void)
{
    // Nothing to do
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CMenuLevel::OnCreate (void)
{
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CMenuLevel::OnDestroy (void)
{
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CMenuLevel::OnUp (void)
{
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CMenuLevel::OnDown (void)
{
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CMenuLevel::OnLeft (void)
{
    // If the first level is selected
    if (m_pOptions->GetLevel() == 0)
    {
        // Select the last level
        m_pOptions->SetLevel (m_pOptions->GetNumberOfLevels() - 1);
    }
    // If the first level is not selected
    else
    {
        // Select the previous level
        m_pOptions->SetLevel (m_pOptions->GetLevel() - 1);
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CMenuLevel::OnRight (void)
{
    // If the last level is selected
    if (m_pOptions->GetLevel() == m_pOptions->GetNumberOfLevels() - 1)
    {
        // Select the first level
        m_pOptions->SetLevel (0);
    }
    // If the last level is not selected
    else
    {
        // Select the next level
        m_pOptions->SetLevel (m_pOptions->GetLevel() + 1);
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CMenuLevel::OnPrevious (void)
{
    // Go to the previous screen
    Exit (MENUACTION_PREVIOUS);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CMenuLevel::OnNext (void)
{
    // Play the menu next sound
    m_pSound->PlaySample (SAMPLE_MENU_NEXT);

    // Go to the next screen
    Exit (MENUACTION_NEXT);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CMenuLevel::OnUpdate (void)
{ 
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CMenuLevel::OnDisplay (void)
{
#ifdef USE_32_PIXELS_PER_BLOCK
    int factor = 16;
#else
    int factor = 8;
#endif
    
    // Set the right font text color and write the menu title string
    m_pFont->SetTextColor (FONTCOLOR_WHITE);
    m_pFont->DrawCenteredX (0, VIEW_WIDTH - 1, TITLE_TEXT_POSITION_Y, m_pOptions->GetLevelName()); 

    // Scan all the blocks of the arena
    for (int X = 0 ; X < ARENA_WIDTH ; X++)
    {
        for (int Y = 0 ; Y < ARENA_HEIGHT ; Y++)
        {            
            EBlockType BlockType = m_pOptions->GetBlockType(X, Y);
            
            if (BlockType == BLOCKTYPE_HARDWALL)
            {    
                m_pDisplay->DrawSprite (MINI_ARENA_POSITION_X + X * factor, 
                                        MINI_ARENA_POSITION_Y + Y * factor, 
                                        NULL, 
                                        NULL, 
                                        56, 
                                        0, 
                                        1, 
                                        1);                     
            }
            else if (BlockType == BLOCKTYPE_RANDOM)
            {
                m_pDisplay->DrawSprite (MINI_ARENA_POSITION_X + X * factor, 
                                        MINI_ARENA_POSITION_Y + Y * factor, 
                                        NULL, 
                                        NULL, 
                                        56, 
                                        1, 
                                        1, 
                                        1);
            }
            else
            {
                bool Shadow = (Y - 1 >= 0 && 
                               (m_pOptions->GetBlockType(X, Y - 1) == BLOCKTYPE_HARDWALL ||
                                m_pOptions->GetBlockType(X, Y - 1) == BLOCKTYPE_RANDOM));

                m_pDisplay->DrawSprite (MINI_ARENA_POSITION_X + X * factor, 
                                        MINI_ARENA_POSITION_Y + Y * factor, 
                                        NULL, 
                                        NULL, 
                                        56, 
                                        (Shadow ? 3 : 2), 
                                        1, 
                                        0); 
                
                switch (BlockType)
                {
                    case BLOCKTYPE_WHITEBOMBER : m_pDisplay->DrawSprite (MINI_ARENA_POSITION_X + X * factor + TILE_POSITION_TO_BOMBER_POSITION, MINI_ARENA_POSITION_Y + Y * factor + TILE_POSITION_TO_BOMBER_POSITION, NULL, NULL, 57, 0, 1, 2); break;
                    case BLOCKTYPE_BLACKBOMBER : m_pDisplay->DrawSprite (MINI_ARENA_POSITION_X + X * factor + TILE_POSITION_TO_BOMBER_POSITION, MINI_ARENA_POSITION_Y + Y * factor + TILE_POSITION_TO_BOMBER_POSITION, NULL, NULL, 57, 1, 1, 2); break;
                    case BLOCKTYPE_REDBOMBER   : m_pDisplay->DrawSprite (MINI_ARENA_POSITION_X + X * factor + TILE_POSITION_TO_BOMBER_POSITION, MINI_ARENA_POSITION_Y + Y * factor + TILE_POSITION_TO_BOMBER_POSITION, NULL, NULL, 57, 2, 1, 2); break;
                    case BLOCKTYPE_BLUEBOMBER  : m_pDisplay->DrawSprite (MINI_ARENA_POSITION_X + X * factor + TILE_POSITION_TO_BOMBER_POSITION, MINI_ARENA_POSITION_Y + Y * factor + TILE_POSITION_TO_BOMBER_POSITION, NULL, NULL, 57, 3, 1, 2); break;
                    case BLOCKTYPE_GREENBOMBER : m_pDisplay->DrawSprite (MINI_ARENA_POSITION_X + X * factor + TILE_POSITION_TO_BOMBER_POSITION, MINI_ARENA_POSITION_Y + Y * factor + TILE_POSITION_TO_BOMBER_POSITION, NULL, NULL, 57, 4, 1, 2); break;
                    default :                                                                                                                                                                                                                    break;
                }
            }
        }
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************
