#include "limitprojector.h"

/**
 * @brief Limitprojector::Limitprojector Creates an limitprojector.
 */
Limitprojector::Limitprojector() {}

/**
 * @brief Limitprojector::reserveSizes Resizes the vertex, half-edge and
 * face vectors. Also recalculates the edge count.
 * @param controlMesh The control mesh.
 * @param newMesh The new mesh. At this point, the mesh is fully empty.
 */
void Limitprojector::reserveSizes(Mesh &controlMesh, Mesh &newMesh) const {
    int newNumEdges = controlMesh.numEdges();
    int newNumFaces = controlMesh.numFaces();
    int newNumHalfEdges = controlMesh.numHalfEdges();
    int newNumVerts = controlMesh.numVerts();

    newMesh.getVertices().resize(newNumVerts);
    newMesh.getHalfEdges().resize(newNumHalfEdges);
    newMesh.getFaces().resize(newNumFaces);
    newMesh.edgeCount = newNumEdges;
}

void Limitprojector::copyData(Mesh &controlMesh, Mesh &newMesh) const {
    QVector<Vertex> &vertices = controlMesh.getVertices();
    QVector<HalfEdge> &halfEdges = controlMesh.getHalfEdges();
    QVector<Face> &faces = controlMesh.getFaces();

    QVector<Vertex> &newVertices = newMesh.getVertices();
    QVector<HalfEdge> &newHalfEdges = newMesh.getHalfEdges();
    QVector<Face> &newFaces = newMesh.getFaces();

    for (int v = 0; v < controlMesh.numVerts(); v++) {
        newVertices[v].out = &newHalfEdges[vertices[v].out->index];
        newVertices[v].index = vertices[v].index;
        newVertices[v].valence = vertices[v].valence;
    }

    for (int h = 0; h < controlMesh.numHalfEdges(); h++) {
        newHalfEdges[h].origin = &newVertices[halfEdges[h].origin->index];
        newHalfEdges[h].next = &newHalfEdges[halfEdges[h].next->index];
        newHalfEdges[h].prev = &newHalfEdges[halfEdges[h].prev->index];
        newHalfEdges[h].twin = halfEdges[h].twin != nullptr ? &newHalfEdges[halfEdges[h].twin->index] : nullptr;
        newHalfEdges[h].face = &newFaces[halfEdges[h].face->index];
        newHalfEdges[h].index = halfEdges[h].index;
        newHalfEdges[h].edgeIndex = halfEdges[h].edgeIndex;
    }

    for (int f = 0; f < controlMesh.numFaces(); f++) {
        newFaces[f].side = &newHalfEdges[faces[f].side->index];
        newFaces[f].index = faces[f].index;
        newFaces[f].valence = faces[f].valence;
    }
}

Mesh Limitprojector::limitProjection(Mesh &controlMesh) const {
    Mesh newMesh;
    reserveSizes(controlMesh, newMesh);
    copyData(controlMesh, newMesh);

    QVector<Vertex> &vertices = controlMesh.getVertices();
    QVector<Vertex> &newVertices = newMesh.getVertices();

    // Vertex Points
    for (int v = 0; v < controlMesh.numVerts(); v++) {
        if (vertices[v].isBoundaryVertex()) {
            newVertices[v].coords = limitBoundaryVertex(vertices[v]);
        } else {
            newVertices[v].coords = limitVertex(vertices[v]);
        }
    }

    return newMesh;
}


QVector3D Limitprojector::limitBoundaryVertex(const Vertex& vertex) const {
    // Boundary limit stencil [1 4 1] / 6
    return (vertex.prevBoundaryHalfEdge()->origin->coords + vertex.coords*4 + vertex.nextBoundaryHalfEdge()->next->origin->coords) / 6;
}

QVector3D Limitprojector::limitVertex(const Vertex& vertex) const {
    QVector3D v = vertex.coords;
    QVector3D m;
    QVector3D c;
    QVector3D mc = QVector3D(0.0f, 0.0f, 0.0f);
    float n = vertex.valence;
    HalfEdge *edge = vertex.out;

    // Loop through all edges surrounding vertex v
    for (int i=0; i<n; i++) {
        // Midpoint on the edge
        m = (edge->origin->coords + edge->next->origin->coords)/2;

        // Average of the vertices of the face
        c = edge->face->computeCenter();

        // Sum edgemidpoint and facecenter
        mc += (m + c);

        // Next edge
        edge = edge->twin->next;
    }

    return ((n-3)/(n+5)) * v + (4/(n*(n+5))) * mc;
}
