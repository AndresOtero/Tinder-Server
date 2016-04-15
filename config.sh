#!/bin/bash
# Instalación de dependencias y herramientas
echo "Instalación de dependencias..."
apt-get update -q
apt-get install -y \
autotools-dev \
libicu-dev \
build-essential \
cmake \
libbz2-dev \
libcrypto++-dev \
zlib1g-dev \
libsnappy-dev \
libcurl4-gnutls-dev \
doxygen \
lcov \
gcovr

if [ "$1" == "-oldboost" ]
then
 add-apt-repository ppa:afrank/boost -y
 apt-get update -q
 apt-get install libboost1.57-all libboost1.57-all-dev
else
	apt-get install -y libboost-all-dev
fi

mkdir -p build
cd build

if [ "$1" == "-oldboost" -o "$1" == "-travis" ]
	then
	 cmake -DCMAKE_CXX_COMPILER='g++-5' -B. ../project && make
	else
	 cmake CMAKE_BUILD_TYPE=Debug ../project && make	
	fi



