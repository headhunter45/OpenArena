; example2.nsi
;
; This script is based on example1.nsi, but it remember the directory, 
; has uninstall support and (optionally) installs start menu shortcuts.
;
; It will install makensisw.exe into a directory that the user selects,

;--------------------------------

; The name of the installer
Name "OpenArena"

;  The installer icon
Icon "${NSISDIR}\contrib\Icons\setup.ico"

; The file to write
OutFile "OpenArena-0.1.0-alpha.exe"

; The default installation directory
InstallDir "$PROGRAMFILES\HHPS\OpenArena-0.1.0-alpha"

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM SOFTWARE\HHPS\OpenArena-0.1.0-alpha "Install_Dir"

; The text to prompt the user to enter a directory
ComponentText "This will install OpenArena on your computer. Select which options you want installed."

; The text to prompt the user to enter a directory
DirText "Choose a directory to install in to:"

;--------------------------------

; The stuff to install
Section "Base (required)"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File ".\bass.dll"
  File ".\license.txt"
  File ".\OpenArena User's Manual.doc"
  File ".\OpenArena User's Manual.html"
  SetOutPath $INSTDIR\OpenArena
  File ".\bass.dll"
  
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\HHPS\OpenArena-0.1.0-alpha "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\OpenArena v0.1.0-alpha" "DisplayName" "OpenArena v0.1.0-alpha (remove only)"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\OpenArena v0.1.0-alpha" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteUninstaller "uninstall.exe"
  CreateDirectory "$SMPROGRAMS\HHPS\OpenArena"
  SetOutPath $INSTDIR\OpenArena
  CreateShortCut "$SMPROGRAMS\HHPS\OpenArena\Readme v0.1.0-alpha.lnk" "$INSTDIR\OpenArena User's Manual.html"

  
SectionEnd

; optional section (can be disabled by the user)
Section "SDK"

  SetOutPath $INSTDIR
  File ".\oa.sln"
  File ".\oa.vcproj"
  File ".\oa.ncb"
  File ".\oa.suo"
  File ".\heading.txt"
  SetOutPath $INSTDIR\include
  File ".\include\*.h"
  SetOutPath $INSTDIR\lib
  File ".\lib\*.lib"
  SetOutPath $INSTDIR\src
  File ".\src\*.cpp"
  SetOutPath $INSTDIR\OpenArena\oa\config
  File ".\OpenArena\oa\config\my.cfg"
  CreateDirectory $INSTDIR\OpenArena\oa\maps
  CreateDirectory $INSTDIR\OpenArena\oa\music\bgm
  CreateDirectory $INSTDIR\OpenArena\oa\textures\menu
  SetOutPath $INSTDIR\OpenArena

  CreateShortCut "$SMPROGRAMS\HHPS\OpenArena\OpenArena SDK v0.1.0-alpha.lnk" "$INSTDIR\oa.sln"
  
SectionEnd

Section "Media"

  SetOutPath $INSTDIR\OpenArena
  File ".\OpenArena\oa.exe"
  SetOutPath $INSTDIR\OpenArena\oa\config
  File ".\OpenArena\oa\config\my.cfg"
  SetOutPath $INSTDIR\OpenArena\oa\maps
  File ".\OpenArena\oa\maps\intro.map"
  File ".\OpenArena\oa\maps\oamap1.map"
  SetOutPath $INSTDIR\OpenArena\oa\music\bgm
  File ".\OpenArena\oa\music\bgm\*.mp3"
  SetOutPath $INSTDIR\OpenArena\oa\textures
  File ".\OpenArena\oa\textures\*.tga"
  File ".\OpenArena\oa\textures\*.bmp"
  SetOutPath $INSTDIR\OpenArena\oa\textures\menu
  File ".\OpenArena\oa\textures\menu\*.bmp"
  File ".\OpenArena\oa\textures\menu\*.tga"

  SetOutPath $INSTDIR\OpenArena
  CreateShortCut "$SMPROGRAMS\HHPS\OpenArena\OpenArena v0.1.0-alpha.lnk" "$INSTDIR\OpenArena\oa.exe"

  

SectionEnd

;--------------------------------

; Uninstaller

UninstallText "This will uninstall example2. Hit next to continue."

; Uninstall section

Section "Uninstall"
  
  ; remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\OpenArena v0.1.0-alpha"
  DeleteRegKey HKLM SOFTWARE\HHPS\OpenArena-0.1.0-alpha

  ; remove files and uninstaller
  Delete /REBOOTOK $INSTDIR\OpenArena\*.*
  Delete /REBOOTOK $INSTDIR\include\*.*
  Delete /REBOOTOK $INSTDIR\lib\*.*
  Delete /REBOOTOK $INSTDIR\src\*.*
  Delete /REBOOTOK $INSTDIR\bass.dll
  Delete /REBOOTOK $INSTDIR\heading.txt
  Delete /REBOOTOK $INSTDIR\license.txt
  Delete /REBOOTOK $INSTDIR\oa.ncb
  Delete /REBOOTOK $INSTDIR\oa.sln
  Delete /REBOOTOK $INSTDIR\oa.sou
  Delete /REBOOTOK $INSTDIR\oa.vcproj
  Delete /REBOOTOK "$INSTDIR\OpenArena User's Manual.doc"
  Delete /REBOOTOK "$INSTDIR\OpenArena User's Manual.html"
  Delete /REBOOTOK $INSTDIR\uninstall.exe

  ; remove shortcuts, if any
  Delete /REBOOTOK "$SMPROGRAMS\HHPS\OpenArena\Readme v0.1.0-alpha.lnk"
  Delete /REBOOTOK "$SMPROGRAMS\HHPS\OpenArena\OpenArena SDK v0.1.0-alpha.lnk"
  Delete /REBOOTOK "$SMPROGRAMS\HHPS\OpenArena\OpenArena v0.1.0-alpha.lnk"

  ; remove directories used
  RMDIR /r $INSTDIR\include
  RMDIR /r $INSTDIR\lib
  RMDIR /r $INSTDIR\OpenArena
  RMDIR /r $INSTDIR\src
  RMDIR /r "$INSTDIR"



SectionEnd