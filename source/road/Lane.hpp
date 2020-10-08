#pragma once

#include "../geom/Vector2D.hpp"
#include "../geom/Math.hpp"

namespace avs {
namespace road {


class Lane
{
protected:
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
            << ", width=" <<  lane.get_width()
            << ", length=" << lane.get_length()
            << ", start=" << lane.get_center()
            << ", forward=" << lane.get_forward_vector()
            << ")";
        return out;
    }

};

class Shoulder : public Lane
{
public:
    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    Shoulder() = default;
    Shoulder(const float &shoulder_id, const float &shoulder_width,
            const float &shoulder_length, const geom::Vector2D &center) :
        Lane(shoulder_id, shoulder_width, shoulder_length, center){}
    
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
            << ", width=" <<  shoulder.get_width()
            << ", length=" << shoulder.get_length()
            << ", start=" << shoulder.get_center()
            << ", forward=" << shoulder.get_forward_vector()
            << ")";
        return out;
    }
    
};

} // namespace road
} // namespace avs