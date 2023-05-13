

# LINUX DEBUG
#cmake_minimum_required(VERSION 3.22.1)
#
#project(BLAST)
#
#set(CMAKE_CXX_STANDARD 17)
#
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
#
#set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1_linux/lib/cmake/SFML")
#
#find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
#
#
#
#add_executable(BLAST
#        src/main.cpp
#
#        src/Source/Entity.cpp
#        src/Source/Animation.cpp
#        src/Source/SpriteMethods.cpp
#        src/Source/Client.cpp
#        src/Source/Game.cpp
#        src/Source/InputText.cpp
#        src/Source/MainMenu.cpp
#        src/Source/Map.cpp
#        src/Source/Missile.cpp
#        src/Source/Object.cpp
#        src/Source/Player.cpp
#        src/Source/Server.cpp
#        #src/Source/Application.cpp
#        src/Source/RayCaster.cpp)
#
#target_link_libraries(BLAST PRIVATE sfml-graphics sfml-window sfml-system sfml-network)






#WINDOWS DEBUG

#cmake_minimum_required(VERSION 3.22.1)
#
#project(BLAST)
#
#set(CMAKE_CXX_STANDARD 17)
#
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
#
#set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1_windows_MinGW64bit/lib/cmake/SFML")
#
#find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
#
#set_target_properties(sfml-graphics PROPERTIES IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1_windows_MinGW64bit/lib/sfml-graphics-d.lib")
#set_target_properties(sfml-window PROPERTIES IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1_windows_MinGW64bit/lib/sfml-window-d.lib")
#set_target_properties(sfml-system PROPERTIES IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1_windows_MinGW64bit/lib/sfml-system-d.lib")
#set_target_properties(sfml-network PROPERTIES IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1_windows_MinGW64bit/lib/sfml-network-d.lib")
#
#add_executable(BLAST
#        src/main.cpp
#
#        src/Source/Entity.cpp
#        src/Source/Animation.cpp
#        src/Source/SpriteMethods.cpp
#        src/Source/Client.cpp
#        src/Source/Game.cpp
#        src/Source/InputText.cpp
#        src/Source/MainMenu.cpp
#        src/Source/Map.cpp
#        src/Source/Missile.cpp
#        src/Source/Object.cpp
#        src/Source/Player.cpp
#        src/Source/Server.cpp
#        #src/Source/Application.cpp
#        src/Source/RayCaster.cpp)
#
#if(WIN32)
#    add_custom_command(TARGET BLAST POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_directory
#            "${PROJECT_SOURCE_DIR}/SFML-2.5.1_windows_MinGW64bit/bin"
#            $<TARGET_FILE_DIR:BLAST>)
#endif()
#
#target_link_libraries(BLAST PRIVATE sfml-graphics sfml-window sfml-system sfml-network)

# WINDOWS STATIC RELEASE
cmake_minimum_required(VERSION 3.22.1)

project(BLAST)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")

# Set SFML_DIR to the location of the SFML package
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1_windows_MinGW64bit/lib/cmake/SFML")

# Set the SFML_STATIC macro
add_definitions(-DSFML_STATIC)

# Find the SFML package and specify the components to use
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(BLAST WIN32
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
        )

if(WIN32)
    add_custom_command(TARGET BLAST POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}/SFML-2.5.1_windows_MinGW64bit/bin"
            $<TARGET_FILE_DIR:BLAST>
            )
endif()

target_link_libraries(BLAST PRIVATE sfml-graphics sfml-window sfml-system sfml-network sfml-audio)


#WINDOWS RELEASE

#cmake_minimum_required(VERSION 3.22.1)
#
#project(BLAST)
#
#set(CMAKE_CXX_STANDARD 17)
#
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")
#
#set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1_windows_MinGW64bit/lib/cmake/SFML")
#
#find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
#
#set_target_properties(sfml-graphics PROPERTIES IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1_windows_MinGW64bit/lib/sfml-graphics.lib")
#set_target_properties(sfml-audio PROPERTIES IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1_windows_MinGW64bit/lib/sfml-audio.lib")
#set_target_properties(sfml-window PROPERTIES IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1_windows_MinGW64bit/lib/sfml-window.lib")
#set_target_properties(sfml-system PROPERTIES IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1_windows_MinGW64bit/lib/sfml-system.lib")
#set_target_properties(sfml-network PROPERTIES IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1_windows_MinGW64bit/lib/sfml-network.lib")
#
#add_executable(BLAST
#        src/main.cpp
#
#        src/Source/Entity.cpp
#        src/Source/Animation.cpp
#        src/Source/SpriteMethods.cpp
#        src/Source/Client.cpp
#        src/Source/Game.cpp
#        src/Source/InputText.cpp
#        src/Source/MainMenu.cpp
#        src/Source/Map.cpp
#        src/Source/Missile.cpp
#        src/Source/Object.cpp
#        src/Source/Player.cpp
#        src/Source/Server.cpp
#        #src/Source/Application.cpp
#        src/Source/RayCaster.cpp)
#
#if(WIN32)
#    add_custom_command(TARGET BLAST POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_directory
#            "${PROJECT_SOURCE_DIR}/SFML-2.5.1_windows_MinGW64bit/bin"
#            $<TARGET_FILE_DIR:BLAST>)
#endif()
#
#target_link_libraries(BLAST PRIVATE sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
#



# LINUX KINDA RELEASE
#cmake_minimum_required(VERSION 3.22.1)
#project(BLAST)
#
#set(CMAKE_CXX_STANDARD 17)
#
## Set the build type to Release
#set(CMAKE_BUILD_TYPE Release)
#
#set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1_linux/lib/cmake/SFML")
#find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
#
#add_executable(BLAST
#        src/main.cpp
#
#        src/Source/Entity.cpp
#        src/Source/Animation.cpp
#        src/Source/SpriteMethods.cpp
#        src/Source/Client.cpp
#        src/Source/Game.cpp
#        src/Source/InputText.cpp
#        src/Source/MainMenu.cpp
#        src/Source/Map.cpp
#        src/Source/Missile.cpp
#        src/Source/Object.cpp
#        src/Source/Player.cpp
#        src/Source/Server.cpp
#        #src/Source/Application.cpp
#        src/Source/RayCaster.cpp)
#target_link_libraries(BLAST PRIVATE sfml-graphics sfml-window sfml-system sfml-network)