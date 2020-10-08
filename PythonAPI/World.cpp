#include "world/World.hpp"

#include <boost/python.hpp>


void export_world()
{
    namespace bp = boost::python;
    namespace wo = avs::world;
    namespace ag = avs::geom;

    // Make from avsimpy.world import ... work
    bp::object utilModule(bp::handle<>(bp::borrowed(PyImport_AddModule("avsimpy.world"))));
    // Make from avsimpy import world work
    bp::scope().attr("world") = utilModule;
    bp::scope util_scope = utilModule;

    bp::class_<wo::World>("World")
        .def(bp::init<const std::string>((bp::arg("config_file"))))
        .def("get_road", &wo::World::get_road)
        .def("get_agents", CALL_RETURNING_LIST(wo::World, get_agents))
        .def("get_agent", &wo::World::get_agent, bp::arg("agent_id"))
        .def("get_obstacles", CALL_RETURNING_LIST(wo::World, get_obstacles))
        .def("get_obstacle", &wo::World::get_obstacle, bp::arg("obstacle_id"))
        .def(bp::self_ns::str(bp::self_ns::self))
    ;

}
