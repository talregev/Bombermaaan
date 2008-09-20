/************************************************************************************

    Copyright (C) 2000-2002, 2007 Thibaut Tollemer
    Copyright (C) 2007, 2008 Bernd Arnold
	Copyright (C) 2008 Jerome Bigot

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
// COptions.cpp

#include "stdafx.h"
#include "COptions.h"
#include "CInput.h"
#include "CItem.h"
#include <iostream>
#include <fstream>
#include <string>


//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#define TIMESTART_MINUTES   1
#define TIMESTART_SECONDS   0

#define TIMEUP_MINUTES      0
#define TIMEUP_SECONDS      35

#define CONFIGURATION_KEYBOARD_1      0
#define CONFIGURATION_KEYBOARD_2      1
#define CONFIGURATION_JOYSTICK_1      2

// Initial number of items when a new arena is built
#define INITIAL_ITEMBOMB        11
#define INITIAL_ITEMFLAME       8
#define INITIAL_ITEMROLLER      7
#define INITIAL_ITEMKICK        2
#define INITIAL_ITEMSKULL       1
#define INITIAL_ITEMTHROW       2
#define INITIAL_ITEMPUNCH       2
#define INITIAL_ITEMREMOTE      2

// Initial flame size
#define INITIAL_FLAMESIZE       2

// Initial number of bombs the bomber can drop
#define INITIAL_BOMBS           1

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

COptions::COptions (void)
{
    m_LevelsData = NULL;
	m_NumberOfItemsInWalls = NULL;
	m_InitialBomberSkills = NULL;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

COptions::~COptions (void)
{
    Destroy();
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

COptions& COptions::operator = (COptions& Copy)
{
    m_TimeStartMinutes = Copy.m_TimeStartMinutes;
    m_TimeStartSeconds = Copy.m_TimeStartSeconds;
    m_TimeUpMinutes = Copy.m_TimeUpMinutes;
    m_TimeUpSeconds = Copy.m_TimeUpSeconds;

    int i, j, k;

    for (i = 0 ; i < MAX_PLAYERS ; i++)
    {
        m_BomberType[i] = Copy.m_BomberType[i];
        m_PlayerInput[i] = Copy.m_PlayerInput[i];
    }

    m_PlayerCount = Copy.m_PlayerCount;
    m_BattleCount = Copy.m_BattleCount;
    m_DisplayMode = Copy.m_DisplayMode;

    for (i = 0 ; i < MAX_PLAYER_INPUT ; i++)
        for (j = 0 ; j < NUM_CONTROLS ; j++)
            m_Control[i][j] = Copy.m_Control[i][j];
    
    m_Level = Copy.m_Level;
    m_NumberOfLevels = Copy.m_NumberOfLevels;
    
    AllocateLevels(m_NumberOfLevels);

    for (i = 0 ; i < m_NumberOfLevels ; i++)
    {
        levelFileNames_short = Copy.levelFileNames_short;
        levelFileNames_full  = Copy.levelFileNames_full;

        for (j = 0 ; j < ARENA_WIDTH ; j++)
            for (k = 0 ; k < ARENA_HEIGHT ; k++)
                m_LevelsData[i][j][k] = Copy.m_LevelsData[i][j][k];

        for (j = ITEM_NONE ; j < NUMBER_OF_ITEMS ; j++) {
            m_NumberOfItemsInWalls[i][j] = Copy.m_NumberOfItemsInWalls[i][j];
        }

        for (j = BOMBERSKILL_DUMMYFIRST ; j < NUMBER_OF_BOMBERSKILLS ; j++) {
            m_InitialBomberSkills[i][j] = Copy.m_InitialBomberSkills[i][j];
        }

    }

    return *this;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool COptions::Create( bool useAppDataFolder, std::string dynamicDataFolder, std::string pgmFolder )
{
    // Set the file name of the configuration file including full path
    configFileName = dynamicDataFolder.c_str();
    configFileName.append( "config.dat" );
    theLog.WriteLine( "Options         => Name of config file: '%s'.", configFileName.c_str() );
    
    // Load configuration file
    if (!LoadConfiguration())
        return false;

    // Load game levels data and names
    if (!LoadLevels( useAppDataFolder ? dynamicDataFolder : "", pgmFolder ))
        return false;
    

    // Everything went ok.
    return true;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void COptions::Destroy (void)
{
    //-------------------------------
    // Free all level data and names
    //-------------------------------

    if (m_LevelsData != NULL)
    {
        for (int i = 0 ; i < m_NumberOfLevels ; i++)
        {
            for (int j = 0 ; j < ARENA_WIDTH ; j++)
                delete [] m_LevelsData[i][j];

            delete [] m_LevelsData[i];
        }

        delete [] m_LevelsData;
        m_LevelsData = NULL;
        
		for (int i = 0 ; i < m_NumberOfLevels ; i++) {
			delete [] m_InitialBomberSkills[i];
			delete [] m_NumberOfItemsInWalls[i];
			m_InitialBomberSkills[i] = NULL;
			m_NumberOfItemsInWalls[i] = NULL;
		}

		m_NumberOfItemsInWalls = NULL;
		m_InitialBomberSkills = NULL;

        m_NumberOfLevels = 0;
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void COptions::SaveBeforeExit (void)
{
   // Try to open the configuration file
    FILE* pConfigFile = fopen( configFileName.c_str(), "wb");
    
    // Write configuration to file
    if (pConfigFile != NULL)
    {
        WriteData(pConfigFile);
        fclose(pConfigFile);
    } 
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool COptions::LoadConfiguration (void)
{
    // Try to open the configuration file
    FILE* pConfigFile = fopen( configFileName.c_str(), "rb" );
    
    // If the configuration file doesn't exist
    if (pConfigFile == NULL)
    {
        //----------------------------------
        // Set default configuration values
        //----------------------------------

        int i;

        m_TimeUpMinutes = TIMEUP_MINUTES;
        m_TimeUpSeconds = TIMEUP_SECONDS;
        m_TimeStartMinutes = TIMESTART_MINUTES;
        m_TimeStartSeconds = TIMESTART_SECONDS;
        m_BomberType[0] = BOMBERTYPE_MAN;
        m_BomberType[1] = BOMBERTYPE_MAN;
        m_BomberType[2] = BOMBERTYPE_OFF;
        m_BomberType[3] = BOMBERTYPE_OFF;
        m_BomberType[4] = BOMBERTYPE_OFF;
        m_Level = 0;

        for (i = 0 ; i < MAX_PLAYERS ; i++)
            m_PlayerInput[i] = 0;
        
        m_BattleCount = 3;
        m_DisplayMode = DISPLAYMODE_WINDOWED;

        m_Control[CONFIGURATION_KEYBOARD_1][CONTROL_UP]      = KEYBOARD_NUMPAD8;
        m_Control[CONFIGURATION_KEYBOARD_1][CONTROL_DOWN]    = KEYBOARD_NUMPAD5;
        m_Control[CONFIGURATION_KEYBOARD_1][CONTROL_LEFT]    = KEYBOARD_NUMPAD4;
        m_Control[CONFIGURATION_KEYBOARD_1][CONTROL_RIGHT]   = KEYBOARD_NUMPAD6;
        m_Control[CONFIGURATION_KEYBOARD_1][CONTROL_ACTION1] = KEYBOARD_PRIOR;
        m_Control[CONFIGURATION_KEYBOARD_1][CONTROL_ACTION2] = KEYBOARD_HOME;

        m_Control[CONFIGURATION_KEYBOARD_2][CONTROL_UP]      = KEYBOARD_R;
        m_Control[CONFIGURATION_KEYBOARD_2][CONTROL_DOWN]    = KEYBOARD_F;
        m_Control[CONFIGURATION_KEYBOARD_2][CONTROL_LEFT]    = KEYBOARD_D;
        m_Control[CONFIGURATION_KEYBOARD_2][CONTROL_RIGHT]   = KEYBOARD_G;
        m_Control[CONFIGURATION_KEYBOARD_2][CONTROL_ACTION1] = KEYBOARD_2;
        m_Control[CONFIGURATION_KEYBOARD_2][CONTROL_ACTION2] = KEYBOARD_1;

        for (i = CONFIGURATION_JOYSTICK_1 ; i < MAX_PLAYER_INPUT ; i++)
        {
            m_Control[i][CONTROL_UP]      = JOYSTICK_UP;
            m_Control[i][CONTROL_DOWN]    = JOYSTICK_DOWN;
            m_Control[i][CONTROL_LEFT]    = JOYSTICK_LEFT;
            m_Control[i][CONTROL_RIGHT]   = JOYSTICK_RIGHT;
            m_Control[i][CONTROL_ACTION1] = JOYSTICK_BUTTON(0);
            m_Control[i][CONTROL_ACTION2] = JOYSTICK_BUTTON(1);
        }

        m_Level = 0;

        // Create the configuration file
        pConfigFile = fopen( configFileName.c_str(), "wb" );
        
        // If creation failed
        if (pConfigFile == NULL)
        {
            // Log failure
            theLog.WriteLine ("Options         => !!! Could not create config file '%s'.", configFileName.c_str() );

            return false;
        }
        
        // Write the configuration file
        WriteData(pConfigFile);
    }
    // If the configuration file exists
    else
    {
        // Read the configuration file.
        ReadData(pConfigFile);
    }

    // The configuration file is not needed anymore
    fclose(pConfigFile);

    // Success
    return true;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void COptions::ReadData (FILE* pConfigFile)
{
    // Read each configuration value in the file
    fread(&m_TimeUpMinutes, sizeof(int), 1, pConfigFile);
    fread(&m_TimeUpSeconds, sizeof(int), 1, pConfigFile);
    fread(&m_TimeStartMinutes, sizeof(int), 1, pConfigFile);
    fread(&m_TimeStartSeconds, sizeof(int), 1, pConfigFile);
    fread(&m_DisplayMode, sizeof(EDisplayMode), 1, pConfigFile);
    fread(&m_BattleCount, sizeof(int), 1, pConfigFile);
    fread(m_BomberType, sizeof(EBomberType), MAX_PLAYERS, pConfigFile);
    fread(m_PlayerInput, sizeof(int), MAX_PLAYERS, pConfigFile);
    fread(m_Control, sizeof(int), MAX_PLAYER_INPUT * NUM_CONTROLS, pConfigFile);
    fread(&m_Level, sizeof(int), 1, pConfigFile);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void COptions::WriteData (FILE* pConfigFile)
{
    // Write each configuration value in the file
    fwrite(&m_TimeUpMinutes, sizeof(int), 1, pConfigFile);
    fwrite(&m_TimeUpSeconds, sizeof(int), 1, pConfigFile);
    fwrite(&m_TimeStartMinutes, sizeof(int), 1, pConfigFile);
    fwrite(&m_TimeStartSeconds, sizeof(int), 1, pConfigFile);
    fwrite(&m_DisplayMode, sizeof(EDisplayMode), 1, pConfigFile);
    fwrite(&m_BattleCount, sizeof(int), 1, pConfigFile);
    fwrite(m_BomberType, sizeof(EBomberType), MAX_PLAYERS, pConfigFile);
    fwrite(m_PlayerInput, sizeof(int), MAX_PLAYERS, pConfigFile);
    fwrite(m_Control, sizeof(int), MAX_PLAYER_INPUT * NUM_CONTROLS, pConfigFile);
    fwrite(&m_Level, sizeof(int), 1, pConfigFile);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void COptions::AllocateLevels (int NumberOfLevels)
{
    ASSERT(m_LevelsData == NULL);
	ASSERT(m_NumberOfItemsInWalls == NULL);
	ASSERT(m_InitialBomberSkills == NULL);
    
    m_LevelsData = new EBlockType** [NumberOfLevels];
	m_NumberOfItemsInWalls = new int* [NumberOfLevels];
	m_InitialBomberSkills = new int* [NumberOfLevels];

    for (int i = 0 ; i < NumberOfLevels ; i++)
    {
        m_LevelsData[i] = new EBlockType* [ARENA_WIDTH];

        for (int j = 0 ; j < ARENA_WIDTH ; j++)
            m_LevelsData[i][j] = new EBlockType [ARENA_HEIGHT];

        m_NumberOfItemsInWalls[i] = new int [NUMBER_OF_ITEMS];
        m_InitialBomberSkills[i] = new int [NUMBER_OF_BOMBERSKILLS];
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool COptions::LoadLevels( std::string dynamicDataFolder, std::string pgmFolder )
{
    FILE* File;
    long FindHandle;
    _finddata_t FindData;
    m_NumberOfLevels = 0;


    //-------------------------------------------
    // Set the path where the level files are stored
    // (in the program files folder)
    //-------------------------------------------
    
    std::string levelFilePath_pgmFolder;
    levelFilePath_pgmFolder = pgmFolder;
    levelFilePath_pgmFolder.append( "\\Levels\\" );

    std::string levelFilePath_pgmFolderMask;
    levelFilePath_pgmFolderMask = levelFilePath_pgmFolder;
    levelFilePath_pgmFolderMask.append( "*.txt" );


    //-------------------------------------------
    // Determine number of level files available
    // (in the program files folder)
    //-------------------------------------------
    
    theLog.WriteLine( "Options         => Loading level files '%s'.", levelFilePath_pgmFolderMask.c_str() );

    FindHandle = _findfirst( levelFilePath_pgmFolderMask.c_str(), &FindData );
    
    if (FindHandle != -1)
    {
        do 
        {
            m_NumberOfLevels++;

            std::string fileNameWithoutPath( FindData.name );
            std::string fileNameWithPath( levelFilePath_pgmFolder );
            fileNameWithPath.append( FindData.name );

            levelFileNames_short.push_back( fileNameWithoutPath );
            levelFileNames_full.push_back( fileNameWithPath );
        }
        while (_findnext(FindHandle, &FindData) != -1);
    }

    _findclose(FindHandle);


    // If a dynamic folder is set, load level files from there, too
    if ( dynamicDataFolder != "" ) {

        //-------------------------------------------
        // Set the path where the level files are stored
        // (in the user's application data folder)
        //-------------------------------------------

        std::string levelFilePath_dynamicDataFolder;
        levelFilePath_dynamicDataFolder = dynamicDataFolder;
        levelFilePath_dynamicDataFolder.append( "Levels\\" );

        std::string levelFilePath_dynamicDataFolderMask;
        levelFilePath_dynamicDataFolderMask = levelFilePath_dynamicDataFolder;
        levelFilePath_dynamicDataFolderMask.append( "*.txt" );


        //-------------------------------------------
        // Determine number of level files available
        // (in the dynamic data folder)
        //-------------------------------------------    

        theLog.WriteLine( "Options         => Loading level files '%s'.", levelFilePath_dynamicDataFolderMask.c_str() );

        FindHandle = _findfirst( levelFilePath_dynamicDataFolderMask.c_str(), &FindData );
        
        if (FindHandle != -1)
        {
            do 
            {
                m_NumberOfLevels++;

                std::string fileNameWithoutPath( FindData.name );
                std::string fileNameWithPath( levelFilePath_dynamicDataFolder );
                fileNameWithPath.append( FindData.name );

                levelFileNames_short.push_back( fileNameWithoutPath );
                levelFileNames_full.push_back( fileNameWithPath );
            }
            while (_findnext(FindHandle, &FindData) != -1);
        }

        _findclose(FindHandle);

    }


    //---------------------
    // Check for a problem
    //---------------------

    // If there is no level
    if (m_NumberOfLevels == 0)
    {
        // Log failure
        theLog.WriteLine ("Options         => !!! There should be at least 1 level.");

        return false;
    }

    // If the level number we read in the cfg file is invalid compared to the number of existing levels
    if (m_Level >= m_NumberOfLevels)
    {
        // Select the first level
        m_Level = 0;
    }

    //-----------------------------------
    // Allocate data and name for levels
    //-----------------------------------

    AllocateLevels(m_NumberOfLevels);
    
    //------------------------------------------------------
    // Load all the level files detected earlier
    //------------------------------------------------------
    
    bool ErrorOccurred = false;    
    
    for( unsigned int CurrentLevel = 0; CurrentLevel < levelFileNames_short.size(); CurrentLevel++ ) {

        // theLog.WriteLine ("Options         => Loading level file %s...", levelFileNames_full.at(CurrentLevel).c_str() );

        // Open the existing level file for reading
        File = fopen( levelFileNames_full.at(CurrentLevel).c_str(), "rt" );

        // If it failed
        if (File == NULL)
        {
            // Stop loading levels
            break;
        }

        string s;
        ifstream in;
        in.open( levelFileNames_full.at(CurrentLevel).c_str(), ios_base::in );
        getline( in, s );
        int LevelVersion;
        if ( sscanf( s.c_str(), "; Bombermaaan level file version=%d\n", &LevelVersion ) == 0 ) {
            LevelVersion = 1;
        }
        
        switch ( LevelVersion ) {

            case 1:
                if (! LoadLevel_Version1( File, CurrentLevel ) ) {
                    ErrorOccurred = true;
                }
                break;

            case 2:
                if (!LoadLevel_Version2( in, CurrentLevel ) ) {
                    ErrorOccurred = true;
                }
                break;

            default:
                theLog.WriteLine ("Options         => !!! Unsupported version of level file %s.", levelFileNames_short.at(CurrentLevel).c_str());
                ErrorOccurred = true;
                break;

        }

		// Close the level file
        fclose(File);
    
        // If there wasn't any problem
        if (!ErrorOccurred)
        {
            theLog.WriteLine ("Options         => Level file %s was successfully loaded (version %d).", levelFileNames_short.at(CurrentLevel).c_str(), LevelVersion);
        }
        // If there was a problem
        else
        {
            theLog.WriteLine ("Options         => !!! Could not load level file %s (version %d).", levelFileNames_short.at(CurrentLevel).c_str(), LevelVersion);
            // Stop loading levels
            break;
        }

    }


    // If we had to stop then there is a problem.
    if (ErrorOccurred)
        return false;

    // Everything went right
    return true;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool COptions::LoadLevel_Version1( FILE* File, int CurrentLevel ) {

    bool StopReadingFile = false;

    // For each line of characters to read
    for (int y = 0 ; y < ARENA_HEIGHT ; y++)
    {
        // Buffer where we'll store one line of characters. We'll read the two EOL characters as well.
        char Line[ARENA_WIDTH + 1];
    
        // Read one line of characters (including the EOL chars)
        int ReadBytes = fread(Line, sizeof(char), (ARENA_WIDTH + 1), File);

        // Check if all the characters were read and that the two last bytes are EOL characters
        if (ReadBytes < ARENA_WIDTH + 1 || Line[ARENA_WIDTH] != 10)
        {
            // Log there is a problem
            theLog.WriteLine ("Options         => !!! Level file is incorrect (%d, %d, %d).", ReadBytes, Line[ARENA_WIDTH], Line[ARENA_WIDTH + 1]);
        
            // Close the level file
            fclose(File);

            // Stop loading levels
            StopReadingFile = true;
            break;
        }

        // For each character representing a block in this line
        for (int x = 0 ; x < ARENA_WIDTH ; x++)
        {
            // According to the character value, store the corresponding block type in the current position and level
            switch(Line[x])
            {
                case '*' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_HARDWALL;    break;
                case '-' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_RANDOM;      break;
                case ' ' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_FREE;        break;
                case '1' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_WHITEBOMBER; break;
                case '2' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_BLACKBOMBER; break;
                case '3' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_REDBOMBER;   break;
                case '4' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_BLUEBOMBER;  break;
                case '5' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_GREENBOMBER; break;
                case 'R' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_MOVEBOMB_RIGHT; break;
                case 'D' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_MOVEBOMB_DOWN;  break;
                case 'L' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_MOVEBOMB_LEFT;  break;
                case 'U' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_MOVEBOMB_UP;    break;
                default  : 
                {
                    // Log there is a problem
                    theLog.WriteLine ("Options         => !!! Level file is incorrect (unknown character %c).", Line[x]);
                
                    // Close the level file
                    fclose(File);

                    // Stop loading levels
                    StopReadingFile = true;
                    break;
                }
            }
        }

        // If there was a problem
        if (StopReadingFile)
        {
            // Stop reading this level file
            break;
        }
    }

    m_NumberOfItemsInWalls[CurrentLevel][ITEM_BOMB] = INITIAL_ITEMBOMB;
    m_NumberOfItemsInWalls[CurrentLevel][ITEM_FLAME] = INITIAL_ITEMFLAME;
    m_NumberOfItemsInWalls[CurrentLevel][ITEM_KICK] = INITIAL_ITEMKICK;
    m_NumberOfItemsInWalls[CurrentLevel][ITEM_ROLLER] = INITIAL_ITEMROLLER;
    m_NumberOfItemsInWalls[CurrentLevel][ITEM_SKULL] = INITIAL_ITEMSKULL;
    m_NumberOfItemsInWalls[CurrentLevel][ITEM_THROW] = INITIAL_ITEMTHROW;
    m_NumberOfItemsInWalls[CurrentLevel][ITEM_PUNCH] = INITIAL_ITEMPUNCH;
	m_NumberOfItemsInWalls[CurrentLevel][ITEM_REMOTE] = INITIAL_ITEMREMOTE;

    m_InitialBomberSkills[CurrentLevel][ BOMBERSKILL_FLAME ] = INITIAL_FLAMESIZE;
    m_InitialBomberSkills[CurrentLevel][ BOMBERSKILL_BOMBS ] = INITIAL_BOMBS;
    m_InitialBomberSkills[CurrentLevel][ BOMBERSKILL_BOMBITEMS ] = 0;
    m_InitialBomberSkills[CurrentLevel][ BOMBERSKILL_FLAMEITEMS ] = 0;
    m_InitialBomberSkills[CurrentLevel][ BOMBERSKILL_ROLLERITEMS ] = 0;
    m_InitialBomberSkills[CurrentLevel][ BOMBERSKILL_KICKITEMS ] = 0;
    m_InitialBomberSkills[CurrentLevel][ BOMBERSKILL_THROWITEMS ] = 0;
    m_InitialBomberSkills[CurrentLevel][ BOMBERSKILL_PUNCHITEMS ] = 0;
	m_InitialBomberSkills[CurrentLevel][ BOMBERSKILL_REMOTEITEMS ] = 0;


    return !StopReadingFile;

}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool COptions::LoadLevel_Version2( ifstream& file, int CurrentLevel ) {

    string s;
    int value;

    // This line should be the [General] section
    getline( file, s );
    if ( s != "[General]" ) {
        theLog.WriteLine ( "Options         => !!! General section not found in level file." );
        return false;
    }

    // Read the width of the map and check whether it is allowed
    // At the moment the width is fix, but maybe the width can be changed in the future
    getline( file, s );
    if ( sscanf( s.c_str(), "Width=%d\n", &value ) != 1 ) {
        theLog.WriteLine ("Options         => !!! General option is incorrect (%s).", s.c_str() );
        return false;
    }
    if ( value != ARENA_WIDTH ) {
        theLog.WriteLine ("Options         => !!! Invalid arena width %d. Only %d is allowed.", value, ARENA_WIDTH );
        return false;
    }

    // Read the height of the map and check whether it is allowed
    // At the moment the height is fix, but maybe the height can be changed in the future
    getline( file, s );
    if ( sscanf( s.c_str(), "Height=%d\n", &value ) != 1 ) {
        theLog.WriteLine ("Options         => !!! General option is incorrect (%s).", s.c_str() );
        return false;
    }
    if ( value != ARENA_HEIGHT ) {
        theLog.WriteLine ("Options         => !!! Invalid arena height %d. Only %d is allowed.", value, ARENA_HEIGHT );
        return false;
    }

    // Read the maximum number of players allowed with this level
    // At the moment this must be set to 5
    // Maybe this is changed in the future
    getline( file, s );
    if ( sscanf( s.c_str(), "MaxPlayers=%d\n", &value ) != 1 ) {
        theLog.WriteLine ("Options         => !!! General option is incorrect (%s).", s.c_str() );
        return false;
    }
    if ( value != 5 ) {
        theLog.WriteLine ("Options         => !!! Invalid maximum players %d. Only %d is allowed.", value, 5 );
        return false;
    }

    // Read the maximum number of players allowed with this level
    // Currently this must be set to 1, though a game with 1 player is not possible
    // Maybe this is changed in the future
    getline( file, s );
    if ( sscanf( s.c_str(), "MinPlayers=%d\n", &value ) != 1 ) {
        theLog.WriteLine ("Options         => !!! General option is incorrect (%s).", s.c_str() );
        return false;
    }
    if ( value != 1 ) {
        theLog.WriteLine ("Options         => !!! Invalid minimum players %d. Only %d is allowed.", value, 1 );
        return false;
    }

    // Check if there is a line with the creator
    // The creator can be empty, it's not stored anywhere at the moment
    getline( file, s );
    if ( s.find( "Creator=" ) != 0 ) {
        theLog.WriteLine ("Options         => !!! General option is incorrect (%s).", s.c_str() );
        return false;
    }

    // Priority line following
    // The priority setting is not used currently
    // For future use:
    // - The levels are first sorted by priority and then by the file name
    getline( file, s );
    if ( s.find( "Priority=0" ) != 0 ) {
        theLog.WriteLine ("Options         => !!! General option is incorrect (%s) - priority expected.", s.c_str() );
        return false;
    }

    // Comment line following (not used currently)
    getline( file, s );
    if ( s.find( "Comment=" ) != 0 ) {
        theLog.WriteLine ("Options         => !!! General option is incorrect (%s) - comment expected.", s.c_str() );
        return false;
    }

    // Description line following (not used currently)
    getline( file, s );
    if ( s.find( "Description=" ) != 0 ) {
        theLog.WriteLine ("Options         => !!! General option is incorrect (%s) - description expected.", s.c_str() );
        return false;
    }

    // Next line should be the [Map] section
    getline( file, s );
    if ( s != "[Map]" ) {
        theLog.WriteLine ( "Options         => !!! Map section not found in level file" );
        return false;
    }

    // For each line of characters to read
    for (int y = 0 ; y < ARENA_HEIGHT ; y++)
    {
        getline( file, s );

        if ( sscanf( s.c_str(), "Line.%d=%*s\n", &value ) != 1 ) {
            theLog.WriteLine ("Options         => !!! Map option is incorrect (%s).", s.c_str() );
            return false;
        }
        if ( value != y ) {
            theLog.WriteLine ("Options         => !!! Invalid line number %d found. Expected line number %d.", value, y );
            return false;
        }

        int pos = s.find( "=" );
        if ( pos == -1 || pos + ARENA_WIDTH + 1 != s.length() ) {
            theLog.WriteLine ("Options         => !!! Level file is incorrect (%d, %d, %d).", pos, y, s.length() );
            return false;
        }

        // pos points to the next character
        pos++;

        // For each character representing a block in this line
        for (int x = 0 ; x < ARENA_WIDTH ; x++)
        {
            // According to the character value, store the corresponding block type in the current position and level
            switch(s.at(pos+x))
            {
                case '*' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_HARDWALL;    break;
                case '-' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_RANDOM;      break;
                case ' ' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_FREE;        break;
                case '1' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_WHITEBOMBER; break;
                case '2' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_BLACKBOMBER; break;
                case '3' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_REDBOMBER;   break;
                case '4' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_BLUEBOMBER;  break;
                case '5' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_GREENBOMBER; break;
                case 'R' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_MOVEBOMB_RIGHT; break;
                case 'D' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_MOVEBOMB_DOWN;  break;
                case 'L' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_MOVEBOMB_LEFT;  break;
                case 'U' : m_LevelsData[CurrentLevel][x][y] = BLOCKTYPE_MOVEBOMB_UP;    break;
                default  : 
                {
                    // Log there is a problem
                    theLog.WriteLine ("Options         => !!! Level file is incorrect (unknown character %c).", s.at(pos+x) );
                    return false;
                }
            }
        }

    }

    // Next line should be the [Settings] section
    getline( file, s );
    if ( s != "[Settings]" ) {
        theLog.WriteLine ( "Options         => !!! Settings section not found in level file" );
        return false;
    }

    //---------------------
    // Read the ItemsInWalls values
    //---------------------

    getline( file, s );
    if ( sscanf( s.c_str(), "ItemsInWalls.Bombs=%d\n", &m_NumberOfItemsInWalls[CurrentLevel][ITEM_BOMB] ) != 1 ) {
        theLog.WriteLine ("Options         => !!! Items in walls is incorrect (%s).", s.c_str() );
        return false;
    }

    getline( file, s );
    if ( sscanf( s.c_str(), "ItemsInWalls.Flames=%d\n", &m_NumberOfItemsInWalls[CurrentLevel][ITEM_FLAME] ) != 1 ) {
        theLog.WriteLine ("Options         => !!! Items in walls is incorrect (%s).", s.c_str() );
        return false;
    }

    getline( file, s );
    if ( sscanf( s.c_str(), "ItemsInWalls.Kicks=%d\n", &m_NumberOfItemsInWalls[CurrentLevel][ITEM_KICK] ) != 1 ) {
        theLog.WriteLine ("Options         => !!! Items in walls is incorrect (%s).", s.c_str() );
        return false;
    }

    getline( file, s );
    if ( sscanf( s.c_str(), "ItemsInWalls.Rollers=%d\n", &m_NumberOfItemsInWalls[CurrentLevel][ITEM_ROLLER] ) != 1 ) {
        theLog.WriteLine ("Options         => !!! Items in walls is incorrect (%s).", s.c_str() );
        return false;
    }

    getline( file, s );
    if ( sscanf( s.c_str(), "ItemsInWalls.Skulls=%d\n", &m_NumberOfItemsInWalls[CurrentLevel][ITEM_SKULL] ) != 1 ) {
        theLog.WriteLine ("Options         => !!! Items in walls is incorrect (%s).", s.c_str() );
        return false;
    }

    getline( file, s );
    if ( sscanf( s.c_str(), "ItemsInWalls.Throws=%d\n", &m_NumberOfItemsInWalls[CurrentLevel][ITEM_THROW] ) != 1 ) {
        theLog.WriteLine ("Options         => !!! Items in walls is incorrect (%s).", s.c_str() );
        return false;
    }

    getline( file, s );
    if ( sscanf( s.c_str(), "ItemsInWalls.Punches=%d\n", &m_NumberOfItemsInWalls[CurrentLevel][ITEM_PUNCH] ) != 1 ) {
        theLog.WriteLine ("Options         => !!! Items in walls is incorrect (%s).", s.c_str() );
        return false;
    }

    // The remote fuse feature came after Level file version 2, so this must be set hard coded
   	m_NumberOfItemsInWalls[CurrentLevel][ITEM_REMOTE] = INITIAL_ITEMREMOTE;
    
    
    //---------------------
    // Read the BomberSkillsAtStart values
    //---------------------

    getline( file, s );
    if ( sscanf( s.c_str(), "BomberSkillsAtStart.FlameSize=%d\n", &m_InitialBomberSkills[CurrentLevel][ BOMBERSKILL_FLAME ] ) != 1 ) {
        theLog.WriteLine ("Options         => !!! Line BomberSkillsAtStart is incorrect (%s).", s.c_str() );
        return false;
    }

    getline( file, s );
    if ( sscanf( s.c_str(), "BomberSkillsAtStart.MaxBombs=%d\n", &m_InitialBomberSkills[CurrentLevel][ BOMBERSKILL_BOMBS ] ) != 1 ) {
        theLog.WriteLine ("Options         => !!! Line BomberSkillsAtStart is incorrect (%s).", s.c_str() );
        return false;
    }

    getline( file, s );
    if ( sscanf( s.c_str(), "BomberSkillsAtStart.BombItems=%d\n", &m_InitialBomberSkills[CurrentLevel][ BOMBERSKILL_BOMBITEMS ] ) != 1 ) {
        theLog.WriteLine ("Options         => !!! Line BomberSkillsAtStart is incorrect (%s).", s.c_str() );
        return false;
    }

    getline( file, s );
    if ( sscanf( s.c_str(), "BomberSkillsAtStart.FlameItems=%d\n", &m_InitialBomberSkills[CurrentLevel][ BOMBERSKILL_FLAMEITEMS ] ) != 1 ) {
        theLog.WriteLine ("Options         => !!! Line BomberSkillsAtStart is incorrect (%s).", s.c_str() );
        return false;
    }

    getline( file, s );
    if ( sscanf( s.c_str(), "BomberSkillsAtStart.RollerItems=%d\n", &m_InitialBomberSkills[CurrentLevel][ BOMBERSKILL_ROLLERITEMS ] ) != 1 ) {
        theLog.WriteLine ("Options         => !!! Line BomberSkillsAtStart is incorrect (%s).", s.c_str() );
        return false;
    }

    getline( file, s );
    if ( sscanf( s.c_str(), "BomberSkillsAtStart.KickItems=%d\n", &m_InitialBomberSkills[CurrentLevel][ BOMBERSKILL_KICKITEMS ] ) != 1 ) {
        theLog.WriteLine ("Options         => !!! Line BomberSkillsAtStart is incorrect (%s).", s.c_str() );
        return false;
    }

    getline( file, s );
    if ( sscanf( s.c_str(), "BomberSkillsAtStart.ThrowItems=%d\n", &m_InitialBomberSkills[CurrentLevel][ BOMBERSKILL_THROWITEMS ] ) != 1 ) {
        theLog.WriteLine ("Options         => !!! Line BomberSkillsAtStart is incorrect (%s).", s.c_str() );
        return false;
    }

    getline( file, s );
    if ( sscanf( s.c_str(), "BomberSkillsAtStart.PunchItems=%d\n", &m_InitialBomberSkills[CurrentLevel][ BOMBERSKILL_PUNCHITEMS ] ) != 1 ) {
        theLog.WriteLine ("Options         => !!! Line BomberSkillsAtStart is incorrect (%s).", s.c_str() );
        return false;
    }

    // The remote fuse feature came after Level file version 2, so this must be set hard coded
	m_InitialBomberSkills[CurrentLevel][ BOMBERSKILL_REMOTEITEMS ] = 0;
    
    
    //---------------------
    // Read the ContaminationsNotUsed setting
    //---------------------

    // This setting controls which contamination should not be used in this level
    // The only one value allowed is "None" at the moment
    getline( file, s );
    if ( s != "ContaminationsNotUsed=None" ) {
        theLog.WriteLine ("Options         => !!! Line ContaminationsNotUsed is incorrect (%s).", s.c_str() );
        return false;
    }

    // Everything went right
    return true;

}
