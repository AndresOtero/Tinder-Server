#!/bin/bash
# Instalación de dependencias y herramientas


OLDBOOST=false
COVERAGE=false
GCINCO=false
TESTS=false
DOXYDOC=false
DEV=false
DEPENDENCIES=false

display_help() {
    echo "Uso: $0 [option...] " >&2
    echo
    echo "    -h, --help         Imprimir esta ayuda"
    echo "    -g++-5             Flag g++-5 para cmake"
    echo "    -oldboost          Compatibilidad de boost para linux version 14.04"
    echo "    -test              Habilita los tests"
    echo "    -coverage          Habilita coverage y agrega -test"
    echo "    -doxydoc           Habilita documentación doxy"
    echo "    -dependencies      Instala dependencias"
    echo "    -dev               Atajo para -test -doxydoc -coverage"
    exit 1
}

while test $# -gt 0; do
        case "$1" in
                -h|--help)
						display_help
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
                -dev)
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

if [ "$COVERAGE" = true ] 
then
	TESTS=true
fi

if [ "$DOXYDOC" = true ] 
then
	TESTS=true
fi




CMAKE_PARAMS=""

TEST_PARAM=OFF
COVERAGE_PARAM=OFF
DOXY_DOC_PARAM=OFF
CMAKE_BUILD_TYPE=Release
if [ "$TESTS" = true ]
	then
	TEST_PARAM=ON
	CMAKE_BUILD_TYPE=Debug
fi
if [ "$COVERAGE" = true ]
	then
	COVERAGE_PARAM=ON
	CMAKE_BUILD_TYPE=Debug
fi
if [ "$DOXYDOC" = true ]
	then
	DOXY_DOC_PARAM=ON
	CMAKE_BUILD_TYPE=Debug
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

if [ "$GCINCO" = true ]
	then
	cmake -DCMAKE_CXX_COMPILER='g++-5' -B. -DTESTS=$TEST_PARAM -DCOVERAGE=$COVERAGE_PARAM -DDOXYDOC=$DOXY_DOC_PARAM 	-DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE ../project/  && make
else
	cmake -DTEST=$TEST_PARAM -DCOVERAGE=$COVERAGE_PARAM -DDOXYDOC=$DOXY_DOC_PARAM -DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE ../project/  && make
fi



