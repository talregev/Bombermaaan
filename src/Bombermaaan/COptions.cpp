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

#include "STDAFX.H"
#include "COptions.h"
#include "CInput.h"
#include "CArena.h"
#include <sstream>

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#define TIMESTART_MINUTES   1
#define TIMESTART_SECONDS   0

#define TIMEUP_MINUTES      0
#define TIMEUP_SECONDS      35

#define CONFIGURATION_KEYBOARD_1      0
#define CONFIGURATION_KEYBOARD_2      1
#define CONFIGURATION_KEYBOARD_3      2
#define CONFIGURATION_KEYBOARD_4      3
#define CONFIGURATION_KEYBOARD_5      4
#define CONFIGURATION_JOYSTICK_1      5

// This check ensures we've also set NUMBER_OF_KEYBOARD_CONFIGURATIONS in CInput.h appropriate
#if NUMBER_OF_KEYBOARD_CONFIGURATIONS != CONFIGURATION_JOYSTICK_1
#error "Mismatch between first joystick input and number of keyboard configurations"
#endif

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
    configFileName.append( "config.xml" );
    theLog.WriteLine( "Options         => Name of config file: '%s'.", configFileName.c_str() );
    
    // Set default configuration values before loading the configuration file and overwriting the default
    SetDefaultValues();

    // Load configuration file and overwrite the previously set defaults
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
    int i, j;
    
    //-------------------------------
    // Free all level data and names
    //-------------------------------

    if (m_LevelsData != NULL)
    {
        for (i = 0 ; i < m_NumberOfLevels ; i++)
        {
            for (j = 0 ; j < ARENA_WIDTH ; j++)
                delete [] m_LevelsData[i][j];

            delete [] m_LevelsData[i];
            delete [] m_InitialBomberSkills[i];
            delete [] m_NumberOfItemsInWalls[i];
        }

        delete [] m_LevelsData;
        delete [] m_InitialBomberSkills;
        delete [] m_NumberOfItemsInWalls;
        m_LevelsData = NULL;
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
    // Write the values to the XML based configuration file
    WriteXMLData();
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void COptions::SetDefaultValues(void)
{
    // Time of a match (TimeStart) and when the arena closing begins (TimeUp)
    m_TimeUpMinutes = TIMEUP_MINUTES;
    m_TimeUpSeconds = TIMEUP_SECONDS;
    m_TimeStartMinutes = TIMESTART_MINUTES;
    m_TimeStartSeconds = TIMESTART_SECONDS;

    // Number of matches for a battle
    m_BattleCount = 3;

    // First level file (index=0) is selected
    m_Level = 2;

    // Default display mode is windowed, not full-screen
    m_DisplayMode = DISPLAYMODE_WINDOWED;

    // Set the bomber types
    m_BomberType[0] = BOMBERTYPE_MAN;
    m_BomberType[1] = BOMBERTYPE_MAN;
    m_BomberType[2] = BOMBERTYPE_OFF;
    m_BomberType[3] = BOMBERTYPE_OFF;
    m_BomberType[4] = BOMBERTYPE_OFF;

    // Initialise player inputs
    for (int i = 0 ; i < MAX_PLAYERS ; i++)
        m_PlayerInput[i] = CONFIGURATION_KEYBOARD_1 + i;

    // Set default keyboard keys and joystick buttons
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

    m_Control[CONFIGURATION_KEYBOARD_3][CONTROL_UP]      = KEYBOARD_I;
    m_Control[CONFIGURATION_KEYBOARD_3][CONTROL_DOWN]    = KEYBOARD_K;
    m_Control[CONFIGURATION_KEYBOARD_3][CONTROL_LEFT]    = KEYBOARD_J;
    m_Control[CONFIGURATION_KEYBOARD_3][CONTROL_RIGHT]   = KEYBOARD_L;
    m_Control[CONFIGURATION_KEYBOARD_3][CONTROL_ACTION1] = KEYBOARD_8;
    m_Control[CONFIGURATION_KEYBOARD_3][CONTROL_ACTION2] = KEYBOARD_7;

    m_Control[CONFIGURATION_KEYBOARD_4][CONTROL_UP]      = KEYBOARD_H;
    m_Control[CONFIGURATION_KEYBOARD_4][CONTROL_DOWN]    = KEYBOARD_N;
    m_Control[CONFIGURATION_KEYBOARD_4][CONTROL_LEFT]    = KEYBOARD_B;
    m_Control[CONFIGURATION_KEYBOARD_4][CONTROL_RIGHT]   = KEYBOARD_M;
    m_Control[CONFIGURATION_KEYBOARD_4][CONTROL_ACTION1] = KEYBOARD_5;
    m_Control[CONFIGURATION_KEYBOARD_4][CONTROL_ACTION2] = KEYBOARD_4;

    m_Control[CONFIGURATION_KEYBOARD_5][CONTROL_UP]      = KEYBOARD_UP;
    m_Control[CONFIGURATION_KEYBOARD_5][CONTROL_DOWN]    = KEYBOARD_DOWN;
    m_Control[CONFIGURATION_KEYBOARD_5][CONTROL_LEFT]    = KEYBOARD_LEFT;
    m_Control[CONFIGURATION_KEYBOARD_5][CONTROL_RIGHT]   = KEYBOARD_RIGHT;
    m_Control[CONFIGURATION_KEYBOARD_5][CONTROL_ACTION1] = KEYBOARD_RCONTROL;
    m_Control[CONFIGURATION_KEYBOARD_5][CONTROL_ACTION2] = KEYBOARD_RSHIFT;

    for ( unsigned int i = CONFIGURATION_JOYSTICK_1 ; i < MAX_PLAYER_INPUT ; i++)
    {
        m_Control[i][CONTROL_UP]      = JOYSTICK_UP;
        m_Control[i][CONTROL_DOWN]    = JOYSTICK_DOWN;
        m_Control[i][CONTROL_LEFT]    = JOYSTICK_LEFT;
        m_Control[i][CONTROL_RIGHT]   = JOYSTICK_RIGHT;
        m_Control[i][CONTROL_ACTION1] = JOYSTICK_BUTTON(0);
        m_Control[i][CONTROL_ACTION2] = JOYSTICK_BUTTON(1);
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool COptions::LoadConfiguration (void)
{
    TiXmlDocument configDoc( configFileName );
    
    // Try to load XML file
    if ( configDoc.LoadFile() ) {

        // The file could be loaded successfully
        int tempRevision = 0;
        TiXmlHandle configHandle( &configDoc );
        TiXmlElement *confRevision = configHandle.FirstChild( "Bombermaaan" ).FirstChild( "Configuration" ).FirstChild( "ConfigRevision" ).ToElement();
        if ( confRevision )
            confRevision->QueryIntAttribute( "value", &tempRevision );

        theLog.WriteLine( "Options         => Configuration file was successfully loaded and is at revision %d.", tempRevision );

        ReadIntFromXML( configDoc, "TimeUp", "minutes", &m_TimeUpMinutes );
        ReadIntFromXML( configDoc, "TimeUp", "seconds", &m_TimeUpSeconds );

        ReadIntFromXML( configDoc, "TimeStart", "minutes", &m_TimeStartMinutes );
        ReadIntFromXML( configDoc, "TimeStart", "seconds", &m_TimeStartSeconds );
        
        ReadIntFromXML( configDoc, "BattleCount", "value", &m_BattleCount );
        
        ReadIntFromXML( configDoc, "LevelFileNumber", "value", &m_Level );

        ReadIntFromXML( configDoc, "DisplayMode", "value", (int*) &m_DisplayMode );

        for ( int i = 0; i < MAX_PLAYERS; i++ ) {
            std::ostringstream oss;
            oss << "bomber" << i;
            std::string attributeName = oss.str();
            ReadIntFromXML( configDoc, "BomberTypes", attributeName, (int*) (&m_BomberType[i]) );
            ReadIntFromXML( configDoc, "PlayerInputs", attributeName, (int*) (&m_PlayerInput[i]) );
        }

        //
        // Read the control settings
        // List of input devices (keyboard n, joystick n) -> Control (up, down, ..., action1, action2) -> Key/Button
        //

        // Create a handle to the XML document
        TiXmlHandle handle( &configDoc );

        // Fetch the element
        TiXmlElement *element = handle.FirstChild( "Bombermaaan" ).FirstChild( "Configuration" ).FirstChild( "ControlList" ).FirstChild( "Control" ).ToElement();

        // If the element exists, go on
        if ( element )
        {
            // Loop through all sub-elements of the ControlList node
            for ( ; element; element = element->NextSiblingElement() )
            {
                int id = -1;
                element->QueryIntAttribute( "id", &id );

                // The id must be between 0 and MAX_PLAYER_INPUT
                if ( id < 0 || id >= MAX_PLAYER_INPUT )
                    continue;

                // Read all control values (up, down, left, right, action1, action2)
                for ( unsigned int ctrl = 0; ctrl < NUM_CONTROLS; ctrl++ )
                {
                    int ctrldata = -1;

                    std::ostringstream oss;
                    oss << "control" << ctrl;
                    std::string attributeName = oss.str();

                    element->QueryIntAttribute( attributeName, &ctrldata);

                    // Verify we have read a valid number
                    if ( ctrldata >= 0 )
                    {
                        m_Control[id][ctrl] = ctrldata;
                    }
                }
            }
        }

    } else {

        // The configuration could not be loaded, maybe it doesn't exist
        theLog.WriteLine ("Options         => Configuration file could not be loaded." );

    }

    //! We always return true since it doesn't matter if the configuration file could not be loaded
    // Success
    return true;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void COptions::WriteXMLData()
{
    // Create document
    TiXmlDocument newConfig;
    TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "UTF-8", "" );
    newConfig.LinkEndChild( decl );

    // Root node
    TiXmlElement * root = new TiXmlElement( "Bombermaaan" );
    newConfig.LinkEndChild( root );

    // Comment
    TiXmlComment * comment = new TiXmlComment();
    comment->SetValue(" Configuration settings for the Bombermaaan game (http://bombermaaan.sf.net/) " );
    root->LinkEndChild( comment );

    // Configuration tree node - all options have this node as parent
    TiXmlElement * config = new TiXmlElement( "Configuration" );
    root->LinkEndChild( config );

    //! The revision number is currently 1
    TiXmlElement* configRev = new TiXmlElement( "ConfigRevision" );
    configRev->SetAttribute( "value", 1 );
    config->LinkEndChild( configRev );

    // TimeUp (when will arena close begin)
    TiXmlElement* configTimeUp = new TiXmlElement( "TimeUp" );
    configTimeUp->SetAttribute( "minutes", m_TimeUpMinutes );
    configTimeUp->SetAttribute( "seconds", m_TimeUpSeconds );
    config->LinkEndChild( configTimeUp );

    // TimeStart (the duration of a match)
    TiXmlElement* configTimeStart = new TiXmlElement( "TimeStart" );
    configTimeStart->SetAttribute( "minutes", m_TimeStartMinutes );
    configTimeStart->SetAttribute( "seconds", m_TimeStartSeconds );
    config->LinkEndChild( configTimeStart );

    // BattleCount
    TiXmlElement* configBattleCount = new TiXmlElement( "BattleCount" );
    configBattleCount->SetAttribute( "value", m_BattleCount );
    config->LinkEndChild( configBattleCount );

    // LevelFileNumber
    TiXmlElement* configLevel = new TiXmlElement( "LevelFileNumber" );
    configLevel->SetAttribute( "value", m_Level );
    config->LinkEndChild( configLevel );

    // DisplayMode
    TiXmlElement* configDisplayMode = new TiXmlElement( "DisplayMode" );
    configDisplayMode->SetAttribute( "value", (int) m_DisplayMode );
    config->LinkEndChild( configDisplayMode );

    // BomberTypes
    TiXmlElement* configBomberTypes = new TiXmlElement( "BomberTypes" );
    for ( int i = 0; i < MAX_PLAYERS; i++ ) {
        std::ostringstream oss;
        oss << "bomber" << i;
        std::string attributeName = oss.str();
        configBomberTypes->SetAttribute( attributeName, (int) m_BomberType[i] );
    }
    config->LinkEndChild( configBomberTypes );

    // PlayerInputs
    TiXmlElement* configPlayerInputs = new TiXmlElement( "PlayerInputs" );
    for ( int i = 0; i < MAX_PLAYERS; i++ ) {
        std::ostringstream oss;
        oss << "bomber" << i;
        std::string attributeName = oss.str();
        configPlayerInputs->SetAttribute( attributeName, (int) m_PlayerInput[i] );
    }
    config->LinkEndChild( configPlayerInputs );

    // ControlList
    TiXmlElement* configControlList = new TiXmlElement( "ControlList" );
    for ( unsigned int i = 0; i < MAX_PLAYER_INPUT; i++ )
    {
        TiXmlElement* configControl = new TiXmlElement( "Control" );
        configControl->SetAttribute( "id", i );
        for ( unsigned int ctrl = 0; ctrl < NUM_CONTROLS; ctrl++ )
        {
            std::ostringstream oss;
            oss << "control" << ctrl;
            std::string attributeName = oss.str();
            configControl->SetAttribute( attributeName, (int) m_Control[i][ctrl] );
        }
        configControlList->LinkEndChild( configControl );
    }
    config->LinkEndChild( configControlList );


    //
    // Save file
    //
    bool saveOkay = newConfig.SaveFile( configFileName );

    // Log a message
    theLog.WriteLine( "Options         => Configuration file was %s written.", ( saveOkay ? "successfully" : "not" ) );
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

/**
 *  \brief Read an integer from the XML document structure.
 *  This function reads an attribute of the node /Bombermaaan/Configuration/NAME, where NAME can be specified by configNode.
 *
 *  @param doc          The TinyXML document
 *  @param configNode   The name of the node below /Bombermaaan/Configuration/
 *  @param attrName     The name of the attribute to be read
 *  @param value        Value of the specified attribute
 *  @todo Set first three parameters to const if possible
 */

void COptions::ReadIntFromXML( TiXmlDocument &doc, std::string configNode, std::string attrName, int *value )
{
    // Create a handle to the XML document
    TiXmlHandle handle( &doc );

    // Fetch the element
    TiXmlElement *element = handle.FirstChild( "Bombermaaan" ).FirstChild( "Configuration" ).FirstChild( configNode ).ToElement();

    // If the element exists, read the int value from the specified attribute
    // The value variable stays unchanged if there's no int value
    if ( element )
        element->QueryIntAttribute( attrName, value );
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
    long FindHandle;
    _finddata_t FindData;
    m_NumberOfLevels = 0;

#ifndef WIN32
    // initialise OUR data structure
    FindData.name = NULL;
    FindData.suffix = NULL;
#endif
            
    //-------------------------------------------
    // Set the path where the level files are stored
    // (in the program files folder)
    //-------------------------------------------
    
    std::string levelFilePath_pgmFolder;
    levelFilePath_pgmFolder = pgmFolder;
    if (pgmFolder.length() >= 1)
    {
        char delim = pgmFolder.c_str()[pgmFolder.length()-1];
        if (delim != '\\' && delim != '/')
#ifdef WIN32
            levelFilePath_pgmFolder.append("\\");
#else
            levelFilePath_pgmFolder.append("/");
#endif
    }
#ifdef WIN32
    levelFilePath_pgmFolder.append( "Levels\\" );
#else
    levelFilePath_pgmFolder.append( "Levels/" );
#endif
    
    std::string levelFilePath_pgmFolderMask;
    levelFilePath_pgmFolderMask = levelFilePath_pgmFolder;
    levelFilePath_pgmFolderMask.append( "*.TXT" );

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
#ifdef WIN32
        levelFilePath_dynamicDataFolder.append( "Levels\\" );
#else
        levelFilePath_dynamicDataFolder.append( "Levels/" );
#endif

        std::string levelFilePath_dynamicDataFolderMask;
        levelFilePath_dynamicDataFolderMask = levelFilePath_dynamicDataFolder;
        levelFilePath_dynamicDataFolderMask.append( "*.TXT" );


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

        //theLog.WriteLine ("Options         => Loading level file %s...", levelFileNames_full.at(CurrentLevel).c_str() );

        // Open the existing level file for reading
        ifstream in;
        in.open( levelFileNames_full.at(CurrentLevel).c_str(), ios_base::in );

        // If it failed
        if (!in.is_open())
        {
            theLog.WriteLine ("Options         => Loading level file %s failed.", levelFileNames_full.at(CurrentLevel).c_str() );
            // Stop loading levels
            break;
        }

        string s;
        getline( in, s );
        int LevelVersion;
        if ( sscanf( s.c_str(), "; Bombermaaan level file version=%d\n", &LevelVersion ) == 0 ) {
            LevelVersion = 1;
        }
        
        switch ( LevelVersion ) {

            case 1:
                if (!LoadLevel_Version1( in, CurrentLevel ) ) {
                    ErrorOccurred = true;
                }
                break;

            case 2:
                if (!LoadLevel_Version2( in, CurrentLevel ) ) {
                    ErrorOccurred = true;
                }
                break;

            case 3:
                if (!LoadLevel_Version3( in, CurrentLevel ) ) {
                    ErrorOccurred = true;
                }
                break;
            
            default:
                theLog.WriteLine ("Options         => !!! Unsupported version of level file %s.", levelFileNames_short.at(CurrentLevel).c_str());
                ErrorOccurred = true;
                break;

        }

		// Close the level file
        in.close();
        
        unsigned int sumOfMaxItems;

        // too many items?
        if (!CheckMaxNumberOfItems( CurrentLevel, &sumOfMaxItems ))
        {
            // Log there is a problem
            theLog.WriteLine ("Options         => !!! Level file is incorrect (Too many items: %d of %d allowed).", sumOfMaxItems, MAX_ITEMS);

            // Stop loading levels
            ErrorOccurred = true;
        }

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

bool COptions::LoadLevel_Version1( ifstream& File, int CurrentLevel ) {

    bool StopReadingFile = false;
    filebuf *pbuf = File.rdbuf();
    
    // go to the beginning
    pbuf->pubseekpos (0,ios::in);

    // For each line of characters to read
    for (int y = 0 ; y < ARENA_HEIGHT ; y++)
    {
        // Buffer where we'll store one line of characters. We'll read the two EOL characters as well.
        string Line;
        int ReadBytes;
    
        // Read one line of characters (including the EOL chars)
        if (File.good())
        {
            getline( File, Line );
            ReadBytes = Line.size();
        }
        else
        {
            ReadBytes = 0;
        }

        // Check if all the characters were read
        if (ReadBytes < ARENA_WIDTH)
        {
            // Log there is a problem
            theLog.WriteLine ("Options         => !!! Level file is incorrect (Line: %d, Length: %d).", y+1, ReadBytes);
        
            // Close the level file
            File.close();

            // Stop loading levels
            StopReadingFile = true;
            break;
        }

        // For each character representing a block in this line
        for (int x = 0 ; x < ARENA_WIDTH ; x++)
        {
            // According to the character value, store the corresponding block type in the current position and level
            switch(Line.c_str()[x])
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
                    File.close();

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

bool COptions::LoadLevel_Version2( ifstream& file, int CurrentLevel, bool requireRemoteFuse ) {

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
        if ( pos == -1 || pos + ARENA_WIDTH + 1 != (int)s.length() ) {
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

    // The remote fuse feature came after Level file version 2, so requireRemoteFuse must be true,
    // otherwise hardcode this:
    getline( file, s );
    if (requireRemoteFuse)
    {
        if ( sscanf( s.c_str(), "ItemsInWalls.Remotes=%d\n", &m_NumberOfItemsInWalls[CurrentLevel][ITEM_REMOTE] ) != 1 ) {
            theLog.WriteLine ("Options         => !!! Items in walls is incorrect (%s).", s.c_str() );
            return false;
        }
        getline( file, s );
    }    
    else
    {
   	    m_NumberOfItemsInWalls[CurrentLevel][ITEM_REMOTE] = INITIAL_ITEMREMOTE;
    }
    
    
    //---------------------
    // Read the BomberSkillsAtStart values
    //---------------------
    // note: The getline command supposed to be here is above
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

    // The remote fuse feature came after Level file version 2, so this must be set hard coded if requireRemoteFuse is false
    getline( file, s );
    if (requireRemoteFuse)
    {
        if ( sscanf( s.c_str(), "BomberSkillsAtStart.RemoteItems=%d\n", &m_InitialBomberSkills[CurrentLevel][ BOMBERSKILL_REMOTEITEMS ] ) != 1 ) {
            theLog.WriteLine ("Options         => !!! Line BomberSkillsAtStart is incorrect (%s).", s.c_str() );
            return false;
        }
        getline( file, s );
    }    
    else
    {
   	    m_InitialBomberSkills[CurrentLevel][ BOMBERSKILL_REMOTEITEMS ] = 0;
    }
    
    //---------------------
    // Read the ContaminationsNotUsed setting
    //---------------------

    // This setting controls which contamination should not be used in this level
    // The only one value allowed is "None" at the moment
    // the getline command supposed to be here is above!
    if ( s != "ContaminationsNotUsed=None" ) {
        theLog.WriteLine ("Options         => !!! Line ContaminationsNotUsed is incorrect (%s).", s.c_str() );
        return false;
    }

    // Everything went right
    return true;

}

/**
 * @brief   check if this level does not exceed the maximum possible number of items
 * @param   Level           the number of the level to check
 * @param   sumOfMaxItems   pointer to an integer variable where the sum of max items is counted
 * @return  true if the number of maximum allowed items is not exceeded, false otherwise
 */
bool COptions::CheckMaxNumberOfItems( int Level, unsigned int *sumOfMaxItems )
{
    // check if maximum number of items is not exceeded
    // we do this, because if there is a draw game when many bombers die
    // they all lose their items at the same time.
    *sumOfMaxItems = 0;
    unsigned int i;

    // count items in walls
    for (i = ITEM_NONE + 1; i < NUMBER_OF_ITEMS; i++)
    {
        *sumOfMaxItems += m_NumberOfItemsInWalls[Level][i];
    }

    // count initial bomber skills (note: count the worst case with five players)
    for (i = BOMBERSKILL_DUMMYFIRST + 1; i < NUMBER_OF_BOMBERSKILLS; i++)
    {
        // initial skills like bombs and flames will not be lost
        if (i != BOMBERSKILL_FLAME && i != BOMBERSKILL_BOMBS)
            *sumOfMaxItems += m_InitialBomberSkills[Level][i] * MAX_PLAYERS;
    }
        
    if (*sumOfMaxItems > MAX_ITEMS)
        return false;
    else
        return true;
}
