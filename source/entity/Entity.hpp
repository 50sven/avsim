#pragma once

#include "../geom/Vector2D.hpp"
#include "../geom/Transform.hpp"
#include "../geom/BoundingBox.hpp"
#include "../geom/Geometry.hpp"

#include <string>


namespace avs {
namespace entity {

class Entity
{
protected:
    int id;
    geom::Transform transform;
    geom::Vector2D size;

    geom::Rectangle geometry;
    geom::BoundingBox bounding_box;

public:
    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    Entity() = default;
    Entity(const int &entity_id, const geom::Transform &entity_transform, const geom::Vector2D &entity_size) : 
        id(entity_id),
        transform(entity_transform),
        size(entity_size),
        geometry(entity_transform, entity_size),
        bounding_box(geometry) {}
    // ==================================================
    //  MEMBER VARIABLES
    // ==================================================
    


    // ==================================================
    //  METHODS
    // ==================================================
    
    int get_id() const
    {
        return id;
    }
    
    geom::Vector2D get_location() const
    {
        return transform.location;
    }

    geom::Transform get_transform() const
    {
        return transform;
    }

    geom::Vector2D get_size() const
    {
        return size;
    }

    geom::BoundingBox get_bounding_box() const
    {
        return bounding_box;
    }

    geom::Rectangle get_geometry() const
    {   
        return geometry;
    }

    // ==================================================
    //  OPERATORS
    // ==================================================

    bool operator==(const Entity &other_entity) const
    {
        return (id == other_entity.get_id());
    }

    bool operator!=(const Entity &other_entity) const
    {
        return !(*this == other_entity);
    }

};

} // namespace avs
} // namespace entity