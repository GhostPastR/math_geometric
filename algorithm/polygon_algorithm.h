#ifndef POLYGON_ALGORITHM_H
#define POLYGON_ALGORITHM_H

#include <algorithm>
#include <ranges>
#include <vector>

#include "line_algorithm.h"
#include "point_algorithm.h"

namespace agl::polygon_algo{

template<c_point2d Point>
constexpr bool is_convex_polygone(const std::vector<Point> &points){
    if(points.size() < 3){
        return false;
    }
    auto calc_direct = [](const Point &p1, const Point &p2, const Point &p3){
        const Point v1 = {p2.x() - p1.x(), p2.y() - p1.y()};
        const Point v2 = {p3.x() - p2.x(), p3.y() - p2.y()};
        return v1.x() * v2.y() - v1.y() * v2.x();
    };

    int direct = calc_direct(*std::prev(points.end()), *points.begin(), *std::next(points.begin())) > 0 ? 1 : -1;
    for(auto begin = std::next(points.begin()), end = std::prev(points.end()); begin != end; ++begin ){
        if(std::exchange(direct,calc_direct(*std::prev(begin), *begin, *std::next(begin)) > 0 ? 1 : -1) != direct){
            return false;
        }
    }
    return true;
}

template<c_point2d Point>
constexpr bool is_rectangle(const std::vector<Point> &points){
    if(points.size() != 4){
        return false;
    }
    if((point_algo::distance(points[0], points[1]) == point_algo::distance(points[2], points[3]))
        && (point_algo::distance(points[1], points[2]) == point_algo::distance(points[0], points[3]))){
        const Point point1 = {points[0].x() - points[1].x(), points[0].y() - points[1].y()};
        const Point point2 = {points[2].x() - points[1].x(), points[2].y() - points[1].y()};
        return algorithm::compare(point1.x() * point2.x() + point1.y() * point2.y(), 0.);
    }
    return false;
}

template<c_point2d Point>
constexpr bool is_square(const std::vector<Point> &points){
    if(points.size() != 4){
        return false;
    }
    const auto l1 = point_algo::distance(points[0], points[1]);
    const auto l2 = point_algo::distance(points[1], points[2]);
    const auto l3 = point_algo::distance(points[2], points[3]);
    const auto l4 = point_algo::distance(points[0], points[3]);
    if((l1 == l2) && (l3 == l4) && (l1 == l3)){
        const Point point1 = {points[0].x() - points[1].x(), points[0].y() - points[1].y()};
        const Point point2 = {points[2].x() - points[1].x(), points[2].y() - points[1].y()};
        return algorithm::compare(point1.x() * point2.x() + point1.y() * point2.y(), 0.);
    }
    return false;
}

template<c_point2d Point>
constexpr bool is_triangle(const std::vector<Point> &points){
    if(points.size() != 3){
        return false;
    }
    const auto l1 = point_algo::distance(points[0], points[1]);
    const auto l2 = point_algo::distance(points[1], points[2]);
    const auto l3 = point_algo::distance(points[0], points[2]);
    return ((l1 < (l2 + l3)) && (l2 < (l1 + l3)) && (l3 < (l1 + l2)));
}

template<c_point2d Point>
constexpr bool is_regular_polygon(const std::vector<Point> &points){
    if(points.size() < 3){
        return false;
    }
    using Type = Point::type_coordinate;
    std::vector<Type> lenghts;
    lenghts.reserve(points.size());
    std::transform(points.begin(), std::prev(points.end()), points.begin(),
                   std::back_inserter(lenghts), [](const auto &item1, const auto &item2){
        return point_algo::distance(item1, item2);
    });
    if(std::all_of(std::next(lenghts.begin()), lenghts.end(), [lenght = lenghts.front()](const auto &item){
            return item == lenght;
        })){
        const Point point1 = {points[0].x() - points[1].x(), points[0].y() - points[1].y()};
        const Point point2 = {points[2].x() - points[1].x(), points[2].y() - points[1].y()};
        const auto angle = std::acos((point1.x() * point2.x() + point1.y() * point2.y()) /
                     (sqrt(std::pow(point1.x(), 2) + std::pow(point1.y(), 2))
                     * sqrt(std::pow(point2.x(), 2) + std::pow(point2.y(), 2))));
        return algorithm::compare(angle, (1. - 2./points.size()) * algorithm::pi<Type>);
    }
    return false;
}

template<c_point2d Point>
constexpr std::vector<Point> create_convex_polygone(const std::initializer_list<Point> &list){
    std::vector<Point> points;
    points.insert(points.end(), list.begin(), list.end());
    return is_convex_polygone(points) ? points : std::vector<Point>();
}

template<c_point2d Point, std::floating_point Type>
constexpr std::vector<Point> create_rectangle(const Point &point, Type width, Type height){
    return {{point.x(), point.y()},
            {point.x() + width, point.y()},
            {point.x() + width, point.y() - height},
            {point.x(), point.y() - height}};
}

template<c_point2d Point, std::floating_point Type>
constexpr std::vector<Point> create_square(const Point &point, Type length){
    return create_rectangle(point, length, length);
}

template<c_point2d Point>
constexpr std::vector<Point> create_triangle(const Point &point1, const Point &point2, const Point &point3){
    return is_triangle({point1, point2, point3}) ?
               std::vector<Point>{point1, point2, point3} : std::vector<Point>();
}

template<c_point2d Point, std::floating_point Type>
constexpr std::vector<Point> create_triangle(const Point &start, const Type &a, const Type &b, const Type &c){
    const auto angle = acos(-(std::pow(c,2) - std::pow(a,2) - std::pow(b,2)) / (2*a*b));
    const auto point2 = Point{start.x() + a, start.y()};
    const auto temp = Point{point2.x() - b, point2.y()};
    return {start, point2, point_algo::rotate(temp, -angle, point2)};
}

template<c_point2d Point, std::floating_point Type, c_angle Angle>
constexpr std::vector<Point> create_triangle(const Point &start, const Type &a, const Type &c, const Angle &ac){
    const auto point2 = {start.x() + a, start.y()};
    const auto temp = {start.x() + c, start.y()};
    return {start, point2, point_algo::rotate(temp, ac, point2)};
}

template<c_point2d Point, std::floating_point Type, c_angle Angle>
constexpr std::vector<Point> create_triangle(const Point &start, const Type &a, const Angle &ac, const Angle &ab){
    const auto point2 = {start.x() + a, start.y()};
    const auto b = a * std::sin(ab) / std::sin(algorithm::pi<Type> - ac - ab);
    const auto temp = {point2.x() - b, point2.y()};
    return {start, point2, point_algo::rotate(temp, ab, point2)};
}

template<c_point2d Point, std::floating_point Type, std::floating_point TypeAngle>
constexpr std::vector<Point> create_regular_polygon(const Point &center, Type length, size_t count, TypeAngle start = {}){
    std::vector<Point> points;
    TypeAngle angle = algorithm::pi_in_2<Type> / static_cast<Type>(count);
    const auto radius = length / (2 * std::sin(angle / 2));

    const auto numbers = std::ranges::iota_view{size_t(), count};
    std::ranges::transform(numbers, std::back_inserter(points), [center, radius, angle, start](const auto &i){
        return Point{center.x() + radius * std::sin(i * angle + start), center.y() + radius * std::cos(i * angle + start)};
    });
    return points;
}

template<c_point2d Point, std::floating_point Type>
constexpr std::vector<Point> create_regular_polygon(const Point &center, Type length, size_t count){
    return create_regular_polygon(center, length, count, 0.);
}



//Функция возвращает список отрезков, из которого состоит полигон
template<c_polugon Polygon>
constexpr auto get_lines(const Polygon &polygon) -> std::vector<line_view<typename Polygon::type_point>>{
    using Line = line_view<typename Polygon::type_point>;
    std::vector<Line> lines;
    const auto points = polygon.get_points();
    lines.reserve(points.size() + 1);
    std::transform(points.cbegin(), std::prev(points.cend()),
                   std::next(points.cbegin()), std::back_inserter(lines),
                   [](const auto &point1, const auto &point2){
        return Line({point1, true}, {point2, true});
    });
    lines.push_back(Line{{points.back(), true}, {points.front(), true}});
    return lines;
}

//Функция определяет попадает ли точка в полигон
template<c_polugon Polygon, c_point2d_decard Point>
constexpr bool point_appertain_polygon(const Polygon &polygon, const Point &point){
    auto points = polygon.get_points();
    auto size = points.size();
    if(size < 2){
        return false;
    }
    if(std::any_of(points.begin(), points.end(), [point](auto p){return p == point;})){
        return true;
    }
    auto pair_point = line_algo::point_line(point, 0.);
    line_view<Point> half_line{{pair_point.first, true}, {pair_point.second, false}};
    const auto list_line = get_lines(polygon);
    int crosscut = std::accumulate(list_line.begin(), list_line.end(), 0, [half_line](int sum, const auto &item){
        return sum + (line_algo::intersection_line(half_line, item).has_value() ? 1 : 0);
    });
    return (crosscut % 2) == 1;
}

//Функция определяет пересикает ли полигон другой полигон
template<c_polugon Polygon>
constexpr bool polygon_intersect_polygon(const Polygon &polygon1, const Polygon &polygon2){
    auto lines1 = get_lines(polygon1);
    auto lines2 = get_lines(polygon2);
    return std::ranges::any_of(lines1, [&lines2](const auto &line1){
        return std::ranges::any_of(lines2, [&line1](const auto &line2){
            return line_algo::intersection_line(line1, line2).has_value();
        });
    });
}

//Функция определяет попадает ли отрезок в полигон
template<c_polugon Polygon, c_line_view Line>
constexpr bool polygon_appertain_section(const Polygon &polygon, const Line &line){
    if(!line.view_begin.is_view || !line.view_end.is_view){
        return false;
    }
    return (point_appertain_polygon(polygon, line.view_begin.value) && point_appertain_polygon(polygon, line.view_end.value));
}

template<typename T>
class Temp;

//Функция стягивает произвольную точку к ближайшей стороне полигона
template<c_point2d Point, c_polugon Polygon>
constexpr Point point_coupling(const Polygon &polygon, const Point &point){
    auto lines = get_lines(polygon);
    auto temp = lines | std::ranges::views::transform([point](const auto &line){ return line_algo::point_perpendicular(line, point); })
                | std::ranges::views::filter([](const auto &point){ return point.has_value(); })
                | std::ranges::views::transform([](const auto &p){ return p.value(); });
    std::vector<Point> points(temp.begin(), temp.end());
    std::ranges::copy(polygon.get_points(), std::back_inserter(points));
    return *std::min_element(points.begin(), points.end(), [point](const auto &item, const auto &min){
        return point_algo::distance(point, min) > point_algo::distance(point, item);
    });
}

// // // возвращает прямоугольник в который вписан полигон
// // template<std::floating_point Type, c_polugon Polygon>
// // rectangle_impl<Type> polugon_in_rectangle(const Polygon &polygon)
// // {
// //     if(polygon.points.empty()){
// //         return {};
// //     }
// //     std::vector<Type> vector_x(polygon.points.size());
// //     std::transform(polygon.points.begin(), polygon.points.end(), vector_x.begin(), [](auto item){
// //         return item.x;
// //     });
// //     std::vector<Type> vector_y(polygon.points.size());
// //     std::transform(polygon.points.begin(), polygon.points.end(), vector_y.begin(), [](auto item){
// //         return item.y;
// //     });
// //     auto[min_x, max_x] = std::minmax_element(vector_x.begin(), vector_x.end());
// //     auto[min_y, max_y]  = std::minmax_element(vector_y.begin(), vector_y.end());

// //     polygon_impl<Type> temp;
// //     temp.points.push_back({min_x, max_y});
// //     temp.points.push_back({max_x, max_y});
// //     temp.points.push_back({max_x, min_y});
// //     temp.points.push_back({min_x, min_y});
// //     return temp;
// // }

template<c_point2d Point>
constexpr Point get_centre(const std::vector<Point> &points){
    using Type = Point::type_coordinate;
    const auto sum = std::accumulate(points.begin(), points.end(), std::pair<Type, Type>(),
                               [](std::pair<Type, Type> sum, auto item){
        return std::pair<Type, Type>(sum.first + item.x(), sum.second + item.y());
    });
    return {sum.first / points.size(), sum.second / points.size()};
}

template<c_point2d Point, c_polugon Polygon>
constexpr Point get_centre(const Polygon &polygon){
    return get_centre(polygon.get_points());
}

//Функция расширяет правельный многоугольник на заданное расстояния от границы
template<c_regular_polygon Polygon, std::floating_point Type>
constexpr Polygon scale_regular_polygon(const Polygon &polygon, Type distance){
    const auto center = get_centre<typename Polygon::type_point>(polygon);
    const auto points = polygon.get_points();
    const auto d1 = point_algo::distance(point_algo::midplane(*points.begin(), *std::next(points.begin())), center);
    const auto new_lenght = ((d1 + distance) / d1) * point_algo::distance(*points.begin(), *std::next(points.begin()));
    return Polygon(create_regular_polygon(center, new_lenght, points.size(), point_algo::angle(center, *points.begin())));
}

//Функция определяет пересечение линии со сторонами многоугольника.
template<c_polugon Polygon, c_line_view Line>
constexpr auto polygon_apertain_line(const Polygon &poilygon, const Line &line) -> std::vector<typename Polygon::type_point>{
    using Point = Polygon::type_point;
    std::vector<Point> _points;
    const auto lines = get_lines(poilygon);
    auto temp = lines | std::ranges::views::transform([line](const auto &l){ return line_algo::intersection_line(l, line); })
                | std::ranges::views::filter([](const auto &point){ return point.has_value(); })
                | std::ranges::views::transform([](const auto &p){ return p.value(); });
    return std::vector<Point>(temp.begin(), temp.end());
}

//Функция определяет попадает ли полигон в полигон.
template<c_polugon Polygon>
constexpr bool polygon_appertain_polygon(const Polygon &polygon1, const Polygon &polygon2){
    const auto points = polygon2.get_points(); 
    return std::ranges::all_of(points, [polygon1](const auto &point){
        return point_appertain_polygon(polygon1, point);
    });
}

template<c_polugon Polygon, std::floating_point Angle>
constexpr Polygon rotation(const Polygon &polygon, Angle angle){
    const auto center = get_centre<typename Polygon::type_point>(polygon);
    const auto points = polygon.get_points();
    decltype(polygon.get_points()) new_polugon;
    new_polugon.reserve(points.size());
    std::ranges::transform(points, std::back_inserter(new_polugon), [center, angle](const auto &item){
        return point_algo::rotate(item, angle, center);
    });
    return Polygon(new_polugon);
}

}


#endif // POLYGON_ALGORITHM_H
