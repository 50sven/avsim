#pragma once

#include "Entity.hpp"
#include "AgentState.hpp"

#include "../geom/Vector2D.hpp"
#include "../geom/Transform.hpp"
#include "../geom/BoundingBox.hpp"
#include "../geom/Geometry.hpp"
#include "../geom/Math.hpp"
#include "../road/Lane.hpp"
#include "../road/Road.hpp"

#include <string>
#include <utility>
#include <cmath>


namespace avs {
namespace entity {

class Agent : public Entity
{
private:
    inline static int counter = 1;

    road::Road *road_ptr = nullptr;

    AgentState state;

    geom::Vector2D velocity;
    geom::Vector2D acceleration;

    void update_state();

public:
    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    Agent() = default;
    Agent(road::Road *road_ptr, const geom::Transform &transform, const geom::Vector2D &size, const int &lane_desire);
    ~Agent();

    // ==================================================
    //  MEMBER VARIABLES
    // ==================================================
    
    

    // ==================================================
    //  METHODS
    // ==================================================

    void update();

    AgentState &get_state();

    geom::Vector2D get_location();

    geom::Transform get_transform();
    
    geom::Vector2D get_velocity();

    geom::Vector2D get_acceleration();

    geom::Vector2D get_forward_vector();

    std::pair<road::Lane, float> get_nearest_lane();

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