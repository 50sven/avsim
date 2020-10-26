#include "entity/Agent.hpp"


namespace avs {
namespace entity {

    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    Agent::Agent(road::Road *r_ptr, const geom::Transform &transform, const geom::Vector2D &size, const int &lane_desire) : 
        Entity(counter++, transform, size),
        road_ptr(r_ptr)
        {
            update();

            state.size = size;
            state.desired_lane = lane_desire;
        }
    
    Agent::~Agent()
    {
        road_ptr = nullptr;
    }

    // ==================================================
    //  METHODS
    // ==================================================
    
    void Agent::update()
    {
        // Update state
        update_state();

        // Translate and rotate collision hull
        geom::Transform transform = get_transform();
        geometry.move_and_rotate(transform);

        // Update bounding box
        bounding_box.update(geometry);
    }

    void Agent::update_state()
    {
        // Dynamics
        state.location = transform.location;
        state.velocity = velocity;
        state.acceleration = acceleration;
        state.rotation = transform.rotation;

        // Lane
        auto nearest_lane = get_nearest_lane();
        state.current_lane = nearest_lane.first.get_id();
        state.distance_to_center = nearest_lane.second;

        // Orientation
        state.delta_rotation = geom::Math::calculate_angle(get_forward_vector(), nearest_lane.first.get_forward_vector());
    }

    AgentState &Agent::get_state()
    {
        return state;
    }

    geom::Vector2D Agent::get_location()
    {
        return state.location;
    }

    geom::Transform Agent::get_transform()
    {
        geom::Transform state_transform(state.location, state.rotation);
        return state_transform;
    }
    
    geom::Vector2D Agent::get_velocity()
    {
        return state.velocity;
    }

    geom::Vector2D Agent::get_acceleration()
    {
        return state.acceleration;
    }

    geom::Vector2D Agent::get_forward_vector()
    {
        geom::Vector2D forward_vector = geom::Math::get_forward_vector(state.rotation);
        return forward_vector;
    }

    std::pair<road::Lane, float> Agent::get_nearest_lane()
    {
        std::vector<road::Lane> lanes = road_ptr->get_lanes();
        std::pair<road::Lane, float> nearest_lane;
        nearest_lane.second = 100.0f;

        for (auto &lane : lanes)
        {
            float distance = std::abs(state.location.y - lane.get_center().y);
            if (distance < nearest_lane.second &&
                geom::Math::sign(lane.get_id()) == geom::Math::sign(state.desired_lane))
            {
                nearest_lane.first = lane;
                nearest_lane.second = distance;
            }
        }

        return nearest_lane;
    }

    void Agent::set_location(const geom::Vector2D &new_location)
    {
        transform.location = new_location;
    }

    void Agent::set_transform(const geom::Transform &new_transform)
    {   
        transform.location = new_transform.location;
        transform.rotation = new_transform.rotation;
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
            << ", x="<< agent.state.location.x
            << ", y=" << agent.state.location.y
            << ", yaw=" << agent.state.rotation
            << ", size=" << agent.state.size
            << ", ld=" << agent.state.desired_lane
            << ", v=" << agent.state.velocity
            << ", vd=" << agent.state.desired_velocity
            << ")";
        return out;
    }

} // namespace avs
} // namespace entity