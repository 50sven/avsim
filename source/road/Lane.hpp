#pragma once

#include "../geom/Vector2D.hpp"
#include "../geom/Math.hpp"

namespace avs {
namespace road {


class Lane
{
private:
    int id;
    float width;
    float length;
    geom::Vector2D center;
    geom::Vector2D forward_vector;

public:
    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    Lane() = default;
    Lane(const int &lane_id, const float &lane_width, const float &lane_length,
        const geom::Vector2D &center) :
        id(lane_id),
        width(lane_width),
        length(lane_length),
        center(center),
        forward_vector(geom::Math::sign(lane_id), 0.0f) {}

    // ==================================================
    //  METHODS
    // ==================================================

    int get_id() const
    {
        return id;
    }

    float get_width() const
    {
        return width;
    }

    float get_length() const
    {
        return length;
    }

    geom::Vector2D get_center() const
    {
        return center;
    }

    geom::Vector2D get_forward_vector() const
    {
        return forward_vector;
    }

    // ==================================================
    //  OPERATORS
    // ==================================================

    bool operator==(const Lane &other_lane) const
    {
        return (id == other_lane.id);
    }

    bool operator!=(const Lane &other_lane) const
    {
        return !(*this == other_lane);
    }

    friend std::ostream &operator<<(std::ostream &out, const Lane &lane)
    {
        out << std::fixed << std::setprecision(2)
            << "Lane(id=" << lane.get_id()
            << ", start=(x=" << lane.get_center().x
            << ", y=" << lane.get_center().y << "), "
            << "forward(x=" << lane.get_forward_vector().x
            << ", y=" << lane.get_forward_vector().y << "))";
        return out;
    }

};

class Shoulder
{
private:
    int id;
    float width;
    float length;
    geom::Vector2D center;
    geom::Vector2D forward_vector;

public:
    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    Shoulder() = default;
    Shoulder(const float &shoulder_id, const float &shoulder_width,
            const float &shoulder_length, const geom::Vector2D &center) :
        id(shoulder_id),
        width(shoulder_width),
        length(shoulder_length),
        center(center),
        forward_vector(geom::Math::sign(shoulder_id), 0.0f) {}
    
    // ==================================================
    //  METHODS
    // ==================================================

    int get_id() const
    {
        return id;
    }

    float get_width() const
    {
        return width;
    }

    float get_length() const
    {
        return length;
    }

    geom::Vector2D get_center() const
    {
        return center;
    }

    geom::Vector2D get_forward_vector() const
    {
        return forward_vector;
    }
    
    // ==================================================
    //  OPERATORS
    // ==================================================

    bool operator==(const Shoulder &other_shoulder) const
    {
        return (id == other_shoulder.id);
    }

    bool operator!=(const Shoulder &other_shoulder) const
    {
        return !(*this == other_shoulder);
    }
    
    friend std::ostream &operator<<(std::ostream &out, const Shoulder &shoulder)
    {
        out << std::fixed << std::setprecision(2)
            << "Shoulder(id=" << shoulder.get_id()
            << ", start=(x=" << shoulder.get_center().x
            << ", y=" << shoulder.get_center().y << "), "
            << "forward(x=" << shoulder.get_forward_vector().x
            << ", y=" << shoulder.get_forward_vector().y << "))";
        return out;
    }
    
};

} // namespace road
} // namespace avs