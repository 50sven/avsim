# Add executable and link library
add_executable(main main.cpp)
target_link_libraries(main PRIVATE avsim)
target_link_libraries(main PRIVATE yaml-cpp)

# Specify compile features
target_compile_features(main PRIVATE cxx_std_17)
