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


////////////////////
// CGame.h

#ifndef __CGAME_H__
#define __CGAME_H__

#include "CWindow.h"
#include "CTimer.h"
#include "COptions.h"
#include "CDisplay.h"
#include "CInput.h"
#include "CDrawGame.h"
#include "CWinner.h"
#include "CVictory.h"
#include "CMatch.h"
#include "CScores.h"
#include "CMenu.h"
#include "CSound.h"
#include "CMenuYesNo.h"
#include "CTitle.h"
#include "CControls.h"
#include "CDemo.h"

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

//! Describes how the game should currently be updated
enum EGameMode
{
    GAMEMODE_NONE,              //!< No mode! Nothing to update
    GAMEMODE_TITLE,             //!< Title screen (with the main menu)
    GAMEMODE_DEMO,              //!< Demo screen, showing a match between computer players.
    GAMEMODE_CONTROLS,          //!< Controls screen where controls can be customized
    GAMEMODE_MENU,              //!< Menu screen managing all the menu subscreens which allow to setup and start a new match
    GAMEMODE_MATCH,             //!< Match screen : arena and board update, bombers are playing...
    GAMEMODE_WINNER,            //!< Winner screen : display match winner & stuff about scores, update board...
    GAMEMODE_DRAWGAME,          //!< Draw game screen : simple animated screen, update board...
    GAMEMODE_VICTORY,           //!< Victory screen : display battle winner...
    GAMEMODE_GREETS,            //!< Greets screen where the credits are shown
    GAMEMODE_EXIT               //!< In this mode the game will shutdown and exit to windows
};

enum ENetworkMode
{
    NETWORKMODE_LOCAL,
    NETWORKMODE_SERVER,
    NETWORKMODE_CLIENT
};

extern ENetworkMode    NetworkMode;
extern SOCKET          MySocket;
extern SOCKET          ClientSocket;

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

/**
 *  \brief The main window class of Bombermaaan
 *
 * The CGame class is a window. It initializes itself
 * using an application instance, then initializes
 * the timer, the input, the display, the game screens
 * objects, etc. It's the core of the game and manages 
 * switches between game modes (see EGameMode).
 */

class CGame : public CWindow
{
private:
    
    EGameMode       m_GameMode;             //!< Current game mode defining what to update
    HMODULE         m_hModule;              //!< Connection to the resources
    HINSTANCE       m_hInstance;            //!< Application instance handle
    CTimer          m_Timer;                //!< Timer object for movement, animation, synchronization...
    CDisplay        m_Display;              //!< Needed to draw sprites and manage display
    CInput          m_Input;                //!< Needed to read the players choices in menus, match, etc
    CSound          m_Sound;                //!< Needed to play sounds and musics
    COptions        m_Options;              //!< Options chosen by the players
    CScores         m_Scores;               //!< Scores object where we keep the player scores and the draw games count
    CDrawGame       m_DrawGame;             //!< Draw game screen object (happens when the previous match was a draw game)
    CWinner         m_Winner;               //!< Winner screen object (happens when a player just won one match)
    CVictory        m_Victory;              //!< Victory screen object (happens when a player has the score to reach)
    CMatch          m_Match;                //!< Match screen object in which the players fight
    CMenu           m_Menu;                 //!< Menu screen object for the user to choose the options
    CTitle          m_Title;                //!< Title screen object with the main menu
    CControls       m_Controls;             //!< Controls screen object
    CDemo           m_Demo;                 //!< Demo screen object in which we show a match betweeen computer players.
    CMenuYesNo      m_MenuYesNo;            //!< Yes/No message box object

    void            OnActivateApp  (WPARAM wParam, LPARAM lParam);
    void            OnMove         (WPARAM wParam, LPARAM lParam);
    void            OnKeyDown      (WPARAM wParam, LPARAM lParam);
    void            OnKeyUp        (WPARAM wParam, LPARAM lParam);
    void            OnPaint        (WPARAM wParam, LPARAM lParam);
    bool            OnSysCommand   (WPARAM wParam, LPARAM lParam);
    void            OnWindowActive (void);
    void            StartGameMode (EGameMode GameMode);
    void            FinishGameMode (void);
    CModeScreen*    GetGameModeObject (EGameMode GameMode);

public:

                    CGame (HINSTANCE hInstance, const char* pCommandLine);
    virtual         ~CGame (void);
    bool            Create (const char* pCommandLine);
    void            Destroy (void);
    inline void     SwitchToGameMode (EGameMode GameMode);
};

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

inline void CGame::SwitchToGameMode (EGameMode GameMode)
{
    FinishGameMode();
    StartGameMode(GameMode);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#endif  // __CGAME_H__
