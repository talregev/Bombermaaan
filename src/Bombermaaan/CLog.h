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
// CLog.cpp
//
// by Thibaut "Fury" Tollemer
// 
// Most of the code was taken in the
// Log.cpp/Log.h files of HaCKeR source,
// by Michaël Schoonbrood :
//      - MadButch@OneCoolDude.Com
//      - http://play.as/madbutch
//

#ifndef _LOG_H
#define _LOG_H

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#include <fstream>
#include <iostream>

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#define theLog  CLog::GetLog()

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

//! Implements a log file where messages can be written to
class CLog
{
public:
                    CLog();
    virtual         ~CLog();
    static CLog&    GetLog();                               //!< Get an instance of CLog (singleton)
    bool            Open( const char *pFilename );          //!< Open the log
    bool            Close();                                //!< Close the log
    void            LogLastError();                         //!< Log the last occured error!
    long            Write ( const char *pMessage, ... );
    long            WriteLine( const char *pMessage, ... ); //!< Write a line to the log
    inline bool     IsOpen();                               //!< Return whether the log is open or not

private:

    ofstream        m_theLog;
    bool            m_bOpen;
};

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Return whether the log is open or not
inline bool CLog::IsOpen()
{
    return m_bOpen;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#endif // _LOG_H
