# Find header/source files
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.hpp")
# file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "*.cpp")

file(GLOB libavs_avs_entity_sources
    "${libavs_source_path}/entity/*.cpp"
    "${libavs_source_path}/entity/*.hpp")
set(libavs_sources "${libavs_sources};${libavs_avs_entity_sources}")

file(GLOB libavs_avs_geom_sources
    "${libavs_source_path}/geom/*.cpp"
    "${libavs_source_path}/geom/*.hpp")
set(libavs_sources "${libavs_sources};${libavs_avs_geom_sources}")

file(GLOB libavs_avs_road_sources
    "${libavs_source_path}/road/*.cpp"
    "${libavs_source_path}/road/*.hpp")
set(libavs_sources "${libavs_sources};${libavs_avs_road_sources}")

# Create shared library and include headers
add_library(avsim SHARED ${libavs_sources})
target_include_directories(avsim PUBLIC ${libavs_source_path})

# Link third-party libraries
target_link_libraries(avsim PUBLIC yaml-cpp)

# Set library properties
set_target_properties(avsim PROPERTIES VERSION ${PROJECT_VERSION})

# Specify compile features
target_compile_features(avsim PUBLIC cxx_std_17)
