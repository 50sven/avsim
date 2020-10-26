#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <assert.h>


namespace avs {
namespace geom {

struct Vector2D
{
    // ==================================================
    //  CONSTRUCTORS
    // ==================================================
    Vector2D() = default;
    Vector2D(const float &ix, const float &iy) : x(ix), y(iy) {}
    Vector2D(const Vector2D &v) : x(v.x), y(v.y) {}

    // ==================================================
    //  MEMBER VARIABLES
    // ==================================================

    float x = 0.0f;
    float y = 0.0f;

    // ==================================================
    //  METHODS
    // ==================================================

    float get_length() const
    {
        return std::sqrt(x * x + y * y);
    }

    Vector2D get_unit_vector() const
    {
        const float length = get_length();
        assert(length > 2.0f * std::numeric_limits<float>::epsilon() && "Division by zero!");
        const float n = 1 / length;
        return Vector2D(x * n, y * n);
    }

    Vector2D get_normal_vector() const
    {
        return Vector2D(-y, x);
    }

    // ==================================================
    //  OPERATORS
    // ==================================================

    Vector2D operator+(const Vector2D &other_vector) const
    {
        Vector2D vector(*this);
        vector += other_vector;
        return vector;
    }

    Vector2D &operator+=(const Vector2D &other_vector)
    {
        x += other_vector.x;
        y += other_vector.y;
        return *this;
    }

    Vector2D operator-(const Vector2D &other_vector) const
    {
        Vector2D vector(*this);
        vector -= other_vector;
        return vector;
    }

    Vector2D &operator-=(const Vector2D &other_vector)
    {
        x -= other_vector.x;
        y -= other_vector.y;
        return *this;
    }

    friend Vector2D operator*(const Vector2D this_vector, const float a)
    {
        Vector2D vector(this_vector);
        vector *= a;
        return vector;
    }

    friend Vector2D operator*(const float a, const Vector2D this_vector)
    {   
        Vector2D vector(this_vector);
        vector *= a;
        return vector;
    }

    Vector2D &operator*=(const float a)
    {
        x *= a;
        y *= a;
        return *this;
    }

    friend Vector2D operator/(const Vector2D this_vector, const float a)
    {   
        Vector2D vector(this_vector);
        vector /= a;
        return vector;
    }

    friend Vector2D operator/(const float a, const Vector2D this_vector)
    {   
        Vector2D vector(this_vector);
        vector.x = a / vector.x;
        vector.y = a / vector.y;
        return vector;
    }

    Vector2D &operator/=(const float a)
    {
        x /= a;
        y /= a;
        return *this;
    }

    bool operator==(const Vector2D &other_vector) const
    {
        return (x == other_vector.x) && (y == other_vector.y);
    }

    bool operator!=(const Vector2D &other_vector) const
    {
        return !(*this == other_vector);
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector2D &vector)
    {
        out << std::fixed << std::setprecision(2)
            << "Vector2D(x=" << vector.x << ", y=" << vector.y << ")";
        return out;
    }
};

} // namespace geom
} // namespace avs