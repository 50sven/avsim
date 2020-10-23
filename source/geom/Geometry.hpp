#pragma once

#include "Vector2D.hpp"
#include "Transform.hpp"
#include "Math.hpp"

#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>


namespace avs {
namespace geom {

struct Rectangle
{
    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    Rectangle() = default;
    Rectangle(const Transform &trans, const Vector2D &size) :
        front_left(size.x / 2.0f, size.y / 2.0f),
        front_right(size.x / 2.0f, -size.y / 2.0f),
        back_left(-size.x / 2.0f, size.y / 2.0f),
        back_right(-size.x / 2.0f, -size.y / 2.0f),
        center(trans.location),
        rotation(trans.rotation)
        {
            front_left = geom::Math::rotate_vector_on_origin(front_left, rotation) + trans.location;
            front_right = geom::Math::rotate_vector_on_origin(front_right, rotation) + trans.location;
            back_left = geom::Math::rotate_vector_on_origin(back_left, rotation) + trans.location;
            back_right = geom::Math::rotate_vector_on_origin(back_right, rotation) + trans.location;
        }
    Rectangle(const Rectangle &rect) :
        front_left(rect.front_left),
        front_right(rect.front_right),
        back_left(rect.back_left),
        back_right(rect.back_right),
        center(rect.center),
        rotation(rect.rotation) {}
    
    // ==================================================
    //  MEMBER VARIABLES
    // ==================================================

    Vector2D front_left;
    Vector2D front_right;
    Vector2D back_left;
    Vector2D back_right;

    Vector2D center;
    float rotation;

    // ==================================================
    //  METHODS
    // ==================================================

    void move_and_rotate(const geom::Transform &new_transform)
    {
        geom::Vector2D new_location = new_transform.location;
        float new_deg = new_transform.rotation;

        geom::Vector2D translation_vector = new_location - center;
        float rotation_angle = new_deg - rotation;

        center = new_location;
        rotation = new_deg;

        front_left = geom::Math::rotate_vector_on_point(front_left + translation_vector, rotation_angle, new_location);
        front_right = geom::Math::rotate_vector_on_point(front_right + translation_vector, rotation_angle, new_location);
        back_left = geom::Math::rotate_vector_on_point(back_left + translation_vector, rotation_angle, new_location);
        back_right = geom::Math::rotate_vector_on_point(back_right + translation_vector, rotation_angle, new_location);
    }
    
    // ==================================================
    //  OPERATORS
    // ==================================================

    friend std::ostream &operator<<(std::ostream &out, const Rectangle &rect)
    {
        out << "Rectangle(front_left=" << rect.front_left << ", front_right=" << rect.front_right
            << ", back_left=" << rect.back_left << ", back_right=" << rect.back_right << ")";
        return out;
    }
};


struct Circle
{
    Vector2D center;
    float radius;

    void move(const Vector2D &new_location)
    {
        center = new_location;
    }

    friend std::ostream &operator<<(std::ostream &out, const Circle &c)
    {
        out << "Circle(x=" << c.center.x << ", y=" << c.center.y << ", r=" << c.radius << ")";
        return out;
    }
};

} // namespace geom
} // namespace avs