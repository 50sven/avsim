#include "entity/Entity.hpp"


namespace avs {
namespace entity {

    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    Entity::Entity(const std::string &entity_id, const geom::Transform &transform) : 
        id(entity_id),
        location(transform.location),
        rotation(transform.rotation),
        geometry(transform, size),
        bounding_box(geometry) {}

    // ==================================================
    //  MEMBER VARIABLES
    // ==================================================
    


    // ==================================================
    //  METHODS
    // ==================================================

    std::string Entity::get_id() const
    {
        return id;
    }
    
    geom::Vector2D Entity::get_location() const
    {
        return location;
    }

    geom::Transform Entity::get_transform() const
    {
        geom::Transform transform(location, rotation);
        return transform;
    }

    geom::BoundingBox Entity::get_bounding_box() const
    {
        return bounding_box;
    }

    geom::Rectangle Entity::get_geometry() const
    {   
        return geometry;
    }

    // ==================================================
    //  OPERATORS
    // ==================================================

    bool Entity::operator==(const Entity &other_entity) const
    {
        return (id == other_entity.get_id());
    }

    bool Entity::operator!=(const Entity &other_entity) const
    {
        return !(*this == other_entity);
    }

} // namespace avs
} // namespace entity