#pragma once

#include "../geom/Vector2D.hpp"
#include "../geom/Transform.hpp"
#include "../geom/BoundingBox.hpp"
#include "../geom/Geometry.hpp"
#include "../geom/Math.hpp"

#include <string>


namespace avs {
namespace entity {

class Entity
{
protected:
    const std::string id = "NO_ID";
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
    Entity(const std::string &entity_id, const geom::Transform &transform);

    // ==================================================
    //  MEMBER VARIABLES
    // ==================================================
    


    // ==================================================
    //  METHODS
    // ==================================================
    
    std::string get_id() const;

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