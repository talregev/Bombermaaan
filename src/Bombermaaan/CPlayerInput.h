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


//////////////////////
// CPlayerInput.h

#ifndef __CPLAYERINPUT_H__
#define __CPLAYERINPUT_H__

#include "COptions.h"

#ifdef WIN32
class CDirectInput;
#else
class CSDLInput;
#endif

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#define MAX_PLAYER_INPUT_NAME_LENGTH    16      //!< Maximum length of a string containing a player input name

#define JOYSTICK_UP         0
#define JOYSTICK_DOWN       1
#define JOYSTICK_LEFT       2
#define JOYSTICK_RIGHT      3
#define JOYSTICK_BUTTON(x)  (4 + x)

#define NO_ACTIVATED_CONTROL    -1

#define MAX_CONTROL_NAME_LENGTH     20

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

class CPlayerInput
{
private:

#ifdef WIN32
	CDirectInput*       m_pDirectInput;
#else
	CSDLInput*			m_pDirectInput;
#endif
    COptions*           m_pOptions;
    int                 m_PlayerInput;
    char                m_Name [MAX_PLAYER_INPUT_NAME_LENGTH];
    char                m_ControlName [MAX_CONTROL_NAME_LENGTH];
                        
    void                CreateName (void);
                        
public:                 
                        
                        CPlayerInput();
                        ~CPlayerInput();
#ifdef WIN32
    inline CDirectInput *GetDirectInput (void);
    inline void         SetDirectInput (CDirectInput* pDirectInput);
#else
    inline CSDLInput   *GetDirectInput (void);
    inline void         SetDirectInput (CSDLInput* pDirectInput);
#endif
    inline void         SetOptions (COptions* pOptions);
    void                Create (int PlayerInput);
    void                Destroy (void);
    void                Open (void);
    bool                IsOpened (void);
    void                Close (void);
    inline const char*  GetName (void);
    void                Update (void);
    inline bool         TestUp (void);
    inline bool         TestDown (void);
    inline bool         TestLeft (void);
    inline bool         TestRight (void);
    inline bool         TestAction1 (void);
    inline bool         TestAction2 (void);
    int                 GetActivatedControl (void);
    const char*         GetControlName (int Control);
    bool                TestControl (int Control);
};

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#ifdef WIN32
inline CDirectInput* CPlayerInput::GetDirectInput (void)
#else
inline CSDLInput* CPlayerInput::GetDirectInput (void)
#endif
{
    return m_pDirectInput;
}

#ifdef WIN32
inline void CPlayerInput::SetDirectInput (CDirectInput* pDirectInput)
#else
inline void CPlayerInput::SetDirectInput (CSDLInput* pDirectInput)
#endif
{
    m_pDirectInput = pDirectInput;
}

inline void CPlayerInput::SetOptions (COptions* pOptions)
{
    m_pOptions = pOptions;
}

inline const char* CPlayerInput::GetName (void)
{
    return m_Name;
}

inline bool CPlayerInput::TestUp (void)
{
    return TestControl (CONTROL_UP);
}

inline bool CPlayerInput::TestDown (void)
{
    return TestControl (CONTROL_DOWN);
}

inline bool CPlayerInput::TestLeft (void)
{
    return TestControl (CONTROL_LEFT);
}

inline bool CPlayerInput::TestRight (void)
{
    return TestControl (CONTROL_RIGHT);
}

inline bool CPlayerInput::TestAction1 (void)
{
    return TestControl (CONTROL_ACTION1);
}

inline bool CPlayerInput::TestAction2 (void)
{
    return TestControl (CONTROL_ACTION2);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#endif  // __CPLAYERINPUT_H__
