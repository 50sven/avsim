#include "geom/Vector2D.hpp"
#include "geom/Transform.hpp"
#include "geom/BoundingBox.hpp"
#include "geom/Math.hpp"
#include "geom/CollisionCheck.hpp"

#include <boost/python.hpp>


void export_geom()
{
    namespace bp = boost::python;
    namespace ag = avs::geom;

    // Make from avsimpy.geometrics import ... work
    bp::object utilModule(bp::handle<>(bp::borrowed(PyImport_AddModule("avsimpy.geometrics"))));
    // Make from avsimpy import geometrics work
    bp::scope().attr("geometrics") = utilModule;
    bp::scope util_scope = utilModule;


    bp::class_<ag::Vector2D>("Vector2D")
        .def(bp::init<const float, const float>((bp::arg("x")=0.0f, bp::arg("y")=0.0f)))
        .def(bp::init<const ag::Vector2D>((bp::arg("vector"))))
        .def_readwrite("x", &ag::Vector2D::x)
        .def_readwrite("y", &ag::Vector2D::y)
        .def("get_length", &ag::Vector2D::get_length)
        .def("get_unit_vector", &ag::Vector2D::get_unit_vector)
        .def("__eq__", &ag::Vector2D::operator==)
        .def("__ne__", &ag::Vector2D::operator!=)
        .def(bp::self += bp::self)
        .def(bp::self + bp::self)
        .def(bp::self -= bp::self)
        .def(bp::self - bp::self)
        .def(bp::self *= double())
        .def(bp::self * double())
        .def(double() * bp::self)
        .def(bp::self /= double())
        .def(bp::self / double())
        .def(double() / bp::self)
        .def(bp::self_ns::str(bp::self_ns::self))
    ;

    bp::class_<ag::Transform>("Transform")
        .def(bp::init<const ag::Vector2D, const float>(
            (bp::arg("location")=ag::Vector2D(), bp::arg("rotation")=0.0f)))
        .def(bp::init<const ag::Transform&>((bp::arg("transform"))))
        .def_readwrite("location", &ag::Transform::location)
        .def_readwrite("rotation", &ag::Transform::rotation)
        .def("get_forward_vector", &ag::Transform::get_forward_vector)
        .def("calculate_distance", &ag::Transform::calculate_distance)
        .def("__eq__", &ag::Transform::operator==)
        .def("__ne__", &ag::Transform::operator!=)
        .def(bp::self_ns::str(bp::self_ns::self))
    ;

    bp::class_<ag::BoundingBox>("BoundingBox")
        .def(bp::init<const ag::Vector2D, const ag::Vector2D>(
            (bp::arg("location")=ag::Vector2D(), bp::arg("extent")=ag::Vector2D())))
        .def(bp::init<const float, const float, const float, const float>(
            (bp::arg("x")=0.0f, bp::arg("y")=0.0f, bp::arg("extent_x")=1.0f, bp::arg("extent_y")=1.0f)))
        .def(bp::init<const ag::BoundingBox&>((bp::arg("bounding_box"))))
        .def_readwrite("location", &ag::BoundingBox::center)
        .def_readwrite("extent", &ag::BoundingBox::extent)
        .def("contains", &ag::BoundingBox::contains, bp::arg("point"))
        .def("intersects", &ag::BoundingBox::intersects, bp::arg("bounding_box"))
        .def("__eq__", &ag::BoundingBox::operator==)
        .def("__ne__", &ag::BoundingBox::operator!=)
        .def(bp::self_ns::str(bp::self_ns::self))
    ;

    bp::class_<ag::Math>("math")
        .def("to_radian", &ag::Math::to_radian, bp::arg("deg"))
        .def("to_degree", &ag::Math::to_degree, bp::arg("rad"))
        .def("dot_product", &ag::Math::dot_product, (bp::arg("vector_A"), bp::arg("vector_B")))
        .def("calculate_distance", &ag::Math::calculate_distance, (bp::arg("vector_A"), bp::arg("vector_B")))
        .def("calculate_angle", &ag::Math::calculate_angle, (bp::arg("vector_A"), bp::arg("vector_B")))
        .def("get_forward_vector", &ag::Math::get_forward_vector, bp::arg("deg"))
        .def("rotate_vector_on_origin", &ag::Math::rotate_vector_on_origin, (bp::arg("vector"), bp::arg("deg")))
        .def("rotate_vector_on_point", &ag::Math::rotate_vector_on_point, (bp::arg("vector"), bp::arg("deg"), bp::arg("point")))
    ;

    bp::class_<ag::CollisionChecker>("CollisionChecker")
        .def("check_collision", &ag::CollisionChecker::check_collision, (bp::arg("entity_A"), bp::arg("entity_B")))
        .def(bp::self_ns::str(bp::self_ns::self))
    ;

}
