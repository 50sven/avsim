#pragma once

#include <cmath>
#include "Vector2D.hpp"


namespace avs {
namespace geom {

class Math {

public:

    static constexpr float to_radian(float deg)
    {
        return deg * (M_PI / 180.0);
    }

    static constexpr float to_degree(float rad)
    {
        return rad * (180.0 / M_PI);
    }

    static float dot_product(const Vector2D &vector_A, const Vector2D &vector_B)
    {
        return (vector_A.x * vector_B.x + vector_A.y * vector_B.y);  
    }

    static float calculate_distance(const Vector2D &vector_A, const Vector2D &vector_B)
    {
        return std::sqrt(std::pow((vector_A.x - vector_B.x), 2) + std::pow((vector_A.y - vector_B.y), 2));  
    }

    static float calculate_angle(const Vector2D &vector_A, const Vector2D &vector_B)
    {
        return to_degree(std::acos(dot_product(vector_A, vector_B) / (vector_A.get_length() * vector_B.get_length())));
    }

    static Vector2D get_forward_vector(const float &deg)
    {
        const float rad = Math::to_radian(deg);
        const float cy = std::cos(rad);
        const float sy = std::sin(rad);
        return {cy, sy};
    }

    static Vector2D rotate_vector_on_origin(const Vector2D &vector, const float &deg)
    {
        Vector2D new_vector(vector);
        float rad = to_radian(deg);
        new_vector.x = vector.x * std::cos(rad) - vector.y * std::sin(rad);
        new_vector.y = vector.x * std::sin(rad) + vector.y * std::cos(rad);
        return new_vector;
    }

    static Vector2D rotate_vector_on_point(const Vector2D &vector, const float deg, const Vector2D &point)
    {
        Vector2D new_vector(vector);
        new_vector -= point;
        new_vector = rotate_vector_on_origin(new_vector, deg);
        return new_vector + point;
    }

};

} // namespace avs
} // namespace geom