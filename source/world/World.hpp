#pragma once

#include "../road/Lane.hpp"
#include "../road/Road.hpp"
#include "../entity/Entity.hpp"
#include "../entity/Agent.hpp"
#include "../entity/Obstacle.hpp"
#include "../geom/CollisionCheck.hpp"
#include "../geom/Vector2D.hpp"
#include "../geom/Transform.hpp"
#include "../utils/Renderer.hpp"

#include <string>
#include <vector>
#include <utility>
#include <random>

using vector_of_pairs = std::vector<std::pair<avs::entity::Entity, avs::entity::Entity>>;


namespace avs {
namespace world {


class World
{
private:
    
    YAML::Node config;

    road::Road road;
    std::vector<entity::Agent> agents;
    std::vector<entity::Obstacle> obstacles;

    geom::CollisionChecker collision_checker;

    utils::Renderer renderer;
    bool rendering_enabled = false;

    void create_obstacles(const YAML::Node &obstacles_config)
    {
        // Add obstacles
        for (auto const &ob : obstacles_config)
        {
            // Get position
            road::Lane lane = road.get_lane(ob["position"]["lane"].as<int>());
            geom::Vector2D position(ob["position"]["offset"]["x"].as<float>(),
                                    ob["position"]["offset"]["y"].as<float>());
            position.y += lane.get_center().y;
            // Get rotation
            float rotation = ob["rotation"].as<float>();
            // Create obstacle
            geom::Transform transform(position, rotation);
            geom::Vector2D size(ob["size"]["length"].as<float>(),
                                ob["size"]["width"].as<float>());
            entity::Obstacle obstacle(transform, size);
            obstacles.push_back(obstacle);
        }
    }

    void create_agents(const YAML::Node &agents_config)
    {
        // Add agents
        for (auto const &ag : agents_config)
        {
            // Get (randomized) position
            road::Lane lane = road.get_lane(ag["position"]["lane"].as<int>());
            geom::Vector2D position(lane.get_center());

            if (ag["position"]["offset"]["dist"].as<std::string>() != "")
            {
                std::random_device rd_pos;
                std::mt19937 mt_pos(rd_pos());

                float offset_x = 0.0f;
                float offset_y = 0.0f;

                if (ag["position"]["offset"]["dist"].as<std::string>() == "uniform")
                {
                    float lower_bound_x = ag["position"]["offset"]["x"][0].as<float>();
                    float upper_bound_x = ag["position"]["offset"]["x"][1].as<float>();
                    float lower_bound_y = ag["position"]["offset"]["y"][0].as<float>();
                    float upper_bound_y = ag["position"]["offset"]["y"][1].as<float>();

                    std::uniform_real_distribution<float> dist_x(lower_bound_x, upper_bound_x);
                    std::uniform_real_distribution<float> dist_y(lower_bound_y, upper_bound_y);

                    offset_x = dist_x(mt_pos);
                    offset_y = dist_y(mt_pos);
                }
                else if (ag["position"]["offset"]["dist"].as<std::string>() == "normal")
                {
                    float mean_x = ag["position"]["offset"]["x"][0].as<float>();
                    float std_x = ag["position"]["offset"]["x"][1].as<float>();
                    float mean_y = ag["position"]["offset"]["y"][0].as<float>();
                    float std_y = ag["position"]["offset"]["y"][1].as<float>();

                    std::normal_distribution<float> dist_x(mean_x, std_x);
                    std::normal_distribution<float> dist_y(mean_y, std_y);

                    offset_x = dist_x(mt_pos);
                    offset_y = dist_y(mt_pos);
                }

                position.x = offset_x;
                position.y += offset_y;
            }

            // Get (randomized) velocity
            geom::Vector2D velocity(ag["velocity"]["v"][0].as<float>(), 0.0f);
            float velocity_desire = ag["velocity"]["desire"][0].as<float>();

            if (ag["velocity"]["dist"].as<std::string>() != "")
            {
                std::random_device rd_vel;
                std::mt19937 mt_vel(rd_vel());

                if (ag["velocity"]["dist"].as<std::string>() == "uniform")
                {
                    float lower_bound_v = ag["velocity"]["v"][0].as<float>();
                    float upper_bound_v = ag["velocity"]["v"][1].as<float>();
                    float lower_bound_vd = ag["velocity"]["desire"][0].as<float>();
                    float upper_bound_vd = ag["velocity"]["desire"][1].as<float>();

                    std::uniform_real_distribution<float> dist_v(lower_bound_v, upper_bound_v);
                    std::uniform_real_distribution<float> dist_vd(lower_bound_vd, upper_bound_vd);

                    velocity.x = dist_v(mt_vel);
                    velocity_desire = dist_vd(mt_vel);
                }
                else if (ag["velocity"]["dist"].as<std::string>() == "normal")
                {
                    float mean_v = ag["velocity"]["v"][0].as<float>();
                    float std_v = ag["velocity"]["v"][1].as<float>();
                    float mean_vd = ag["velocity"]["desire"][0].as<float>();
                    float std_vd = ag["velocity"]["desire"][1].as<float>();

                    std::normal_distribution<float> dist_v(mean_v, std_v);
                    std::normal_distribution<float> dist_vd(mean_vd, std_vd);

                    velocity.x = dist_v(mt_vel);
                    velocity_desire = dist_vd(mt_vel);
                }
            }

            // Get rotation (aligned to desired lane direction)
            float rotation;
            if (lane.get_id() > 0)
            {
                rotation = 0.0f;
            }
            else
            {
                velocity.x = -velocity.x;
                rotation = 180.0;
            }

            // Create agent
            geom::Transform transform(position, rotation);
            geom::Vector2D size(ag["size"]["length"].as<float>(),
                                ag["size"]["width"].as<float>());
            entity::Agent agent(transform,
                                size,
                                ag["position"]["desire"].as<int>(),
                                velocity_desire);
            agent.set_velocity(velocity);
            agents.push_back(agent);
        }
    }

public:
    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    World() = default;
    World(const std::string &config_file) :
        road(config_file)
        {
            std::filesystem::path path(config_file);
            if (path.is_relative())
            {
                throw std::invalid_argument("Relative path is used. Use absolute path instead.");
            }
            config = YAML::LoadFile(path);
            rendering_enabled = config["functional"]["rendering"].as<bool>();

            create_obstacles(config["static"]["obstacles"]);

            create_agents(config["dynamic"]["agents"]);

            if (rendering_enabled == true)
            {
                renderer.init(road, obstacles);
            }
        }
    
