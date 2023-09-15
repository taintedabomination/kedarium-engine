#version 330 core

in vec3 currentPosition;
in vec3 vertCol;
in vec2 vertTex;
in vec3 vertNorm;

out vec4 FragColor;

uniform sampler2D tex0;
uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform vec3 cameraPosition;

void main()
{
  vec3 normal = normalize(vertNorm);
  vec3 lightDirection = normalize(lightPosition - currentPosition);

  float ambient = 0.15f;
  float diffuse = max(dot(normal, lightDirection), 0.f);

  float specularIntensity = 0.5f;
  vec3 viewDirection = normalize(cameraPosition - currentPosition);
  vec3 reflectionDirection = reflect(-lightDirection, normal);
  float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.f), 8);
  float specular = specularAmount * specularIntensity;

  FragColor = texture(tex0, vertTex) * vec4(vertCol, 1.f) * lightColor * (diffuse + ambient + specular);
}
