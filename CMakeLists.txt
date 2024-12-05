cmake_minimum_required(VERSION 3.6)

project(tyrepile)

add_subdirectory(magidoor)

add_executable(tyrepile main.cpp Stacker.cpp Tile.cpp)
if (WIN32)
	TARGET_LINK_LIBRARIES(tyrepile mdoor Ws2_32)
Else()
	TARGET_LINK_LIBRARIES(tyrepile mdoor)
endif()
