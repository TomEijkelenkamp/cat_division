#version 410
layout(quads, equal_spacing, cw) in;

layout(location = 0) in vec3[] vertcoords_tc;
layout(location = 1) in vec3[] vertnormals_tc;

layout(location = 0) out vec3 vertcoords_te;
layout(location = 1) out vec3 vertnormals_te;

uniform mat4 modelviewmatrix;
uniform mat4 projectionmatrix;
uniform mat3 normalmatrix;

void main() {
  float u = gl_TessCoord.x;
  float v = gl_TessCoord.y;

  // Bilinear interpolation
  vec3 pos = mix(mix(vertcoords_tc[5], vertcoords_tc[6], u),
                 mix(vertcoords_tc[9], vertcoords_tc[10], u), v);

  vec3 normal = mix(mix(vertnormals_tc[5], vertnormals_tc[6], u),
                  mix(vertnormals_tc[9], vertnormals_tc[10], u), v);

  gl_Position = projectionmatrix * modelviewmatrix * vec4(pos, 1.0);
  vertcoords_te = vec3(modelviewmatrix * vec4(pos, 1.0));
  vertnormals_te = normalize(normalmatrix * normal);
}
