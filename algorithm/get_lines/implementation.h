#ifndef AGL_ALGORITHM_GET_LINES_IMPLEMENTATION_H
#define AGL_ALGORITHM_GET_LINES_IMPLEMENTATION_H

#include "algorithm/tag_algoritm.h"
#include "system/assert.h"
#include <algorithm>
#include <vector>

namespace agl::algorithm::dispatch {

template<typename Figure, typename OutObject, typename TagFigure, typename TagLine, typename CoordinateSystem, std::size_t Dimension>
struct get_lines{
    inline constexpr static auto get(const Figure &figure){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<typename Figure, typename OutObject>
struct get_lines<Figure, OutObject, agl::group::polygons, agl::tag::line::line_section, system_coordinat::cartesian, 2>{
    inline constexpr static auto get(const Figure &figure){
        using point = agl::traits::polygon::access_types<Figure>::point;
        std::vector<OutObject> lines;
        const auto &points = agl::traits::polygon::access_points<Figure>::get(figure);
        lines.reserve(points.size() + 1);
        std::transform(points.cbegin(), std::prev(points.cend()),
                       std::next(points.cbegin()), std::back_inserter(lines),
                       [](const auto &point1, const auto &point2){
            return agl::traits::line_section::access_create<OutObject>::get(point1, point2);
        });
        lines.push_back(agl::traits::line_section::access_create<OutObject>::get(points.back(), points.front()));
        return lines;
    }
};

}


namespace agl::algorithm::geometry {

template<typename Figure, typename OutObject>
inline constexpr auto get_lines(const Figure &figure){
    using group = traits::group<Figure>::type_group;
    using type_coordinate_system1 = traits::coordinate_system<Figure>::system;
    constexpr auto dimension1 = traits::dimension<Figure>::value();

    using tag = traits::tag<OutObject>::type_tag;
    using type_coordinate_system2 = traits::coordinate_system<OutObject>::system;
    constexpr auto dimension2 = traits::dimension<OutObject>::value();

    static_assert(agl::assert::is_correct<group>(), "Error!");
    static_assert(agl::assert::is_correct<tag>(), "Error!");
    static_assert(agl::assert::is_correct_compare<type_coordinate_system1, type_coordinate_system2>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension1, dimension2), "Error!");

    return dispatch::get_lines<Figure, OutObject, group, tag, type_coordinate_system1, dimension1>::get(figure);
}

}


#endif // AGL_ALGORITHM_GET_LINES_IMPLEMENTATION_H
