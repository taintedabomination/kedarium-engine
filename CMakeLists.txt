# Version
cmake_minimum_required(VERSION 3.5)

# Constants
set(PROJECT_NAME "kedarium")

# Project Name
project(${PROJECT_NAME})

# CXX Standard
set(CXX_STANDARD_REQUIRED 11)

# Executable
add_executable(
  ${PROJECT_NAME}
  src/Main.cpp
)
