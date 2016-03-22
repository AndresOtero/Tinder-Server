mkdir -p build
cd build
cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_ECLIPSE_VERSION=4.2 -D CMAKE_BUILD_TYPE=Debug ../project -Dtest=on


