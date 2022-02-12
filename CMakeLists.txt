cmake_minimum_required(VERSION 3.15)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(MY_EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/../Graphics-Dependencies/install)

find_package(MY_GLFW REQUIRED)
find_package(MY_ASSIMP REQUIRED)
find_package(MY_GLAD REQUIRED)
find_package(MY_GLM REQUIRED)

include_directories(${MY_EXTERNAL_DIR}/include)
link_directories(${MY_EXTERNAL_DIR}/bin ${MY_EXTERNAL_DIR}/lib)

add_subdirectory(HelloWorld)
add_subdirectory(HelloModel)