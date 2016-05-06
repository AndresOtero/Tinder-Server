#!/bin/bash
# Instalación de dependencias y herramientas


OLDBOOST=false
COVERAGE=false
COVERALLUPLOAD=false
GCINCO=false
TESTS=false
DOXYDOC=false
DEV=false
DEPENDENCIES=false

while test $# -gt 0; do
        case "$1" in
                -h|--help)
                        echo "Configuration script"
                        echo " "
                        echo "config.sh [options]"
                        echo " "
                        echo "options:"
                        echo "-h, --help    				imprimir esta ayuda 							"
                        echo "-g++-5        				flag g++-5 para cmake 							"
                        echo "-oldboost 				compatibilidad de boost para linux version 14.04"
                        echo "-test					habilita los tests 								"
                        echo "-coverage				habilita coverage y agrega -test 								"
                        echo "-doxydoc				habilita documentación doxy 					"
                        echo "-dependencies				instala dependencias"
                        echo "--dev 					atajo para -test -doxydoc -coverage		"
                        exit 0
                        ;;
                -g++-5)
						GCINCO=true
                        shift
                        ;;
                -oldboost)
						OLDBOOST=true
                        shift
                        ;;
                -coverage)
						COVERAGE=true
                        shift
                        ;;
                -doxydoc)
						DOXYDOC=true
                        shift
                        ;;
                -test)
						TESTS=true	
                        shift
                        ;;
                -dependencies)
						DEPENDENCIES=true	
                        shift
                        ;;
                --dev)
						DEV=true
                        shift
                        ;;
                *)
                        break
                        ;;
        esac
done

if [ "$DEV" = true ] 
then
	TESTS=true
	DOXYDOC=true
	COVERAGE=true
fi

if [ "$COVERALLUPLOAD" = true ] 
then
	COVERAGE=true
fi

if [ "$COVERAGE" = true ] 
then
	TESTS=true
fi

if [ "$DOXYDOC" = true ] 
then
	TESTS=true
fi




CMAKE_PARAMS=""



if [ "$TEST" = true ]
	then
	CMAKE_PARAMS="$CMAKE_PARAMS -DTESTS=ON"
fi
if [ "$COVERAGE" = true ]
	then
	CMAKE_PARAMS="$CMAKE_PARAMS -DCOVERALL=ON -DCMAKE_BUILD_TYPE=Debug"
fi
if [ "$COVERALLUPLOAD" = true ]
	then
	CMAKE_PARAMS="$CMAKE_PARAMS -DCOVERALLS_UPLOAD=ON"
fi
if [ "$DOXYDOC" = true ]
	then
	CMAKE_PARAMS="$CMAKE_PARAMS -DBUILD_DOXY_DOC=ON"
fi







if [ "$DEPENDENCIES" = true  ]
then

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
	if [ "$OLDBOOST" = true ]
	then
	 add-apt-repository ppa:afrank/boost -y
	 apt-get update -q
	 apt-get install libboost1.57-all libboost1.57-all-dev
	else
		apt-get install -y libboost-all-dev
	fi
fi

mkdir -p build
cd build
echo "params $CMAKE_PARAMS"

if [ "$GCINCO" = true ]
	then
	cmake -DCMAKE_CXX_COMPILER='g++-5' -B. "$CMAKE_PARAMS" ../project/  && make 
else
	cmake "$CMAKE_PARAMS" ../project/  && make 
fi


