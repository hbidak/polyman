# Microsoft Developer Studio Project File - Name="Projet_infographie" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Projet_infographie - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Projet_infographie.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Projet_infographie.mak" CFG="Projet_infographie - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Projet_infographie - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Projet_infographie - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Projet_infographie - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0xc0c /d "NDEBUG"
# ADD RSC /l 0xc0c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Projet_infographie - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0xc0c /d "_DEBUG"
# ADD RSC /l 0xc0c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Projet_infographie - Win32 Release"
# Name "Projet_infographie - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AdvGlutWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BSpline.cpp
# End Source File
# Begin Source File

SOURCE=.\CameraGL.cpp
# End Source File
# Begin Source File

SOURCE=.\CouleurGL.cpp
# End Source File
# Begin Source File

SOURCE=.\CRU.cpp
# End Source File
# Begin Source File

SOURCE=.\cube.cpp
# End Source File
# Begin Source File

SOURCE=.\cylindre.cpp
# End Source File
# Begin Source File

SOURCE=.\Droite3D.cpp
# End Source File
# Begin Source File

SOURCE=.\FenetreGL.cpp
# End Source File
# Begin Source File

SOURCE=.\GlutMaster.cpp
# End Source File
# Begin Source File

SOURCE=.\GlutWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\Jonction.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\Module.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjetGL.cpp
# End Source File
# Begin Source File

SOURCE=.\OVI.CPP
# End Source File
# Begin Source File

SOURCE=.\Plan3D.cpp
# End Source File
# Begin Source File

SOURCE=.\Point2D.cpp
# End Source File
# Begin Source File

SOURCE=.\Point3D.cpp
# End Source File
# Begin Source File

SOURCE=.\Pointctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Police.cpp
# End Source File
# Begin Source File

SOURCE=.\Principale.cpp
# End Source File
# Begin Source File

SOURCE=.\Propulsion.cpp
# End Source File
# Begin Source File

SOURCE=.\Rectangle.cpp
# End Source File
# Begin Source File

SOURCE=.\Scene.cpp
# End Source File
# Begin Source File

SOURCE=.\selection3D.cpp
# End Source File
# Begin Source File

SOURCE=.\Sphere.cpp
# End Source File
# Begin Source File

SOURCE=.\Station.cpp
# End Source File
# Begin Source File

SOURCE=.\Trajectoire.cpp
# End Source File
# Begin Source File

SOURCE=.\TransformationGL.cpp
# End Source File
# Begin Source File

SOURCE=.\Vecteur.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AdvGlutWnd.h
# End Source File
# Begin Source File

SOURCE=.\BSpline.h
# End Source File
# Begin Source File

SOURCE=.\CameraGL.h
# End Source File
# Begin Source File

SOURCE=.\Constantes.h
# End Source File
# Begin Source File

SOURCE=.\CouleurGL.h
# End Source File
# Begin Source File

SOURCE=.\CRU.h
# End Source File
# Begin Source File

SOURCE=.\cube.h
# End Source File
# Begin Source File

SOURCE=.\cylindre.h
# End Source File
# Begin Source File

SOURCE=.\Droite3D.h
# End Source File
# Begin Source File

SOURCE=.\FenetreGL.h
# End Source File
# Begin Source File

SOURCE=.\GlutMaster.h
# End Source File
# Begin Source File

SOURCE=.\GlutWindow.h
# End Source File
# Begin Source File

SOURCE=.\Jonction.h
# End Source File
# Begin Source File

SOURCE=.\Macros.h
# End Source File
# Begin Source File

SOURCE=.\Module.h
# End Source File
# Begin Source File

SOURCE=.\ObjetGL.h
# End Source File
# Begin Source File

SOURCE=.\OVI.H
# End Source File
# Begin Source File

SOURCE=.\Plan3D.h
# End Source File
# Begin Source File

SOURCE=.\Point.h
# End Source File
# Begin Source File

SOURCE=.\Point2D.h
# End Source File
# Begin Source File

SOURCE=.\Point3D.h
# End Source File
# Begin Source File

SOURCE=.\Pointctrl.h
# End Source File
# Begin Source File

SOURCE=.\Police.h
# End Source File
# Begin Source File

SOURCE=.\Principale.h
# End Source File
# Begin Source File

SOURCE=.\Propulsion.h
# End Source File
# Begin Source File

SOURCE=.\Rectangle.h
# End Source File
# Begin Source File

SOURCE=.\Rgbcolor.h
# End Source File
# Begin Source File

SOURCE=.\Scene.h
# End Source File
# Begin Source File

SOURCE=.\selection3D.h
# End Source File
# Begin Source File

SOURCE=.\Sphere.h
# End Source File
# Begin Source File

SOURCE=.\Station.h
# End Source File
# Begin Source File

SOURCE=.\temps.h
# End Source File
# Begin Source File

SOURCE=.\Trajectoire.h
# End Source File
# Begin Source File

SOURCE=.\TransformationGL.h
# End Source File
# Begin Source File

SOURCE=.\Vecteur.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
