cmake_minimum_required(VERSION 3.2)

project(EmbreadedWM VERSION 0.1
DESCRIPTION "This is the source of the EmbreadedOS display Manager for the EmbreadedWatch."
HOMEPAGE_URL "https://github.com/proatgram/EmbreadedWM"
LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

file(GLOB_RECURSE EmbreadedWM_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE EmbreadedWM_HEADERS "${CMAKE_SOURCE_DIR}/include/*.h}" "${CMAKE_SOURCE_DIR}/include/*.hpp")

add_executable(embreaded-wm ${EmbreadedWM_SOURCES} ${EmbreadedWM_HEADERS})

target_include_directories(embreaded-wm PUBLIC ${CMAKE_SOURCE_DIR}/include)