    // ==================================================
    //  METHODS
    // ==================================================

    void tick()
    {
        // Update world state
        vector_of_pairs collisions = collision_checker.check_collisions(agents, obstacles);
        if (collisions.size() > 0)
        {
            reset();
        }
    }

    void reset()
    {
        agents.clear();
        create_agents(config["dynamic"]["agents"]);
    }

    void render()
    {
        renderer.draw(agents);
    }

    const road::Road get_road() const
    {
        return road;
    }

    std::vector<entity::Agent> &get_agents()
    {
        return agents;
    }

    entity::Agent &get_agent(const int &agent_id)
    {
        auto it = std::find_if(agents.begin(), agents.end(), [agent_id]
        (const entity::Agent &agent) -> bool {return agent.get_id() == agent_id;});
        
        return *it;
    }

    std::vector<entity::Obstacle> get_obstacles() const
    {
        return obstacles;
    }

    entity::Obstacle get_obstacle(const int &obstacle_id) const
    {
        auto it = std::find_if(obstacles.begin(), obstacles.end(), [obstacle_id]
        (const entity::Obstacle &obstacle) -> bool {return obstacle.get_id() == obstacle_id;});
        
        return *it;
    }
    
    // ==================================================
    //  OPERATORS
    // ==================================================

    friend std::ostream &operator<<(std::ostream &out, World &world)
    {
        out << std::fixed << std::setprecision(2);
        out << "World(";
        for (auto &lane : world.get_road().get_lanes())
        {
            out << "\n   " << lane;
        }
        for (auto &shoulder : world.get_road().get_shoulders())
        {
            out << "\n   " << shoulder;
        }
        for (auto &agent : world.get_agents())
        {
            out << "\n   " << agent;
        }
        for (auto &obstacle : world.get_obstacles())
        {
            out << "\n   " << obstacle;
        }
        out << "\n)";
        return out;
    }
};


} // namespace avs
} // namespace world