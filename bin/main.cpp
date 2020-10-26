#include "geom/Vector2D.hpp"
#include "geom/Transform.hpp"
#include "geom/BoundingBox.hpp"
#include "geom/CollisionCheck.hpp"
#include "entity/Agent.hpp"
#include "entity/Obstacle.hpp"
#include "entity/AgentState.hpp"
#include "road/Lane.hpp"
#include "road/Road.hpp"
#include "world/World.hpp"
#include "utils/Renderer.hpp"
#include "yaml-cpp/yaml.h"

#include <filesystem>
#include <iostream>
#include <random>
#include <chrono>
#include <string>

typedef std::chrono::high_resolution_clock Clock;

using namespace avs;

int main(int argc, char const *argv[])
{
    std::cout << std::endl << "World!" << std::endl << std::endl;

    std::filesystem::path cwd = std::filesystem::current_path();
    std::string config_file = cwd.string() + "/data/test.yaml";
    world::World world(config_file);
    bool is_valid;

    std::cout << std::endl << world << std::endl << std::endl;

    while(true)
    {
        // Update world state
        is_valid = world.tick();

        // Render world
        world.render();

        // Reset if world is not valid (=collision)
        if (is_valid == false)
        {
            world.reset();
            std::cout << std::endl << world << std::endl << std::endl;
        }

        // Move agents
        std::vector<entity::Agent> &agents = world.get_agents();
        for (auto &agent : agents)
        {
            entity::AgentState state = agent.get_state();
            geom::Vector2D location = agent.get_location();
            location.x += geom::Math::sign(agent.get_state().desired_lane) * 1.0;
            agent.set_location(location);
        }
    }

    return 0;
}
