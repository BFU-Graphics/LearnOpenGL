file(GLOB MY_SRCS src/*.h src/*.cpp)

# HelloVulkan
file(GLOB HelloVulkan_src src/main.cpp)
add_executable(HelloVulkan ${MY_SRCS} ${HelloVulkan_src})
target_include_directories(
        HelloVulkan
        PRIVATE
        ${Vulkan_INCLUDE_DIRS}
)
target_link_directories(
        HelloVulkan
        PRIVATE
        src
)
target_link_libraries(
        HelloVulkan
        PRIVATE
        ${ASSIMP_LIBRARIES}
        glfw3
        glad
        ${Vulkan_LIBRARIES}
)