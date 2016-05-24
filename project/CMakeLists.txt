cmake_minimum_required (VERSION 3.2.2)

option(TEST "Build all tests." OFF)
option(COVERAGE "Enable code coverage." OFF)
option(DOXYDOC "build doxygen documentation" OFF)




project (tinder-server C CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 11)
if(COVERAGE AND TEST)
	message(STATUS "TESTS COVERAGE ENABLED")
	include(CodeCoverage)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage -coverage")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage -coverage")
	SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage -coverage")
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


# Agrega directorios para la búsqueda de módulos CMake dentro de la variable CMAKE_MODULE_PATH
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${RUTA_COVERALLS_CMAKE})

add_subdirectory (app) 
add_subdirectory (server) 

if(TEST)
	message(STATUS "TESTS ENABLED")
	enable_testing ()
	add_subdirectory (test)
endif()


if(DOXYDOC AND TEST)
	message(STATUS "BUILD DOXY DOC ENABLED")
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
    endif()
endif()

###################################################
# Configuración de la herramienta coveralls-cmake #
###################################################

# Si activo Coveralls en la llamada de CMake
	
#if (COVERAGE)
	# Agrego el módulo CMake correspondiente...
#	include(Coveralls)

	# ...Agrego los flags de coverage (-fprofile-arcs -ftest-coverage)...
#	coveralls_turn_on_coverage()

	# ... Y preparo la herramienta coveralls-cmake
	# 1er argumento: Lista de archivos fuente
	# 2do argumento: "ON" para subir al sitio Coveralls.io
	# 3er argumento: Ruta alternativa de ubicación de la herramienta coveralls-cmake
	
#	file(GLOB_RECURSE APP_SOURCES "app/src/*.cpp" "app/src/*.c" )
#	coveralls_setup("${APP_SOURCES}"
#			${COVERALLS_UPLOAD}
#			"${CMAKE_MODULE_PATH}")
#endif(COVERAGE)
