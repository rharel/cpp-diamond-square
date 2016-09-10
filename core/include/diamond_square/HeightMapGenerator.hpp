/**
 * Height map generator class header.
 *
 * @author Raoul Harel
 * @url github.com/rharel/cpp-diamond-square
 */

#pragma once

#include <functional>
#include <type_traits>
#include <vector>

#include <diamond_square/HeightMap.hpp>
#include <diamond_square/NoiseGenerator.hpp>


namespace diamond_square
{
    /**
     * This class represents a height-map generation procedure utilizing the 
     * diamond-square algorithm.
     *
     * @typeparam T Map data type (must be floating-point).
     */
    template <typename T>
    class HeightMapGenerator
    {
        static_assert
        (
            std::is_floating_point<T>::value, 
            "is arithmetic"
        );

        public:
        /**
         * Creates a new generator instance.
         *
         * @param level_of_detail
         *      Determines map resolution. The map's plane is a square, 
         *      with each side equal to 2^LOD + 1 units in length.
         * @param noise_generator
         *      An instance of the noise-generator class. It is used as a 
         *      source for the random offsets demanded by the diamond-square
         *      algorithm.
         */
        HeightMapGenerator
        (
            unsigned int level_of_detail,
            NoiseGenerator<T>& noise_generator
        );

        /**
         * Generates random height values for the internal height map.
         */
        void Generate();

        /**
         * Gets the internal height map (read only)
         */
        const HeightMap<T>& map() const;
        /**
         * Gets the internal height map.
         */
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
