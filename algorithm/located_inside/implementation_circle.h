#ifndef AGL_ALGORITHM_LOCATED_INSIDE_CIRCLE_IMPLEMENTATION_H
#define AGL_ALGORITHM_LOCATED_INSIDE_CIRCLE_IMPLEMENTATION_H

#include "algorithm/math_algorithm.h"
#include "system/traits.h"
#include <cmath>

namespace agl::algorithm::inside_circle::dispatch {

template<typename Object1,
         typename Object2,
         typename Tag,
         typename SystemCoorinate,
         std::size_t Dimension>
struct located_inside{
    inline constexpr static auto get(const Object1 &a, const Object2 &b){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<typename Object1,
         typename Object2>
struct located_inside<Object1,
                      Object2,
                      agl::tag::point::point,
                      agl::system_coordinat::cartesian,
                      2>{
    inline constexpr static auto get(const Object1 &a, const Object2 &b){
        using Point = agl::traits::circle::access_types<Object1>::center;
        const auto &center = agl::traits::circle::access_center<Object1>::get(a);
        const auto &radius = agl::traits::circle::access_radius<Object1>::get(a);
        const auto &c_x = agl::traits::point::access_point<Point, 0>::get(center);
        const auto &c_y = agl::traits::point::access_point<Point, 1>::get(center);
        const auto &x = agl::traits::point::access_point<Object2, 0>::get(b);
        const auto &y = agl::traits::point::access_point<Object2, 1>::get(b);
        return algorithm::less_than_equal(std::pow(x - c_x, 2) + std::pow(y - c_y, 2), std::pow(radius, 2));
    }
};

}


namespace agl::algorithm::inside_circle {

template<typename Object1,
         typename Object2,
         typename Tag,
         typename SystemCoorinate,
         std::size_t Dimension>
inline constexpr auto located_inside(const Object1 &a, const Object2 &b){
    return agl::algorithm::inside_circle::dispatch::located_inside<Object1,
                                                                   Object2,
                                                                   Tag,
                                                                   SystemCoorinate,
                                                                   Dimension>::get(a, b);
}

}


#endif // AGL_ALGORITHM_LOCATED_INSIDE_CIRCLE_IMPLEMENTATION_H
