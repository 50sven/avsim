#include "entity/Obstacle.hpp"


namespace avs {
namespace entity {

    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    Obstacle::Obstacle(const geom::Transform &transform, const geom::Vector2D &size) : 
        Entity(counter--, transform, size) {}

    // ==================================================
    //  MEMBER VARIABLES
    // ==================================================

    
    
    // ==================================================
    //  METHODS
    // ==================================================

    

    // ==================================================
    //  OPERATORS
    // ==================================================
    
    std::ostream &operator<<(std::ostream &out, const Obstacle &obstacle)
    {
        out << "Obstacle(id=" << obstacle.get_id()
            << ", x="<< obstacle.get_transform().location.x
            << ", y=" << obstacle.get_transform().location.y
            << ", yaw=" << obstacle.get_transform().rotation
            << ", size=" << obstacle.get_size()
            << ")";
        return out;
    }

} // namespace avs
} // namespace entity