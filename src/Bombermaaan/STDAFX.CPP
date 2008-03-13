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


/**
 *  \file stdafx.cpp
 *  \brief Pre-compiled file
 */

#include "stdafx.h"

// TODO: Check if they are still used. I think they are replaced by CDebug class methods
float g_Debug_GameSpeed;
bool  g_Debug_CanBombersDie;
bool  g_Debug_CanBombersBeSick;
bool  g_Debug_CanBombersKick;
bool  g_Debug_IsComputerConsoleActive [MAX_PLAYERS];