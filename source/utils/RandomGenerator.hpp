#pragma once

#include <random>


namespace avs {
namespace utils {


class RandomFloatGenerator
{
private:

    std::mt19937 generator;

public:

    RandomFloatGenerator()
        {
            std::random_device rnd_seed;
            generator.seed(rnd_seed());
        }
    RandomFloatGenerator(const int &seed) :
        generator(seed) {}

    float get_uniform(const float &lower_bound, const float &upper_bound)
    {
        std::uniform_real_distribution<float> uniform_distribution(lower_bound, upper_bound);
        return uniform_distribution(generator);
    }

    float get_normal(const float &mean, const float &std)
    {
        std::normal_distribution<float> normal_distribution(mean, std);
        return normal_distribution(generator);
    }
};


} // namespace utils
} // namespace avs