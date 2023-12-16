#ifndef LIMITPROJECTOR_H
#define LIMITPROJECTOR_H

#include "mesh/mesh.h"

/**
 * @brief The Limitprojector class is an abstract class that allows for limitprojection
 * meshes.
 */
class Limitprojector
{
public:
    Limitprojector();
    Mesh limitprojection(Mesh& mesh);
};

#endif // LIMITPROJECTOR_H
