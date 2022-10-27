file(GLOB MY_SRCS src/*.h src/*.cpp)
file(GLOB TEST01 test/main.cpp)
add_executable(HelloModel ${TEST01} ${MY_SRCS})
target_include_directories(
        HelloModel
        PUBLIC
        src
        ../deps/stb
)
target_link_libraries(
        HelloModel
        PUBLIC
        assimp::assimp
        glm::glm
        glfw
        glad
)
target_compile_definitions(
        HelloModel
        PUBLIC
        MY_SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/shader/"
        MY_TEXTURE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/texture/"
        MY_SRC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/src/"
        MY_MODEL_DIR="${CMAKE_CURRENT_SOURCE_DIR}/model/"
)