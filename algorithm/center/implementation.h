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

template<c_polygon Figure,
         c_point_2d PointOut>
    requires c_cartesian<Figure> && c_cartesian<PointOut> && c_demension_2<Figure>
struct center<Figure,
              PointOut>{
    inline constexpr static auto get(const Figure &figure){
        using Point = agl::traits::polygon::access_types<Figure>::point;
        using Type = agl::traits::point::element_point_v<Point, 0>;

        const auto &points = agl::traits::polygon::access_points<Figure>::get(figure);
        const auto sum = std::accumulate(points.begin(), points.end(), std::pair<Type, Type>(),
                                   [](std::pair<Type, Type> sum, auto item){
            const auto[x, y] = agl::traits::access_propery<Point>::get(item);
            return std::pair<Type, Type>(sum.first + x, sum.second + y);
        });
        return agl::traits::make<PointOut>::apply(sum.first / points.size(), sum.second / points.size());
    }
};

}

//На будущие: добавить функции для 3D

#endif // AGL_ALGORITHM_CENTER_IMPLEMENTATION_H
