#include "entity/Agent.hpp"


namespace avs {
namespace entity {

    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    Agent::Agent(const geom::Transform &transform, const geom::Vector2D &size, const int &lane_desire, const float &velocity_desire) : 
        Entity(counter++, transform, size)
        {
            desired_lane = lane_desire;
            desired_velocity = velocity_desire;
        }

    // ==================================================
    //  MEMBER VARIABLES
    // ==================================================

    
    
    // ==================================================
    //  METHODS
    // ==================================================
    
    void Agent::update_state()
    {
        // Translation and rotation of collision hull
        geometry.move_and_rotate(transform);

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
        geom::Vector2D forward_vector = geom::Math::get_forward_vector(transform.rotation);
        return forward_vector;
    }

    int Agent::get_desired_lane() const
    {
        return desired_lane;
    }

    float Agent::get_desired_velocity() const
    {
        return desired_velocity;
    }

    void Agent::set_location(const geom::Vector2D &new_location)
    {
        transform.location = new_location;
        Agent::update_state();
    }

    void Agent::set_transform(const geom::Transform &new_transform)
    {   
        transform.location = new_transform.location;
        transform.rotation = new_transform.rotation;
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
        out << "Agent(id=" << agent.get_id()
            << ", x="<< agent.get_transform().location.x
            << ", y=" << agent.get_transform().location.y
            << ", yaw=" << agent.get_transform().rotation
            << ", size=" << agent.get_size()
            << ", ld=" << agent.get_desired_lane()
            << ", v=" << agent.get_velocity()
            << ", vd=" << agent.get_desired_velocity()
            << ")";
        return out;
    }

} // namespace avs
} // namespace entity