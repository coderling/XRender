mkdir -p build/osx
cd build/osx
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../../
make
make install