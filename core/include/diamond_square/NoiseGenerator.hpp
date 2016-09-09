#pragma once

#include <random>
#include <type_traits>


namespace diamond_square 
{
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

        NoiseGenerator
        (
            EasingFunction easing_function,
            T min_range,
            T max_range,
            T bias = 0.0f 
        );

        void Seed(unsigned int value);

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
