#include "Geom.cpp"
#include "Entity.cpp"

BOOST_PYTHON_MODULE(avsimpy)
{   
    namespace bp = boost::python;
    
    PyEval_InitThreads();
    bp::object package = bp::scope();
    package.attr("__path__") = "avsimpy";
    export_geom();
    export_entity();
}