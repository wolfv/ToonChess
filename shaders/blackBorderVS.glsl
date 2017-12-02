uniform bool selected;
vec4 position;

void main(void){
  // If the mesh is selected, move it
  if(selected){
    position = gl_Vertex + vec4(0, 0, 0.6, 0);
  } else {
    position = gl_Vertex;
  }

  // Enlarge the mesh
  float factor = 0.1;
  vec4 deformation = vec4(factor, factor, factor, 0.0) * normalize(position);
  vec4 deformedPosition = deformation + position;

  // The position of the vertex
  gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * deformedPosition;
}
