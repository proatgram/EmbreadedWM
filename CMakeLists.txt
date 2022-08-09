cmake_minimum_required(VERSION 3.2)

# set(CMAKE_TOOLCHAIN_FILE "/media/thetimbrick/4d2d47b0-3ef2-4c5a-8721-f1970dd6ff77/host/share/buildroot/toolchainfile.cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(EmbreadedWM VERSION 0.1
DESCRIPTION "This is the source of the EmbreadedOS display Manager for the EmbreadedWatch."
HOMEPAGE_URL "https://github.com/proatgram/EmbreadedWM"
LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

file(GLOB_RECURSE EmbreadedWM_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE EmbreadedWM_HEADERS "${CMAKE_SOURCE_DIR}/include/*.h}" "${CMAKE_SOURCE_DIR}/include/*.hpp")

find_library(LIBX11 X11)
if(${LIBX11} STREQUAL "LIBX11-NOTFOUND")
    message(FATAL_ERROR "libx11 libraries not found. Please install them and continue.")
endif()

add_executable(embreaded-wm ${EmbreadedWM_SOURCES} ${EmbreadedWM_HEADERS})

target_link_libraries(embreaded-wm ${LIBX11})

target_include_directories(embreaded-wm PUBLIC ${CMAKE_SOURCE_DIR}/include)