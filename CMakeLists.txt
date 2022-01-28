cmake_minimum_required(VERSION 3.21)
project(LearnOpenGL)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(MY_EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external)

find_package(MY_GLFW REQUIRED)
find_package(MY_ASSIMP REQUIRED)
find_package(MY_GLAD REQUIRED)
find_package(MY_GLM REQUIRED)

include_directories(${MY_EXTERNAL_DIR}/include)
link_directories(${MY_EXTERNAL_DIR}/bin external/lib)

add_subdirectory(HelloWorld)
