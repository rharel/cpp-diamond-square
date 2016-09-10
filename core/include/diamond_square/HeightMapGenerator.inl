/**
 * Height map generator implementation.
 *
 * @author Raoul Harel
 * @url github.com/rharel/cpp-diamond-square
 */

#include <diamond_square/HeightMapGenerator.hpp>


namespace diamond_square
{
    template <typename T>
    HeightMapGenerator<T>::HeightMapGenerator
    (
        const unsigned int level_of_detail,
        NoiseGenerator<T>& noise_generator
    )
        : map_(level_of_detail),
          noise_generator_(&noise_generator) {}
    
    template <typename T>
    void HeightMapGenerator<T>::Generate()
    {
        const unsigned int size = map_.width();
        const unsigned int max_lod = map_.level_of_detail();

        for (unsigned int i = 0; i < max_lod; ++i)
        {
            relative_level_of_detail_ = 
                static_cast<float>(i) / 
                static_cast<float>(max_lod);

            const unsigned int lod = max_lod - i;
            const unsigned int square_size = static_cast<unsigned int>
            (
                std::pow(2, lod) + 1
            );
            const unsigned int square_radius = (square_size - 1) / 2;

            const unsigned int dx = square_size - 1;
            const unsigned int dy = dx;

            unsigned int y = dy / 2;
            while (y < size)
            {
                unsigned int x = dx / 2;
                while (x < size)
                {
                    PerformDiamondStep(x, y, square_radius);
                    PerformSquareStep(x, y, square_radius);
                    x += dx;
                }
                y += dy;
            }
        }
    }
    template <typename T>
    void HeightMapGenerator<T>::PerformDiamondStep
    (
        const unsigned int x,
        const unsigned int y,
        const unsigned int r  // radius
    )
    {
        map_.At(x, y) = 
            AverageDiamondNeighbours(x, y, r) + 
            noise_generator_->Generate(relative_level_of_detail_);
    }
    template <typename T>
    void HeightMapGenerator<T>::PerformSquareStep
    (
        const unsigned int x,
        const unsigned int y,
        const unsigned int r  // radius
    )
    {
        map_.At(x - r, y) = 
            AverageSquareNeighbours(x - r, y, r) +
            noise_generator_->Generate(relative_level_of_detail_);
        map_.At(x + r, y) = 
            AverageSquareNeighbours(x + r, y, r) +
            noise_generator_->Generate(relative_level_of_detail_);
        map_.At(x, y - r) = 
            AverageSquareNeighbours(x, y - r, r) +
            noise_generator_->Generate(relative_level_of_detail_);
        map_.At(x, y + r) = 
            AverageSquareNeighbours(x, y + r, r) +
            noise_generator_->Generate(relative_level_of_detail_);
    }

    template <typename T>
    T HeightMapGenerator<T>::AverageDiamondNeighbours
    (
        const unsigned int x,
        const unsigned int y,
        const unsigned int r  // radius
    )
    {
        const T sum = 
            map_.At(x - r, y - r) +
            map_.At(x - r, y + r) +
            map_.At(x + r, y + r) +
            map_.At(x + r, y - r);
        return 0.25f * sum;
    }
    template <typename T>
    T HeightMapGenerator<T>::AverageSquareNeighbours
    (
        const unsigned int x,
        const unsigned int y,
        const unsigned int r  // radius
    )
    {
        const T sum = 
            map_.At(x - r, y) +
            map_.At(x + r, y) +
            map_.At(x, y - r) +
            map_.At(x, y + r);
        return 0.25f * sum;
    }

    template <typename T>
    const HeightMap<T>& HeightMapGenerator<T>::map() const
    {
        return map_;
    }
    template <typename T>
    HeightMap<T>& HeightMapGenerator<T>::map()
    {
        return map_;
    }
}
