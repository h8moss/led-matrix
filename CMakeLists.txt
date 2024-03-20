include(ExternalProject)

project(led-matrix)

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

ExternalProject_Add(
	rpi-rgb-led-matrix
	PREFIX ${CMAKE_SOURCE_DIR}/rpi-rgb-led-matrix
	GIT_REPOSITORY https://github.com/hzeller/rpi-rgb-led-matrix
	SOURCE_DIR ${CMAKE_SOURCE_DIR}/rpi-rgb-led-matrix/src/rpi-rgb-led-matrix
	UPDATE_COMMAND ""
	CONFIGURE_COMMAND ""
	BUILD_IN_SOURCE ON
	BUILD_COMMAND "make"
	INSTALL_COMMAND ""
)

include_directories(
	${CMAKE_SOURCE_DIR}/rpi-rgb-led-matrix/src/rpi-rgb-led-matrix/include
	${CMAKE_SOURCE_DIR}/include
)


link_directories(${CMAKE_BINARY_DIR}/rpi-rgb-led-matrix/src/rpi-rgb-led-matrix/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion")

set(SHARED_SOURCES
	${CMAKE_SOURCE_DIR}/src/common/canvas/text_drawer.cpp
	${CMAKE_SOURCE_DIR}/src/common/models/color.cpp
	${CMAKE_SOURCE_DIR}/src/common/util/array_to_vector.cpp
	${CMAKE_SOURCE_DIR}/src/common/util/better_canvas.cpp
	${CMAKE_SOURCE_DIR}/src/common/util/pad_zeros.cpp
	${CMAKE_SOURCE_DIR}/src/common/util/split_string.cpp
	${CMAKE_SOURCE_DIR}/src/modules/colors/renderers/circle_animation_renderer.cpp
	${CMAKE_SOURCE_DIR}/src/modules/colors/renderers/corners_animation_renderer.cpp
	${CMAKE_SOURCE_DIR}/src/modules/colors/renderers/pulse_animation_renderer.cpp
	${CMAKE_SOURCE_DIR}/src/modules/colors/colors_configuration.cpp
	${CMAKE_SOURCE_DIR}/src/modules/colors/colors_module.cpp
	${CMAKE_SOURCE_DIR}/src/modules/game-of-life/game_of_life_board.cpp
	${CMAKE_SOURCE_DIR}/src/modules/game-of-life/game_of_life_configuration.cpp
	${CMAKE_SOURCE_DIR}/src/modules/game-of-life/game_of_life_module.cpp
	${CMAKE_SOURCE_DIR}/src/modules/module_configuration.cpp
)

set(CLI_SOURCES ${SHARED_SOURCES} ${CMAKE_SOURCE_DIR}/src/cli.cpp)
set(MANAGER_SOURCES ${SHARED_SOURCES} ${CMAKE_SOURCE_DIR}/src/manager.cpp)

add_executable(led-matrix ${CLI_SOURCES})
add_executable(led-matrix-manager ${MANAGER_SOURCES})

find_library(RGBMATRIX_LIB rgbmatrix HINTS ${CMAKE_SOURCE_DIR}/rpi-rgb-led-matrix/src/rpi-rgb-led-matrix/lib)
if(NOT RGBMATRIX_LIB)
	message(FATAL_ERROR "Could not find rgbmatrix")
endif()

target_link_libraries(led-matrix PRIVATE  rt m pthread ${RGBMATRIX_LIB})
target_link_libraries(led-matrix-manager PRIVATE  rt m pthread ${RGBMATRIX_LIB})
