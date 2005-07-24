; This script is based on example2.nsi

;--------------------------------

; The name of the installer
Name "OpenArena"

;  The installer icon
Icon "${NSISDIR}\Contrib\Graphics\Icons\modern-install-blue-full.ico"

;  The uninstaller icon
UninstallIcon "${NSISDIR}\Contrib\Graphics\Icons\modern-install-blue-full.ico"


; The file to write
OutFile "OpenArena-0.1.2-alpha.exe"

; The default installation directory
InstallDir "$PROGRAMFILES\HHPS\OpenArena-0.1.2-alpha"

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM SOFTWARE\HHPS\OpenArena-0.1.2-alpha "Install_Dir"

; The text to prompt the user to enter a directory
ComponentText "This will install OpenArena on your computer. Select which options you want installed."

; The text to prompt the user to enter a directory
DirText "Choose a directory to install in to:"

;--------------------------------

; Main section docs and libs
Section - "Base (required)"

  SectionIn RO
  
  ;Dynamic libraries
  CreateDirectory $INSTDIR
  SetOutPath $INSTDIR
  File ".\OpenArena\bass.dll"
  WriteUninstaller "uninstall.exe"
  
  ;Documentation
  CreateDirectory "$INSTDIR\doc"
  SetOutPath "$INSTDIR\doc"
  File ".\doc\*.doc"
  File ".\doc\*.html"
    
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\HHPS\OpenArena-0.1.2-alpha "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\OpenArena v0.1.2-alpha" "DisplayName" "OpenArena v0.1.2-alpha (remove only)"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\OpenArena v0.1.2-alpha" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteUninstaller "uninstall.exe"
  CreateDirectory "$SMPROGRAMS\HHPS\OpenArena"
  SetOutPath $INSTDIR\OpenArena
  CreateShortCut "$SMPROGRAMS\HHPS\OpenArena\Readme v0.1.2-alpha.lnk" "$INSTDIR\doc\OpenArena User's Manual.html"

SectionEnd

; Source Files required to create and compile a game using the OpenArena SDK
Section "SDK"

	CreateDirectory "$INSTDIR\sources"
  SetOutPath "$INSTDIR\sources"
  File ".\*.txt"
  File ".\*.nsi"
  File ".\oa.*"
  File ".*"
  File "Makefile"
 
  CreateDirectory "$INSTDIR\sources\lib"
  SetOutPath "$INSTDIR\sources\lib"
  File ".\lib\bass.lib"
  
  CreateDirectory "$INSTDIR\sources\include"
  SetOutPath "$INSTDIR\sources\include"
  File ".\include\*.h"
  
  CreateDirectory "$INSTDIR\sources\src"
  SetOutPath "$INSTDIR\sources\src"
  File ".\src\*.cpp"
  File ".\Makefile"
  
  CreateDirectory "$INSTDIR\sources\OpenArena"
  SetOutPath "$INSTDIR\sources\OpenArena"
  File ".\OpenArena\bass.dll"
  
  CreateDirectory "$INSTDIR\sources\OpenArena\oa"
  CreateDirectory "$INSTDIR\sources\OpenArena\oa\config"
  SetOutPath "$INSTDIR\sources\OpenArena\oa\config"
  File ".\OpenArena\oa\config\my.cfg"
  
  CreateDirectory "$INSTDIR\sources\OpenArena\oa\maps"
  SetOutPath "$INSTDIR\sources\OpenArena\oa\maps"
  File ".\OpenArena\oa\maps\intro.map"
  
  CreateDirectory "$INSTDIR\sources\OpenArena\oa\music\bgm"
  ;SetOutPath "$INSTDIR\sources\OpenArena\oa\music\bgm"
  ;File ".\OpenArena\oa\music\bgm\*.mp3"
  
  CreateDirectory "$INSTDIR\sources\OpenArena\oa\textures"
  SetOutPath "$INSTDIR\sources\OpenArena\oa\textures"
  File ".\OpenArena\oa\textures\*.bmp"
  File ".\OpenArena\oa\textures\*.tga"
  CreateDirectory "$INSTDIR\sources\OpenArena\oa\textures\menu"
  SetOutPath "$INSTDIR\sources\OpenArena\oa\textures\menu"
  File ".\OpenArena\oa\textures\menu\*.bmp"
  File ".\OpenArena\oa\textures\menu\*.tga"
  
  CreateDirectory "$INSTDIR\sources\ModelConverter"
  SetOutPath "$INSTDIR\sources\ModelConverter"
  File ".\ModelConverter\*.cs"
  File ".\ModelConverter\*.ico"
  File ".\ModelConverter\*.csproj"
  File ".\ModelConverter\*.csproj.user"
  
  CreateShortCut "$SMPROGRAMS\HHPS\OpenArena\OpenArena SDK v0.1.2-alpha.lnk" "$INSTDIR\sources\oa.sln"
  
