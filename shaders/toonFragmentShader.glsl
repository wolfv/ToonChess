varying vec3 normal;

vec3 lightDir = vec3(0.0, 1.0, 1.0);

vec4 applyCelShading(vec4 color){
  float intensity = dot(lightDir, normalize(normal));
  float factor = 1.0;

  if(intensity < 0.5) factor = 0.5;

  color *= vec4(factor, factor, factor, 1.0);

  return color;
}

void main(void){
  vec4 color = vec4(0.63, 0.11, 0.11, 1.0);

  gl_FragColor = applyCelShading(color);
}
