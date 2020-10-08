#include "road/Lane.hpp"
#include "road/Road.hpp"
#include "geom/Vector2D.hpp"

#include <boost/python.hpp>


void export_road()
{
    namespace bp = boost::python;
    namespace ar = avs::road;
    namespace ag = avs::geom;

    // Make from avsimpy.road import ... work
    bp::object utilModule(bp::handle<>(bp::borrowed(PyImport_AddModule("avsimpy.road"))));
    // Make from avsimpy import road work
    bp::scope().attr("road") = utilModule;
    bp::scope util_scope = utilModule;


    bp::class_<ar::Lane>("Lane")
        .def(bp::init<const int, const float, const float, ag::Vector2D>((bp::arg("id"), bp::arg("width"), bp::arg("length"), bp::arg("center"))))
        .add_property("id", &ar::Lane::get_id)
        .add_property("width", &ar::Lane::get_width)
        .add_property("length", &ar::Lane::get_length)
        .def("get_center", &ar::Lane::get_center)
        .def("get_forward_vector", &ar::Lane::get_forward_vector)
        .def("__eq__", &ar::Lane::operator==)
        .def("__ne__", &ar::Lane::operator!=)
        .def(bp::self_ns::str(bp::self_ns::self))
    ;

    bp::class_<ar::Shoulder>("Shoulder")
        .def(bp::init<const int, const float, const float, ag::Vector2D>((bp::arg("id"), bp::arg("width"), bp::arg("length"), bp::arg("center"))))
        .add_property("id", &ar::Shoulder::get_id)
        .add_property("width", &ar::Shoulder::get_width)
        .add_property("length", &ar::Shoulder::get_length)
        .def("get_center", &ar::Shoulder::get_center)
        .def("get_forward_vector", &ar::Shoulder::get_forward_vector)
        .def("__eq__", &ar::Shoulder::operator==)
        .def("__ne__", &ar::Shoulder::operator!=)
        .def(bp::self_ns::str(bp::self_ns::self))
    ;

    bp::class_<ar::Road>("Road")
        .def(bp::init<const std::string>((bp::arg("config_file"))))
        .add_property("length", &ar::Road::get_length)
        .add_property("speed_limit", &ar::Road::get_speed_limit)
        .def("get_lanes", CALL_RETURNING_LIST(ar::Road, get_lanes))
        .def("get_lane", &ar::Road::get_lane, bp::arg("lane_id"))
        .def("get_shoulders", CALL_RETURNING_LIST(ar::Road, get_shoulders))
        .def("get_shoulder", &ar::Road::get_shoulder, bp::arg("shoulder_id"))
        .def(bp::self_ns::str(bp::self_ns::self))
    ;

}
