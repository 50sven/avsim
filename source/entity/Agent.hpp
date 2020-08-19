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

class Agent : public Entity
{
private:
    static unsigned int counter;
    const float speed_limit = 30.0;

    geom::Vector2D velocity;
    geom::Vector2D acceleration;

    void update_state();

public:
    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    Agent() = default;
    Agent(const geom::Transform &transform);

    // ==================================================
    //  MEMBER VARIABLES
    // ==================================================
    


    // ==================================================
    //  METHODS
    // ==================================================
    
    geom::Vector2D get_velocity() const;

    geom::Vector2D get_acceleration() const;

    geom::Vector2D get_forward_vector() const;

    void set_location(const geom::Vector2D &new_location);

    void set_transform(const geom::Transform &new_transform);

    void set_velocity(const geom::Vector2D &new_velocity);

    void set_acceleration(const geom::Vector2D &new_acceleration);

    // ==================================================
    //  OPERATORS
    // ==================================================

    friend std::ostream &operator<<(std::ostream &out, const Agent &agent);

};

} // namespace avs
} // namespace entity