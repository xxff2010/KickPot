#define MyAppName "KickPot"
#define MyAppVersion "0.1.0"
#define MyAppPublisher "KickPot"
#define MyAppExeName "KickPot.exe"

[Setup]
AppId={{8B0E3A91-5F44-4B2E-9D70-2B12A4F9C681}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
DefaultDirName={autopf}\KickPot
DefaultGroupName={#MyAppName}
UninstallDisplayIcon={app}\{#MyAppExeName}
ArchitecturesInstallIn64BitMode=x64
ArchitecturesAllowed=x64
PrivilegesRequired=admin
OutputDir=dist
OutputBaseFilename=KickPot-Setup
Compression=lzma2
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "Create a desktop shortcut"; GroupDescription: "Additional shortcuts:"; Flags: unchecked

[Files]
Source: "dist\KickPot\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{group}\KickPot"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\KickPot"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "Launch KickPot"; Flags: postinstall nowait skipifsilent
