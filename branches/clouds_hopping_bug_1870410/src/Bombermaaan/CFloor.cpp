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


////////////////
// CFloor.cpp

#include "stdafx.h"
#include "CFloor.h"         // CFloor
#include "CDisplay.h"   // CDisplay
#include "CArena.h"         // CArena and arena values
#include "CArenaSnapshot.h"

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Floor sprite layer
#define FLOOR_SPRITELAYER       0

// Floor sprites
#define FLOORSPRITE_NOSHADOW    0       // Floor with no shadow
#define FLOORSPRITE_SHADOW      1       // Floor with shadow

#define ARENA_FLOOR_SPRITETABLE             0

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

CFloor::CFloor (void) : CElement()
{
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

CFloor::~CFloor (void)
{
    
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CFloor::Create (int BlockX, int BlockY)
{
    CElement::Create();

    m_iX = m_pArena->ToPosition (BlockX);
    m_iY = m_pArena->ToPosition (BlockY);
    m_BlockX = BlockX;
    m_BlockY = BlockY;
    m_Dead = false;
}


//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CFloor::Destroy (void)
{
    CElement::Destroy();
}


//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool CFloor::Update (float /*DeltaTime*/)
{
    // The arena can destroy this floor if it is dead
    return m_Dead;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Draws a sprite (shadow or not) in the right
// layer in the arena

void CFloor::Display (void)
{
    // If there is no item and (no wall or a burning wall or a falling wall)
    if (!m_pArena->IsItem(m_BlockX,m_BlockY) &&
        (
         !m_pArena->IsWall(m_BlockX,m_BlockY) || 
         m_pArena->IsBurningWall(m_BlockX,m_BlockY) || 
         m_pArena->IsFallingWall(m_BlockX,m_BlockY)
        ))
    {

        // Try to determine if there is a shadow on this floor.
        // This is true if there is a non falling wall above.
        int Sprite;

        // If there can be a block above and if there is a wall above and it's not a falling wall
        if (m_BlockY - 1 >= 0 && 
            m_pArena->IsWall(m_BlockX,m_BlockY-1) && 
            !m_pArena->IsFallingWall(m_BlockX,m_BlockY-1))
        {
            // Then there is a shadow
            Sprite = FLOORSPRITE_SHADOW;
        }
        // No wall above or falling wall above
        else
        {
            // Then there is a no shadow
            Sprite = FLOORSPRITE_NOSHADOW;
        }

        // Add the sprite in the layer. Priority is not used.
        m_pDisplay->DrawSprite (m_iX, 
                                m_iY, 
                                NULL,                            // Draw entire sprite
                                NULL,                            // No need to clip
                                ARENA_FLOOR_SPRITETABLE, 
                                Sprite, 
                                FLOOR_SPRITELAYER,
                                PRIORITY_UNUSED);
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CFloor::OnWriteSnapshot (CArenaSnapshot& Snapshot)
{
    Snapshot.WriteInteger(m_iX);
    Snapshot.WriteInteger(m_iY);
    Snapshot.WriteInteger(m_BlockX);
    Snapshot.WriteInteger(m_BlockY);
    Snapshot.WriteBoolean(m_Dead);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//****************************************************************************************************************************

void CFloor::OnReadSnapshot (CArenaSnapshot& Snapshot)
{
    Snapshot.ReadInteger(&m_iX);
    Snapshot.ReadInteger(&m_iY);
    Snapshot.ReadInteger(&m_BlockX);
    Snapshot.ReadInteger(&m_BlockY);
    Snapshot.ReadBoolean(&m_Dead);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Called by hard walls crushing this floor. A hard wall "crushes" the floor
// where it is because the floor should be dead : it cannot be seen anymore.

void CFloor::Crush (void)
{
    m_Dead = true;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************
