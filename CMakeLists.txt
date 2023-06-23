cmake_minimum_required(VERSION 3.22.1)

project(BLAST)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")


if(UNIX)

    set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1_linux/lib/cmake/SFML")

endif ()

if(WIN32)

    set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1_windows_MinGW64bit/lib/cmake/SFML")

endif ()

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)


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
        src/Source/Takeover.cpp
        src/Source/PathFinder.cpp
        src/Headers/Constants.h
        )


if(WIN32)
    add_custom_command(TARGET BLAST POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}/SFML-2.5.1_windows_MinGW64bit/bin"
            $<TARGET_FILE_DIR:BLAST>
            )
endif()

target_link_libraries(BLAST PRIVATE sfml-graphics sfml-window sfml-system sfml-network sfml-audio)

