#include "World.hpp"


namespace avs {
namespace world {


    geom::Vector2D World::get_random_position(geom::Vector2D &position, const YAML::Node &pos_conf)
    {
        float offset_x;
        float offset_y;
        std::string distribution = pos_conf["dist"].as<std::string>();

        if (distribution == "uniform")
        {
            float lower_bound_x = pos_conf["x"][0].as<float>();
            float upper_bound_x = pos_conf["x"][1].as<float>();
            float lower_bound_y = pos_conf["y"][0].as<float>();
            float upper_bound_y = pos_conf["y"][1].as<float>();

            offset_x = rnd_gen.get_uniform(lower_bound_x, upper_bound_x);
            offset_y = rnd_gen.get_uniform(lower_bound_y, upper_bound_y);
        }
        else if (distribution == "normal")
        {
            float mean_x = pos_conf["x"][0].as<float>();
            float std_x = pos_conf["x"][1].as<float>();
            float mean_y = pos_conf["y"][0].as<float>();
            float std_y = pos_conf["y"][1].as<float>();

            offset_x = rnd_gen.get_normal(mean_x, std_x);
            offset_y = rnd_gen.get_normal(mean_y, std_y);
        }
        else
        {
            assert("Distribution not supported. Use normal or uniform.");
        }

        position.x = offset_x;
        position.y += offset_y;

        return position;
    }

    std::tuple<geom::Vector2D, float> World::get_random_velocities(const YAML::Node &vel_conf)
    {
        geom::Vector2D velocity;
        float velocity_desire;
        std::string distribution = vel_conf["dist"].as<std::string>();

        if (distribution == "uniform")
        {
            float lower_bound_v = vel_conf["v"][0].as<float>();
            float upper_bound_v = vel_conf["v"][1].as<float>();
            float lower_bound_vd = vel_conf["desire"][0].as<float>();
            float upper_bound_vd = vel_conf["desire"][1].as<float>();

            velocity.x = rnd_gen.get_uniform(lower_bound_v, upper_bound_v);
            velocity_desire = rnd_gen.get_uniform(lower_bound_vd, upper_bound_vd);
        }
        else if (distribution == "normal")
        {
            float mean_v = vel_conf["v"][0].as<float>();
            float std_v = vel_conf["v"][1].as<float>();
            float mean_vd = vel_conf["desire"][0].as<float>();
            float std_vd = vel_conf["desire"][1].as<float>();

            velocity.x = rnd_gen.get_normal(mean_v, std_v);
            velocity_desire = rnd_gen.get_normal(mean_vd, std_vd);
        }
        else
        {
            assert("Distribution not supported. Use normal or uniform.");
        }
        
        return {velocity, velocity_desire};
    }

    void World::create_obstacles(const YAML::Node &obstacles_config)
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

    void World::create_agents(const YAML::Node &agents_config)
    {
        // Create agents
        for (auto const &ag : agents_config)
        {
            geom::Transform transform;
            geom::Vector2D size(ag["size"]["length"].as<float>(),
                                ag["size"]["width"].as<float>());
            entity::Agent agent(&road,
                                transform,
                                size,
                                ag["position"]["desire"].as<int>());
            agents.push_back(agent);
        }
    }

    void World::reset_agents()
    {
        std::cout << "---------------------RESET---------------------" << std::endl;
        YAML::Node agents_config = config["dynamic"]["agents"];

        for (auto &agent : agents)
        {
            int agent_idx = agent.get_id() - 1;
            YAML::Node ag = agents_config[agent_idx];

            // Get (randomized) position
            road::Lane lane = road.get_lane(ag["position"]["lane"].as<int>());
            geom::Vector2D position;

            if (ag["position"]["offset"]["dist"].as<std::string>() != "")
            {
                geom::Vector2D lane_center = lane.get_center();
                position = get_random_position(lane_center, ag["position"]["offset"]);
            }
            else
            {
                position = {lane.get_center()};
            }
            

            // Get (randomized) velocities
            geom::Vector2D velocity;
            float velocity_desire;

            if (ag["velocity"]["dist"].as<std::string>() != "")
            {
                auto [v, vd] = get_random_velocities(ag["velocity"]);
                velocity = {std::clamp(v.x, 5.0f, 20.0f), 0.0f};
                velocity_desire = std::clamp(vd, 8.0f, 16.0f);
            }
            else
            {
                velocity = {ag["velocity"]["v"][0].as<float>(), 0.0f};
                velocity_desire = ag["velocity"]["desire"][0].as<float>();
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
                rotation = 180.0f;
            }

            // Reset agent
            geom::Transform transform(position, rotation);
            agent.set_transform(transform);
            agent.set_velocity(velocity);
            agent.set_acceleration(geom::Vector2D(0.0f, 0.0f));
            entity::AgentState &state = agent.get_state();
            state.desired_velocity = velocity_desire;
            state.collision = false;
            state.collision_objects.clear();
        }
    }

    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    World::World(const std::string &config_file)
        {
            // Read config file
            std::filesystem::path path(config_file);
            if (path.is_relative())
            {
                throw std::invalid_argument("Relative path is used. Use absolute path instead.");
            }
            config = YAML::LoadFile(path);

            // Initialize seed generator
            if (!config["functional"]["seed"].IsNull())
            {
                rnd_gen = {config["functional"]["seed"].as<int>()};
            }

            // Build world elements
            road = {config["static"]["road"]};

            create_obstacles(config["static"]["obstacles"]);

            create_agents(config["dynamic"]["agents"]);

            reset();

            // Initialize rendering
            rendering_enabled = config["functional"]["rendering"].as<bool>();
            if (rendering_enabled == true)
            {
                renderer.init(road, obstacles);
            }
        }
    
    // ==================================================
    //  METHODS
    // ==================================================

    bool World::tick()
    {
        // Check for valid world state
        if (is_valid == false)
        {
            return false;
        }

        // Update agent states
        for (auto &agent : agents)
        {
            agent.update();
        }

        // Check for collisions
        bool collision = collision_checker.check_collisions(agents, obstacles);

        if (collision == true)
        {
            is_valid = false;
        }

        return is_valid;
    }

    void World::reset()
    {
        reset_agents();
        is_valid = true;
        tick();
    }

    void World::render()
    {
        renderer.draw(agents);
    }

    road::Road &World::get_road()
    {
        return road;
    }

    std::vector<entity::Agent> &World::get_agents()
    {
        return agents;
    }

    entity::Agent &World::get_agent(const int &agent_id)
    {
        auto it = std::find_if(agents.begin(), agents.end(), [agent_id]
        (const entity::Agent &agent) -> bool {return agent.get_id() == agent_id;});
        
        return *it;
    }

    std::vector<entity::Obstacle> &World::get_obstacles()
    {
        return obstacles;
    }

    entity::Obstacle &World::get_obstacle(const int &obstacle_id)
    {
        auto it = std::find_if(obstacles.begin(), obstacles.end(), [obstacle_id]
        (const entity::Obstacle &obstacle) -> bool {return obstacle.get_id() == obstacle_id;});
        
        return *it;
    }
    
    // ==================================================
    //  OPERATORS
    // ==================================================

    std::ostream &operator<<(std::ostream &out, World &world)
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


} // namespace avs
} // namespace world