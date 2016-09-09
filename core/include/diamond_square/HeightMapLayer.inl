#include <diamond_square/HeightMapLayer.hpp>


namespace diamond_square
{
    template <typename T>
    HeightMapLayer<T>::HeightMapLayer
    (
        HeightMap<T>& map,
        const unsigned int level_of_detail
    )
        : map_(&map)
    {
        set_level_of_detail(level_of_detail);
    }

    template <typename T>
    T HeightMapLayer<T>::At
    (
        const unsigned int x,
        const unsigned int y
    ) const
    {
        return map_->At
        (
            ConvertCoordinate(x),
            ConvertCoordinate(y)
        );   
    }
    template <typename T>
    T& HeightMapLayer<T>::At
    (
        const unsigned int x,
        const unsigned int y
    )
    {
        return map_->At
        (
            ConvertCoordinate(x),
            ConvertCoordinate(y)
        );   
    }

    template <typename T>
    unsigned int HeightMapLayer<T>::ConvertCoordinate
    (
        const unsigned int i
    ) const
    {
        const unsigned int side_length = (map_->width() - 1) / (width_ - 1);
        const unsigned int step_size = side_length / 2;
        return step_size * (i + 1);    
    }

    template <typename T>
    unsigned int HeightMapLayer<T>::width() const
    {
        return width_;
    }
    template <typename T>
    unsigned int HeightMapLayer<T>::height() const
    {
        return width_;
    }

    template <typename T>
    const HeightMap<T>& HeightMapLayer<T>::map() const
    {
        return *map_;
    }
    template <typename T>
    HeightMap<T>& HeightMapLayer<T>::map()
    {
        return *map_;
    }

    template <typename T>
    unsigned int HeightMapLayer<T>::level_of_detail() const
    {
        return level_of_detail_;
    }
    template <typename T>
    void HeightMapLayer<T>::set_level_of_detail(const unsigned int value)
    {
        level_of_detail_ = value;
        width_ = static_cast<unsigned int>
        (
            std::pow(2, level_of_detail_) + 1
        );
    }
}
