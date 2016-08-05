ECHO Debug Cleanup Started
ECHO %1

CD /D %1
:: SET name=%random%
:: ECHO "%name%"  > .\compiled\main.cpp

del /q .\bin\*.*
xcopy /s /y .\debugdlls .\bin
xcopy /s /y .\x64\Debug .\bin
del /q .\x64\Debug\*.*
del /q .\x64\Release\*.*
del /q .\VoxelQuest\x64\Debug\*.*
del /q .\VoxelQuest\x64\Release\*.*

ECHO running EXE
cd bin
VoxelQuest.exe
cd ..
