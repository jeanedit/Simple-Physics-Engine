cmake_minimum_required(VERSION 3.18)

project(Graphics)
set(CMAKE_CXX_STANDARD 17)

set(SRC_DIR src)
file(GLOB GRAPHICS_SRC "${SRC_DIR}/*.h" "${SRC_DIR}/*.cpp")

# Add the stb_image header and source files
set(STB_IMAGE_DIR "../Vendor/STB_IMAGE")
file(GLOB STB_IMAGE_FILES "${STB_IMAGE_DIR}/include/stb_image.h" "${STB_IMAGE_DIR}/src/stb_image.cpp")

add_library(Graphics STATIC ${GRAPHICS_SRC} ${STB_IMAGE_FILES})


# Link the executable to the GLFW library
target_link_libraries(Graphics PRIVATE glfw)
target_link_libraries(Graphics PRIVATE glad)
target_link_libraries(Graphics PRIVATE glm)

target_include_directories(Graphics PRIVATE "${STB_IMAGE_DIR}/include")
target_include_directories(Graphics INTERFACE ${SRC_DIR})
