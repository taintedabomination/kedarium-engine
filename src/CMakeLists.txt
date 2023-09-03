# Library
add_library(
  Kedarium
  File.cpp
  Graphics.cpp
)

# Include Directory
target_include_directories(Kedarium PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
