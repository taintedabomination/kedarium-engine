# Version
cmake_minimum_required(VERSION 3.5)

# Constants
set(PROJECT_NAME "kedarium")
set(OpenGL_GL_PREFERENCE LEGACY)

# Project Name
project(${PROJECT_NAME})

# Packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# CXX Standard
set(CXX_STANDARD_REQUIRED 11)

# Executable
add_executable(
  ${PROJECT_NAME}
  src/Main.cpp
)
target_link_libraries(${PROJECT_NAME} PUBLIC GL GLEW glfw)
