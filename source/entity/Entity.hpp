#pragma once

#include "../geom/Vector2D.hpp"
#include "../geom/Transform.hpp"
#include "../geom/BoundingBox.hpp"
#include "../geom/Geometry.hpp"
#include "../geom/Math.hpp"


namespace avs {
namespace entity {

class Entity
{
protected:
    const geom::Vector2D size = {4.0f, 2.0f};
    geom::Vector2D location;
    float rotation;

    geom::Rectangle geometry;
    geom::BoundingBox bounding_box;

public:
    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    Entity() = default;
    Entity(const float &entity_id, const geom::Transform &transform);

    // ==================================================
    //  MEMBER VARIABLES
    // ==================================================
    
    const unsigned int id = 0;

    // ==================================================
    //  METHODS
    // ==================================================
    
    geom::Vector2D get_location() const;

    geom::Transform get_transform() const;

    geom::BoundingBox get_bounding_box() const;

    geom::Rectangle get_geometry() const;

    // ==================================================
    //  OPERATORS
    // ==================================================

    bool operator==(const Entity &other_entity) const;

    bool operator!=(const Entity &other_entity) const;

};

} // namespace avs
} // namespace entity