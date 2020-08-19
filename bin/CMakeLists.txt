# Add executable and link library
add_executable(main main.cpp)
target_link_libraries(main PRIVATE avsim)

# Specify compile features
target_compile_features(main PRIVATE cxx_std_17)
