#ifndef SPLINERENDERER_H
#define SPLINERENDERER_H

#include <QOpenGLShaderProgram>

#include "../mesh/mesh.h"
#include "renderer.h"

/**
 * @brief The SplineRenderer class is responsible for rendering
 * Tessellated regular b-spline patches.
 */
class SplineRenderer : public Renderer {
 public:
  SplineRenderer();
  ~SplineRenderer() override;

  void updateUniforms();
  void updateBuffers(Mesh& m);
  void draw();

 protected:
  QOpenGLShaderProgram* constructSplineShader(const QString& name) const;
  void initShaders() override;
  void initBuffers() override;

 private:
  GLuint vao;
  GLuint meshCoordsBO, meshNormalsBO, meshIndexBO;
  int meshIBOSize;
  QOpenGLShaderProgram* splineShader;

  // Uniforms
  GLint uniModelViewMatrix, uniProjectionMatrix, uniNormalMatrix;
};

#endif  // TessRenderer_H
