::rd /S /Q build\win
::md build\win
cd build\win

cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug ../../
mingw32-make
mingw32-make install
pause