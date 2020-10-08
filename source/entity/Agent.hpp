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
    inline static int counter = 1;
    int desired_lane;
    float desired_velocity;

    geom::Vector2D velocity;
    geom::Vector2D acceleration;

    void update_state();

public:
    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    Agent() = default;
    Agent(const geom::Transform &transform, const geom::Vector2D &size, const int &lane_desire=1, const float &velocity_desire=12.0f);

    // ==================================================
    //  MEMBER VARIABLES
    // ==================================================
    
    

    // ==================================================
    //  METHODS
    // ==================================================
    
    geom::Vector2D get_velocity() const;

    geom::Vector2D get_acceleration() const;

    geom::Vector2D get_forward_vector() const;

    int get_desired_lane() const;

    float get_desired_velocity() const;

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