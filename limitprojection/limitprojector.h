#ifndef LIMITPROJECTOR_H
#define LIMITPROJECTOR_H

#include "mesh/mesh.h"
#include <QOpenGLDebugLogger>

/**
 * @brief The Limitprojector class is an class that allows for limitprojection
 * meshes.
 */
class Limitprojector
{
public:
    Limitprojector();
    Mesh limitProjection(Mesh &controlMesh) const;

private:
    void reserveSizes(Mesh &controlMesh, Mesh &newMesh) const;
    void copyData(Mesh &controlMesh, Mesh &newMesh) const;
    QVector3D limitBoundaryVertex(const Vertex& vertex) const;
    QVector3D limitVertex(const Vertex& vertex) const;
};

#endif // LIMITPROJECTOR_H
