#ifndef AGL_ALGORITHM_DISTANCE_IMPLEMENTATION_LINE_CARTESIAN_H
#define AGL_ALGORITHM_DISTANCE_IMPLEMENTATION_LINE_CARTESIAN_H

#include "algorithm/distance/implementation_cartesian.h"
#include "system/system_concept.h"
#include "system/traits.h"
#include <cmath>

namespace agl::algorithm::dispatch::d1::distance_line_algo {

template<typename Figure,
         typename CoordinateSystem,
         std::size_t Dimension>
struct distance{
    inline constexpr static auto get(const Figure &figure){
        static_assert(false, "No 'distance' calculations have been implemented for these points.");
    }
};

template<c_straight_line Figure,
         typename CoordinateSystem,
         std::size_t Dimension>
struct distance<Figure,
                CoordinateSystem,
                Dimension>{
    inline constexpr static auto get(const Figure &figure){
        using Type = traits::straight_line::access_types<Figure>::parameter;
        return std::numeric_limits<Type>::infinity;
    }
};

template<c_half_line_2d Figure,
         typename CoordinateSystem,
         std::size_t Dimension>
struct distance<Figure,
                CoordinateSystem,
                Dimension>{
    inline constexpr static auto get(const Figure &figure){
        using Type = traits::half_line::access_types<Figure>::parameter;
        return std::numeric_limits<Type>::infinity;
    }
};

template<c_line_section Figure,
         typename CoordinateSystem,
         std::size_t Dimension>
struct distance<Figure,
                CoordinateSystem,
                Dimension>{
    inline constexpr static auto get(const Figure &figure){
        using Point = traits::line_section::access_types<Figure>::point;
        const auto &a = traits::line_section::access_start<Figure>::get(figure);
        const auto &b = traits::line_section::access_stop<Figure>::get(figure);
        return agl::algorithm::dispatch::d2::distance_point_algo::distance<Point,
                                                                           CoordinateSystem,
                                                                           Dimension>(a, b);
    }
};

}

#endif // AGL_ALGORITHM_DISTANCE_IMPLEMENTATION_LINE_CARTESIAN_H
