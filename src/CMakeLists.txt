# Library
add_library(
  Kedarium
  Core.cpp
  File.cpp
  Window.cpp
  Graphics.cpp
  Camera.cpp
  Color.cpp
)

# Include Directory
target_include_directories(Kedarium PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
