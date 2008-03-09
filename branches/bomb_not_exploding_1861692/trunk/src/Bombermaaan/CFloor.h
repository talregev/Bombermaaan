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


//////////////
// CFloor.h

#ifndef __CFLOOR_H__
#define __CFLOOR_H__

#include "CElement.h"

class CArena;
class CDisplay;
class CArenaSnapshot;

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

//! An element in the arena which represents a bomb.
class CFloor : public CElement
{
private:

    int             m_iX;                               //!< Integer position X (in pixels) in the arena
    int             m_iY;                               //!< Integer position Y (in pixels) in the arena
    int             m_BlockX;                           //!< Position X (in blocks) in the arena grid
    int             m_BlockY;                           //!< Position Y (in blocks) in the arena grid
    bool            m_Dead;                             //!< Should the floor be deleted by the arena?
                                                        
public:                                                 
                                                        
                    CFloor (void);                      //!< Constructor. Initialize the base class.
    virtual         ~CFloor (void);                     //!< Destructor. Uninitialize the base class.
    void            Create (int BlockX, int BlockY);    //!< Initialize the floor.
    void            Destroy (void);                     //!< Uninitialize the floor.
    bool            Update (float DeltaTime);           //!< Update the element. Return whether the element should be deleted by the arena.
    void            Display (void);                     //!< Display the floor.
    void            OnWriteSnapshot (CArenaSnapshot& Snapshot);
    void            OnReadSnapshot (CArenaSnapshot& Snapshot);
    void            Crush (void);                       //!< Make the floor react when the floor is crushed by a wall.
    inline int      GetBlockX (void);                   //!< Return the block position X of the floor
    inline int      GetBlockY (void);                   //!< Return the block position Y of the floor
};

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

inline int CFloor::GetBlockX (void) 
{ 
    return m_BlockX; 
}

inline int CFloor::GetBlockY (void) 
{ 
    return m_BlockY;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#endif
