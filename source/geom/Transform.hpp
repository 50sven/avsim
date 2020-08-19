#pragma once

#include "Vector2D.hpp"
#include "Math.hpp"

#include <iostream>
#include <iomanip>

namespace avs {
namespace geom {

class Transform
{
public:
    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    Transform() = default;
    Transform(const Vector2D &loc) : location(loc), rotation(0.0f) {}
    Transform(const Vector2D &loc, const float &yaw) : location(loc), rotation(yaw) {}
    Transform(const Transform &trans) : location(trans.location), rotation(trans.rotation) {}

    // ==================================================
    //  MEMBER VARIABLES
    // ==================================================

    Vector2D location;
    float rotation;

    // ==================================================
    //  METHODS
    // ==================================================

    Vector2D get_forward_vector() const
    {
        return Math::get_forward_vector(rotation);
    }

    float calculate_distance(const Transform &other_transform) const
    {
        return Math::calculate_distance(location, other_transform.location);
    }

    // ==================================================
    //  OPERATORS
    // ==================================================

    bool operator==(const Transform &other_transform) const
    {
      return (location == other_transform.location) && (rotation == other_transform.rotation);
    }

    bool operator!=(const Transform &other_transform) const
    {
      return !(*this == other_transform);
    }

    friend std::ostream &operator<<(std::ostream &out, const Transform &transform)
    {
        out << std::fixed << std::setprecision(2)
            << "Transform(x=" << transform.location.x << ", y="
            << transform.location.y << ", yaw="
            << transform.rotation << ")";
        return out;
    }

};

} // namespace geom
} // namespace avs