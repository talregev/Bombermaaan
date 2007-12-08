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


#ifndef __CDEBUG_H__
#define __CDEBUG_H__

class CTimer;
class CGame;

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#define theDebug CDebug::GetInstance()

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

class CDebug
{
public:
    
    CDebug();
    ~CDebug();
    static CDebug&  GetInstance();
    inline void SetTimer (CTimer* pTimer);
    inline void SetGame (CGame* pGame);
    void Create();
    void Destroy();
    void HandleKey (DWORD VirtualKeyCode);
    inline bool CanBombersDie();
    inline bool CanBombersBeSick();
    inline bool CanBombersKick();
    inline bool IsComputerConsoleActive (int Player);

private:
    
    CTimer* m_pTimer;
    CGame* m_pGame;
    float m_GameSpeed;
    bool m_CanBombersDie;
    bool m_CanBombersBeSick;
    bool m_CanBombersKick;
    bool m_IsComputerConsoleActive [5];
};

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

inline void CDebug::SetTimer (CTimer* pTimer)
{
    m_pTimer = pTimer;
}

inline void CDebug::SetGame (CGame* pGame)
{
    m_pGame = pGame;
}

inline bool CDebug::CanBombersDie()
{
    return m_CanBombersDie;
}

inline bool CDebug::CanBombersBeSick()
{
    return m_CanBombersBeSick;
}

inline bool CDebug::CanBombersKick()
{
    return m_CanBombersKick;
}

inline bool CDebug::IsComputerConsoleActive (int Player)
{
    ASSERT(Player >= 0);
    ASSERT(Player < 5);

    return m_IsComputerConsoleActive[Player];
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#endif // __CDEBUG_H__