SectionEnd

Section "Media"

	CreateDirectory "$INSTDIR"
  SetOutPath "$INSTDIR"
  File ".\OpenArena\oa.exe"
  
  CreateDirectory "$INSTDIR\oa"
  CreateDirectory "$INSTDIR\oa\config"
  SetOutPath "$INSTDIR\oa\config"
  File ".\OpenArena\oa\config\my.cfg"
  
  CreateDirectory "$INSTDIR\oa\maps"
  SetOutPath $INSTDIR\oa\maps
  File ".\OpenArena\oa\maps\intro.map"
  File ".\OpenArena\oa\maps\oamap1.map"
  
  CreateDirectory "$INSTDIR\oa\music"
  CreateDirectory "$INSTDIR\oa\music\bgm"
  SetOutPath $INSTDIR\oa\music\bgm
  File ".\OpenArena\oa\music\bgm\*.mp3"
  
  CreateDirectory "$INSTDIR\oa\textures"
  SetOutPath $INSTDIR\oa\textures
  File ".\OpenArena\oa\textures\*.tga"
  File ".\OpenArena\oa\textures\*.bmp"
  
  CreateDirectory "$INSTDIR\oa\textures\menu"
  SetOutPath $INSTDIR\oa\textures\menu
  File ".\OpenArena\oa\textures\menu\*.bmp"
  File ".\OpenArena\oa\textures\menu\*.tga"

  SetOutPath $INSTDIR
  CreateShortCut "$SMPROGRAMS\HHPS\OpenArena\OpenArena v0.1.2-alpha.lnk" "$INSTDIR\oa.exe"

SectionEnd

;--------------------------------
; Uninstaller

UninstallText "This will uninstall OpenArena. Hit next to continue."
; Uninstall section

Section "Uninstall"
  
  ; remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\OpenArena v0.1.2-alpha"
  DeleteRegKey HKLM SOFTWARE\HHPS\OpenArena-0.1.2-alpha

  ; remove files and uninstaller
  Delete /REBOOTOK "$INSTDIR\oa"
  Delete /REBOOTOK "$INSTDIR\sources"
  Delete /REBOOTOK "$INSTDIR\doc"
  Delete /REBOOTOK "$INSTDIR\*.exe"
  Delete /REBOOTOK "$INSTDIR\*.dll"
  
  ;Delete /REBOOTOK $INSTDIR\lib\*
  ;Delete /REBOOTOK $INSTDIR\src\*.*
  ;Delete /REBOOTOK $INSTDIR\bass.dll
  ;Delete /REBOOTOK $INSTDIR\heading.txt
  ;Delete /REBOOTOK $INSTDIR\license.txt
  ;Delete /REBOOTOK $INSTDIR\oa.ncb
  ;Delete /REBOOTOK $INSTDIR\oa.sln
  ;Delete /REBOOTOK $INSTDIR\oa.sou
  ;Delete /REBOOTOK $INSTDIR\oa.vcproj
  ;Delete /REBOOTOK "$INSTDIR\OpenArena User's Manual.doc"
  ;Delete /REBOOTOK "$INSTDIR\OpenArena User's Manual.html"
  
  Delete /REBOOTOK $INSTDIR\uninstall.exe

  ; remove shortcuts, if any
  Delete /REBOOTOK "$SMPROGRAMS\HHPS\OpenArena\Readme v0.1.2-alpha.lnk"
  Delete /REBOOTOK "$SMPROGRAMS\HHPS\OpenArena\OpenArena SDK v0.1.2-alpha.lnk"
  Delete /REBOOTOK "$SMPROGRAMS\HHPS\OpenArena\OpenArena v0.1.2-alpha.lnk"

  ; remove directories used
  RMDIR /r $INSTDIR\include
  RMDIR /r $INSTDIR\lib
  RMDIR /r $INSTDIR\OpenArena
  RMDIR /r $INSTDIR\src
  RMDIR /r "$INSTDIR"

SectionEnd