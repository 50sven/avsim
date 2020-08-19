#include "entity/Agent.hpp"


namespace avs {
namespace entity {

    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    Agent::Agent(const geom::Transform &transform) : 
        Entity(counter++, transform) {}

    // ==================================================
    //  MEMBER VARIABLES
    // ==================================================

    unsigned int Agent::counter = 0;
    
    // ==================================================
    //  METHODS
    // ==================================================
    
    void Agent::update_state()
    {
        // Translation and rotation of collision hull
        geometry.move_and_rotate(location, rotation);

        // Update bounding box
        bounding_box.update(geometry);
    }
    
    geom::Vector2D Agent::get_velocity() const
    {
        return velocity;
    }

    geom::Vector2D Agent::get_acceleration() const
    {
        return acceleration;
    }

    geom::Vector2D Agent::get_forward_vector() const
    {
        geom::Vector2D forward_vector = geom::Math::get_forward_vector(rotation);
        return forward_vector;
    }

    void Agent::set_location(const geom::Vector2D &new_location)
    {
        location = new_location;
        Agent::update_state();
    }

    void Agent::set_transform(const geom::Transform &new_transform)
    {   
        location = new_transform.location;
        rotation = new_transform.rotation;
        Agent::update_state();
    }

    void Agent::set_velocity(const geom::Vector2D &new_velocity)
    {
        velocity = new_velocity;
    }

    void Agent::set_acceleration(const geom::Vector2D &new_acceleration)
    {
        acceleration = new_acceleration;
    }

    // ==================================================
    //  OPERATORS
    // ==================================================

    std::ostream &operator<<(std::ostream &out, const Agent &agent)
    {
        out << "Agent(id=" << agent.id << ", x="<< agent.location.x << ", y=" << agent.location.y << ", yaw=" << agent.rotation << ")";
        return out;
    }

} // namespace avs
} // namespace entity