#pragma once

#include <type_traits>
#include <vector>


namespace diamond_square
{
    template <typename T>
    class HeightMap
    {
        static_assert
        (
            std::is_floating_point<T>::value,
            "is floating point"
        );

        public:
        HeightMap(unsigned int level_of_detail);

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
        unsigned int size() const;

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
