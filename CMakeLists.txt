include(ExternalProject)

# Basic Compiler options
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(led-matrix VERSION 0.1.0)

# Depend on ImageMagick++
add_definitions( -DMAGICKCORE_QUANTUM_DEPTH=8 )
add_definitions( -DMAGICKCORE_HDRI_ENABLE=0 )

# Graphics Magick
execute_process(COMMAND GraphicsMagick++-config --cxxflags
OUTPUT_VARIABLE GM_CFLAGS 
OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND GraphicsMagick++-config --cppflags
OUTPUT_VARIABLE GM_CPPFLAGS 
OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND GraphicsMagick++-config --ldflags
OUTPUT_VARIABLE GM_LDFLAGS 
OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND GraphicsMagick++-config --libs 
OUTPUT_VARIABLE GM_LIBS 
OUTPUT_STRIP_TRAILING_WHITESPACE)

message(STATUS "CFLAGS ${GM_CFLAGS}")
message(STATUS "CPPFLAGS ${GM_CPPFLAGS}")
message(STATUS "LDFLAGS ${GM_LDFLAGS}")
message(STATUS "LIBS ${GM_LIBS}")

set(GM_COMP_FLAGS "${GM_CFLAGS} ${GM_CPPFLAGS}")
# set(GM_LINK_FLAGS "${GM_LDFLAGS} ${GM_LIBS}")

separate_arguments(GM_COMP_FLAGS)
separate_arguments(GM_LDFLAGS)
separate_arguments(GM_LIBS)

set(GM_LIBS_PROPER)

foreach(lib IN LISTS GM_LIBS)
  # Remove the -l prefix
  string(REPLACE "-l" "" lib_name ${lib})
  # Append the modified library to the list
  list(APPEND GM_LIBS_PROPER ${lib_name})
endforeach()

foreach(flag ${GM_COMP_FLAGS})
    add_compile_options(${flag})
endforeach()

foreach(flag ${GM_LDFLAGS})
  message(STATUS "LINK FLAG: ${flag}")
  add_link_options(${flag})
endforeach()

message(STATUS "GraphicsMagick compile flags: ${GM_COMP_FLAGS}")
message(STATUS "GraphicsMagick link flags: ${GM_LDFLAGS}")

# Depend on rpi-rgb-led-matrix
ExternalProject_Add(
	rpi-rgb-led-matrix
	PREFIX ${CMAKE_SOURCE_DIR}/rpi-rgb-led-matrix
	GIT_REPOSITORY https://github.com/hzeller/rpi-rgb-led-matrix
	SOURCE_DIR ${CMAKE_SOURCE_DIR}/rpi-rgb-led-matrix/src/rpi-rgb-led-matrix
	BINARY_DIR ${CMAKE_SOURCE_DIR}/rpi-rgb-led-matrix/src/rpi-rgb-led-matrix/lib
	UPDATE_COMMAND ""
	CONFIGURE_COMMAND ""
	BUILD_COMMAND "make"
	INSTALL_COMMAND ""
)

# Add rpi-rgb-led-matrix library file
ExternalProject_Get_Property(rpi-rgb-led-matrix BINARY_DIR)
add_library(led-matrix-lib UNKNOWN IMPORTED)
set_property(TARGET led-matrix-lib PROPERTY IMPORTED_LOCATION ${BINARY_DIR}/librgbmatrix.a)

# Include rpi-rgb-led-matrix/include/ and include/

include_directories(
	${CMAKE_SOURCE_DIR}/include
)

include_directories(SYSTEM
	${CMAKE_SOURCE_DIR}/rpi-rgb-led-matrix/src/rpi-rgb-led-matrix/include
)

# Add link for rpi-rgb-led-matrix
link_directories(${CMAKE_BINARY_DIR}/rpi-rgb-led-matrix/src/rpi-rgb-led-matrix/lib)

# Add CLI11
add_subdirectory(CLI11)

