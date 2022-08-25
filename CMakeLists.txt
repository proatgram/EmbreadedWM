cmake_minimum_required(VERSION 3.2)
include(FindPkgConfig)

# set(CMAKE_TOOLCHAIN_FILE "/media/thetimbrick/4d2d47b0-3ef2-4c5a-8721-f1970dd6ff77/host/share/buildroot/toolchainfile.cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(EmbreadedWM VERSION 0.1
DESCRIPTION "This is the source of the EmbreadedOS display Manager for the EmbreadedWatch."
HOMEPAGE_URL "https://github.com/proatgram/EmbreadedWM"
LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_BUILD_TYPE "Debug")

pkg_check_modules(GTKMM3 REQUIRED gtkmm-3.0)
pkg_check_modules(GDKMM3 REQUIRED gdkmm-3.0)
pkg_check_modules(GLIBMM2 REQUIRED glibmm-2.4)

file(GLOB_RECURSE EmbreadedWM_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE EmbreadedWM_HEADERS "${CMAKE_SOURCE_DIR}/include/*.h}" "${CMAKE_SOURCE_DIR}/include/*.hpp")

find_library(LIBX11 X11 REQUIRED)

find_library(LIBDESKENTRY deskentry REQUIRED)

add_executable(embreaded-wm ${EmbreadedWM_SOURCES} ${EmbreadedWM_HEADERS})

include_directories(AFTER SYSTEM  ${GTKMM3_INCLUDE_DIRS} ${GDKMM3_INCLUDE_DIRS} ${GLIBMM2_INCLUDE_DIRS})

target_link_libraries(embreaded-wm ${LIBX11}  ${GTKMM3_LIBRARIES} ${GDKMM3_LIBRARIES} ${GLIBMM2_LIBRARIES} ${LIBDESKENTRY})

target_include_directories(embreaded-wm PUBLIC ${CMAKE_SOURCE_DIR}/include)
