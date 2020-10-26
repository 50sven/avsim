#pragma once

#include "Entity.hpp"

#include "../geom/Vector2D.hpp"
#include "../geom/Transform.hpp"

#include <vector>


namespace avs {
namespace entity {


struct AgentState
{
    // ==================================================
    //  MEMBER VARIABLES
    // ==================================================

    // Dynamics
    geom::Vector2D location;
    geom::Vector2D velocity;
    geom::Vector2D acceleration;
    float rotation;

    // Statics
    geom::Vector2D size;    // currently constant
    int desired_lane;       // constant
    float desired_velocity; // randomized per episode

    // Lane
    int current_lane;
    float distance_to_center;
    float delta_rotation;

    // Collision
    bool collision;
    std::vector<entity::Entity> collision_objects;

    // ==================================================
    //  OPERATORS
    // ==================================================

    friend std::ostream &operator<<(std::ostream &out, const AgentState &state)
    {
        out << "AgentState(x=" << state.location.x
            << ", y=" << state.location.y
            << ", v=" << state.velocity
            << ", a=" << state.acceleration
            << ", yaw=" << state.rotation
            << ", size=" << state.size
            << ", ld=" << state.desired_lane
            << ", vd=" << state.desired_velocity
            << ", cl=" << state.current_lane
            << ", dtc=" << state.distance_to_center
            << ", dr=" << state.delta_rotation
            << ", coll=" << state.collision
            << ")";
        return out;
    }
};


}   // namespace entity
}   // namespace avs
