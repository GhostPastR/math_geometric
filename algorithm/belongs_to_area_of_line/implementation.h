#ifndef AGL_ALGORITHM_BELONGS_TO_AREA_OF_LINE_IMPLEMENTATION_H
#define AGL_ALGORITHM_BELONGS_TO_AREA_OF_LINE_IMPLEMENTATION_H

#include "system/traits.h"
#include "system/system_concept.h"
#include "algorithm/math_algorithm.h"
#include <cmath>

namespace agl::algorithm::dispatch {

template<typename Line,
         typename Point>
struct belongs_to_area_of_line{
    inline constexpr static auto get(const Line &line,
                                     const Point &point){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<c_straight_line Line,
         c_point_2d Point>
    requires c_cartesian<Line> && c_cartesian<Point>
struct belongs_to_area_of_line<Line, Point>{
    inline constexpr static bool get(const Line &line,
                                     const Point &point){
        return true;
    }
};

template<c_half_line_2d Line,
         c_point_2d Point>
    requires c_cartesian<Line> && c_cartesian<Point>
struct belongs_to_area_of_line<Line, Point>{
    inline constexpr static bool get(const Line &line,
                                     const Point &point){
        using type = traits::half_line::access_types<Line>::direction;
        using point_line = traits::half_line::access_types<Line>::start;
        const c_point_2d auto &start = traits::half_line::access_start<Line>::get(line);
        const auto &line_angle = traits::half_line::access_direction<Line>::get(line);
        const auto &line_x = traits::point::access_point<point_line, 0>::get(start);
        const auto &line_y = traits::point::access_point<point_line, 1>::get(start);
        const auto &x = traits::point::access_point<Point, 0>::get(point);
        const auto &y = traits::point::access_point<Point, 1>::get(point);

        type angle{};
        type d = algorithm::pi_on_2<type>;
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

template<c_line_section Line,
         c_point_2d Point>
    requires c_cartesian<Line> && c_cartesian<Point>
struct belongs_to_area_of_line<Line, Point>{
    inline constexpr static bool get(const Line &line,
                                     const Point &point){
        using point_line = traits::line_section::access_types<Line>::point;
        const c_point_2d auto &start = traits::line_section::access_start<Line>::get(line);
        const c_point_2d auto &stop = traits::line_section::access_stop<Line>::get(line);
        const auto &x1 = traits::point::access_point<point_line, 0>::get(start);
        const auto &y1 = traits::point::access_point<point_line, 1>::get(start);
        const auto &x2 = traits::point::access_point<point_line, 0>::get(stop);
        const auto &y2 = traits::point::access_point<point_line, 1>::get(stop);
        const auto &x = traits::point::access_point<Point, 0>::get(point);
        const auto &y = traits::point::access_point<Point, 1>::get(point);

        bool flag_x = (x1 < x2) ? algorithm::interval_strict(x, x1, x2) : algorithm::interval_strict(x, x2, x1);
        bool flag_y = (y1 < y2) ? algorithm::interval_strict(y, y1, y2) : algorithm::interval_strict(y, y2, y1);
        return flag_x && flag_y;
    }
};

}

#endif // AGL_ALGORITHM_BELONGS_TO_AREA_OF_LINE_IMPLEMENTATION_H
