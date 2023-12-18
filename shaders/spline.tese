#version 410
layout(quads, equal_spacing, cw) in;

layout(location = 0) in vec3[] vertcoords_tc;
layout(location = 1) in vec3[] vertnormals_tc;

layout(location = 0) out vec3 vertcoords_te;
layout(location = 1) out vec3 vertnormals_te;

uniform mat4 modelviewmatrix;
uniform mat4 projectionmatrix;
uniform mat3 normalmatrix;

float B0(float u) {
  return (1-u) * (1-u) * (1-u) / 6;
}

float B1(float u) {
  return (4 - 6*u*u + 3*u*u*u) / 6;
}

float B2(float u) {
  return (1 + 3*u + 3*u*u - 3*u*u*u) / 6;
}

float B3(float u) {
  return u*u*u / 6;
}


void main() {
  float u = gl_TessCoord.x;
  float v = gl_TessCoord.y;

  vec3 pos = vertcoords_tc[0] * B0(u)*B3(v) + vertcoords_tc[1] * B1(u)*B3(v) + vertcoords_tc[2] * B2(u)*B3(v) + vertcoords_tc[3] * B3(u)*B3(v)
           + vertcoords_tc[4] * B0(u)*B2(v) + vertcoords_tc[5] * B1(u)*B2(v) + vertcoords_tc[6] * B2(u)*B2(v) + vertcoords_tc[7] * B3(u)*B2(v)
           + vertcoords_tc[8] * B0(u)*B1(v) + vertcoords_tc[9] * B1(u)*B1(v) + vertcoords_tc[10] * B2(u)*B1(v) + vertcoords_tc[11] * B3(u)*B1(v)
           + vertcoords_tc[12] * B0(u)*B0(v) + vertcoords_tc[13] * B1(u)*B0(v) + vertcoords_tc[14] * B2(u)*B0(v) + vertcoords_tc[15] * B3(u)*B0(v);

  vec3 nor = vertnormals_tc[0] * B0(u)*B3(v) + vertnormals_tc[1] * B1(u)*B3(v) + vertnormals_tc[2] * B2(u)*B3(v) + vertnormals_tc[3] * B3(u)*B3(v)
           + vertnormals_tc[4] * B0(u)*B2(v) + vertnormals_tc[5] * B1(u)*B2(v) + vertnormals_tc[6] * B2(u)*B2(v) + vertnormals_tc[7] * B3(u)*B2(v)
           + vertnormals_tc[8] * B0(u)*B1(v) + vertnormals_tc[9] * B1(u)*B1(v) + vertnormals_tc[10] * B2(u)*B1(v) + vertnormals_tc[11] * B3(u)*B1(v)
           + vertnormals_tc[12] * B0(u)*B0(v) + vertnormals_tc[13] * B1(u)*B0(v) + vertnormals_tc[14] * B2(u)*B0(v) + vertnormals_tc[15] * B3(u)*B0(v);

  gl_Position = projectionmatrix * modelviewmatrix * vec4(pos, 1.0);
  vertcoords_te = vec3(modelviewmatrix * vec4(pos, 1.0));
  vertnormals_te = normalize(normalmatrix * nor);
}
