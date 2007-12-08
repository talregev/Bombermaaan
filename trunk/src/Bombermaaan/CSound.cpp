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


/////////////////////////
// CSound.cpp

#include "stdafx.h"
#include "CSound.h"
#include <fmod_errors.h>

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************



//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

CSound::CSound (void)
{
    // No connection to the resources yet
    m_hModule = NULL;

    // Sound is unpaused
    m_GlobalPause = false;

    // Reset the sample and song pointers
    int i;

    for (i = 0 ; i < NUM_SAMPLES ; i++)
        m_Samples[i] = NULL;
    
    for (i = 0 ; i < NUM_SONGS ; i++)
        m_Songs[i] = NULL;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

CSound::~CSound (void)
{
    // Nothing to do
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool CSound::Create (void)
{
    //-----------------
    // Initialize FMOD
    //-----------------
    
    // If the FMOD DLL version is not correct
    if (FSOUND_GetVersion() != FMOD_VERSION)
    {
        // Log failure
        theLog.WriteLine ("Sound           => !!! Bad FMOD.DLL version (%.02f). Should be %.02f.", FSOUND_GetVersion(), FMOD_VERSION);
        
        // Get out
        return false;
    }

    // Select default sound card
    FSOUND_SetDriver (0);

    // If FMOD initialization fails
    if (!FSOUND_Init (44100, 32, 0))
    {
        // Log failure
        theLog.WriteLine ("Sound           => !!! Could not initialize FSOUND. Error is : %s", FMOD_ErrorString(FSOUND_GetError()));
        
        // There will be no sound during the game
        m_SoundOK = false;

        // Impossible to continue initialization, but return it's ok
        return true;
    }
    // If FMOD initialization succeeded
    else
    {
        // Log success
        theLog.WriteLine ("Sound           => FSOUND initialization was successful.");

        // OK, the sound works
        m_SoundOK = true;
    }

    //---------------------
    // Load the sound data
    //---------------------

    if (!LoadSample (SAMPLE_BOMB_DROP             , SND_BOMB_DROP              ) ||
        !LoadSample (SAMPLE_BOMBER_DEATH          , SND_BOMBER_DEATH           ) ||
        !LoadSample (SAMPLE_BOMB_BOUNCE           , SND_BOMB_BOUNCE            ) ||
        !LoadSample (SAMPLE_BOMBER_PUNCH          , SND_BOMBER_PUNCH           ) ||
        !LoadSample (SAMPLE_BOMBER_THROW          , SND_BOMBER_THROW           ) ||
        !LoadSample (SAMPLE_BOMBER_LOSE_ITEM      , SND_BOMBER_LOSE_ITEM       ) ||
        !LoadSample (SAMPLE_BREAK_1               , SND_BREAK_1                ) ||
        !LoadSample (SAMPLE_BREAK_2               , SND_BREAK_2                ) ||
        !LoadSample (SAMPLE_DRAW_GAME             , SND_DRAW_GAME              ) ||
        !LoadSample (SAMPLE_EXPLOSION_01_1        , SND_EXPLOSION_01_1         ) ||
        !LoadSample (SAMPLE_EXPLOSION_01_2        , SND_EXPLOSION_01_2         ) ||
        !LoadSample (SAMPLE_EXPLOSION_02_1        , SND_EXPLOSION_02_1         ) ||
        !LoadSample (SAMPLE_EXPLOSION_02_2        , SND_EXPLOSION_02_2         ) ||
        !LoadSample (SAMPLE_EXPLOSION_03_1        , SND_EXPLOSION_03_1         ) ||
        !LoadSample (SAMPLE_EXPLOSION_03_2        , SND_EXPLOSION_03_2         ) ||
        !LoadSample (SAMPLE_EXPLOSION_04_1        , SND_EXPLOSION_04_1         ) ||
        !LoadSample (SAMPLE_EXPLOSION_04_2        , SND_EXPLOSION_04_2         ) ||
        !LoadSample (SAMPLE_EXPLOSION_05_1        , SND_EXPLOSION_05_1         ) ||
        !LoadSample (SAMPLE_EXPLOSION_05_2        , SND_EXPLOSION_05_2         ) ||
        !LoadSample (SAMPLE_EXPLOSION_06_1        , SND_EXPLOSION_06_1         ) ||
        !LoadSample (SAMPLE_EXPLOSION_06_2        , SND_EXPLOSION_06_2         ) ||
        !LoadSample (SAMPLE_EXPLOSION_07_1        , SND_EXPLOSION_07_1         ) ||
        !LoadSample (SAMPLE_EXPLOSION_07_2        , SND_EXPLOSION_07_2         ) ||
        !LoadSample (SAMPLE_EXPLOSION_08_1        , SND_EXPLOSION_08_1         ) ||
        !LoadSample (SAMPLE_EXPLOSION_08_2        , SND_EXPLOSION_08_2         ) ||
        !LoadSample (SAMPLE_EXPLOSION_09_1        , SND_EXPLOSION_09_1         ) ||
        !LoadSample (SAMPLE_EXPLOSION_09_2        , SND_EXPLOSION_09_2         ) ||
        !LoadSample (SAMPLE_EXPLOSION_10_1        , SND_EXPLOSION_10_1         ) ||
        !LoadSample (SAMPLE_EXPLOSION_10_2        , SND_EXPLOSION_10_2         ) ||
        !LoadSample (SAMPLE_HURRY                 , SND_HURRY                  ) ||
        !LoadSample (SAMPLE_ITEM_FUMES            , SND_ITEM_FUMES             ) ||
        !LoadSample (SAMPLE_MENU_NEXT             , SND_MENU_NEXT              ) ||
        !LoadSample (SAMPLE_MENU_PREVIOUS         , SND_MENU_PREVIOUS          ) ||
        !LoadSample (SAMPLE_MENU_BEEP             , SND_MENU_BEEP              ) ||
        !LoadSample (SAMPLE_MENU_ERROR            , SND_MENU_ERROR             ) ||
        !LoadSample (SAMPLE_PAUSE                 , SND_PAUSE                  ) ||
        !LoadSample (SAMPLE_PICK_ITEM_1           , SND_PICK_ITEM_1            ) ||
        !LoadSample (SAMPLE_PICK_ITEM_2           , SND_PICK_ITEM_2            ) ||
        !LoadSample (SAMPLE_RING_DING             , SND_RING_DING              ) ||
        !LoadSample (SAMPLE_SICK_1                , SND_SICK_1                 ) ||
        !LoadSample (SAMPLE_SICK_2                , SND_SICK_2                 ) ||
        !LoadSample (SAMPLE_SICK_3                , SND_SICK_3                 ) ||
        !LoadSample (SAMPLE_VICTORY               , SND_VICTORY                ) ||
        !LoadSample (SAMPLE_WALL_CLAP_1           , SND_WALL_CLAP_1            ) ||
        !LoadSample (SAMPLE_WALL_CLAP_2           , SND_WALL_CLAP_2            ) ||
        !LoadSample (SAMPLE_WINNER                , SND_WINNER                 ) ||
        !LoadSong   (SONG_MATCH_MUSIC_1_NORMAL    , SND_MATCH_MUSIC_1_NORMAL   ) ||
        !LoadSong   (SONG_MATCH_MUSIC_1_FAST      , SND_MATCH_MUSIC_1_FAST     ) ||
        !LoadSong   (SONG_MENU_MUSIC              , SND_MENU_MUSIC             ) ||
        !LoadSong   (SONG_CONTROLS_MUSIC          , SND_CONTROLS_MUSIC         ) ||
        !LoadSong   (SONG_TITLE_MUSIC             , SND_TITLE_MUSIC            ))
    {
        // Failure, get out (error is logged by the LoadSample() and LoadSong() methods)
        return false;
    }

    // Everything went right
    return true;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CSound::Destroy (void)
{
    // If the sound works
    if (m_SoundOK)
    {    
        int i;

        // Stop all samples that are playing
        FSOUND_StopSound (FSOUND_ALL);

        // Free all the samples
        for (i = 0 ; i < NUM_SAMPLES ; i++)
        {
            if (m_Samples[i] != NULL)
            {
                FSOUND_Sample_Free (m_Samples[i]);
                m_Samples[i] = NULL;
            }
        }

        // Free all the songs
        for (i = 0 ; i < NUM_SONGS ; i++)
        {
            if (m_Songs[i] != NULL)
            {
                FMUSIC_StopSong (m_Songs[i]);
                FMUSIC_FreeSong (m_Songs[i]);
                m_Songs[i] = NULL;
            }
        }
    
        // Shutdown FMOD
        FSOUND_Close();
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool CSound::LoadSample (ESample Sample, int ResourceID)
{
    // Check if the sample slot is free
    ASSERT (m_Samples[Sample] == NULL);

    LPVOID pData;
    DWORD DataSize;

    // If we could not get the sound resource information
    if (!GetSoundResource (ResourceID, pData, DataSize))
    {
        // Get out
        return false;
    }

    // Tell FMOD to load the sample that is currently in memory, and store the sample handle
    m_Samples[Sample] = FSOUND_Sample_Load (FSOUND_FREE, 
                                                  (const char *) pData, 
                                                  FSOUND_LOADMEMORY | FSOUND_LOOP_OFF | FSOUND_2D, 
                                                  0, DataSize );

    // If it failed
    if (m_Samples[Sample] == NULL)
    {
        // Log failure
        theLog.WriteLine ("Sound           => !!! Could not load sample.");
        
        // Get out
        return false;
    }

    // Everything went right
    return true;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CSound::FreeSample (ESample Sample)
{
    // If the sample slot is not free
    if (m_Samples[Sample] != NULL)
    {
        // Tell FMOD to free the sample
        FSOUND_Sample_Free (m_Samples[Sample]);
        
        // Free the sample slot
        m_Samples[Sample]	= NULL;
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool CSound::LoadSong (ESong Song, int ResourceID)
{
    // Check if the song slot is free
    ASSERT (m_Songs[Song] == NULL);

    LPVOID pData;
    DWORD DataSize;

    // If we could not get the sound resource information
    if (!GetSoundResource (ResourceID, pData, DataSize))
    {
        // Get out
        return false;
    }

    // Tell FMOD to load the song that is currently in memory, and store the song handle
	m_Songs[Song] = FMUSIC_LoadSongEx ((char *) pData, 0, DataSize, FSOUND_LOADMEMORY, NULL, 0);

    // If it failed
    if (m_Songs[Song] == NULL)
    {
        // Log failure
        theLog.WriteLine ("Sound           => !!! Could not load song.");
        
        // Get out
        return false;
    }

    // Everything went right
    return true;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CSound::FreeSong (ESong Song)
{
    // If the song slot is not free
    if (m_Songs[Song] != NULL)
    {
        // Tell FMOD to free the song
        FMUSIC_FreeSong (m_Songs[Song]);
        
        // Free the song slot
        m_Songs[Song]	= NULL;
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool CSound::GetSoundResource (int ResourceID, LPVOID &pData, DWORD &DataSize)
{
    // Find the resource file
    HRSRC hResource = FindResource (m_hModule, MAKEINTRESOURCE(ResourceID), "SOUND");

    // If it failed
    if (hResource == NULL)
    {
        // Log failure
        theLog.WriteLine ("Sound           => !!! Could not find resource.");
        theLog.LogLastError ();

        // Get out
        return false;
    }

    // Load the resource file into memory
    HGLOBAL hGlobal = LoadResource (m_hModule, hResource);

    // If it failed
    if (hGlobal == NULL)
    {
        // Log failure
        theLog.WriteLine ("Sound           => !!! Could not load resource.");
        theLog.LogLastError ();

        // Get out
        return false;
    }

    // Get the address of the resource file in memory
    pData = LockResource (hGlobal);

    // If it failed
    if (pData == NULL)
    {
        // Log failure
        theLog.WriteLine ("Sound           => !!! Could not lock resource.");
        theLog.LogLastError ();

        // Get out
        return false;
    }

    // Get the size (in bytes) of the PNG resource file
    DataSize = SizeofResource (m_hModule, hResource);

    // If it failed
    if (DataSize == 0)
    {
        // Log failure
        theLog.WriteLine ("Sound           => !!! Could not get resource size.");
        theLog.LogLastError ();

        // Get out
        return false;
    }

    // Everything went right
    return true;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CSound::SetPause (bool Pause)
{
    // If the sound works
    if (m_SoundOK)
    {    
        if (m_GlobalPause == !Pause)
        {    
            FSOUND_SetPaused (FSOUND_ALL, !m_GlobalPause);

            for (int i = 0 ; i < NUM_SONGS ; i++)
            {
                if (m_Songs[i] != NULL)
                {
                    FMUSIC_SetPaused (m_Songs[i], !m_GlobalPause);
                }
            }

            m_GlobalPause = !m_GlobalPause;
        }
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CSound::PlaySong (ESong Song)
{
    // If the sound works
    if (m_SoundOK)
    {    
        // If the song exists
        if (m_Songs[Song] != NULL)
        {
            // Start playing this song
            FMUSIC_PlaySong (m_Songs[Song]);
        }
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CSound::StopSong (ESong Song)
{
    // If the sound works
    if (m_SoundOK)
    {    
        // If the song exists
        if (m_Songs[Song] != NULL)
        {
            // Stop playing this song
            FMUSIC_StopSong (m_Songs[Song]);
        }
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CSound::PlaySample (ESample Sample)
{    
    // If the sound works
    if (m_SoundOK)
    {    
        // If the sample exists
        if (m_Samples[Sample] != NULL)
        {
            // Start playing this sample
            FSOUND_PlaySound (FSOUND_FREE, m_Samples[Sample]);
        }
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CSound::SetSampleVolume (int VolumePerCent)
{
    // If the sound works
    if (m_SoundOK)
    {    
        // Set the volume of all samples
        FSOUND_SetSFXMasterVolume (VolumePerCent * 255 / 100);
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CSound::SetSongVolume (ESong Song, int VolumePerCent)
{
    // If the sound works
    if (m_SoundOK)
    {    
        // If this song exists
        if (m_Songs[Song] != NULL)
        {
            // Set the volume for this song
            FMUSIC_SetMasterVolume (m_Songs[Song], VolumePerCent * 255 / 100);
        }
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************
