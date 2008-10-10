; Bombermaaan Installation Script
; Written by Bernd Arnold, 2008-07-05
;
; http://bombermaaan.sourceforge.net/
;

; The APPID is kept as long as the first two numbers in the version are the same
; (the whole 1.3 version uses the same APPID)
; (yes, two opening curly braces and only one closing curly brace)
#define APPID "{{577ACC96-0D1D-4AA1-BFCC-DA0630FA24B0}"       <------------ Needs to be changed for version 1.4!

#define MAJOR 1
#define MINOR 4
#define RELEASE 0
#define BUILD 476       <------------ Needs to be changed for version 1.4!
#define BUILDDATE "20081011"       <------------ Needs to be changed for version 1.4!

#define APPVERFULL Str(MAJOR) + "." + Str(MINOR) + "." + Str(RELEASE) + "." + Str(BUILD)
#define APPVERMAIN Str(MAJOR) + "." + Str(MINOR)

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={#APPID}
AppName=Bombermaaan
AppVerName=Bombermaaan {#APPVERMAIN}
AppPublisher=The Bombermaaan team
AppPublisherURL=http://bombermaaan.sourceforge.net/
AppSupportURL=http://bombermaaan.sourceforge.net/
AppUpdatesURL=http://bombermaaan.sourceforge.net/
DefaultDirName={pf}\Bombermaaan {#APPVERMAIN}
DefaultGroupName=Bombermaaan {#APPVERMAIN}
AllowNoIcons=true
LicenseFile=..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\COPYING.txt
OutputDir=.\output
OutputBaseFilename=Bombermaaan_{#APPVERFULL}_setup
Compression=lzma
SolidCompression=true
VersionInfoVersion={#APPVERFULL}
VersionInfoDescription=Installer for Bombermaaan
VersionInfoCopyright=Copyright (C) 2000-2002, 2007, 2008 Thibaut Tollemer, Bernd Arnold, Jerome Bigot, Markus Drescher
WizardImageFile=compiler:wizmodernimage-is.bmp
; This is not the best image since the setup dialog shows only square, not a rectangle
WizardSmallImageFile=HeaderImage_Innosetup.bmp
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
Source: ..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\Bombermaaan_32.exe; DestDir: {app}; Flags: ignoreversion
Source: ..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\Bombermaaan.dll; DestDir: {app}; Flags: ignoreversion
Source: ..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\Bombermaaan_16.exe; DestDir: {app}; Flags: ignoreversion
Source: ..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\Bombermaaan_32.dll; DestDir: {app}; Flags: ignoreversion
Source: ..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\Bombermaaan_32.exe; DestDir: {app}; Flags: ignoreversion
Source: ..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\CHANGELOG.txt; DestDir: {app}; Flags: ignoreversion
Source: ..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\COPYING.txt; DestDir: {app}; Flags: ignoreversion
Source: ..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\Readme.html; DestDir: {app}; Flags: ignoreversion
Source: ..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\libogg-0.dll; DestDir: {app}; Flags: ignoreversion
Source: ..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\libvorbis-0.dll; DestDir: {app}; Flags: ignoreversion
Source: ..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\libvorbisfile-3.dll; DestDir: {app}; Flags: ignoreversion
Source: ..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\SDL.dll; DestDir: {app}; Flags: ignoreversion
Source: ..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\SDL_mixer.dll; DestDir: {app}; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files
Source: ..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\Levels\L1.TXT; DestDir: {app}\Levels\
Source: ..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\Levels\L2.TXT; DestDir: {app}\Levels\
Source: ..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\Levels\L3.TXT; DestDir: {app}\Levels\
Source: ..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\Levels\L4.TXT; DestDir: {app}\Levels\
Source: ..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\Levels\L5.TXT; DestDir: {app}\Levels\
Source: ..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\Levels\L6.TXT; DestDir: {app}\Levels\
Source: ..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\Levels\L7.TXT; DestDir: {app}\Levels\
Source: ..\tools\output\Bombermaaan_{#APPVERFULL}_{#BUILDDATE}_win32\Levels\L8.TXT; DestDir: {app}\Levels\

[Icons]
Name: {group}\Bombermaaan (large size); Filename: {app}\Bombermaaan_32.exe; WorkingDir: {app}; Comment: Runs Bombermaaan in a large window; IconIndex: 0; Languages: english spanish slovenian slovak russian portuguese polish norwegian italian hungarian hebrew french finnish dutch danish czech catalan brazilianportuguese basque; Parameters: --use-appdata-dir
Name: {group}\Bombermaaan (großes Fenster); Filename: {app}\Bombermaaan_32.exe; WorkingDir: {app}; Comment: Startet Bombermaaan in einem großen Fenster; IconIndex: 0; Tasks: ; Languages: german; Parameters: --use-appdata-dir
Name: {group}\Bombermaaan (classic); Filename: {app}\Bombermaaan_16.exe; WorkingDir: {app}; Comment: Runs Bombermaaan in a small window (classic style); IconIndex: 0; Languages: english spanish slovenian slovak russian portuguese polish norwegian italian hungarian hebrew french finnish dutch danish czech catalan brazilianportuguese basque; Parameters: --use-appdata-dir
Name: {group}\Bombermaaan (klassisch); Filename: {app}\Bombermaaan_16.exe; WorkingDir: {app}; Comment: Startet Bombermaaan in einem kleinen Fenster (die klassische Variante); IconIndex: 0; Languages: german; Parameters: --use-appdata-dir
Name: {group}\Readme; Filename: {app}\Readme.html; Comment: Opens the HTML readme; Languages: english spanish slovenian slovak russian portuguese polish norwegian italian hungarian hebrew french finnish dutch danish czech catalan brazilianportuguese basque
Name: {group}\Liesmich; Filename: {app}\Readme.html; Comment: Öffnet die Liesmich-Datei (Readme) in einem Webbrowser (derzeit nur auf Englisch); Languages: german
Name: {group}\License (GPL); Filename: {app}\COPYING.txt; Comment: Open the license file (Bombermaaan is licensed under the GNU General Public License); Languages: english spanish slovenian slovak russian portuguese polish norwegian italian hungarian hebrew french finnish dutch danish czech catalan brazilianportuguese basque
Name: {group}\Lizenz (GPL); Filename: {app}\COPYING.txt; Comment: Öffnet die Lizenzdatei (Bombermaaan wird unter der GNU General Public License lizenziert); Languages: german
Name: {group}\{cm:ProgramOnTheWeb,Bombermaaan}; Filename: http://bombermaaan.sourceforge.net/
Name: {group}\{cm:UninstallProgram,Bombermaaan}; Filename: {uninstallexe}
Name: {commondesktop}\Bombermaaan; Filename: {app}\Bombermaaan_32.exe; Tasks: desktopicon; Parameters: --use-appdata-dir
Name: {userappdata}\Microsoft\Internet Explorer\Quick Launch\Bombermaaan; Filename: {app}\Bombermaaan_32.exe; Tasks: quicklaunchicon

[Run]
Filename: {app}\Bombermaaan_32.exe; Description: {cm:LaunchProgram,Bombermaaan}; Flags: nowait postinstall skipifsilent unchecked; Parameters: --use-appdata-dir

[Dirs]
Name: {app}\Levels

[Registry]
Root: HKLM; Subkey: Software\Bombermaaan\Version {#APPVERMAIN}; ValueType: string; ValueName: InstallDirectory; ValueData: {app}\; Flags: uninsdeletekey; Tasks: ; Languages: 
; The data of the following three registry keys is updated for every update of version 1.3 - so it reflects the latest update of version 1.3
Root: HKLM; Subkey: Software\Bombermaaan\Version {#APPVERMAIN}; ValueType: string; ValueName: Version; ValueData: {#APPVERFULL}; Flags: uninsdeletekey; Tasks: ; Languages: 
Root: HKLM; Subkey: Software\Bombermaaan\Version {#APPVERMAIN}; ValueType: string; ValueName: Build; ValueData: {#BUILD}; Flags: uninsdeletekey; Tasks: ; Languages: 
Root: HKLM; Subkey: Software\Bombermaaan\Version {#APPVERMAIN}; ValueType: string; ValueName: Builddate; ValueData: {#BUILDDATE}; Flags: uninsdeletekey; Tasks: ; Languages: 

[Code]
function InitializeSetup(): Boolean;
var
	InstalledInPath: String;
begin
	Result := true;
	InstalledInPath := '';

	RegQueryStringValue( HKLM,
	                     'Software\Microsoft\Windows\CurrentVersion\Uninstall\' + ExpandConstant( '{#APPID}' ) + '_is1',
	                     'Inno Setup: App Path',
	                     InstalledInPath );

	if InstalledInPath <> '' then begin
		MsgBox( 'Bombermaaan is already installed in ' + #13 +
		        InstalledInPath + '.' + #13#13 +
		        'Please uninstall Bombermaaan first. Sorry for the inconvenience - I hope this is not necessary in the future. Setup aborted.',
				mbError, MB_OK
				);
		Result := false;
	end
end;
