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
// CConsole.h

#ifndef __CCONSOLE_H__
#define __CCONSOLE_H__

#include <windows.h>

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

//! Easy access to singleton console object
#define theConsole  CConsole::GetConsole()

// Flags to use to specify the text color. 
// Example : 
// CONSOLE_FOREGROUND_RED | CONSOLE_FOREGROUND_BLUE | CONSOLE_FOREGROUND_GREEN | 
// CONSOLE_BACKGROUND_INTENSITY | CONSOLE_BACKGROUND_RED
// Grey foreground and light red background.
#define CONSOLE_FOREGROUND_RED          FOREGROUND_RED  
#define CONSOLE_FOREGROUND_GREEN        FOREGROUND_GREEN
#define CONSOLE_FOREGROUND_BLUE         FOREGROUND_BLUE  
#define CONSOLE_FOREGROUND_INTENSITY    FOREGROUND_INTENSITY  
#define CONSOLE_BACKGROUND_RED          BACKGROUND_RED  
#define CONSOLE_BACKGROUND_GREEN        BACKGROUND_GREEN
#define CONSOLE_BACKGROUND_BLUE         BACKGROUND_BLUE  
#define CONSOLE_BACKGROUND_INTENSITY    BACKGROUND_INTENSITY  

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

class CConsole
{
private:

    HANDLE              m_StdOut;                       //!< Handle to console output
    bool                m_Open;                         //!< Is the console opened?
    WORD                m_Color;                        //!< Current text color (background/foreground)
    char                m_Message[2048];                //!< Last message written to the console
    int                 m_NumberOfRepeatedMessages;     //!< How many consecutive identical messages have been sent?
    bool                m_FilterRepeatedMessage;        //!< Should we manage message repetition by not displaying all consecutive identical messages?

public:

                        CConsole();
                        ~CConsole();
    static CConsole&    GetConsole (void);                  //!< Get the console singleton
    void                Open (void);                        //!< Open the console window
    void                Close (void);                       //!< Close the console window
    void                Write (const char *pMessage, ...);  //!< Write a formatted string to the console
    inline bool         IsOpen (void);                      //!< Returns whether the console window is opened
    inline void         SetTextColor (WORD Color);          //!< Set the color to use when writing text to the console
    inline WORD         GetTextColor (void);                //!< Get the color to use when writing text to the console
    inline void         SetFilterRepeatedMessages (bool Filter); //!< Tell whether consecutive identical messages should be filtered or not
};

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

inline bool CConsole::IsOpen (void)
{
    return m_Open;
}

inline void CConsole::SetTextColor (WORD Color)
{
    SetConsoleTextAttribute (m_StdOut, Color);

    m_Color = Color;
}

inline WORD CConsole::GetTextColor (void)
{
    return m_Color;
}

inline void CConsole::SetFilterRepeatedMessages (bool Filter)
{
    m_FilterRepeatedMessage = Filter;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#endif // __CCONSOLE_H__