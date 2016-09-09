#pragma once

#include <functional>
#include <type_traits>
#include <vector>

#include <diamond_square/HeightMap.hpp>
#include <diamond_square/NoiseGenerator.hpp>


namespace diamond_square
{
    template <typename T>
    class HeightMapGenerator
    {
        static_assert
        (
            std::is_floating_point<T>::value, 
            "is arithmetic"
        );

        public:

        HeightMapGenerator
        (
            unsigned int level_of_detail,
            NoiseGenerator<T>& noise_generator
        );

        void Generate();

        const HeightMap<T>& map() const;
        HeightMap<T>& map();

        private:
        void PerformDiamondStep
        (
            unsigned int x,
            unsigned int y,
            unsigned int radius
        );
        void PerformSquareStep
        (
            unsigned int x,
            unsigned int y,
            unsigned int radius
        );

        T AverageDiamondNeighbours
        (
            unsigned int x,
            unsigned int y,
            unsigned int radius
        );
        T AverageSquareNeighbours
        (
            unsigned int x,
            unsigned int y,
            unsigned int radius
        );

        HeightMap<T> map_;
        NoiseGenerator<T>* noise_generator_;
        T relative_level_of_detail_;
    };
}

#include <diamond_square/HeightMapGenerator.inl>
