#pragma once

#include <type_traits>

#include <diamond_square/HeightMap.hpp>


namespace diamond_square
{
    template <typename T>
    class HeightMapLayer
    {
        static_assert
        (
            std::is_floating_point<T>::value,
            "is floating point"
        );

        public:
        HeightMapLayer
        (
            HeightMap<T>& map,
            unsigned int level_of_detail
        );

        T At
        (
            unsigned int x,
            unsigned int y
        ) const;
        T& At
        (
            unsigned int x,
            unsigned int y
        );

        unsigned int level_of_detail() const;
        unsigned int width() const;
        unsigned int height() const;

        const HeightMap<T>& map() const;
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
