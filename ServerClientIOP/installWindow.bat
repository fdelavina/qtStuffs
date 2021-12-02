@echo off
Rem execute the application using our enviroment
echo Installing... 

SET CURRENT_DIR=%CD%
SET QT_BIN= "C:\Qt\5.15.2\mingw81_64\bin"
SET MiMainFile=WindowApp

Rem echo Mi nombre de usuario es %NOMBRE_USUARIO%

if not exist %MiMainFile% (
    mkdir %MiMainFile%
)

SET /p UserConfig=Debug o Release, d=debug r=release? 

if %UserConfig%==d (set config=Debugito) else (set config=releasito) 

Rem copia de los binarios
xcopy /Y %CURRENT_DIR%\output\%config%\bin\ %CURRENT_DIR%\%MiMainFile%
Rem copia de las librerias
xcopy /Y %CURRENT_DIR%\output\%config%\lib\ %CURRENT_DIR%\%MiMainFile%

Rem copia de las librerias de qt
xcopy /Y %QT_BIN%\Qt5Core.dll Qt5Network.dll Qt5WebSockets.dll %CURRENT_DIR%\%MiMainFile%
xcopy /Y %QT_BIN%\Qt5Network.dll %CURRENT_DIR%\%MiMainFile%
xcopy /Y %QT_BIN%\Qt5WebSockets.dll %CURRENT_DIR%\%MiMainFile%

pause
exit