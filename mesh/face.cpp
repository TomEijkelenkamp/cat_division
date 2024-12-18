#include "face.h"

#include <QDebug>

#include "halfedge.h"
#include "vertex.h"

/**
 * @brief Face::Face Creates a face with some default values.
 */
Face::Face() {
  side = nullptr;
  valence = 0;
  index = 0;
  normal = QVector3D();
}

/**
 * @brief Face::Face Creates a new face with a half-edge side, valence and
 * index.
 * @param side One of the half-edges that lives within this face.
 * @param valence Number of edges of this face.
 * @param index Index of the face within the mesh.
 */
Face::Face(HalfEdge* side, int valence, int index) {
  this->side = side;
  this->valence = valence;
  this->index = index;
  normal = QVector3D();
}

/**
 * @brief Face::recalculateNormal Recalculates the normal of this face.
 */
void Face::recalculateNormal() { normal = computeNormal(); }

/**
 * @brief Face::computeNormal Computes the normal of this face. Note that this
 * will not give the most accurate normal for non-planar faces.
 * @return The normal of this face.
 */
QVector3D Face::computeNormal() const {
  QVector3D pPrev = side->prev->origin->coords;
  QVector3D pCur = side->origin->coords;
  QVector3D pNext = side->next->origin->coords;

  QVector3D edgeA = pPrev - pCur;
  QVector3D edgeB = pNext - pCur;

  QVector3D faceNormal = QVector3D::crossProduct(edgeB, edgeA);
  // don't use normalized, since this presents issues with small numbers
  return faceNormal / faceNormal.length();
}

/**
 * @brief Face::computeCenter Computes the center coordinates of this face.
 * @return The center coordinates of this face.
 */
QVector3D Face::computeCenter() const {
    QVector3D center = side->origin->coords;
    HalfEdge *edge = side->next;
    while (edge != side) {
        center += edge->origin->coords;
        edge = edge->next;
    }
    return center / valence;
}

bool Face::isQuad() const {
    return valence == 4;
}

bool Face::isRegularQuad() const {
    if (!isQuad()) return false;

    HalfEdge *edge = side;
    do {
        if (edge->twin == nullptr || !edge->twin->face->isQuad()) {
            return false;
        }
        if (edge->origin == nullptr || edge->origin->valence != 4) {
            return false;
        }
        if (edge->twin->next->twin == nullptr || !edge->twin->next->twin->face->isQuad()) {
            return false;
        }
        edge = edge->next;
    } while (edge != side);

    return true;
}

/**
 * @brief Face::debugInfo Prints some debug info of this face.
 */
void Face::debugInfo() const {
  qDebug() << "Face at Index =" << index << "Side =" << side
           << "Val =" << valence;
}
