#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 currentPosition;

uniform mat4 cameraMatrix;
uniform mat4 model;

void main()
{
  currentPosition = vec3(model * vec4(aPos, 1.0f));
  gl_Position = cameraMatrix * vec4(currentPosition, 1.f);
}
