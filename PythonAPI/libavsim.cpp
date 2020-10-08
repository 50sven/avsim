#define CALL_RETURNING_LIST(cls, fn) +[](const cls &self) { \
      boost::python::list result; \
      for (auto &&item : self.fn()) { \
        result.append(item); \
      } \
      return result; \
    }


#include "Geom.cpp"
#include "Entity.cpp"
#include "Road.cpp"
#include "World.cpp"


BOOST_PYTHON_MODULE(avsimpy)
{   
    namespace bp = boost::python;
    
    PyEval_InitThreads();
    bp::object package = bp::scope();
    package.attr("__path__") = "avsimpy";
    export_geom();
    export_entity();
    export_road();
    export_world();
}