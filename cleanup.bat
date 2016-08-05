ECHO Cleanup Started
ECHO %1

CD /D %1
ECHO changed directory
:: SET name=%random%
:: ECHO "%name%"  > .\compiled\main.cpp

del /q .\bin\*.*
ECHO change2
xcopy /s /y .\dlls .\bin
ECHO change3
xcopy /s /y .\x64\Release .\bin
ECHO change4
del /q .\x64\Debug\*.*
ECHO change5
del /q .\x64\Release\*.*
del /q .\VoxelQuest\x64\Debug\*.*
del /q .\VoxelQuest\x64\Release\*.*

ECHO running EXE
cd bin
VoxelQuest.exe
cd ..
