#version 130

uniform mat4 VMatrix;
uniform mat4 MMatrix;
uniform mat4 PMatrix;

void main(void){
  // Enlarge the mesh
  float factor = 0.1;
  vec4 deformation = vec4(factor, factor, factor, 0.0) * normalize(gl_Vertex);
  vec4 deformedPosition = deformation + gl_Vertex;

  // The position of the vertex
  gl_Position = PMatrix * VMatrix * MMatrix * deformedPosition;
}
