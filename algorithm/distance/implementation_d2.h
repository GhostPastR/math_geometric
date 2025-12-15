#ifndef AGL_ALGORITHM_DISTANCE_D2_H
#define AGL_ALGORITHM_DISTANCE_D2_H

#include "algorithm/equation_of_line/interface.h"
#include "algorithm/distance/implementation_cartesian.h"
#include "algorithm/intersection/interface.h"
#include "algorithm/perpendicular/interface.h"


#include "system/traits.h"
#include <cmath>

namespace agl::algorithm::dispatch::d2::point_to_object {

namespace dispatch {

template<typename Object1,
         typename Object2>
struct distance{
    inline constexpr static auto get(const Object1 &point, const Object2 &object){
        static_assert(false, "No 'distance' calculations have been implemented for these points.");
    }
};

template<c_point_2d Point,
         c_straight_line Line>
    requires c_cartesian_all<Line,Point>
struct distance<Point,
                Line>{
    inline constexpr static auto get(const Point &point, const Line &object){
        const auto a = agl::traits::straight_line::access_parameter<Line, 0>::get(object);
        const auto b = agl::traits::straight_line::access_parameter<Line, 1>::get(object);
        const auto c = agl::traits::straight_line::access_parameter<Line, 2>::get(object);
        const auto x = agl::traits::point::access_point<Point, 0>::get(point);
        const auto y = agl::traits::point::access_point<Point, 1>::get(point);
        return std::abs(algorithm::determine(a, -b, y, x) + c) / sqrt(algorithm::determine(a, -b, b, a));
    }
};

template<c_point_2d Point,
         c_half_line_2d Line>
    requires c_cartesian_all<Line,Point>
struct distance<Point,
                Line>{
    inline constexpr static auto get(const Point &point, const Line &object){
        using str_line = agl::traits::half_line::access_straight_line<Line>::type;
        const auto line = agl::algorithm::equation_of_line<str_line>(object);
        const auto x = agl::traits::point::access_point<Point, 0>::get(point);
        const auto y = agl::traits::point::access_point<Point, 1>::get(point);
        const auto p_line = agl::algorithm::perpendicular<str_line>(line, point);
        if(agl::algorithm::intersection<Point>(object, p_line).has_value()){
            const auto &a = agl::traits::straight_line::access_parameter<str_line, 0>::get(line);
            const auto &b = agl::traits::straight_line::access_parameter<str_line, 1>::get(line);
            const auto &c = agl::traits::straight_line::access_parameter<str_line, 2>::get(line);
            return std::abs(algorithm::determine(a, -b, y, x) + c) / sqrt(algorithm::determine(a, -b, b, a));
        }
        const auto start = agl::traits::half_line::access_start<Line>::get(object);
        return agl::algorithm::dispatch::d2::distance_point_algo::distance<Point>(start, point);
    }
};

template<c_point_2d Point,
         c_line_section Line>
    requires c_cartesian_all<Line,Point> && c_demension_2<Line>
struct distance<Point,
                Line>{
    inline constexpr static auto get(const Point &point, const Line &object){
        using str_line = agl::traits::line_section::access_straight_line<Line>::type;
        const auto line = agl::algorithm::equation_of_line<str_line>(object);
        const auto x = agl::traits::point::access_point<Point, 0>::get(point);
        const auto y = agl::traits::point::access_point<Point, 1>::get(point);
        const auto p_line = agl::algorithm::perpendicular<str_line>(line, point);
        if(agl::algorithm::intersection<Point>(object, p_line).has_value()){
            const auto &a = agl::traits::straight_line::access_parameter<str_line, 0>::get(line);
            const auto &b = agl::traits::straight_line::access_parameter<str_line, 1>::get(line);
            const auto &c = agl::traits::straight_line::access_parameter<str_line, 2>::get(line);
            return std::abs(algorithm::determine(a, -b, y, x) + c) / sqrt(algorithm::determine(a, -b, b, a));
        }
        const auto start = agl::traits::line_section::access_start<Line>::get(object);
        const auto stop = agl::traits::line_section::access_stop<Line>::get(object);
        return std::min(agl::algorithm::dispatch::d2::distance_point_algo::distance<Point>(start, point),
                        agl::algorithm::dispatch::d2::distance_point_algo::distance<Point>(stop, point));
    }
};

}

template<typename Object1,
         typename Object2,
         typename CoordinateSystem,
         std::size_t Dimension>
inline constexpr auto distance(const Object1 &point, const Object2 &object){
    return agl::algorithm::dispatch::d2::point_to_object::dispatch::distance<Object1,
                                                                             Object2>::get(point, object);
}

}

#endif // AGL_ALGORITHM_DISTANCE_D2_H
