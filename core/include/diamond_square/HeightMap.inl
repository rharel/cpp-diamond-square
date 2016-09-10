/**
 * Height map class implementation.
 *
 * @author Raoul Harel
 * @url github.com/rharel/cpp-diamond-square
 */

#include <diamond_square/HeightMap.hpp>


namespace diamond_square
{
    template <typename T>
    HeightMap<T>::HeightMap(unsigned int level_of_detail)
    {
        set_level_of_detail(level_of_detail);
    }

    template <typename T>
    T HeightMap<T>::At
    (
        const unsigned int x,
        const unsigned int y
    ) const
    {
        return data_.at(Index(x, y));
    }
    template <typename T>
    T& HeightMap<T>::At
    (
        const unsigned int x,
        const unsigned int y
    )
    {
        return data_.at(Index(x, y));
    }

    template <typename T>
    unsigned int HeightMap<T>::width() const
    {
        return width_;
    }
    template <typename T>
    unsigned int HeightMap<T>::height() const
    {
        return width_;
    }
    template <typename T>
    unsigned int HeightMap<T>::size() const
    {
        return data_.size();
    }

    template <typename T>
    const T* HeightMap<T>::data() const
    {
        return data_.data();
    }

    template <typename T>
    unsigned int HeightMap<T>::Index
    (
        const unsigned int x,
        const unsigned int y
    ) const
    {
        const unsigned int x_wrapped = x % width_;
        const unsigned int y_wrapped = y % width_;

        return y_wrapped * width_ + x_wrapped;
    }

    template <typename T>
    unsigned int HeightMap<T>::level_of_detail() const
    {
        return level_of_detail_;
    }
    template <typename T>
    void HeightMap<T>::set_level_of_detail(const unsigned int value)
    {
        level_of_detail_ = value;
        width_ = static_cast<unsigned int>
        (
            std::pow(2, level_of_detail_) + 1
        );
        data_.resize(width_ * width_);
    }
}
