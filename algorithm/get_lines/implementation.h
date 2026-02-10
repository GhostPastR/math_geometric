#ifndef AGL_ALGORITHM_GET_LINES_IMPLEMENTATION_H
#define AGL_ALGORITHM_GET_LINES_IMPLEMENTATION_H

#include "system/system_concept.h"
#include <algorithm>
#include <vector>

namespace agl::algorithm::dispatch {

template<typename Figure,
         typename OutObject>
struct get_lines{
    inline constexpr static auto get(const Figure &figure){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<c_group_polygon Figure,
         c_create_line_section OutObject>
requires c_cartesian<Figure> && c_cartesian<OutObject> && c_demension_2<Figure> && c_demension_2<OutObject>
struct get_lines<Figure,
                 OutObject>{
    inline constexpr static auto get(const Figure &figure){
        using point = agl::traits::polygon::access_types<Figure>::point;
        std::vector<OutObject> lines;
        const auto &points = agl::traits::polygon::access_points<Figure>::get(figure);
        lines.reserve(points.size() + 1);
        std::transform(points.cbegin(), std::prev(points.cend()),
                       std::next(points.cbegin()), std::back_inserter(lines),
                       [](const auto &point1, const auto &point2){
            return agl::traits::make<OutObject>::apply(point1, point2);
        });
        lines.push_back(agl::traits::make<OutObject>::apply(points.back(), points.front()));
        return lines;
    }
};

}

#endif // AGL_ALGORITHM_GET_LINES_IMPLEMENTATION_H
