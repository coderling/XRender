mkdir build/osx
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../../
mingw32-make
mingw32-make install
pause