#ifndef AGL_ALGORITHM_POINT_COUPLING_IMPLEMENTATION_H
#define AGL_ALGORITHM_POINT_COUPLING_IMPLEMENTATION_H

#include "algorithm/distance/interface.h"
#include "algorithm/get_lines/interface.h"

namespace agl::algorithm::dispatch {

template<typename Figure,
         typename Point>
struct point_coupling{
    inline constexpr static auto get(const Figure &figure, const Point &point, bool is_perpendicular){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

//Добавить для луча и прямой
template<c_line_section Line,
         c_point_2d Point>
    requires c_cartesian_all<Line, Point> && c_demension_2_all<Line, Point>
struct point_coupling<Line,
                      Point>{
    inline constexpr static auto get(const Line &line, const Point &point, bool is_perpendicular) -> std::optional<Point>{
        using str_line = ::agl::traits::line_section::access_straight_line<Line>::type;
        auto p_line = ::agl::algorithm::perpendicular<str_line>(line, point);
        if(const auto int_point = ::agl::algorithm::intersection<Point>(line, p_line); int_point.has_value()){
            return int_point;
        }
        const auto &start = ::agl::traits::line_section::access_start<Line>::get(line);
        const auto &stop = ::agl::traits::line_section::access_stop<Line>::get(line);
        if(is_perpendicular){
            return std::nullopt;
        }
        auto d1 = ::agl::algorithm::distance(point, start);
        auto d2 = ::agl::algorithm::distance(point, stop);
        if(d1 < d2){
            return start;
        }
        return stop;
    }
};


template<c_group_polygon Polygon,
         c_point_2d Point>
    requires c_cartesian_all<Polygon, Point> && c_demension_2_all<Polygon, Point>
struct point_coupling<Polygon,
                      Point>{
    inline constexpr static auto get(const Polygon &polygon, const Point &point, bool is_perpendicular) -> std::optional<Point>{
        using str_line = agl::traits::polygon::access_line_section<Polygon>::type;
        using point_polygon = agl::traits::polygon::access_types<Polygon>::point;
        const auto lines = agl::algorithm::get_lines<str_line>(polygon);
        std::vector<std::optional<point_polygon>> c_points;
        c_points.reserve(lines.size() + 1);
        std::ranges::transform(lines, std::back_inserter(c_points), [point](const auto &line){
            return point_coupling<str_line,
                                  Point>::get(line, point, true);
        });
        std::erase_if(c_points, [](const auto &item){
            return !item.has_value();
        });
        if(!is_perpendicular){
            const auto &points = agl::traits::polygon::access_points<Polygon>::get(polygon);
            std::ranges::copy(points, std::back_inserter(c_points));
        }
        if(!c_points.empty()){
            return *std::min_element(c_points.cbegin(), c_points.cend(), [point](const auto &item, const auto &min){
                return agl::algorithm::distance(point, min.value()) > agl::algorithm::distance(point, item.value());
            });
        }
        return std::nullopt;
    }
};

}

#endif // AGL_ALGORITHM_POINT_COUPLING_IMPLEMENTATION_H
