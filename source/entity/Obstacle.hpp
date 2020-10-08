#pragma once

#include "Entity.hpp"
#include "../geom/Vector2D.hpp"
#include "../geom/Transform.hpp"
#include "../geom/BoundingBox.hpp"
#include "../geom/Geometry.hpp"
#include "../geom/Math.hpp"

#include <string>


namespace avs {
namespace entity {

class Obstacle : public Entity
{
private:

    inline static int counter = -1;

public:
    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    Obstacle() = default;
    Obstacle(const geom::Transform &transform, const geom::Vector2D &size);

    // ==================================================
    //  MEMBER VARIABLES
    // ==================================================



    // ==================================================
    //  METHODS
    // ==================================================



    // ==================================================
    //  OPERATORS
    // ==================================================

    friend std::ostream &operator<<(std::ostream &out, const Obstacle &obstacle);

};

} // namespace avs
} // namespace entity