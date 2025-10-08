#ifndef AGL_ALGORITHM_POINT_COUPLING_IMPLEMENTATION_H
#define AGL_ALGORITHM_POINT_COUPLING_IMPLEMENTATION_H

#include "algorithm/distance/interface.h"
#include "algorithm/get_lines/interface.h"

#include "algorithm/point_coupling/implementation_line.h"

namespace agl::algorithm::dispatch {

template<typename Figure,
         typename Point,
         typename Group,
         typename Tag,
         typename CoordinateSystem,
         std::size_t Dimension>
struct point_coupling{
    inline constexpr static auto get(const Figure &figure, const Point &point, bool is_perpendicular){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<typename Figure,
         typename Point,
         typename Tag,
         typename CoordinateSystem,
         std::size_t Dimension>
struct point_coupling<Figure,
                      Point,
                      agl::group::lines,
                      Tag,
                      CoordinateSystem,
                      Dimension>{
    inline constexpr static auto get(const Figure &figure, const Point &point, bool is_perpendicular) -> std::optional<Point>{
        return agl::algorithm::dispatch::group_line::point_coupling<Figure,
                                                                    Point,
                                                                    Tag,
                                                                    CoordinateSystem,
                                                                    Dimension>(figure, point, is_perpendicular);
    }
};



template<typename Figure,
         typename Point>
struct point_coupling<Figure,
                      Point,
                      agl::group::polygons,
                      agl::tag::point::point,
                      agl::system_coordinat::cartesian,
                      2>{
    inline constexpr static auto get(const Figure &figure, const Point &point, bool is_perpendicular) -> std::optional<Point>{
        using str_line = agl::traits::polygon::access_line_section<Figure>::type;
        using point_polygon = agl::traits::polygon::access_types<Figure>::point;
        const auto lines = agl::algorithm::get_lines<str_line>(figure);
        std::vector<std::optional<point_polygon>> c_points;
        c_points.reserve(lines.size() + 1);
        std::ranges::transform(lines, std::back_inserter(c_points), [point](const auto &line){
            return point_coupling<str_line,
                                  Point,
                                  agl::group::lines,
                                  agl::tag::point::point,
                                  agl::system_coordinat::cartesian,
                                  2>::get(line, point, true);
        });
        std::erase_if(c_points, [](const auto &item){
            return !item.has_value();
        });
        if(!is_perpendicular){
            const auto &points = agl::traits::polygon::access_points<Figure>::get(figure);
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

template<typename Figure, typename Point>
inline constexpr auto point_coupling(const Figure &figure, const Point &point, bool is_perpendicular){
    using group = traits::group<Figure>::type_group;
    using tag = traits::tag<Point>::type_tag;
    using type_coordinate_system1 = traits::coordinate_system<Figure>::system;
    using type_coordinate_system2 = traits::coordinate_system<Point>::system;
    constexpr auto dimension1 = traits::dimension<Figure>::value();
    constexpr auto dimension2 = traits::dimension<Point>::value();

    static_assert(agl::assert::is_correct<group>(), "Error!");
    static_assert(agl::assert::is_correct<tag>(), "Error!");
    static_assert(agl::assert::is_correct_compare<type_coordinate_system1, type_coordinate_system2>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension1, dimension2), "Error!");

    return dispatch::point_coupling<Figure,
                                    Point,
                                    group,
                                    tag,
                                    type_coordinate_system1,
                                    dimension1>::get(figure, point, is_perpendicular);
}

}


#endif // AGL_ALGORITHM_POINT_COUPLING_IMPLEMENTATION_H
