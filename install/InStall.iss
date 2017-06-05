; �ű��� Inno Setup �ű��� ���ɣ�
; �йش��� Inno Setup �ű��ļ�����ϸ��������İ����ĵ���

[Setup]
; ע��: AppId ֵ����Ψһʶ���Ӧ�ó���
; ��ֹ������Ӧ�ó���İ�װ��ʹ����ͬ�� AppId ֵ��
; (��Ҫ����һ���µ� GUID����ѡ�񡰹��� | ���� GUID����)
#define AppName "chilli"
#define AppVersion "1.0.0.3"
AppId={{5B303E75-D8B9-4A49-B064-EA2E3FB50ED7}}
AppName={#AppName}
AppVersion={#AppVersion}
AppCopyright=Copyright (C) Inc.
AppComments=""
VersionInfoVersion={#AppVersion}
VersionInfoDescription={#AppName}��װ��
AppPublisher=""
DefaultDirName={pf32}\{#AppName}
DefaultGroupName={#AppName}
AllowNoIcons=yes
AlwaysShowDirOnReadyPage=yes
AlwaysShowGroupOnReadyPage=yes
DisableWelcomePage=no
OutputDir=.\
OutputBaseFilename={#AppName}.{#AppVersion}
Compression=lzma2/ultra
SolidCompression=yes
PrivilegesRequired=admin

ArchitecturesInstallIn64BitMode=x64 ia64

[Languages]
Name: "chinese"; MessagesFile: "ChineseSimplified.isl"

[Tasks]
;Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
;Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
;Source: "..\bin\CloopenAgent.htm"; DestDir: "{app}"; Flags: ignoreversion 32bit
Source: "..\Win32\bin.Release\conf\*.xml"; DestDir: "{app}\conf\"; Flags: ignoreversion restartreplace uninsrestartdelete 32bit
Source: "..\Win32\bin.Release\conf\*.js"; DestDir: "{app}\conf\"; Flags: ignoreversion restartreplace uninsrestartdelete 32bit
Source: "..\Win32\bin.Release\*.dll"; DestDir: "{app}"; Flags: ignoreversion restartreplace uninsrestartdelete 32bit
Source: "..\Win32\bin.Release\chilli.exe"; DestDir: "{app}"; Flags: replacesameversion restartreplace uninsrestartdelete 32bit 
Source: "..\Win32\bin.Release\conf\log4cplus.properties"; DestDir: "{app}\conf\"; Flags: ignoreversion restartreplace uninsrestartdelete 32bit 

; ע��: ��Ҫ���κι���ϵͳ�ļ���ʹ�á�Flags: ignoreversion��

[Icons]Name: "{group}\chilli"; Filename: "{app}\chilli.exe"
Name: "{group}\{cm:UninstallProgram,{#AppName}}"; Filename: "{uninstallexe}"
;Name: "{commondesktop}\CloopenClientPlugin"; Filename: "{app}\ClientPlugin.htm"; Tasks: desktopicon
;Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\CloopenClientPlugin"; Filename: "{app}\ClientPlugin.htm"; Tasks: quicklaunchicon


[UninstallDelete]
Type:filesandordirs;Name:{app};
Type:dirifempty;Name:{pf32}\{#AppName};
Type:dirifempty;Name:{group};

[Registry]
;Root: HKLM; Subkey: "SOFTWARE\Samwoo\AA\TIP"; ValueType: string; ValueName: "ConnectionString"; ValueData:"Provider=SQLOLEDB.1;Password=sa;Persist Security Info=True;User ID=sa;Initial Catalog=TF_CMS;Data Source=10.1.86.129"; Flags:createvalueifdoesntexist    uninsdeletekey

