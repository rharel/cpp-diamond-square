/**
 * Noise generator class implementation.
 *
 * @author Raoul Harel
 * @url github.com/rharel/cpp-diamond-square
 */

#include <diamond_square/NoiseGenerator.hpp>


namespace diamond_square
{
    template <typename T>
    NoiseGenerator<T>::NoiseGenerator
    (
        EasingFunction easing_function,
        T min_range,
        T max_range,
        T bias
    )
        : ease_(easing_function),
            min_range_(min_range),
            max_range_(max_range),
            bias_(bias) {}

    template <typename T>
    void NoiseGenerator<T>::Seed(unsigned int value)
    {
        engine_.seed(value);
    }

    template <typename T>
    T NoiseGenerator<T>::Generate(const T relative_lod)
    {
        const T t = 1.0f - ease_(relative_lod);
        const T range_size = 
            min_range_ + t * (max_range_ - min_range_);
        const T half_range_size = 0.5f * range_size;

        std::uniform_real_distribution<T> distribution
        (
            bias_ - half_range_size, 
            bias_ + half_range_size
        );

        return distribution(engine_);
    }
}
