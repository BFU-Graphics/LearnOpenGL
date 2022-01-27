add_executable(HelloTriangle src/main.cpp ${GLAD_SRC})
target_link_libraries(
        HelloTriangle
        PRIVATE
        ${ASSIMP_LIBRARIES}
        glfw3
)
