# Microsoft Developer Studio Project File - Name="astrcmp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=astrcmp - Win32 Test
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "astrcmp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "astrcmp.mak" CFG="astrcmp - Win32 Test"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "astrcmp - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "astrcmp - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE "astrcmp - Win32 Test" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "astrcmp"
# PROP Scc_LocalPath "."

!IF  "$(CFG)" == "astrcmp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f astrcmp.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "astrcmp.exe"
# PROP BASE Bsc_Name "astrcmp.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "nmake /nologo /s /f "Makefile.vc6" CFG="astrcmp - Win32 Release""
# PROP Rebuild_Opt "/a"
# PROP Target_File "Release\astrcmp.exe"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "astrcmp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f astrcmp.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "astrcmp.exe"
# PROP BASE Bsc_Name "astrcmp.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "nmake /nologo /s /f "Makefile.vc6" CFG="astrcmp - Win32 Debug""
# PROP Rebuild_Opt "/a"
# PROP Target_File "Deubg\astrcmp.exe"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "astrcmp - Win32 Test"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "astrcmp___Win32_Test"
# PROP BASE Intermediate_Dir "astrcmp___Win32_Test"
# PROP BASE Cmd_Line "nmake /nologo /s /f "Makefile.vc6""
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "Deubg\astrcmp.exe"
# PROP BASE Bsc_Name ""
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "astrcmp___Win32_Test"
# PROP Intermediate_Dir "astrcmp___Win32_Test"
# PROP Cmd_Line "nmake /nologo /s /f "Makefile.vc6" CFG="astrcmp - Win32 Test""
# PROP Rebuild_Opt "/a"
# PROP Target_File "Test\astrcmp.exe"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "astrcmp - Win32 Release"
# Name "astrcmp - Win32 Debug"
# Name "astrcmp - Win32 Test"

!IF  "$(CFG)" == "astrcmp - Win32 Release"

!ELSEIF  "$(CFG)" == "astrcmp - Win32 Debug"

!ELSEIF  "$(CFG)" == "astrcmp - Win32 Test"

!ENDIF 

# Begin Source File

SOURCE=.\astrcmp.c
# End Source File
# Begin Source File

SOURCE=.\astrcmp.h
# End Source File
# Begin Source File

SOURCE=.\Makefile.vc6
# End Source File
# End Target
# End Project
