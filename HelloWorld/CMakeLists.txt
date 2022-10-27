file(GLOB MY_SRCS src/*.h src/*.cpp)
file(GLOB MY_TESTS test/main.cpp)
add_executable(HelloWorld ${MY_SRCS} ${MY_TESTS})
target_include_directories(HelloWorld
        PRIVATE
        src
        ../deps/stb
        )
target_link_libraries(
        HelloWorld
        PRIVATE
        assimp::assimp
        glm::glm
        glfw
        glad
)
target_compile_definitions(
        HelloWorld
        PRIVATE
        MY_SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/shader/"
        MY_TEXTURE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/texture/"
        MY_SRC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/src/"
)