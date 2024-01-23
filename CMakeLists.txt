cmake_minimum_required(VERSION 3.15)
project(TreeGenerator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

set(SFML_DIR "C:/Users/Kener/Desktop/Games/libs/SFML-2.6.0/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)

include_directories(include)
file(GLOB_RECURSE HEADERS "include/**/*.h" "include/**/*.hpp")
file(GLOB_RECURSE SOURCES "src/**/*.cpp" "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio)

if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32;_CRT_SECURE_NO_WARNINGS)
endif()