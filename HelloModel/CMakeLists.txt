add_definitions(
        -DMY_MODEL_DIR="${CMAKE_CURRENT_SOURCE_DIR}/model/"
        -DMY_SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/shader/"
        -DMY_TEXTURE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/texture/"
        -DMY_SRC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/src/"
)

file(GLOB MY_SRCS src/*.h src/*.cpp)

file(GLOB TEST01 test/test01/main.cpp)
add_executable(HelloModelTest01 ${TEST01} ${MY_SRCS})
target_include_directories(
        HelloModelTest01
        PRIVATE
        src
)
target_link_libraries(
        HelloModelTest01
        PRIVATE
        ${ASSIMP_LIBRARIES}
        glfw
        glad
)
