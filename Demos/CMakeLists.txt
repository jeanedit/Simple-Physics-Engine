cmake_minimum_required(VERSION 3.18)
project(Demos)
set(CMAKE_CXX_STANDARD 17)

set(SRC_DIR src)
file(GLOB DEMOS_SRC "${SRC_DIR}/*.h" "${SRC_DIR}/*.cpp")

# Add your main.cpp file
add_executable(Demos ${DEMOS_SRC})


target_include_directories(Graphics PRIVATE "../Graphics/src")
target_include_directories(Cyclone PRIVATE "../Cyclone/src")

target_link_libraries(Demos PRIVATE glfw)
target_link_libraries(Demos PRIVATE glad)
target_link_libraries(Demos PRIVATE glm)
target_link_libraries(Demos PRIVATE Graphics)
target_link_libraries(Demos PRIVATE Cyclone)

	
# Add the necessary OpenGL flags
#find_package(OpenGL REQUIRED)
#if (OpenGL_FOUND)
#    target_link_libraries(Demos PRIVATE ${OPENGL_gl_LIBRARY})
#endif()
#
# Define the output directory for the executable
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
