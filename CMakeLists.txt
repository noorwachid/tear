cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(tear)

add_library(tear
    src/Tear/Core.h
    src/Tear/Core.cpp

	src/Tear/Utf8.h
	src/Tear/Utf8.cpp

    src/Tear/Event.h
	src/Tear/EventManager.h
	src/Tear/EventManager.cpp
    src/Tear/Key.h
    src/Tear/Key.cpp
	src/Tear/Sequence.h
	src/Tear/Sequence.cpp
    src/Tear/SequenceDatabase.h
    src/Tear/SequenceDatabase.cpp
	src/Tear/Renderer.h
	src/Tear/Renderer.cpp
)

target_include_directories(tear PUBLIC src)

add_executable(tear_application
	src/EntryPoint.cpp
)
target_link_libraries(tear_application tear)

