/**
 * Height map layer class header.
 *
 * @author Raoul Harel
 * @url github.com/rharel/cpp-diamond-square
 */

#pragma once

#include <type_traits>

#include <diamond_square/HeightMap.hpp>


namespace diamond_square
{
    /**
     * This class represents a single-layer view of a height map.
     *
     * @typeparam T Map data type (must be floating-point).
     *
     * @details
     *      This class wraps around an existing instance of a height map and
     *      presents method to interact with a subset of its plane based on 
     *      the level of detail selected.
     *      
     *      For example, given a map with LOD = 2:
     *          o o o o o
     *          o o o o o
     *          o o o o o
     *          o o o o o
     *          o o o o o
     *      The layer at LOD = 1 would present a view of that map from a 
     *      different magnification (x's mark layer positions at the original
     *      positions they point to):
     *          o o o o o
     *          o x o x o
     *          o o o o o
     *          o x o x o
     *          o o o o o
     */
    template <typename T>
    class HeightMapLayer
    {
        static_assert
        (
            std::is_floating_point<T>::value,
            "is floating point"
        );

        public:
        /**
         * Creates a new layer-view instance.
         *
         * @param map 
         *      Height map to wrap around.
         * @param level_of_detail
         *      Determines layer's perspective.
         */
        HeightMapLayer
        (
            HeightMap<T>& map,
            unsigned int level_of_detail
        );

        /**
         * Gets the height value for the given position in the plane.
         *
         * @remarks
         *      x and y values that are larger than the plane's size are 
         *      wrapped.
         */
        T At
        (
            unsigned int x,
            unsigned int y
        ) const;
        /**
         * Gets a reference to the height value for the given position in the 
         * plane.
         *
         * @remarks
         *      x and y values that are larger than the plane's size are 
         *      wrapped.
         */
        T& At
        (
            unsigned int x,
            unsigned int y
        );

        /**
         * Gets the layer's resolution.
         */
        unsigned int level_of_detail() const;
        /**
         * Gets the layer's width.
         *
         * @remarks
         *      Equals to height().
         */
        unsigned int width() const;
        /**
         * Gets the layer's height.
         *
         * @remarks
         *      Equals to width().
         */

        /**
         * Gets the internal height map (read only)
         */
        const HeightMap<T>& map() const;
        /**
         * Gets the internal height map.
         */
        HeightMap<T>& map();

        private:
        unsigned int ConvertCoordinate(unsigned int i) const;

        void set_level_of_detail(unsigned int value);

        HeightMap<T>* map_;
        unsigned int level_of_detail_;
        unsigned int width_;
    };
}

#include <diamond_square/HeightMapLayer.inl>
