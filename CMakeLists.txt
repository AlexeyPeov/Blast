cmake_minimum_required(VERSION 3.22.1)

project(BLAST)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")

# Set SFML_DIR to the location of the SFML package
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

# Set the SFML_STATIC macro
add_definitions(-DSFML_STATIC)

# Find the SFML package and specify the components to use

add_executable(BLAST #WIN32
        src/main.cpp

        src/Source/Entity.cpp
        src/Source/Animation.cpp
        src/Source/SpriteMethods.cpp
        src/Source/Client.cpp
        src/Source/Game.cpp
        src/Source/InputText.cpp
        src/Source/MainMenu.cpp
        src/Source/Map.cpp
        src/Source/Missile.cpp
        src/Source/Object.cpp
        src/Source/Player.cpp
        src/Source/Server.cpp
        #src/Source/Application.cpp
        src/Source/RayCaster.cpp
        src/Headers/Takeover.h
        src/Source/PathFinder.cpp
        src/Headers/Constants.h)

#[[if(WIN32)
    add_custom_command(TARGET BLAST POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}/SFML-2.5.1_windows_MinGW64bit/bin"
            $<TARGET_FILE_DIR:BLAST>
            )
endif()]]

target_link_libraries(BLAST PRIVATE sfml-system sfml-network sfml-graphics sfml-window sfml-audio)