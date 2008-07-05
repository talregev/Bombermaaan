; Bombermaaan Installation Script
; Written by Bernd Arnold, 2008-07-05
;
; http://bombermaaan.sourceforge.net/
; 

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{577ACC96-0D1D-4AA1-BFCC-DA0630FA24B0}
AppName=Bombermaaan
AppVerName=Bombermaaan 1.3
AppPublisher=The Bombermaaan team
AppPublisherURL=http://bombermaaan.sourceforge.net/
AppSupportURL=http://bombermaaan.sourceforge.net/
AppUpdatesURL=http://bombermaaan.sourceforge.net/
DefaultDirName={pf}\Bombermaaan 1.3
DefaultGroupName=Bombermaaan 1.3
AllowNoIcons=true
LicenseFile=.\packages\Bombermaaan_1.3_2008-05-07\COPYING.txt
OutputDir=.\output
OutputBaseFilename=Bombermaaan_1.3.0.423_setup
Compression=lzma
SolidCompression=true
VersionInfoVersion=1.3.0.423
VersionInfoDescription=Installer for Bombermaaan
VersionInfoCopyright=Copyright (C) Thibaut Tollemer, Bernd Arnold
WizardImageFile=compiler:wizmodernimage-is.bmp
; This is not the best image since the setup dialog shows only square, not a rectangle
WizardSmallImageFile=HeaderImage.bmp
WizardImageStretch=false

[Languages]
Name: english; MessagesFile: compiler:Default.isl
Name: basque; MessagesFile: compiler:Languages\Basque.isl
Name: brazilianportuguese; MessagesFile: compiler:Languages\BrazilianPortuguese.isl
Name: catalan; MessagesFile: compiler:Languages\Catalan.isl
Name: czech; MessagesFile: compiler:Languages\Czech.isl
Name: danish; MessagesFile: compiler:Languages\Danish.isl
Name: dutch; MessagesFile: compiler:Languages\Dutch.isl
Name: finnish; MessagesFile: compiler:Languages\Finnish.isl
Name: french; MessagesFile: compiler:Languages\French.isl
Name: german; MessagesFile: compiler:Languages\German.isl
Name: hebrew; MessagesFile: compiler:Languages\Hebrew.isl
Name: hungarian; MessagesFile: compiler:Languages\Hungarian.isl
Name: italian; MessagesFile: compiler:Languages\Italian.isl
Name: norwegian; MessagesFile: compiler:Languages\Norwegian.isl
Name: polish; MessagesFile: compiler:Languages\Polish.isl
Name: portuguese; MessagesFile: compiler:Languages\Portuguese.isl
Name: russian; MessagesFile: compiler:Languages\Russian.isl
Name: slovak; MessagesFile: compiler:Languages\Slovak.isl
Name: slovenian; MessagesFile: compiler:Languages\Slovenian.isl
Name: spanish; MessagesFile: compiler:Languages\Spanish.isl

[Tasks]
Name: desktopicon; Description: {cm:CreateDesktopIcon}; GroupDescription: {cm:AdditionalIcons}; Flags: unchecked
Name: quicklaunchicon; Description: {cm:CreateQuickLaunchIcon}; GroupDescription: {cm:AdditionalIcons}; Flags: unchecked

[Files]
Source: .\packages\Bombermaaan_1.3_2008-05-07\Bombermaaan_32.exe; DestDir: {app}; Flags: ignoreversion
Source: .\packages\Bombermaaan_1.3_2008-05-07\Bombermaaan.dll; DestDir: {app}; Flags: ignoreversion
Source: .\packages\Bombermaaan_1.3_2008-05-07\Bombermaaan_16.exe; DestDir: {app}; Flags: ignoreversion
Source: .\packages\Bombermaaan_1.3_2008-05-07\Bombermaaan_32.dll; DestDir: {app}; Flags: ignoreversion
Source: .\packages\Bombermaaan_1.3_2008-05-07\Bombermaaan_32.exe; DestDir: {app}; Flags: ignoreversion
Source: .\packages\Bombermaaan_1.3_2008-05-07\CHANGELOG.txt; DestDir: {app}; Flags: ignoreversion
Source: .\packages\Bombermaaan_1.3_2008-05-07\COPYING.txt; DestDir: {app}; Flags: ignoreversion
Source: .\packages\Bombermaaan_1.3_2008-05-07\FMOD.DLL; DestDir: {app}; Flags: ignoreversion
Source: .\packages\Bombermaaan_1.3_2008-05-07\Readme.html; DestDir: {app}; Flags: ignoreversion; Tasks: ; Languages: 
; NOTE: Don't use "Flags: ignoreversion" on any shared system files
Source: .\packages\Bombermaaan_1.3_2008-05-07\Levels\L1.TXT; DestDir: {app}\Levels\
Source: .\packages\Bombermaaan_1.3_2008-05-07\Levels\L2.TXT; DestDir: {app}\Levels\
Source: .\packages\Bombermaaan_1.3_2008-05-07\Levels\L3.TXT; DestDir: {app}\Levels\
Source: .\packages\Bombermaaan_1.3_2008-05-07\Levels\L4.TXT; DestDir: {app}\Levels\
Source: .\packages\Bombermaaan_1.3_2008-05-07\Levels\L5.TXT; DestDir: {app}\Levels\
Source: .\packages\Bombermaaan_1.3_2008-05-07\Levels\L6.TXT; DestDir: {app}\Levels\
Source: .\packages\Bombermaaan_1.3_2008-05-07\Levels\L7.TXT; DestDir: {app}\Levels\
Source: .\packages\Bombermaaan_1.3_2008-05-07\Levels\L8.TXT; DestDir: {app}\Levels\

