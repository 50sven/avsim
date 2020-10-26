#pragma once

#include "../road/Lane.hpp"
#include "../road/Road.hpp"
#include "../entity/Entity.hpp"
#include "../entity/Agent.hpp"
#include "../entity/Obstacle.hpp"
#include "../geom/CollisionCheck.hpp"
#include "../geom/Vector2D.hpp"
#include "../geom/Transform.hpp"
#include "../utils/RandomGenerator.hpp"
#include "../utils/Renderer.hpp"

#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <utility>
#include <random>
#include <assert.h>


namespace avs {
namespace world {


class World
{
private:
    
    YAML::Node config;
    utils::RandomFloatGenerator rnd_gen;

    road::Road road;
    std::vector<entity::Agent> agents;
    std::vector<entity::Obstacle> obstacles;

    geom::CollisionChecker collision_checker;

    utils::Renderer renderer;
    bool rendering_enabled = false;
    
    bool is_valid = true;

    geom::Vector2D get_random_position(geom::Vector2D &position, const YAML::Node &pos_conf);

    std::tuple<geom::Vector2D, float> get_random_velocities(const YAML::Node &vel_conf);

    void create_obstacles(const YAML::Node &obstacles_config);

    void create_agents(const YAML::Node &agents_config);

    void reset_agents();

public:
    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    World() = default;
    World(const std::string &config_file);
    
    // ==================================================
    //  METHODS
    // ==================================================

    bool tick();

    void reset();

    void render();

    road::Road &get_road();

    std::vector<entity::Agent> &get_agents();

    entity::Agent &get_agent(const int &agent_id);

    std::vector<entity::Obstacle> &get_obstacles();

    entity::Obstacle &get_obstacle(const int &obstacle_id);
    
    // ==================================================
    //  OPERATORS
    // ==================================================

    friend std::ostream &operator<<(std::ostream &out, World &world);

};


} // namespace avs
} // namespace world