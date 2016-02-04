cd %~dp0\openddl-parser\
cmake -G "Visual Studio 14 2015 Win64" .
cmake --build . --config Debug
cmake --build . --config Release

pause