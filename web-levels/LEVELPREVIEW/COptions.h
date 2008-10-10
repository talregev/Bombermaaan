/************************************************************************************

    Copyright (C) 2000-2002, 2007 Thibaut Tollemer
    Copyright (C) 2007, 2008 Bernd Arnold
	Copyright (C) 2008 Jerome Bigot
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


//////////////////////
// COptions.h
// This COptions class is reduced for the LevelPreview

#ifndef __COPTIONS_H__
#define __COPTIONS_H__

#include "STDAFX.H"

#include <iostream>
#include <fstream>
#include <sstream>
#include "../third-party/simpleini/SimpleIni.h"

using namespace std;

// from CArena.h
#define MAX_ITEMS       50

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// taken from CItem.h
enum EItemType
{
    ITEM_NONE,
    ITEM_BOMB,      //!< Bomb item allows a bomber to drop more bombs
    ITEM_FLAME,     //!< Flame item allows a bomber to drop more powerful bombs
    ITEM_KICK,      //!< Kick item allows a bomber to kick bombs
    ITEM_ROLLER,    //!< Roller item allows a bomber to walk faster
    ITEM_SKULL,     //!< Skull item gives a bomber a sickness.
    ITEM_THROW,     //!< Throw glove item allows a bomber to throw bombs
    ITEM_PUNCH,     //!< Boxing glove item allows a bomber to punch bombs
	ITEM_REMOTE,    //!< Remote bombs item allows a bomber to remotely control bomb fuse
    NUMBER_OF_ITEMS
};

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

enum EBlockType
{
    BLOCKTYPE_HARDWALL,     //!< There must be a hard wall here
    BLOCKTYPE_RANDOM,       //!< There must be either a soft wall, or a free place here (random)
    BLOCKTYPE_FREE,         //!< There must be a free place here 
    BLOCKTYPE_WHITEBOMBER,  //!< The white bomber must start here
    BLOCKTYPE_BLACKBOMBER,  //!< The black bomber must start here
    BLOCKTYPE_REDBOMBER,    //!< The red bomber must start here
    BLOCKTYPE_BLUEBOMBER,   //!< The blue bomber must start here
    BLOCKTYPE_GREENBOMBER,  //!< The green bomber must start here
    BLOCKTYPE_MOVEBOMB_RIGHT,   //!< A bomb starts moving right if placed here
    BLOCKTYPE_MOVEBOMB_DOWN,    //!< A bomb starts moving down if placed here
    BLOCKTYPE_MOVEBOMB_LEFT,    //!< A bomb starts moving left if placed here
    BLOCKTYPE_MOVEBOMB_UP       //!< A bomb starts moving up if placed here
};

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

enum EBomberSkills
{
	BOMBERSKILL_DUMMYFIRST,
    BOMBERSKILL_FLAME,
	BOMBERSKILL_BOMBS,
	BOMBERSKILL_BOMBITEMS,
	BOMBERSKILL_FLAMEITEMS,
	BOMBERSKILL_ROLLERITEMS,
	BOMBERSKILL_KICKITEMS,
	BOMBERSKILL_THROWITEMS,
	BOMBERSKILL_PUNCHITEMS,
	BOMBERSKILL_REMOTEITEMS,
	NUMBER_OF_BOMBERSKILLS
};

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

//! Contains every option in the game and manages the configuration file
class COptions
{
private:

    EBlockType***       m_LevelsData;
	int**				m_NumberOfItemsInWalls;
	int**				m_InitialBomberSkills;
    void                AllocateLevels (int NumberOfLevels); //!< Allocate data and names for the specified number of levels. Warning : does not allocate the names strings (just the array of string pointers).
    bool                LoadLevel_Version1( ifstream& File, int CurrentLevel ); //!< Load level file version 1
    bool                LoadLevel_Version2( const char *fileName, int CurrentLevel, bool requireRemoteFuse = false ); //!< Load level file version 2 (requiredRemoteFuse = false) or 3 (requiredRemoteFuse = true)
    bool                CheckMaxNumberOfItems( int Level, unsigned int *sumOfMaxItems ); //!< Check if number of max items is valid
                        
public:                 
                        
                        COptions (void);                //!< Constructor.
                        ~COptions (void);               //!< Destructor. Do nothing.
    void                Destroy(void);                  //!< Destroy class
    inline EBlockType   GetBlockType (int X, int Y);
    bool                LoadLevel( const char *filename ); //!< Load level file
	inline int			GetNumberOfItemsInWalls (EItemType ItemType);
	inline int			GetInitialBomberSkills (EBomberSkills BomberSkill);
};

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

inline EBlockType COptions::GetBlockType (int X, int Y)
{
    ASSERT (X >= 0 && X < ARENA_WIDTH);
    ASSERT (Y >= 0 && Y < ARENA_HEIGHT);

    return m_LevelsData[0][X][Y];
}

inline int COptions::GetNumberOfItemsInWalls ( EItemType ItemType )
{
	ASSERT (ItemType > ITEM_NONE && ItemType < NUMBER_OF_ITEMS);

    return m_NumberOfItemsInWalls[0][ItemType];
}

inline int COptions::GetInitialBomberSkills ( EBomberSkills BomberSkill )
{
	ASSERT (BomberSkill > BOMBERSKILL_DUMMYFIRST && BomberSkill < NUMBER_OF_BOMBERSKILLS);

	return m_InitialBomberSkills[0][BomberSkill];
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#endif  // __COPTIONS_H__
