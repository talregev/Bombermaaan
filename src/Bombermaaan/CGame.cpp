/************************************************************************************

    Copyright (C) 2000-2002, 2007, 2008 Thibaut Tollemer, Bernd Arnold

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
// CGame.cpp

#include "stdafx.h"
#include "CGame.h"
#include "CWindow.h"
#include "COptions.h"
#include "CDisplay.h"
#include "CInput.h"
#include "CDrawGame.h"
#include "CWinner.h"
#include "CVictory.h"
#include "CMatch.h"
#include "CScores.h"
#include "CControls.h"

ENetworkMode    NetworkMode = NETWORKMODE_LOCAL;
SOCKET          MySocket = INVALID_SOCKET;
SOCKET          ClientSocket = INVALID_SOCKET;

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Define this if the log file should be enabled
#define ENABLE_LOG

// Define this if the console window should be enabled
#define ENABLE_CONSOLE

// Define this if you want the console to filter repeated message
//#define ENABLE_CONSOLE_REPEATED_MESSAGE_FILTERING

// Define this if debug keys should be enabled
#define ENABLE_DEBUG_KEYS

// Define this if the game should update normally even when the window does not have the focus
// Note : when the window does not have the focus, you will not have the input focus.
#define ENABLE_UPDATE_WHEN_WINDOW_IS_INACTIVE

// Define this if you want sound and music in the game
#define ENABLE_SOUND

// This is the game mode that is set at start up. Should be set to GAMEMODE_TITLE for a release.
#define START_UP_GAME_MODE GAMEMODE_TITLE

// Define the name of the DLL (where sprites and sound samples are stored)
#ifdef USE_32_PIXELS_PER_BLOCK
#define NAME_OF_BOMBERMAN_DLL "Bombermaaan_32.dll"
#else
#define NAME_OF_BOMBERMAN_DLL "Bombermaaan.dll"
#endif

// This is the title of the main bombermaaan window
#define BOMBERMAAAN_WINDOW_TITLE "Bombermaaan 2007-12-22"

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

CGame::CGame (HINSTANCE hInstance, const char* pCommandLine) 
     : CWindow (hInstance, pCommandLine, IDI_BOMBER) 
{
    SEED_RANDOM(GetTickCount());

    m_GameMode = GAMEMODE_NONE;
    m_hModule = NULL;    
    m_hInstance = hInstance;

    SetWindowText( m_hWnd, BOMBERMAAAN_WINDOW_TITLE );
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

CGame::~CGame ()
{
    // Nothing to do
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool CGame::Create (const char* pCommandLine)
{
#ifdef ENABLE_CONSOLE

    // Open the console window
    theConsole.Open ();

    #ifndef ENABLE_CONSOLE_REPEATED_MESSAGE_FILTERING
        
        theConsole.SetFilterRepeatedMessages(false);
    
    #endif

#endif

#ifdef ENABLE_LOG

    // Open the log file
    theLog.Open ("log.txt");

#endif

    theDebug.SetGame(this);
    theDebug.SetTimer(&m_Timer);
	theDebug.SetMatch(&m_Match);
    theDebug.Create();

    // If the resource file does not exist
    if (GetFileAttributes( NAME_OF_BOMBERMAN_DLL ) == -1)
    {
        // Failure
        theLog.WriteLine ("Game            => !!! Could not find " NAME_OF_BOMBERMAN_DLL ".");
        MessageBox(m_hWnd, "Could not find " NAME_OF_BOMBERMAN_DLL "!", "Error", MB_OK);
        
        // Get out
        return false;
    }
    
    // Establish connection to the DLL
    m_hModule = LoadLibrary ( NAME_OF_BOMBERMAN_DLL );
    
    // If it failed
    if (m_hModule == NULL)
    {
        // Log error
        theLog.WriteLine ("Game            => !!! Could not load " NAME_OF_BOMBERMAN_DLL );
        theLog.LogLastError();
        
        // Get out
        return false;
    }

    if (!m_Options.Create ())
    {
        // Get out
        return false;
    }

    // Set the objects the input object has to communicate with
    m_Input.SetInstanceHandle (m_hInstance);
    m_Input.SetWindowHandle (m_hWnd);
    m_Input.SetOptions (&m_Options);
    m_Input.SetTimer (&m_Timer);

    // Set the objects the display object has to communicate with
    m_Display.SetWindowHandle (m_hWnd);
    m_Display.SetModuleHandle (m_hModule);

    // Set the objects the match object has to communicate with
    m_Match.SetDisplay (&m_Display);
    m_Match.SetInput (&m_Input);
    m_Match.SetOptions (&m_Options);
    m_Match.SetTimer (&m_Timer);
    m_Match.SetScores (&m_Scores);
    m_Match.SetSound (&m_Sound);

    // Set the objects the demo object has to communicate with
    m_Demo.SetDisplay (&m_Display);
    m_Demo.SetInput (&m_Input);
    m_Demo.SetOptions (&m_Options);
    m_Demo.SetTimer (&m_Timer);
    m_Demo.SetScores (&m_Scores);
    m_Demo.SetSound (&m_Sound);
    
    // Set the objects the draw game object has to communicate with
    m_DrawGame.SetDisplay (&m_Display);
    m_DrawGame.SetInput (&m_Input);
    m_DrawGame.SetTimer (&m_Timer);
    m_DrawGame.SetScores (&m_Scores);
    m_DrawGame.SetOptions (&m_Options);
    m_DrawGame.SetSound (&m_Sound);

    // Set the objects the winner object has to communicate with
    m_Winner.SetDisplay (&m_Display);
    m_Winner.SetInput (&m_Input);
    m_Winner.SetOptions (&m_Options);
    m_Winner.SetTimer (&m_Timer);
    m_Winner.SetScores (&m_Scores);
    m_Winner.SetMatch (&m_Match);
    m_Winner.SetSound (&m_Sound);

    // Set the objects the victory object has to communicate with
    m_Victory.SetDisplay (&m_Display);
    m_Victory.SetInput (&m_Input);
    m_Victory.SetOptions (&m_Options);
    m_Victory.SetTimer (&m_Timer);
    m_Victory.SetScores (&m_Scores);
    m_Victory.SetSound (&m_Sound);

    // Set the objects the scores object has to communicate with
    m_Scores.SetOptions (&m_Options);

    // Set the objects the menu object has to communicate with
    m_Menu.SetDisplay (&m_Display);
    m_Menu.SetInput (&m_Input);
    m_Menu.SetOptions (&m_Options);
    m_Menu.SetTimer (&m_Timer);
    m_Menu.SetSound (&m_Sound);
    m_Menu.SetScores (&m_Scores);

    // Set the objects the title object has to communicate with
    m_Title.SetDisplay (&m_Display);
    m_Title.SetInput (&m_Input);
    m_Title.SetOptions (&m_Options);
    m_Title.SetTimer (&m_Timer);
    m_Title.SetSound (&m_Sound);

    // Set the objects the controls object has to communicate with
    m_Controls.SetDisplay (&m_Display);
    m_Controls.SetInput (&m_Input);
    m_Controls.SetOptions (&m_Options);
    m_Controls.SetTimer (&m_Timer);
    m_Controls.SetSound (&m_Sound);

    // Set the objects the victory object has to communicate with
    m_MenuYesNo.SetDisplay (&m_Display);
    m_MenuYesNo.SetInput (&m_Input);
    m_MenuYesNo.SetTimer (&m_Timer);
    m_MenuYesNo.SetSound (&m_Sound);
    
    // Set the objects the sound object has to communicate with
    m_Sound.SetModuleHandle (m_hModule);

    // If creating the display and setting the display mode failed
    if (!m_Display.Create (m_Options.GetDisplayMode()))
    {
        // Get out
        return false;
    }
    
    // If creating the input failed
    if (!m_Input.Create ())
    {
        // Get out
        return false;
    }

#ifdef ENABLE_SOUND

    // If creating the sound failed
    if (!m_Sound.Create ())
    {
        // Get out
        return false;
    }

    m_Sound.SetSongVolume (SONG_MATCH_MUSIC_1_NORMAL, 65);
    m_Sound.SetSongVolume (SONG_MATCH_MUSIC_1_FAST, 65);
    m_Sound.SetSongVolume (SONG_MENU_MUSIC, 65);
    m_Sound.SetSampleVolume (100);

#endif

    m_MenuYesNo.Create ();

    if (strstr(pCommandLine, "-s") != NULL)
    {
        OutputDebugString("*** STARTING GAME AS SERVER\n");
        NetworkMode = NETWORKMODE_SERVER;
    }
    else if (strstr(pCommandLine, "-c") != NULL)
    {
        OutputDebugString("*** STARTING GAME AS CLIENT\n");
        NetworkMode = NETWORKMODE_CLIENT;
    }

    if (NetworkMode != NETWORKMODE_LOCAL)
    {
        WSAData WsaData;
    
        if (WSAStartup(MAKEWORD(1, 1), &WsaData) != 0) 
        {
            theConsole.Write("WSAStartup failed\n");
            return false;
        }

        MySocket = socket(AF_INET, SOCK_STREAM, 0);

        if (MySocket == INVALID_SOCKET)
        {
            theConsole.Write("socket failed\n");
            return false;
        }

        if (NetworkMode == NETWORKMODE_SERVER)
        {
            SOCKADDR_IN SocketAddress;
            SocketAddress.sin_family = AF_INET;
            SocketAddress.sin_addr.s_addr = INADDR_ANY;
            SocketAddress.sin_port = htons(12345);
    
            theConsole.Write("bind\n");
    
            if (bind(MySocket, (LPSOCKADDR)&SocketAddress, sizeof(SOCKADDR)) == SOCKET_ERROR) 
            {
                theConsole.Write("bind failed\n");
                closesocket(MySocket);
                return false;
            }

            theConsole.Write("listen\n");
    
            if (listen(MySocket, SOMAXCONN) == SOCKET_ERROR)
            {
                theConsole.Write("listen failed\n");
                closesocket(MySocket);
                return false;
            }

            theConsole.Write("accept\n");

            SOCKADDR_IN Address;
            int Size = sizeof(SOCKADDR);

            ClientSocket = accept(MySocket, (LPSOCKADDR)&Address, &Size);

            if (ClientSocket == INVALID_SOCKET) 
            {
                theConsole.Write("accept failed\n");
                return false;
            }
        }
        else if (NetworkMode == NETWORKMODE_CLIENT)
        {
            char IpAddressString[32];
            strcpy(IpAddressString, strstr(pCommandLine, "-c") + 3);
            
            theConsole.Write("connect to %s\n", IpAddressString);

            u_long RemoteAddress = inet_addr(IpAddressString);

            if (RemoteAddress == INADDR_NONE)
            {
                theConsole.Write("The address %s is not a dotted IP address.\n");
                return false;
            }
               
            SOCKADDR_IN SocketAddress;
            SocketAddress.sin_family = AF_INET;
            memcpy(&SocketAddress.sin_addr, &RemoteAddress, sizeof(u_long)); 
            SocketAddress.sin_port = htons(12345);

            if (connect(MySocket, (LPSOCKADDR)&SocketAddress, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
            {
                theConsole.Write("connect failed\n");
                closesocket(MySocket);
                while(1) { }
                return false;
            }
        }

        // Set the current game mode
        StartGameMode (GAMEMODE_MATCH);
    }
    else
    {
        // Set the current game mode
        StartGameMode (START_UP_GAME_MODE);
    }

    // Log that initialization is complete
    theLog.WriteLine ("Game            => Game initialization is complete!");
    
    // Leave a blank line between "game loop" stuff and initialization
    theLog.Write ("\n");

    // Everything went right
    return true;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CGame::Destroy (void)
{
    // Leave a blank line between "game loop" stuff and shutdown
    theLog.Write ("\n");
    
    // Log that shutdown begins
    theLog.WriteLine ("Game            => Game shutdown will now begin.");
    
    // Terminate game mode and set no game mode
    FinishGameMode ();

    closesocket(MySocket);
    closesocket(ClientSocket);

    if (WSACleanup() == SOCKET_ERROR) 
    {
        if (WSAGetLastError() == WSAEINPROGRESS) 
        {
            WSACancelBlockingCall();
            WSACleanup();
        }
    }
    
#ifdef ENABLE_SOUND
    
    m_Sound.Destroy ();

#endif
    
    m_Input.Destroy ();
    m_Display.Destroy ();

    m_Options.SaveBeforeExit ();
    m_Options.Destroy ();
    m_MenuYesNo.Destroy ();
    
    theDebug.Destroy();

    // If there is a connection to the resources
    if (m_hModule != NULL)
    {
        // Close the connection to the resources
        FreeLibrary (m_hModule);
        m_hModule = NULL;
    }

#ifdef ENABLE_CONSOLE

    // Close the console window
    theConsole.Close ();

#endif

#ifdef ENABLE_LOG

    // Close the log file
    theLog.Close ();

#endif

}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

CModeScreen* CGame::GetGameModeObject (EGameMode GameMode)
{
    // According to the specified game mode, return a pointer to the object manager of this mode
    switch (GameMode)
    {
        case GAMEMODE_TITLE    :  return &m_Title;    break;
        case GAMEMODE_DEMO     :  return &m_Demo;     break;
        case GAMEMODE_MENU     :  return &m_Menu;     break;
        case GAMEMODE_MATCH    :  return &m_Match;    break;
        case GAMEMODE_WINNER   :  return &m_Winner;   break;
        case GAMEMODE_DRAWGAME :  return &m_DrawGame; break;
        case GAMEMODE_VICTORY  :  return &m_Victory;  break;
        case GAMEMODE_CONTROLS :  return &m_Controls; break;
        case GAMEMODE_GREETS   :  break;
        case GAMEMODE_EXIT     :  break;
    }

    // There is no object manager for this game mode
    return NULL;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// This method is called when the window is active

void CGame::OnWindowActive (void)
{
    // Prepare a game mode variable to save the mode to set
    EGameMode NextGameMode = m_GameMode;

    m_Timer.Update();
    m_Input.GetMainInput().Update();
    
    // If the menu yes/no is not active
    if (!m_MenuYesNo.IsActive())
    {
        // Update the object corresponding to the current game mode
        if (GetGameModeObject(m_GameMode) != NULL)
            NextGameMode = GetGameModeObject(m_GameMode)->Update ();
    }

    // If the mode screen object corresponding to the current game mode
    // is not asking for changing the game mode 
    if (NextGameMode == m_GameMode)
    {
        // Then let the menu yes/no ask for changing the game mode if needed.
        // Manage the menu yes/no and get the appropriate game mode to set
        NextGameMode = m_MenuYesNo.Update (m_GameMode);
    }

    // Make the display black
    m_Display.Clear ();
    
    // Display the object corresponding to the current game mode
    if (GetGameModeObject(m_GameMode) != NULL)
        GetGameModeObject(m_GameMode)->Display ();

    // Display the menu yes/no if needed    
    m_MenuYesNo.Display();

    // Display everything
    m_Display.Update ();

    // If the next game mode is different from the current game mode
    if (NextGameMode != m_GameMode)
    {
        // Change the game mode
        FinishGameMode ();
        StartGameMode (NextGameMode);
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Set a new game mode. Creates the object 
// corresponding to the new game mode.

void CGame::StartGameMode (EGameMode GameMode)
{
    // Set the new game mode
    m_GameMode = GameMode;
    
    // If we must exit the game
    if (m_GameMode == GAMEMODE_EXIT)
    {
        // Come back to windowed mode in order to avoid a kind
        // of bug with VC++. Otherwise the VC++ window would be
        // resized to the size of the fullscreen mode that was
        // set when exiting.
        m_Display.Create (DISPLAYMODE_WINDOWED);

        // Close the window
        PostMessage (m_hWnd, WM_CLOSE, 0, 0);
    }
    // If we don't have to exit the game
    else
    {
        // Create the object corresponding to the new game mode
        if (GetGameModeObject(m_GameMode) != NULL)
            GetGameModeObject(m_GameMode)->Create ();
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Set no game mode. Destroys the object 
// corresponding to the current game mode.

void CGame::FinishGameMode (void)
{
    // Destroy the object corresponding to the new game mode
    if (GetGameModeObject(m_GameMode) != NULL)
        GetGameModeObject(m_GameMode)->Destroy ();

    // Set no game mode
    m_GameMode = GAMEMODE_NONE;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************


// This is called when the active state of the window 
// changes. This is NOT called on window creation.

void CGame::OnActivateApp (WPARAM wParam, LPARAM lParam)
{
    CWindow::OnActivateApp (wParam, lParam);

#ifdef ENABLE_UPDATE_WHEN_WINDOW_IS_INACTIVE    
    m_Active = true;
#endif

    // If the window gets the focus
    if (m_Active)
    {
        // Resume the timer
        m_Timer.Resume ();

#ifdef ENABLE_SOUND
        // Unpause the sound
        m_Sound.SetPause (false);
#endif
        
        // Open the needed players inputs according to current game mode
        // Create the object corresponding to the new game mode
        if (GetGameModeObject(m_GameMode) != NULL)
            GetGameModeObject(m_GameMode)->OpenInput ();
    }
    // If the window loses the focus
    else
    {
        // Pause the timer
        m_Timer.Pause ();

#ifdef ENABLE_SOUND
        // Pause the sound
        m_Sound.SetPause (true);
#endif

        // Close the needed players inputs according to current game mode
        // Create the object corresponding to the new game mode
        if (GetGameModeObject(m_GameMode) != NULL)
            GetGameModeObject(m_GameMode)->CloseInput ();
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Called when the window moves.

void CGame::OnMove (WPARAM wParam, LPARAM lParam)
{
    CWindow::OnMove (wParam, lParam);
    
    // Create the display manage the movement of the window
    m_Display.OnWindowMove ();
}


//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************


// When the window is active and a key is pressed down,
// this method will be called.

void CGame::OnKeyDown (WPARAM wParam, LPARAM lParam)
{
        
}


//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// When the window is active and a key is released,
// this method will be called.

void CGame::OnKeyUp (WPARAM wParam, LPARAM lParam)
{
#ifdef ENABLE_DEBUG_KEYS
    
    // Read the key that is released and apply changes to the game if needed (for debugging)
    theDebug.HandleKey(wParam);

#endif // ENABLE_DEBUG_KEYS

    // If the CTRL key is not pressed while the key specified by wParam is released
    if (!(GetKeyState(VK_CONTROL) & 0x8000))
    {
        
        EDisplayMode DisplayMode = DISPLAYMODE_NONE;
        
        // Assume we have to change the display mode
        bool SetDisplayMode = true;

        // Change display mode if this is a F1-F4 key
        switch (wParam)
        {
            case VK_F1 : DisplayMode = DISPLAYMODE_FULL1; break;
            case VK_F2 : DisplayMode = DISPLAYMODE_FULL2; break;
            case VK_F3 : DisplayMode = DISPLAYMODE_FULL3; break;
            case VK_F4 : DisplayMode = DISPLAYMODE_WINDOWED; break;
            default    : SetDisplayMode = false; break;
        }

        // If we have to change the display mode 
        // and the new display mode to set is available on the graphic card
        if (SetDisplayMode && m_Display.IsDisplayModeAvailable(DisplayMode))
        {
            // Set the display mode
            m_Display.Create (DisplayMode);

            // Save it in the options
            m_Options.SetDisplayMode (DisplayMode);
        }

	} else {

        // Quickly exit the game with CTRL + F12
        if (wParam == VK_F12)
        {
            FinishGameMode();
            StartGameMode(GAMEMODE_EXIT);
        }

	}
}


//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************


// If the window has to be repainted, the display
// must be updated to redraw the game screen.

void CGame::OnPaint (WPARAM wParam, LPARAM lParam)
{
    // Create the display manage this repainting
    m_Display.OnPaint ();
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// SCREEN SAVER DISABLING DOES NOT WORK

bool CGame::OnSysCommand (WPARAM wParam, LPARAM lParam)
{
    // Check what is the system command
    switch (wParam)
    {
        // If it's a monitor power command or a screen saver execution
        case SC_MONITORPOWER :
        case SC_SCREENSAVE :
        {
            // Do NOT let Windows handle these commands in order
            // to disable these two system commands when the game is running
            return false;
        }
    }

    // Make Windows handle these commands
    return true;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************
