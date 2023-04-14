cmake_minimum_required(VERSION 3.22.1)
project(BLAST)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)



add_executable(BLAST src/main.cpp src/Source/Entity.cpp)
target_link_libraries(BLAST PRIVATE sfml-graphics sfml-window sfml-system sfml-network)