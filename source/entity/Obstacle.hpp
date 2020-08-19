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

    static unsigned int counter;

public:
    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    Obstacle() = default;
    Obstacle(const geom::Transform &transform);

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