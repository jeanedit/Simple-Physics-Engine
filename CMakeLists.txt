cmake_minimum_required(VERSION 3.18)
project(SimplePhysicsEngine)


add_subdirectory("Vendor/Glad")
add_subdirectory("Vendor/GLFW")
add_subdirectory("Vendor/GLM")

add_subdirectory("Graphics")
add_subdirectory("Cyclone")
add_subdirectory("Demos")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Demos)