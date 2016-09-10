/**
 * Noise generator class header.
 *
 * @author Raoul Harel
 * @url github.com/rharel/cpp-diamond-square
 */

#pragma once

#include <random>
#include <type_traits>


namespace diamond_square 
{
    /**
     * This class represents a source of random offsets for the diamond square
     * algorithm.
     */
    template <typename T>
    class NoiseGenerator
    {
        static_assert
        (
            std::is_floating_point<T>::value,
            "is floating point"
        );

        public:
        typedef T (*EasingFunction)(T t);

        /**
         * Creates a new generator instance.
         *
         * @param easing_function
         *      An easing function (as used in tweening).
         * @param min_range
         *      Minimum range size to sample from.
         * @param max_range
         *      Maximum range size to sample from.
         * @param bias
         *      Sample bias.
         */
        NoiseGenerator
        (
            EasingFunction easing_function,
            T min_range,
            T max_range,
            T bias = 0.0f 
        );

        /**
         * Seeds this generator.
         */
        void Seed(unsigned int value);
        /**
         * Generates a random offset.
         *
         * @param relative_level_of_detail
         *      The current LOD in the diamond-square algorithm as a fraction
         *      of the maximum LOD of the map.
         */
        T Generate(T relative_level_of_detail);

        private:
        EasingFunction ease_;
        T bias_;
        T min_range_;
        T max_range_; 

        std::random_device random_device_;
        std::mt19937 engine_ = std::mt19937(random_device_());
    };
}

#include <diamond_square/NoiseGenerator.inl>
