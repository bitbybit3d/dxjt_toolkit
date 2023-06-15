set OSG_DIR=%~dp0..\..\..\contrib\openscenegraph\OpenSceneGraph-3.6.5-install\x64-Debug
set OSG_3RDPARTY_DIR=%OSG_DIR%\..\..\3rdParty_small_v141

set PATH=%OSG_3RDPARTY_DIR%\x64\bin;%OSG_DIR%\bin;%PATH%

set OSG_FILE_PATH=%OSG_DIR%\..\..\OpenSceneGraph-Data-3.4.0;%OSG_DIR%\..\..\OpenSceneGraph-Data-3.4.0\Images
set OSG_WINDOW=50 50 640 480
set OSG_THREADING=SingleThreaded

set "PATH=%PATH%;%ProgramFiles(x86)%\Microsoft Visual Studio\Installer"
for /f "usebackq delims=" %%i in (`vswhere.exe -version "[17.0,17.99]" -requires Microsoft.VisualStudio.Workload.NativeDesktop -property installationPath`) do (
    set "DevEnvDir=%%i\Common7\IDE\"
  )

start "" "%DevEnvDir%\devenv.exe" examples_jt_toolkit.sln
