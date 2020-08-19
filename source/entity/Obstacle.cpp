#include "entity/Obstacle.hpp"


namespace avs {
namespace entity {

    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    Obstacle::Obstacle(const geom::Transform &transform) : 
        Entity("O" + std::to_string(counter++), transform) {}

    // ==================================================
    //  MEMBER VARIABLES
    // ==================================================

    unsigned int Obstacle::counter = 0;
    
    // ==================================================
    //  METHODS
    // ==================================================

    

    // ==================================================
    //  OPERATORS
    // ==================================================
    
    std::ostream &operator<<(std::ostream &out, const Obstacle &Obstacle)
    {
        out << "Obstacle(id=" << Obstacle.get_id() << ", x="<< Obstacle.location.x << ", y=" << Obstacle.location.y << ", yaw=" << Obstacle.rotation << ")";
        return out;
    }

} // namespace avs
} // namespace entity