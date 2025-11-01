#ifndef AGL_ALGORITHM_CENTER_IMPLEMENTATION_H
#define AGL_ALGORITHM_CENTER_IMPLEMENTATION_H

#include "system/system_concept.h"
#include "system/traits.h"
#include <cmath>
#include <numeric>

namespace agl::algorithm::dispatch {

template<typename Figure,
         typename PointOut>
struct center{
    inline constexpr static auto get(const Figure &figure){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<typename Figure,
         typename PointOut>
    requires c_cartesian<Figure> && c_cartesian<PointOut>
struct center<Figure,
              PointOut>{
    inline constexpr static auto get(const Figure &figure){
        using Point = agl::traits::polygon::access_types<Figure>::point;
        using Type = agl::traits::point::access_types<Point>::point;
        const auto &points = agl::traits::polygon::access_points<Figure>::get(figure);
        const auto sum = std::accumulate(points.begin(), points.end(), std::pair<Type, Type>(),
                                   [](std::pair<Type, Type> sum, auto item){
            using x = agl::traits::point::access_point<Point, 0>;
            using y = agl::traits::point::access_point<Point, 1>;
            return std::pair<Type, Type>(sum.first + x::get(item), sum.second + y::get(item));
        });
        return agl::traits::make<PointOut>::apply(sum.first / points.size(), sum.second / points.size());
    }
};

}

#endif // AGL_ALGORITHM_CENTER_IMPLEMENTATION_H
