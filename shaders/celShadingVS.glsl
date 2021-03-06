#version 130

varying float vLightIntensity;
varying vec3 vLightPosition;

uniform vec3 lightDirection;

// View/Movement/Projection matrices
uniform mat4 VMatrix;
uniform mat4 MMatrix;
uniform mat4 PMatrix;

// Normal matrix
uniform mat4 NMatrix;

// Light matrix and projection light matrix
uniform mat4 LMatrix;
uniform mat4 PLMatrix;

vec4 lightPosition;
vec3 normal;
vec3 lightDir = normalize(lightDirection);

void main(void){
  // Compute the normal of the vertex and the light intensity
  normal = (NMatrix * vec4(gl_Normal, 1.0)).xyz;
  lightDir = lightDir;

  vLightIntensity = - dot(lightDir, normalize(normal));

  // Compute position in the light coordinates system
  lightPosition = PLMatrix * LMatrix * MMatrix * gl_Vertex;
  vLightPosition = vec3(0.5, 0.5, 0.5) +
    lightPosition.xyz/lightPosition.w * 0.5;

  // The position of the vertex
  gl_Position = PMatrix * VMatrix * MMatrix * gl_Vertex;
}
