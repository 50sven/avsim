# Boost.python
find_package( Boost 1.73.0 REQUIRED COMPONENTS python)
find_package(PythonInterp 3)
find_package(PythonLibs 3 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
link_libraries(${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

PYTHON_ADD_MODULE(avsimpy libavsim.cpp)
target_link_libraries(avsimpy PRIVATE avsim)