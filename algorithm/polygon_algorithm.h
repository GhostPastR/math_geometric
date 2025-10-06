// #ifndef POLYGON_ALGORITHM_H
// #define POLYGON_ALGORITHM_H

// #include <algorithm>
// #include <ranges>
// #include <vector>

// #include "line_algorithm.h"
// #include "point_algorithm.h"

// namespace agl::polygon_algo{


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







// //Функция определяет пересечение линии со сторонами многоугольника.
// template<c_polugon Polygon, c_line_view Line>
// constexpr auto polygon_apertain_line(const Polygon &poilygon, const Line &line) -> std::vector<typename Polygon::type_point>{
//     using Point = Polygon::type_point;
//     std::vector<Point> _points;
//     const auto lines = get_lines(poilygon);
//     auto temp = lines | std::ranges::views::transform([line](const auto &l){ return line_algo::intersection_line(l, line); })
//                 | std::ranges::views::filter([](const auto &point){ return point.has_value(); })
//                 | std::ranges::views::transform([](const auto &p){ return p.value(); });
//     return std::vector<Point>(temp.begin(), temp.end());
// }

// //Функция определяет пересикает ли полигон другой полигон
// template<c_polugon Polygon>
// constexpr bool polygon_intersect_polygon(const Polygon &polygon1, const Polygon &polygon2){
//     auto lines1 = get_lines(polygon1);
//     auto lines2 = get_lines(polygon2);
//     return std::ranges::any_of(lines1, [&lines2](const auto &line1){
//         return std::ranges::any_of(lines2, [&line1](const auto &line2){
//             return line_algo::intersection_line(line1, line2).has_value();
//         });
//     });
// }

// }


// #endif // POLYGON_ALGORITHM_H
