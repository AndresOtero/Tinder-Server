cmake_minimum_required (VERSION 3.2.2)

option(TEST "Build all tests." OFF)
option(COVERAGE "Enable code coverage." OFF)
option(BUILD_DOXY_DOC "build doxygen documentation" OFF)

# Setea las opciones para la herramienta coveralls-cmake
option(COVERALLS "Activa el soporte para Coveralls.io" OFF)
option(COVERALLS_UPLOAD "Sube el json generado de coveralls" OFF)


project (tinder-server C CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 11)
if(COVERAGE AND TEST)
	include(CodeCoverage)
	SET(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -g -O0 -Wall --coverage")
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -Wall -W --coverage")
	SET(CMAKE_EXE_LINKER_FLAGS "--coverage")
    SETUP_TARGET_FOR_COVERAGE(
				coverage  # Name for custom target.
				testapp         # Name of the test driver executable that runs the tests.
				coverage-report            # Name of output directory.
				)
endif()

#############################################
### Seteos para el uso de coveralls-cmake ###
#############################################


# Seteo la ruta donde se encuentran los scripts de la herramienta coveralls-cmake
set(RUTA_COVERALLS_CMAKE "${RUTA_TOOLS}/coveralls-cmake/cmake")

# Agrega directorios para la búsqueda de módulos CMake dentro de la variable CMAKE_MODULE_PATH
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${RUTA_COVERALLS_CMAKE})

add_subdirectory (app) 
add_subdirectory (server) 

if(TEST)
	enable_testing ()
	add_subdirectory (test)
endif()


if(BUILD_DOXY_DOC AND TESTS)
    find_package(Doxygen)
    if(NOT DOXYGEN_FOUND)
        message(WARNING "Doxygen not found, unable to generate documentation")
    else()

    	if(DOXYGEN_FOUND)
			configure_file(${CMAKE_CURRENT_SOURCE_DIR}/app/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
			add_custom_target(doxyDoc
			${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
			COMMENT "Generating API documentation with Doxygen" VERBATIM
		)
		endif(DOXYGEN_FOUND)
        #set(DOXY_DOC_DEST_DIR ${CMAKE_BINARY_DIR} CACHE PATH "Path to the doxygen output")                      ## used in the doxyfile.in
        #set(DOXY_DOC_INPUT_ROOT_DIRS ${CMAKE_HOME_DIRECTORY}/app CACHE PATH "Path from where to start to parse")    ## used in the doxyfile.in
        #set(DOXY_DOC_EXCLUDE_PATTERNS_DIRS ${CMAKE_BINARY_DIR} CACHE STRING "Regex patterns exclusion")          ## used in the doxyfile.in
        #set(DOXY_DOC_COMMON_IMG_PATH ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "Path from which doxygen will be able to found referenced images")## used in the doxyfile.in
        #configure_file(doxyfile.in ${CMAKE_BINARY_DIR}/doxyfile @ONLY)
        #message(STATUS ${CMAKE_HOME_DIRECTORY})
        #add_custom_target(doxyDoc COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_BINARY_DIR}/doxyfile"
         #   WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}
          #  COMMENT "Building user's documentation into doxyDoc build dir..."
        #)
    endif()
endif()

###################################################
# Configuración de la herramienta coveralls-cmake #
###################################################

# Si activo Coveralls en la llamada de CMake
if (COVERALLS)
	# Agrego el módulo CMake correspondiente...
	include(Coveralls)

	# ...Agrego los flags de coverage (-fprofile-arcs -ftest-coverage)...
	coveralls_turn_on_coverage()

	# ... Y preparo la herramienta coveralls-cmake
	# 1er argumento: Lista de archivos fuente
	# 2do argumento: "ON" para subir al sitio Coveralls.io
	# 3er argumento: Ruta alternativa de ubicación de la herramienta coveralls-cmake
	coveralls_setup("${SRC_TESTEABLE}"
			${COVERALLS_UPLOAD}
			"${RUTA_COVERALLS_CMAKE}")
endif(COVERALLS)