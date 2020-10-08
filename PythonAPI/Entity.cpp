#include "entity/Entity.hpp"
#include "entity/Agent.hpp"
#include "entity/Obstacle.hpp"
#include "geom/Transform.hpp"

#include <boost/python.hpp>


void export_entity()
{
    namespace bp = boost::python;
    namespace ae = avs::entity;
    namespace ag = avs::geom;

    // Make from avsimpy.entity import ... work
    bp::object utilModule(bp::handle<>(bp::borrowed(PyImport_AddModule("avsimpy.entity"))));
    // Make from avsimpy import entity work
    bp::scope().attr("entity") = utilModule;
    bp::scope util_scope = utilModule;

    bp::class_<ae::Entity>("Entity", bp::no_init);

    bp::class_<ae::Agent, bp::bases<ae::Entity>>("Agent")
        .def(bp::init<const ag::Transform, const ag::Vector2D, const int, const float>((bp::arg("transformation")=ag::Transform(), bp::arg("size")=ag::Vector2D(4.0f, 2.0f), bp::arg("desired_lane")=1, bp::arg("desired_velocity")=12.0f)))
        .add_property("id", &ae::Agent::get_id)
        .add_property("bounding_box", &ae::Agent::get_bounding_box)
        .add_property("geometry", &ae::Agent::get_geometry)
        .add_property("size", &ae::Agent::get_size)
        .add_property("desired_lane", &ae::Agent::get_desired_lane)
        .add_property("desired_velocity", &ae::Agent::get_desired_velocity)
        .def("get_location", &ae::Agent::get_location)
        .def("get_transform", &ae::Agent::get_transform)
        .def("get_velocity", &ae::Agent::get_velocity)
        .def("get_acceleration", &ae::Agent::get_acceleration)
        .def("get_forward_vector", &ae::Agent::get_forward_vector)
        .def("set_location", &ae::Agent::set_location, bp::arg("location"))
        .def("set_transform", &ae::Agent::set_transform, bp::arg("transform"))
        .def("set_velocity", &ae::Agent::set_velocity, bp::arg("velocity"))
        .def("set_acceleration", &ae::Agent::set_acceleration, bp::arg("acceleration"))
        .def("__eq__", &ae::Agent::operator==)
        .def("__ne__", &ae::Agent::operator!=)
        .def(bp::self_ns::str(bp::self_ns::self))
    ;

    bp::class_<ae::Obstacle, bp::bases<ae::Entity>>("Obstacle")
        .def(bp::init<const ag::Transform, const ag::Vector2D>(
            (bp::arg("transformation")=ag::Transform(), bp::arg("size")=ag::Vector2D(4.0f, 2.0f))))
        .add_property("id", &ae::Obstacle::get_id)
        .add_property("bounding_box", &ae::Obstacle::get_bounding_box)
        .add_property("geometry", &ae::Obstacle::get_geometry)
        .add_property("size", &ae::Obstacle::get_size)
        .def("get_location", &ae::Obstacle::get_location)
        .def("get_transform", &ae::Obstacle::get_transform)
        .def("__eq__", &ae::Obstacle::operator==)
        .def("__ne__", &ae::Obstacle::operator!=)
        .def(bp::self_ns::str(bp::self_ns::self))
    ;
}