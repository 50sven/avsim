#pragma once

#include "Vector2D.hpp"
#include "Geometry.hpp"

#include <ostream>
#include <iomanip>
#include <algorithm>
#include <array>


namespace avs {
namespace geom {

struct BoundingBox
{
    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    BoundingBox() = default;
    BoundingBox(const float &x, const float &y, const float &ex, const float &ey) :
        center(Vector2D(x, y)),
        extent(Vector2D(ex, ey)){}
    BoundingBox(const Vector2D &loc, const Vector2D &ext) :
        center(loc),
        extent(ext) {}
    BoundingBox(const Rectangle &rect) :
        center(rect.center)
        {
            float max_x = std::max({rect.front_left.x, rect.front_right.x, rect.back_left.x, rect.back_right.x});
            float max_y = std::max({rect.front_left.y, rect.front_right.y, rect.back_left.y, rect.back_right.y});

            extent.x = max_x - center.x;
            extent.y = max_y - center.y;
        }
    BoundingBox(const BoundingBox &other_bb) :
        center(other_bb.center),
        extent(other_bb.extent) {}
    
    // ==================================================
    //  MEMBER VARIABLES
    // ==================================================

    Vector2D center;
    Vector2D extent;
    
    // ==================================================
    //  METHODS
    // ==================================================
    
    bool contains(const Vector2D &point) const
    {
        Vector2D point_in_bb_space = point - center;
        return  point_in_bb_space.x <= extent.x && point_in_bb_space.x >= -extent.x &&
                point_in_bb_space.y <= extent.y && point_in_bb_space.y >= -extent.y;
    }

    bool intersects(BoundingBox &other_bb) const
    {
        // Get bottom-left and top-right corner of the this bounding box
        Vector2D bottomleft = center + Vector2D(-extent.x, -extent.y);
        Vector2D top_right = center + Vector2D(extent.x, extent.y);
        // Get bottom-left and top-right corner of the other bounding box
        Vector2D other_bb_bottomleft = other_bb.center + Vector2D(-other_bb.extent.x, -other_bb.extent.y);
        Vector2D other_bb_top_right = other_bb.center + Vector2D(other_bb.extent.x, other_bb.extent.y);
        // Check collision via axis projections
        bool horizontal_overlap = (bottomleft.x <= other_bb_top_right.x && top_right.x >= other_bb_bottomleft.x);
        bool vertical_overlap = (bottomleft.y <= other_bb_top_right.y && top_right.y >= other_bb_bottomleft.y);

        return (horizontal_overlap && vertical_overlap);
    }

    void update(const Rectangle &rectangle)
    {
        center = rectangle.center;

        float max_x = std::max({rectangle.front_left.x, rectangle.front_right.x, rectangle.back_left.x, rectangle.back_right.x});
        float max_y = std::max({rectangle.front_left.y, rectangle.front_right.y, rectangle.back_left.y, rectangle.back_right.y});

        extent.x = max_x - center.x;
        extent.y = max_y - center.y;
    }

    // ==================================================
    //  OPERATORS
    // ==================================================

    bool operator==(const BoundingBox &other_bb) const
    {
      return (center == other_bb.center) && (extent == other_bb.extent);
    }

    bool operator!=(const BoundingBox &other_bb) const
    {
      return !(*this == other_bb);
    }

    friend std::ostream &operator<<(std::ostream &out, const BoundingBox &bb)
    {
        out << std::fixed << std::setprecision(2)
            << "BoundingBox(x=" << bb.center.x << ", y=" << bb.center.y 
            << ", extent_x=" << bb.extent.x << ", extent_y=" << bb.extent.y << ")";
        return out;
    }

};

} // namespace avs
} // namespace geom