#ifndef AGL_ALGORITHM_CONTAIN_IMPLEMENTATION_H
#define AGL_ALGORITHM_CONTAIN_IMPLEMENTATION_H

#include "algorithm/math_algorithm.h"
#include "algorithm/equation_of_line/interface.h"
#include "algorithm/belongs_to_area_of_line/interface.h"
#include "system/traits.h"
#include <cmath>

namespace agl::algorithm::dispatch {

template<typename Object1,
         typename Object2,
         typename Tag1,
         typename Tag2,
         typename CoordinateSystem,
         std::size_t Dimension>
struct contain{
    inline constexpr static auto get(const Object1 &object1, const Object2 &object2){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<typename Object1,
         typename Object2>
struct contain<Object1,
               Object2,
               agl::tag::line::straight_line,
               agl::tag::point::point,
               agl::system_coordinat::cartesian,
               2>{
    inline constexpr static bool get(const Object1 &object1, const Object2 &object2){
        using namespace agl::traits::straight_line;
        using Type = access_types<Object1>::parameter;
        const auto &a = access_parameter<Object1, 0>::get(object1);
        const auto &b = access_parameter<Object1, 1>::get(object1);
        const auto &c = access_parameter<Object1, 2>::get(object1);
        const auto &x = agl::traits::point::access_point<Object2, 0>::get(object2);
        const auto &y = agl::traits::point::access_point<Object2, 1>::get(object2);
        return algorithm::compare(algorithm::determine(a, -b, y, x) + c, 0.);
    }
};

template<typename Object1,
         typename Object2>
struct contain<Object1,
               Object2,
               agl::tag::line::half_line,
               agl::tag::point::point,
               agl::system_coordinat::cartesian,
               2>{
    inline constexpr static bool get(const Object1 &object1, const Object2 &object2){
        const auto [a,b,c] = agl::algorithm::equation_of_line(object1);
        const auto &x = agl::traits::point::access_point<Object2, 0>::get(object2);
        const auto &y = agl::traits::point::access_point<Object2, 1>::get(object2);
        if(algorithm::compare(algorithm::determine(a, -b, y, x) + c, 0.)){
            return agl::algorithm::belongs_to_area_of_line(object1, object2);
        }
        return false;
    }
};

template<typename Object1,
         typename Object2>
struct contain<Object1,
               Object2,
               agl::tag::line::line_section,
               agl::tag::point::point,
               agl::system_coordinat::cartesian,
               2>{
    inline constexpr static bool get(const Object1 &object1, const Object2 &object2){
        return contain<Object1,
                       Object2,
                       agl::tag::line::half_line,
                       agl::tag::point::point,
                       agl::system_coordinat::cartesian,
                       2>::get(object1, object2);
    }
};

}


namespace agl::algorithm::geometry {

template<typename Object1,
         typename Object2>
inline constexpr bool contain(const Object1 &object1, const Object2 &object2){
    using type_cs1 = traits::coordinate_system<Object1>::system;
    using type_cs2 = traits::coordinate_system<Object2>::system;
    using tag1 = traits::tag<Object1>::type_tag;
    using tag2 = traits::tag<Object2>::type_tag;
    constexpr auto dimension1 = traits::dimension<Object1>::value();
    constexpr auto dimension2 = traits::dimension<Object2>::value();

    static_assert(agl::assert::is_correct<tag1>(), "Error!");
    static_assert(agl::assert::is_correct<tag2>(), "Error!");
    static_assert(agl::assert::is_correct_compare<type_cs1, type_cs2>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension1, dimension2), "Error!");

    return dispatch::contain<Object1,
                             Object2,
                             tag1,
                             tag2,
                             type_cs1,
                             dimension1>::get(object1, object2);
}

}


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
