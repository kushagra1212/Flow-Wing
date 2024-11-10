!include "MUI2.nsh"
!include "LogicLib.nsh"

Name "FlowWing"
Outfile "FlowWingInstaller.exe"
InstallDir "$PROGRAMFILES\\FlowWing"
RequestExecutionLevel admin

!define LIBDIR "$INSTDIR\\lib"
!define BINDIR "$INSTDIR\\bin"
!define MODULESDIR "$INSTDIR\\lib\\modules"
!define VC_REDIST_URL "https://aka.ms/vs/17/release/vc_redist.x64.exe"
!define VC_REDIST_PATH "$TEMP\\vc_redist.x64.exe"

Section "MainSection" SEC01
    ; Create directories
    SetOutPath "$INSTDIR"
    CreateDirectory "${BINDIR}"
    CreateDirectory "${LIBDIR}"
    CreateDirectory "${MODULESDIR}"
    
    ; Extract binary files
    SetOutPath "${BINDIR}"
    DetailPrint "Extracting binary files..."
    File /r "bin\\*.*"
    
    ; Extract library files
    SetOutPath "${LIBDIR}"
    DetailPrint "Extracting library files..."
    File /r "lib\\*.*"
    
    ; Extract module files
    SetOutPath "${MODULESDIR}"
    DetailPrint "Extracting module files..."
    File /r "lib\\modules\\*.*"
    
    ; Handle Visual C++ Redistributable
    DetailPrint "Checking Visual C++ Redistributable..."
    ReadRegDword $R0 HKLM "SOFTWARE\\Microsoft\\VisualStudio\\14.0\\VC\\Runtimes\\x64" "Installed"
    ${If} $R0 != "1"
        DetailPrint "Downloading Visual C++ Redistributable..."
        NSISdl::download "${VC_REDIST_URL}" "${VC_REDIST_PATH}"
        Pop $0
        ${If} $0 == "success"
            DetailPrint "Installing Visual C++ Redistributable..."
            ExecWait '"${VC_REDIST_PATH}" /install /quiet /norestart' $R1
            ${If} $R1 != "0"
                DetailPrint "Visual C++ Redistributable installation failed with code: $R1"
            ${Else}
                DetailPrint "Visual C++ Redistributable installed successfully"
            ${EndIf}
        ${Else}
            DetailPrint "Failed to download Visual C++ Redistributable: $0"
        ${EndIf}
        Delete "${VC_REDIST_PATH}"
    ${Else}
        DetailPrint "Visual C++ Redistributable is already installed"
    ${EndIf}
    
; Update PATH environment variable
DetailPrint "Updating PATH environment variable..."
ReadRegStr $0 HKLM "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment" "Path"
${If} $0 == ""
  StrCpy $0 ""
${EndIf}
StrCpy $0 "$0;$INSTDIR\\bin;$INSTDIR\\lib"
WriteRegStr HKLM "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment" "Path" "$0"
SendMessage ${HWND_BROADCAST} ${WM_WININICHANGE} 0 "STR:Environment"

    
    ; Set FlowWing registry entries
    WriteRegStr HKLM "Software\\FlowWing" "ModulesPath" "${MODULESDIR}"
    
    ; Create uninstaller
    WriteUninstaller "$INSTDIR\\Uninstall.exe"
    
    DetailPrint "Installation completed"
SectionEnd

Section "Uninstall"
    ; Remove installed files
    RMDir /r "$INSTDIR"
    
    ; Clean up registry
    DeleteRegKey HKLM "Software\\FlowWing"
    
    ; Note: In this simplified version, we don't modify PATH during uninstall
    ; as it could potentially damage the PATH if multiple versions were installed
    
    DetailPrint "Uninstallation completed"
SectionEnd

; Modern UI Configuration
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\\Contrib\\Graphics\\Icons\\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\\Contrib\\Graphics\\Icons\\modern-uninstall.ico"

; Pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

; Language
!insertmacro MUI_LANGUAGE "English"