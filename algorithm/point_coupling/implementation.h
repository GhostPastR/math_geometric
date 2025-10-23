#ifndef AGL_ALGORITHM_POINT_COUPLING_IMPLEMENTATION_H
#define AGL_ALGORITHM_POINT_COUPLING_IMPLEMENTATION_H

#include "algorithm/distance/interface.h"
#include "algorithm/get_lines/interface.h"

#include "algorithm/point_coupling/implementation_line.h"

namespace agl::algorithm::dispatch {

template<typename Figure,
         typename Point,
         typename CoordinateSystem,
         std::size_t Dimension>
struct point_coupling{
    inline constexpr static auto get(const Figure &figure, const Point &point, bool is_perpendicular){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<c_group_line Line,
         c_point_2d Point,
         typename CoordinateSystem,
         std::size_t Dimension>
struct point_coupling<Line,
                      Point,
                      CoordinateSystem,
                      Dimension>{
    inline constexpr static auto get(const Line &line, const Point &point, bool is_perpendicular) -> std::optional<Point>{
        return agl::algorithm::dispatch::group_line::point_coupling<Line,
                                                                    Point,
                                                                    CoordinateSystem,
                                                                    Dimension>(line, point, is_perpendicular);
    }
};



template<c_group_polygon Polygon,
         c_point_2d Point>
struct point_coupling<Polygon,
                      Point,
                      agl::system_coordinat::cartesian,
                      2>{
    inline constexpr static auto get(const Polygon &polygon, const Point &point, bool is_perpendicular) -> std::optional<Point>{
        using str_line = agl::traits::polygon::access_line_section<Polygon>::type;
        using point_polygon = agl::traits::polygon::access_types<Polygon>::point;
        const auto lines = agl::algorithm::get_lines<str_line>(polygon);
        std::vector<std::optional<point_polygon>> c_points;
        c_points.reserve(lines.size() + 1);
        std::ranges::transform(lines, std::back_inserter(c_points), [point](const auto &line){
            return point_coupling<str_line,
                                  Point,
                                  agl::system_coordinat::cartesian,
                                  2>::get(line, point, true);
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


namespace agl::algorithm::geometry {

template<typename Figure,
         typename Point>
inline constexpr auto point_coupling(const Figure &figure, const Point &point, bool is_perpendicular){
    using type_coordinate_system1 = traits::coordinate_system<Figure>::system;
    using type_coordinate_system2 = traits::coordinate_system<Point>::system;
    constexpr auto dimension1 = traits::dimension<Figure>::value();
    constexpr auto dimension2 = traits::dimension<Point>::value();

    static_assert(agl::assert::is_correct_compare<type_coordinate_system1, type_coordinate_system2>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension1, dimension2), "Error!");

    return dispatch::point_coupling<Figure,
                                    Point,
                                    type_coordinate_system1,
                                    dimension1>::get(figure, point, is_perpendicular);
}

}


#endif // AGL_ALGORITHM_POINT_COUPLING_IMPLEMENTATION_H
