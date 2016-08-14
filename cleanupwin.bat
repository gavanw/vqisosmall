ECHO Cleanup Started
ECHO %1

CD /D %1
xcopy /s /y .\dlls .\x64\Release