# Font directory
set(FONT_DIR "\\\"${CMAKE_SOURCE_DIR}/rpi-rgb-led-matrix/src/rpi-rgb-led-matrix/fonts/\\\"")

if(DEFINED DEVLAPTOP)
	set(DEVLAPTOPFLAG "-DDEVLAPTOP=1")
else()
	set(DEVLAPTOPFLAG "")
endif()

# Add warnings to compilation
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEVLAPTOPFLAG} -DFONT_DIR=${FONT_DIR}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -DDEBUG -DFONT_DIR=${FONT_DIR} -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion")

# All sources
set(SHARED_SOURCES
	${CMAKE_SOURCE_DIR}/src/common/canvas/better_canvas.cpp
	${CMAKE_SOURCE_DIR}/src/common/canvas/debug_canvas.cpp
	${CMAKE_SOURCE_DIR}/src/common/models/color.cpp
	${CMAKE_SOURCE_DIR}/src/common/util/arg_parser.cpp
	${CMAKE_SOURCE_DIR}/src/common/util/array_to_vector.cpp
	${CMAKE_SOURCE_DIR}/src/common/util/enum_checked_transformer.cpp
	${CMAKE_SOURCE_DIR}/src/common/util/pad_zeros.cpp
	${CMAKE_SOURCE_DIR}/src/common/util/split_string.cpp
	${CMAKE_SOURCE_DIR}/src/common/util/starts_with.cpp
	${CMAKE_SOURCE_DIR}/src/modules/colors/renderers/circle_animation_renderer.cpp
	${CMAKE_SOURCE_DIR}/src/modules/colors/renderers/corners_animation_renderer.cpp
	${CMAKE_SOURCE_DIR}/src/modules/colors/renderers/pulse_animation_renderer.cpp
	${CMAKE_SOURCE_DIR}/src/modules/colors/renderers/renderer.cpp
	${CMAKE_SOURCE_DIR}/src/modules/colors/colors_configuration.cpp
	${CMAKE_SOURCE_DIR}/src/modules/colors/colors_module.cpp
	${CMAKE_SOURCE_DIR}/src/modules/game-of-life/game_of_life_board.cpp
	${CMAKE_SOURCE_DIR}/src/modules/game-of-life/game_of_life_configuration.cpp
	${CMAKE_SOURCE_DIR}/src/modules/game-of-life/game_of_life_module.cpp
	${CMAKE_SOURCE_DIR}/src/modules/images/images_configuration.cpp
	${CMAKE_SOURCE_DIR}/src/modules/images/images_module.cpp
	${CMAKE_SOURCE_DIR}/src/modules/time-date/time_date_configuration.cpp
	${CMAKE_SOURCE_DIR}/src/modules/time-date/time_date_module.cpp
)

# Sources for the two different executables
set(CLI_SOURCES ${SHARED_SOURCES} ${CMAKE_SOURCE_DIR}/src/cli.cpp)
set(MANAGER_SOURCES ${SHARED_SOURCES} ${CMAKE_SOURCE_DIR}/src/manager.cpp)

# Add executables
add_executable(led-matrix ${CLI_SOURCES})
add_executable(led-matrix-manager ${MANAGER_SOURCES})

# Make the executables depend on rpi-rgb-led-matrix
add_dependencies(led-matrix rpi-rgb-led-matrix)
add_dependencies(led-matrix-manager rpi-rgb-led-matrix)

# Link the executables
target_link_libraries(led-matrix PRIVATE  rt m pthread led-matrix-lib CLI11::CLI11 )
target_link_libraries(led-matrix-manager PRIVATE  rt m pthread led-matrix-lib CLI11::CLI11 )

foreach(lib IN LISTS GM_LIBS_PROPER)
    target_link_libraries(led-matrix PRIVATE ${lib})
    target_link_libraries(led-matrix-manager PRIVATE ${lib})
endforeach()
