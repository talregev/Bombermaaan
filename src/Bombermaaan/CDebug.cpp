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


/////////////////////////////////////////
// CDebug.cpp

#include "stdafx.h"
#include "CDebug.h"
#include "CGame.h"
#include "CTimer.h"

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

CDebug::CDebug()
{
    m_pTimer = NULL;
    m_pGame = NULL;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

CDebug::~CDebug()
{
    
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CDebug::Create()
{   
    ASSERT(m_pTimer != NULL);
    ASSERT(m_pGame != NULL);

    // Set initial game debug variables
    m_GameSpeed = 1.0f;
    m_CanBombersDie = true;
    m_CanBombersBeSick = true;
    m_CanBombersKick = true;
    m_IsComputerConsoleActive[0] = false;
    m_IsComputerConsoleActive[1] = false;
    m_IsComputerConsoleActive[2] = false;
    m_IsComputerConsoleActive[3] = false;
    m_IsComputerConsoleActive[4] = false;

    // Actually set the speed of the game
    m_pTimer->SetSpeed (m_GameSpeed);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CDebug::Destroy()
{   
    // Reset the game speed to normal
    m_pTimer->SetSpeed (1.0f);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

CDebug& CDebug::GetInstance()
{
   static CDebug Debug;

   return Debug;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CDebug::HandleKey (DWORD VirtualKeyCode)
{
    // While holding the CTRL key :
    
    // CONTROL GAME SPEED
    // The return key on the numeric pad sets the game speed to normal
    // The * on the numeric pad makes the game very fast
    // The / on the numeric pad makes the game very slow
    // The + on the numeric pad increases the game speed
    // The - on the numeric pad decreases the game speed

    // START OR RESTART A MATCH
    // Press the F1 key

    // TOGGLE THE BOMBERS' INVULNERABILITY
    // Press the F2 key

    // TOGGLE THE DEBUGGING INFORMATION OF EACH COMPUTER PLAYER
    // Press the number of the player (0-4)
    
    if (GetKeyState(VK_CONTROL) & 0x8000)
    {
        switch (VirtualKeyCode)
        {            
            case VK_MULTIPLY :
            {
                m_GameSpeed = 5.0f;
            
                // Set the new game speed
                m_pTimer->SetSpeed (m_GameSpeed);

                break;
            }
        
            case VK_DIVIDE :
            {
                m_GameSpeed = 0.2f;
            
                // Set the timer speed
                m_pTimer->SetSpeed (m_GameSpeed);

                break;
            }

            case VK_RETURN :
            {
                m_GameSpeed = 1.0f;
            
                // Set the timer speed
                m_pTimer->SetSpeed (m_GameSpeed);

                break;
            }
        
            case VK_ADD :
            {
                m_GameSpeed += 0.2f;
            
                if (m_GameSpeed > 5.0f)
                {
                    m_GameSpeed = 5.0f;
                }

                // Set the timer speed
                m_pTimer->SetSpeed (m_GameSpeed);

                break;
            }

            case VK_SUBTRACT :
            {
                m_GameSpeed -= 0.2f;
            
                if (m_GameSpeed < 0.0f)
                {
                    m_GameSpeed = 0.0f;
                }

                // Set the timer speed
                m_pTimer->SetSpeed (m_GameSpeed);

                break;
            }

            case VK_F1 :
            {
                m_pGame->SwitchToGameMode (GAMEMODE_MATCH);

                break;
            }

            case VK_F2 :
            {
                // Make the bombers invulnerable or not
                m_CanBombersDie = !m_CanBombersDie;
                
                break;
            }

            case VK_NUMPAD0 : m_IsComputerConsoleActive[0] = !m_IsComputerConsoleActive[0]; break;
            case VK_NUMPAD1 : m_IsComputerConsoleActive[1] = !m_IsComputerConsoleActive[1]; break;
            case VK_NUMPAD2 : m_IsComputerConsoleActive[2] = !m_IsComputerConsoleActive[2]; break;
            case VK_NUMPAD3 : m_IsComputerConsoleActive[3] = !m_IsComputerConsoleActive[3]; break;
            case VK_NUMPAD4 : m_IsComputerConsoleActive[4] = !m_IsComputerConsoleActive[4]; break;
        }
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************
