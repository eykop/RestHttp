conan install conanfile.txt --build missing
cmake CMakeLists.txt -B build/debug
cd build/debug
make

