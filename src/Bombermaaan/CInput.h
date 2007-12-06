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
// CInput.h

#ifndef __CINPUT_H__
#define __CINPUT_H__

class CTimer;

#include "CDirectInput.h"
#include "CMainInput.h"
#include "CPlayerInput.h"
#include "COptions.h"

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#define NUMBER_OF_KEYBOARD_CONFIGURATIONS     2   //!< Number of keyboard configurations to allow

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

class CInput
{
private:

    COptions*               m_pOptions;         //!< Link to options object to use
    CTimer*                 m_pTimer;           //!< Link to timer object to use
    CDirectInput            m_DirectInput;      //!< DirectInput object managing the DirectInput interface
    CMainInput              m_MainInput;        //!< The main input device
    CPlayerInput*           m_PlayerInput;      //!< Dynamically allocated array of player input devices
                            
public:                     
                            
                            CInput (void);
                            ~CInput (void);
    inline void             SetWindowHandle (HWND hWnd);                //!< Set the window whose input should be received
    inline void             SetInstanceHandle (HINSTANCE hInstance);    //!< Set the instance of the application
    inline void             SetOptions (COptions *pOptions);            //!< Set link to options object to use
    inline void             SetTimer (CTimer *pTimer);                  //!< Set link to timer object to use
    bool                    Create (void);                              //!< Initialize the object
    void                    Destroy (void);                             //!< Uninitialize the object
    inline CMainInput&      GetMainInput (void);
    inline CPlayerInput&    GetPlayerInput (int PlayerInput);
    inline int              GetPlayerInputCount (void);                 
    
};

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

inline void CInput::SetWindowHandle (HWND hWnd)
{
    // Set the window handle the DirectInput object has to communicate with
    m_DirectInput.SetWindowHandle (hWnd);
}

inline void CInput::SetInstanceHandle (HINSTANCE hInstance)
{
    // Set the instance handle the DirectInput object has to communicate with
    m_DirectInput.SetInstanceHandle (hInstance);
}

inline void CInput::SetOptions (COptions *pOptions)
{
    m_pOptions = pOptions;
}

inline void CInput::SetTimer (CTimer *pTimer)
{
    m_pTimer = pTimer;
    m_MainInput.SetTimer (pTimer);
}

inline CMainInput& CInput::GetMainInput (void)
{
    return m_MainInput;
}

inline CPlayerInput& CInput::GetPlayerInput (int PlayerInput)
{
    ASSERT (PlayerInput >= 0);
    ASSERT (PlayerInput < GetPlayerInputCount());

    return m_PlayerInput[PlayerInput];
}

inline int CInput::GetPlayerInputCount (void)
{
    return NUMBER_OF_KEYBOARD_CONFIGURATIONS + m_DirectInput.GetJoystickCount();
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#endif  // __CINPUT_H__
