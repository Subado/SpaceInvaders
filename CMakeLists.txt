cmake_minimum_required(VERSION 3.2)
project(Chess LANGUAGES CXX)

set(CMAKE_CXX_COMPILER "/bin/g++")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules")

set(SOURCE
	src/main.cpp
	src/App.cpp
	src/SceneNode.cpp
	src/SpriteNode.cpp
	src/World.cpp
	src/Command.cpp
	src/CommandQueue.cpp
	src/Player.cpp
	src/GameState.cpp
	src/MenuState.cpp
	src/TitleState.cpp
	src/State.cpp
	src/StateStack.cpp
	src/Cannon.cpp
	src/Entity.cpp
	src/Utility.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/SFML")
	set(SFML_STATIC_LIBRARIES TRUE)
endif()

find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)
message(CMAKE_CXX_COMPILER="${CMAKE_CXX_COMPILER}")


add_executable(main ${SOURCE})
target_link_libraries(main sfml-graphics)
