#ifndef AGL_ALGORITHM_BELONGS_TO_AREA_OF_LINE_IMPLEMENTATION_H
#define AGL_ALGORITHM_BELONGS_TO_AREA_OF_LINE_IMPLEMENTATION_H

#include "system/assert.h"
#include "system/traits.h"
#include "algorithm/math_algorithm.h"
#include <cmath>

namespace agl::algorithm::dispatch {

template<typename Line, typename Object, typename TagLine, typename TagObject, typename CoordinateSystem, std::size_t Dimension>
struct belongs_to_area_of_line{
    inline constexpr static auto get(const Line &line, const Object &object){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<typename Line, typename Object, typename CoordinateSystem, std::size_t Dimension>
struct belongs_to_area_of_line<Line, Object, agl::tag::tag_straight_line, agl::tag::tag_point, CoordinateSystem, Dimension>{
    inline constexpr static bool get(const Line &line, const Object &object){
        return true;
    }
};

template<typename Line, typename Object>
struct belongs_to_area_of_line<Line, Object, agl::tag::tag_half_line, agl::tag::tag_point, system_coordinat::cartesian, 2>{
    inline constexpr static bool get(const Line &line, const Object &object){
        using Type = traits::traits_half_line::type_property<Line>::type_direction;
        using Point = traits::traits_half_line::type_property<Line>::type_start;
        const auto &start = traits::traits_half_line::access_start<Line>::get(line);
        const auto &line_angle = traits::traits_half_line::access_direction<Line>::get(line);
        const auto &line_x = traits::traits_point::access_point<Point, 0>::get(start);
        const auto &line_y = traits::traits_point::access_point<Point, 1>::get(start);
        const auto &x = traits::traits_point::access_point<Point, 0>::get(object);
        const auto &y = traits::traits_point::access_point<Point, 1>::get(object);

        Type angle{};
        Type d = algorithm::pi_on_2<Type>;
        if(algorithm::interval_left_strict(line_angle, std::exchange(angle, angle + d), angle)){
            return algorithm::less_than_equal(line_x, x) && algorithm::less_than_equal(line_y, y);
        }
        if(algorithm::interval_left_strict(line_angle, std::exchange(angle, angle + d), angle)){
            return algorithm::less_than_equal(line_x, x) && algorithm::greater_than_equal(line_y, y);
        }
        if(algorithm::interval_left_strict(line_angle, std::exchange(angle, angle + d), angle)){
            return algorithm::greater_than_equal(line_x, x) && algorithm::greater_than_equal(line_y, y);
        }
        if(algorithm::interval_left_strict(line_angle, std::exchange(angle, angle + d), angle)){
            return algorithm::greater_than_equal(line_x, x) && algorithm::less_than_equal(line_y, y);
        }
        return false;
    }
};

template<typename Line, typename Object>
struct belongs_to_area_of_line<Line, Object, agl::tag::tag_line_section, agl::tag::tag_point, system_coordinat::cartesian, 2>{
    inline constexpr static bool get(const Line &line, const Object &object){
        using Point = traits::traits_line_section::type_property<Line>::type_point;
        const auto &start = traits::traits_line_section::access_start<Line>::get(line);
        const auto &stop = traits::traits_line_section::access_stop<Line>::get(line);
        const auto &x1 = traits::traits_point::access_point<Point, 0>::get(start);
        const auto &y1 = traits::traits_point::access_point<Point, 1>::get(start);
        const auto &x2 = traits::traits_point::access_point<Point, 0>::get(stop);
        const auto &y2 = traits::traits_point::access_point<Point, 1>::get(stop);
        const auto &x = traits::traits_point::access_point<Point, 0>::get(object);
        const auto &y = traits::traits_point::access_point<Point, 1>::get(object);

        bool flag_x = (x1 < x2) ? algorithm::interval_strict(x, x1, x2) : algorithm::interval_strict(x, x2, x1);
        bool flag_y = (y1 < y2) ? algorithm::interval_strict(y, y1, y2) : algorithm::interval_strict(y, y2, y1);
        return flag_x && flag_y;
    }
};

}


namespace agl::algorithm::geometry {

template<typename Line, typename Object>
inline constexpr bool belongs_to_area_of_line(const Line &line, const Object &object){
    using tag_line = traits::tag<Line>::type_tag;
    using tag_object = traits::tag<Object>::type_tag;
    using type_cs1 = traits::coordinate_system<Line>::system;
    using type_cs2 = traits::coordinate_system<Object>::system;
    constexpr auto dimension1 = traits::dimension<Line>::value();
    constexpr auto dimension2 = traits::dimension<Object>::value();

    static_assert(agl::assert::is_correct<tag_line>(), "Error!");
    static_assert(agl::assert::is_correct<tag_object>(), "Error!");
    static_assert(agl::assert::is_correct_compare<type_cs1, type_cs2>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension1, dimension2), "Error!");

    return dispatch::belongs_to_area_of_line<Line, Object, tag_line, tag_object, type_cs1, dimension1>::get(line, object);
}

}


#endif // AGL_ALGORITHM_BELONGS_TO_AREA_OF_LINE_IMPLEMENTATION_H
