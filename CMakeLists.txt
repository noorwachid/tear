cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Tear)

add_library(Tear
    Source/Tear/Term.cpp
    Source/Tear/Term.h

	Source/Tear/Renderer.cpp
	Source/Tear/Renderer.h
	Source/Tear/Node.cpp
	Source/Tear/Node.h
	Source/Tear/Cell.h
	Source/Tear/Utf8.cpp
	Source/Tear/Utf8.h

    Source/Tear/Event.h
	Source/Tear/EventManager.cpp
	Source/Tear/EventManager.h
    Source/Tear/Key.cpp
    Source/Tear/Key.h
	Source/Tear/Sequence.h
    Source/Tear/SequenceManager.cpp
    Source/Tear/SequenceManager.h
)

target_include_directories(Tear PUBLIC Source)

add_executable(Tear_Application
	Source/EntryPoint.cpp
)
target_link_libraries(Tear_Application Tear)

