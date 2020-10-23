#pragma once

#include "Vector2D.hpp"
#include "Math.hpp"
#include "entity/Entity.hpp"
#include "entity/Agent.hpp"
#include "entity/Obstacle.hpp"

#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>
#include <algorithm>

using vector_of_pairs = std::vector<std::pair<avs::entity::Entity, avs::entity::Entity>>;


namespace avs {
namespace geom {

class CollisionChecker
{
private:

    bool is_overlapping(const Rectangle &geometry_A, const Rectangle &geometry_B, const Vector2D &axis)
    {   
        // Calculate scalar values of the (pseudo) projections
        // Pseudo: axis is not normalize since only the relative values are required for the overlap check
        std::array<float, 4> projection_scalars_A;
        projection_scalars_A[0] = Math::dot_product(geometry_A.front_left, axis);
        projection_scalars_A[1] = Math::dot_product(geometry_A.front_right, axis);
        projection_scalars_A[2] = Math::dot_product(geometry_A.back_left, axis);
        projection_scalars_A[3] = Math::dot_product(geometry_A.back_right, axis);

        std::array<float, 4> projection_scalars_B;
        projection_scalars_B[0] = Math::dot_product(geometry_B.front_left, axis);
        projection_scalars_B[1] = Math::dot_product(geometry_B.front_right, axis);
        projection_scalars_B[2] = Math::dot_product(geometry_B.back_left, axis);
        projection_scalars_B[3] = Math::dot_product(geometry_B.back_right, axis);

        // Check for overlap
        float min_A = *std::min_element(projection_scalars_A.begin(), projection_scalars_A.end());
        float max_A = *std::max_element(projection_scalars_A.begin(), projection_scalars_A.end());
        float min_B = *std::min_element(projection_scalars_B.begin(), projection_scalars_B.end());
        float max_B = *std::max_element(projection_scalars_B.begin(), projection_scalars_B.end());

        if (max_A >= min_B && max_B >= max_A)
        {
            return true;
        }
        else if (max_B >= min_A && max_A >= max_B)
        {
            return true;
        }

        return false;
    }

public:
    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    CollisionChecker() = default;

    // ==================================================
    //  METHODS
    // ==================================================

    // This function assumes rectangles as geometries (but can be adapted to handle other geometries)
    bool check_collision(const entity::Entity &entity_A, const entity::Entity &entity_B)
    {
        // Quick pre-check for bounding box intersection
        BoundingBox bb_A = entity_A.get_bounding_box();
        BoundingBox bb_B = entity_B.get_bounding_box();
        bool is_intersecting = bb_A.intersects(bb_B);
        if (!is_intersecting)
        {   
            return false;
        }

        // Calculate projection axis
        // Only 4 are required, since two axis are always parallel
        Rectangle geometry_A = entity_A.get_geometry();
        Rectangle geometry_B = entity_B.get_geometry();
        std::array<Vector2D, 4> projection_axis;
        
        projection_axis[0] = geometry_A.front_left - geometry_A.front_right;
        projection_axis[1] = geometry_A.front_left - geometry_A.back_left;
        projection_axis[2] = geometry_B.front_left - geometry_B.front_right;
        projection_axis[3] = geometry_B.front_left - geometry_B.back_left;

        for (Vector2D const &axis : projection_axis)
        {   
            if (!is_overlapping(geometry_A, geometry_B, axis))
            {
                return false;
            }
        }
        
        return true;
    }

    vector_of_pairs check_collisions(const std::vector<entity::Agent> &agents, const std::vector<entity::Obstacle> &obstacles)
    {
        bool is_collided = false;
        vector_of_pairs collisions;
        for (auto it_agent_A = agents.begin(); it_agent_A < agents.end(); it_agent_A++)
        {
            // Check collision with other agents
            for (auto it_agent_B = it_agent_A + 1; it_agent_B < agents.end(); it_agent_B++)
            {
                is_collided = check_collision(*it_agent_A, *it_agent_B);
                if (is_collided == true)
                {
                    std::pair<entity::Entity, entity::Entity> collision_pair(*it_agent_A, *it_agent_B);
                    collisions.push_back(collision_pair);
                }
            }

            // Check collision with obstacles
            for (auto &obstacle : obstacles)
            {
                is_collided = check_collision(*it_agent_A, obstacle);
                if (is_collided == true)
                {
                    std::pair<entity::Entity, entity::Entity> collision_pair(*it_agent_A, obstacle);
                    collisions.push_back(collision_pair);
                }
            }
        }

        return collisions;
    }

    // ==================================================
    //  OPERATORS
    // ==================================================

    friend std::ostream &operator<<(std::ostream &out, const CollisionChecker &cc)
    {
        out << "CollisionChecker(SeparatingAxisTheorem)";
        return out;
    }

};

} // namespace geom
} // namespace avs


// Approximate collision with cirlce 
// Not used at all since Separating Axis Theorem is fast enough for small n (agents + obstacles)

// class CollisionHull
// {
// private:

//     std::vector<Circle> circles;
//     Vector2D *location;
//     float *rotation;

// public:
//     // ==================================================
//     //  CONSTRUCTORS
//     // ==================================================

//     CollisionHull() = default;
//     CollisionHull(Vector2D *loc, float *yaw, const Vector2D &size) :
//         location(loc),
//         rotation(yaw)
//     {   
//         // Check for coordinates
//         // Check general x-y-relations in all classes -> align to x-axis
//         int n_circles = int(size.x / size.y) + 1;
//         float delta_1 = size.x / (2 * n_circles);
//         float delta_2 = size.x / n_circles;
//         float radius = std::sqrt( (std::pow(size.y, 2) / 4) + std::pow(delta_1, 2) );
//         float x = -size.x / 2 + delta_1;
//         float y = 0.0f;
//         for (int i = 0; i < n_circles; i++)
//         {
//             Circle c;
//             c.center = Vector2D(x + delta_2 * i, y);
//             c.radius = radius;
//             circles.push_back(c);
//         }
//     }

//     ~CollisionHull()
//     {
//         location = nullptr;
//         rotation = nullptr;
//     }

//     // ==================================================
//     //  MEMBER VARIABLES
//     // ==================================================



//     // ==================================================
//     //  METHODS
//     // ==================================================

//     std::vector<Circle> get_circles() const
//     {
//         return circles;
//     }

//     Vector2D get_location() const
//     {
//         return *location;
//     }

//     float get_rotation() const
//     {
//         return *rotation;
//     }

//     bool intersects(const CollisionHull &ch) const
//     {   
//         Vector2D vector_diff = ch.get_location() - this->get_location();

//         for (auto const &this_circle : circles)
//         {
//             for (auto const &ch_circle : ch.get_circles())
//             {   
//                 Vector2D rotated_this_center = Math::rotate_vector_on_origin(this_circle.center, *rotation);
//                 Vector2D rotated_ch_center = Math::rotate_vector_on_origin(ch_circle.center, ch.get_rotation());
//                 rotated_ch_center += vector_diff;

//                 float distance = Math::calculate_distance(rotated_this_center, rotated_ch_center);
//                 if (distance <= this_circle.radius + ch_circle.radius)
//                 {
//                     return true;
//                 }
//             }
//         }
//         return false;
//     }

//     // ==================================================
//     //  OPERATORS
//     // ==================================================



// };