/**
 * Height map class header.
 *
 * @author Raoul Harel
 * @url github.com/rharel/cpp-diamond-square
 */

#pragma once

#include <type_traits>
#include <vector>


namespace diamond_square
{
    /**
     * This class represents a square height-map - associating a height value
     * (z) with each position (x, y) on its plane.
     *
     * @typeparam T Map data type (must be floating-point).
     */
    template <typename T>
    class HeightMap
    {
        static_assert
        (
            std::is_floating_point<T>::value,
            "is floating point"
        );

        public:
        /**
         * Creates a new height map instance of given size.
         *
         * @param level_of_detail
         *      Determines map resolution. The map's plane is a square, 
         *      with each side equal to 2^LOD + 1 units in length.
         */
        HeightMap(unsigned int level_of_detail);

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
         * Gets the plane's resolution.
         */
        unsigned int level_of_detail() const;
        /**
         * Gets the plane's width.
         *
         * @remarks
         *      Equals to height().
         */
        unsigned int width() const;
        /**
         * Gets the plane's height.
         *
         * @remarks
         *      Equals to width().
         */
        unsigned int height() const;
        /**
         * Gets the map's data buffer size.
         *
         * @remarks
         *      Equals to width() * height().
         */
        unsigned int size() const;

        /**
         * Gets a pointer to the map's data buffer size.
         *
         * @details
         *      The data buffer is an array containing the height values for
         *      each position on the map's plane. Its ordering is y-major.
         */
        const T* data() const;

        private:
        unsigned int Index
        (
            unsigned int x,
            unsigned int y
        ) const;

        void set_level_of_detail(unsigned int value);

        unsigned int level_of_detail_;
        unsigned int width_;
        std::vector<T> data_;
    };
}

#include <diamond_square/HeightMap.inl>