[Icons]
Name: {group}\Bombermaaan (large size); Filename: {app}\Bombermaaan_32.exe; WorkingDir: {app}; Comment: Runs Bombermaaan in a large window; IconIndex: 0; Languages: english spanish slovenian slovak russian portuguese polish norwegian italian hungarian hebrew french finnish dutch danish czech catalan brazilianportuguese basque
Name: {group}\Bombermaaan (groﬂes Fenster); Filename: {app}\Bombermaaan_32.exe; WorkingDir: {app}; Comment: Startet Bombermaaan in einem groﬂen Fenster; IconIndex: 0; Tasks: ; Languages: german
Name: {group}\Bombermaaan (classic); Filename: {app}\Bombermaaan_16.exe; WorkingDir: {app}; Comment: Runs Bombermaaan in a small window (classic style); IconIndex: 0; Languages: english spanish slovenian slovak russian portuguese polish norwegian italian hungarian hebrew french finnish dutch danish czech catalan brazilianportuguese basque
Name: {group}\Bombermaaan (klassisch); Filename: {app}\Bombermaaan_16.exe; WorkingDir: {app}; Comment: Startet Bombermaaan in einem kleinen Fenster (die klassische Variante); IconIndex: 0; Languages: german
Name: {group}\Readme; Filename: {app}\Readme.html; Comment: Opens the HTML readme; Languages: english spanish slovenian slovak russian portuguese polish norwegian italian hungarian hebrew french finnish dutch danish czech catalan brazilianportuguese basque
Name: {group}\Liesmich; Filename: {app}\Readme.html; Comment: ÷ffnet die Liesmich-Datei (Readme) in einem Webbrowser (derzeit nur auf Englisch); Languages: german
Name: {group}\License (GPL); Filename: {app}\COPYING.txt; Comment: Open the license file (Bombermaaan is licensed under the GNU General Public License); Languages: english spanish slovenian slovak russian portuguese polish norwegian italian hungarian hebrew french finnish dutch danish czech catalan brazilianportuguese basque
Name: {group}\Lizenz (GPL); Filename: {app}\COPYING.txt; Comment: ÷ffnet die Lizenzdatei (Bombermaaan wird unter der GNU General Public License lizenziert); Languages: german
Name: {group}\{cm:ProgramOnTheWeb,Bombermaaan}; Filename: http://bombermaaan.sourceforge.net/
Name: {group}\{cm:UninstallProgram,Bombermaaan}; Filename: {uninstallexe}
Name: {commondesktop}\Bombermaaan; Filename: {app}\Bombermaaan_32.exe; Tasks: desktopicon
Name: {userappdata}\Microsoft\Internet Explorer\Quick Launch\Bombermaaan; Filename: {app}\Bombermaaan_32.exe; Tasks: quicklaunchicon

[Run]
Filename: {app}\Bombermaaan_32.exe; Description: {cm:LaunchProgram,Bombermaaan}; Flags: nowait postinstall skipifsilent unchecked

[Dirs]
Name: {app}\Levels
[Registry]
Root: HKLM; Subkey: Software\Bombermaaan\Build 423; ValueType: string; ValueName: InstallDirectory; ValueData: {app}\; Flags: uninsdeletekey; Tasks: ; Languages: 
Root: HKLM; Subkey: Software\Bombermaaan\Build 423; ValueType: string; ValueName: Version; ValueData: 1.3.0.423; Flags: uninsdeletekey; Tasks: ; Languages: 
