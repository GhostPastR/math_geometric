#ifndef AGL_ALGORITHM_CENTER_IMPLEMENTATION_H
#define AGL_ALGORITHM_CENTER_IMPLEMENTATION_H

#include "system/assert.h"
#include "system/system_concept.h"
#include "system/traits.h"
#include <cmath>
#include <numeric>

namespace agl::algorithm::dispatch {

template<typename Figure,
         typename PointOut,
         typename CoordinateSystem,
         std::size_t Dimension>
struct center{
    inline constexpr static auto get(const Figure &figure){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<c_polygon Figure,
         c_point_2d PointOut>
struct center<Figure,
              PointOut,
              agl::system_coordinat::cartesian,
              2>{
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
        return agl::traits::point::access_create<PointOut>::get(sum.first / points.size(),
                                                                sum.second / points.size());
    }
};


}


namespace agl::algorithm::geometry {

template<typename Figure,
         typename PointOut>
inline constexpr auto center(const Figure &figure){
    using type_cs = traits::coordinate_system<Figure>::system;
    constexpr auto dimension = traits::dimension<Figure>::value();
    static_assert(agl::assert::is_correct<type_cs>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");
    return dispatch::center<Figure,
                            PointOut,
                            type_cs,
                            dimension>::get(figure);
}

}


#endif // AGL_ALGORITHM_CENTER_IMPLEMENTATION_H
