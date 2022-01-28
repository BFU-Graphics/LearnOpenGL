add_definitions(
        -DMY_SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/shader/"
        -DMY_SRC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/src/"
)

file(GLOB MY_SRCS src/*.h src/*.cpp)
file(GLOB MY_TESTS test/main.cpp)

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
        glfw3
        glad
)
