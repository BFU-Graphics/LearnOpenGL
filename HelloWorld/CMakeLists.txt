add_definitions(
        -DMY_SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/shader/"
        -DMY_TEXTURE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/texture/"
        -DMY_SRC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/src/"
)

file(GLOB MY_SRCS src/*.h src/*.cpp)

# TEST BasicFrameWork
file(GLOB MY_TESTS test/BasicFrameWork/main.cpp)
add_executable(HelloWorld ${MY_SRCS} ${MY_TESTS})
target_include_directories(
        HelloWorld
        PRIVATE
        src
)
target_link_libraries(
        HelloWorld
        PRIVATE
        ${ASSIMP_LIBRARIES}
        glfw
        glad
)