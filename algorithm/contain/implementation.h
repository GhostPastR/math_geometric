#ifndef AGL_ALGORITHM_CONTAIN_IMPLEMENTATION_H
#define AGL_ALGORITHM_CONTAIN_IMPLEMENTATION_H

#include "algorithm/math_algorithm.h"
#include "algorithm/equation_of_line/interface.h"
#include "algorithm/belongs_to_area_of_line/interface.h"
#include "system/traits.h"
#include <cmath>

namespace agl::algorithm::dispatch {

template<typename Object1,
         typename Object2>
struct contain{
    inline constexpr static auto get(const Object1 &object1, const Object2 &object2){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<c_group_line Line,
         c_point_2d Point>
    requires c_cartesian<Line> && c_cartesian<Point> && c_demension_2<Line>
struct contain<Line,
               Point>{
    inline constexpr static bool get(const Line &line, const Point &point){
        const auto [a,b,c] = agl::algorithm::equation_of_line(line);
        const auto &x = agl::traits::point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::point::access_point<Point, 1>::get(point);
        if(algorithm::compare(algorithm::determine(a, -b, y, x) + c, 0.)){
            return agl::algorithm::belongs_to_area_of_line(line, point);
        }
        return false;
    }
};

template<c_circle Circle,
         c_point_2d Point>
    requires c_cartesian<Circle> && c_cartesian<Point> && c_demension_2<Circle>
struct contain<Circle,
               Point>{
    inline constexpr static bool get(const Circle &circle, const Point &point){
        using Center = agl::traits::circle::access_types<Circle>::center;
        const auto &center = agl::traits::circle::access_center<Circle>::get(circle);
        const auto &radius = agl::traits::circle::access_radius<Circle>::get(circle);
        const auto &c_x = agl::traits::point::access_point<Center, 0>::get(center);
        const auto &c_y = agl::traits::point::access_point<Center, 1>::get(center);
        const auto &x = agl::traits::point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::point::access_point<Point, 1>::get(point);
        return algorithm::less_than_equal(std::pow(x - c_x, 2) + std::pow(y - c_y, 2), std::pow(radius, 2));
    }
};

}

//На будущие: добавить функции для 3D




// //Функция определяет попадает ли точка в полигон
// template<c_polugon Polygon, c_point2d_decard Point>
// constexpr bool point_appertain_polygon(const Polygon &polygon, const Point &point){
//     auto points = polygon.get_points();
//     auto size = points.size();
//     if(size < 2){
//         return false;
//     }
//     if(std::any_of(points.begin(), points.end(), [point](auto p){return p == point;})){
//         return true;
//     }
//     auto pair_point = line_algo::point_line(point, 0.);
//     line_view<Point> half_line{{pair_point.first, true}, {pair_point.second, false}};
//     const auto list_line = get_lines(polygon);
//     int crosscut = std::accumulate(list_line.begin(), list_line.end(), 0, [half_line](int sum, const auto &item){
//         return sum + (line_algo::intersection_line(half_line, item).has_value() ? 1 : 0);
//     });
//     return (crosscut % 2) == 1;
// }

// //Функция определяет попадает ли отрезок в полигон
// template<c_polugon Polygon, c_line_view Line>
// constexpr bool polygon_appertain_section(const Polygon &polygon, const Line &line){
//     if(!line.view_begin.is_view || !line.view_end.is_view){
//         return false;
//     }
//     return (point_appertain_polygon(polygon, line.view_begin.value) && point_appertain_polygon(polygon, line.view_end.value));
// }

// //Функция определяет попадает ли полигон в полигон.
// template<c_polugon Polygon>
// constexpr bool polygon_appertain_polygon(const Polygon &polygon1, const Polygon &polygon2){
//     const auto points = polygon2.get_points();
//     return std::ranges::all_of(points, [polygon1](const auto &point){
//         return point_appertain_polygon(polygon1, point);
//     });
// }



#endif // AGL_ALGORITHM_<>_IMPLEMENTATION_H
