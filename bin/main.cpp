#include "geom/Vector2D.hpp"
#include "geom/Transform.hpp"
#include "geom/BoundingBox.hpp"
#include "geom/CollisionCheck.hpp"
#include "entity/Agent.hpp"
#include "entity/Obstacle.hpp"

#include <iostream>
#include <random>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

using namespace avs;

int main(int argc, char const *argv[])
{
    std::cout << "Testing functionality!" << std::endl << std::endl;

    std::cout << "Vector2D!" << std::endl << std::endl;
    geom::Vector2D vec1(1.34, 2.98);
    std::cout << vec1 << std::endl;
    geom::Vector2D uvec1 = vec1.get_unit_vector();
    std::cout << "Unit Vector1 : " << uvec1 << std::endl;
    geom::Vector2D vec2(5.54, 13.21);
    std::cout << vec2 << std::endl;
    geom::Vector2D vec3 = vec1 + vec2;
    std::cout << "Vector1 + Vector2 = " << vec3 << std::endl;
    geom::Vector2D vec4 = vec1 * 2;
    std::cout << "Vector1 * 2 = " << vec3 << std::endl;
    geom::Vector2D vec5 = 2 * vec1;
    std::cout << "2 * Vector1 = " << vec3 << std::endl;
    geom::Vector2D vec6 = vec1 / 2;
    std::cout << "Vector1 / 2 = " << vec3 << std::endl;
    geom::Vector2D vec7 = 2 / vec1;
    std::cout << "2 / Vector1 = " << vec3 << std::endl;

    std::cout << std::endl << "Transformation!" << std::endl << std::endl;
    geom::Transform trans(vec1, 90.0);
    std::cout << trans << std::endl;
    geom::Transform trans2(geom::Vector2D(1.0, 2.0), 180.0f);
    std::cout << trans2 << std::endl;


    std::random_device seed_generator;
    std::mt19937 random_generator(seed_generator());
    std::uniform_real_distribution<float> dist_coord(0, 1);
    std::uniform_real_distribution<float> dist_r(0, 360.0);

    const int n = 100;
    std::cout << std::endl << "Agent Collision Checking! (n=" << n << ")"  << std::endl << std::endl;
    std::vector<entity::Entity> my_entities;
    for (int i = 0; i < n; i++)
    {
        float x = dist_coord(seed_generator);
        float y = dist_coord(seed_generator);
        float r = dist_r(seed_generator);
        geom::Transform transform({x, y}, r);

        if (i <= n / 2 - 1)
        {
            entity::Agent agent(transform);
            my_entities.push_back(agent);
        }
        else
        {
            entity::Obstacle obstacle(transform);
            my_entities.push_back(obstacle);
        }
    }

    auto t1 = Clock::now();
    int counter = 0;
    geom::CollisionChecker cc = geom::CollisionChecker();
    for (auto it = my_entities.begin(); it < my_entities.end(); it++)
    {
        // Check collision Agent-Agent
        for (auto jt = it + 1; jt != my_entities.end(); jt++)
        {   
            counter += cc.check_collision(*it, *jt);
        }
    }
    auto t2 = Clock::now();
    std::cout << counter << " collisions were detected" << std::endl;
    std::cout << "Delta t2-t1: " 
              << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()
              << " microseconds" << std::endl << std::endl;
    
    geom::Transform transA({0.0f, 0.0f}, 0.0);
    entity::Agent agentA(transA);

    geom::Rectangle geometry = agentA.get_geometry();
    std::cout << agentA << std::endl;
    std::cout << geometry.front_left << std::endl;
    std::cout << geometry.front_right << std::endl;
    std::cout << geometry.back_left << std::endl;
    std::cout << geometry.front_right << std::endl;
    std::cout << "--------------------" << std::endl;
    geom::Transform transB({0.0f, 0.0f}, 45.0);
    agentA.set_transform(transB);
    geometry = agentA.get_geometry();
    std::cout << agentA << std::endl;
    std::cout << geometry.front_left << std::endl;
    std::cout << geometry.front_right << std::endl;
    std::cout << geometry.back_left << std::endl;
    std::cout << geometry.front_right << std::endl;
    std::cout << "--------------------" << std::endl;
    geom::Transform transC({-3.0f, 2.0f}, 0.0);
    agentA.set_transform(transC);
    geometry = agentA.get_geometry();
    std::cout << agentA << std::endl;
    std::cout << geometry.front_left << std::endl;
    std::cout << geometry.front_right << std::endl;
    std::cout << geometry.back_left << std::endl;
    std::cout << geometry.front_right << std::endl;

    return 0;
}
