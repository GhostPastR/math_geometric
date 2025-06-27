#ifndef LINE_ALGORITHM_H
#define LINE_ALGORITHM_H

#include "point_algorithm.h"

template<c_point2d_decard Point>
struct line_view{
    using type_point = Point::type_coordinate;
    using point = Point;

    view<Point> view_begin;
    view<Point> view_end;
};

template<typename Type>
concept c_line_temp = requires(Type temp){
    typename Type::type_point;
    temp.view_confines();
};


template<c_line_temp Line>
auto view_line(const Line &temp) -> line_view<typename Line::type_point>{
    return temp.view_confines();
}

template<typename Type>
concept c_line_view = requires(Type temp){
    typename Type::type_point;
    typename Type::point;

    temp.view_begin;
    temp.view_end;
};


namespace line_algo{

namespace {

template<c_line_view View, c_point2d_decard Point>
constexpr bool belongs_to_area_of_line(const View &line, const Point &point){
    if(!line.view_begin.is_view && !line.view_end.is_view){
        return true;
    }
    if(!line.view_end.is_view){
        using Type = Point::type_coordinate;
        const auto direction = point_algo::angle(line.view_begin.value, line.view_end.value);
        Type angle{};
        Type d = algorithm::pi_on_2<Type>;
        if(algorithm::interval_left_strict(direction, std::exchange(angle, angle + d), angle)){
            return algorithm::less_than_equal(line.view_begin.value.x(), point.x())
            && algorithm::less_than_equal(line.view_begin.value.y(), point.y());
        }
        if(algorithm::interval_left_strict(direction, std::exchange(angle, angle + d), angle)){
            return algorithm::less_than_equal(line.view_begin.value.x(), point.x())
            && algorithm::greater_than_equal(line.view_begin.value.y(), point.y());
        }
        if(algorithm::interval_left_strict(direction, std::exchange(angle, angle + d), angle)){
            return algorithm::greater_than_equal(line.view_begin.value.x(), point.x())
            && algorithm::greater_than_equal(line.view_begin.value.y(), point.y());
        }
        if(algorithm::interval_left_strict(direction, std::exchange(angle, angle + d), angle)){
            return algorithm::greater_than_equal(line.view_begin.value.x(), point.x())
            && algorithm::less_than_equal(line.view_begin.value.y(), point.y());
        }
        return false;
    }
    bool _flagX;
    bool _flagY;
    if(line.view_begin.value.x() < line.view_end.value.x() ){
        _flagX = algorithm::interval_strict(point.x(), line.view_begin.value.x(), line.view_end.value.x());
    }
    else{
        _flagX = algorithm::interval_strict(point.x(), line.view_end.value.x(), line.view_begin.value.x());
    }

    if(line.view_begin.value.y() < line.view_end.value.y() ){
        _flagY = algorithm::interval_strict(point.y(), line.view_begin.value.y(), line.view_end.value.y());
    }
    else{
        _flagY = algorithm::interval_strict(point.y(), line.view_end.value.y(), line.view_begin.value.y());
    }
    return _flagX && _flagY;

}

}

template<std::floating_point Type>
constexpr bool compare(Type a1, Type b1, Type c1, Type a2, Type b2, Type c2){
    const bool compare_a = algorithm::compare(a1, a2);
    const bool compare_b = algorithm::compare(b1, b2);
    const bool compare_c = algorithm::compare(c1, c2);
    if(compare_a && compare_b && compare_c){
        return true;
    }
    else{
        Type k{};
        if(!algorithm::compare(a2, 0.)){
            k = a1 / a2;
        }
        else if(!algorithm::compare(b2, 0.)){
            k = b1 / b2;
        }
        else if(!algorithm::compare(c2, 0.)){
            k = c1 / c2;
        }
        if(algorithm::compare(k, 0.)){
            return false;
        }
        return algorithm::compare(a1, k * a2)
               && algorithm::compare(b1, k * b2)
               && algorithm::compare(c1, k * c2);
    }
}

template<c_point2d_decard Point, std::floating_point Type>
constexpr std::pair<Point,Point> point_line(Type a, Type b, Type c){
    const bool is_zero_a = algorithm::compare(a, 0.);
    const bool is_zero_b = algorithm::compare(b, 0.);
    if(is_zero_a && is_zero_b){
        return {Point(0,0), Point(0,0)};
    }
    if(is_zero_a){
        return {Point(0., -c / b), Point(1., -c / b)};
    }
    if(is_zero_b){
        return {Point(-c / a, 0.), Point(-c / a, 1.)};
    }
    return {Point(0, -c / b), Point(1, -(a + c) / b)};
}

template<c_point2d_decard Point, std::floating_point Angle>
constexpr std::pair<Point,Point> point_line(const Point &point, Angle angle){
    return {point, point_algo::new_point(point, angle, 1.)};
}


template<c_point2d_decard Point>
constexpr auto equation_line_quick(const Point &point1, const Point &point2)
    -> std::tuple<typename Point::type_coordinate, typename Point::type_coordinate, typename Point::type_coordinate>{
    const auto a = point1.y() - point2.y();
    const auto b = point2.x() - point1.x();
    return {a, b, -b * point1.y() - a * point1.x()};
}

template<c_point2d_decard Point, std::floating_point TypeAngle,
         c_function_angle<typename Point::type_coordinate> ClassFunc = algorithm::function_angle<typename Point::type_coordinate>>
constexpr auto equation_line_quick(const Point &point, TypeAngle direction)
    -> std::tuple<typename Point::type_coordinate, typename Point::type_coordinate, typename Point::type_coordinate>{
    const auto a = -ClassFunc::cos(direction);
    const auto b = ClassFunc::sin(direction);
    return {a, b, -b * point.y() - a * point.x()};
}

//Функция возвращает кратчайшие расстояние от точки до прямой, если значение меньше 0 то точка находится слева, если больше то справа
template<c_line_view View, c_point2d_decard Point>
constexpr auto distance_to_line(const View &line, const Point &point) -> View::type_point{
    const auto [a,b,c] = equation_line_quick(line.view_begin.value, line.view_end.value);
    const auto distance = (a * point.x() + b * point.y() + c) / sqrt(a * a + b * b);
    if(!line.view_begin.is_view && !line.view_end.is_view){
        return distance;
    }
    const auto dist_start = point_algo::distance(line.view_begin.value, point);
    if(!line.view_end.is_view){
        return std::min(std::abs(distance), dist_start);
    }
    const auto dist_stop = point_algo::distance(line.view_end.value, point);
    return std::min({std::abs(distance), dist_start, dist_stop});
}

//Функция возвращает значение функции f(x,y) = Ax + By + C
template<c_line_view View, c_point2d_decard Point>
constexpr auto value_function(const View &line, const Point &point){
    const auto [a,b,c] = equation_line_quick(line.view_begin.value, line.view_end.value);
    return point.x() * a + point.y() * b + c;
}


//Функция возвращает точку пересечения 2-х линий
template<c_line_view View>
constexpr auto intersection_line(const View &line1, const View &line2) ->  std::optional<typename View::point>{
    using Point = View::point;
    const auto [a1,b1,c1] = equation_line_quick(line1.view_begin.value, line1.view_end.value);
    const auto [a2,b2,c2] = equation_line_quick(line2.view_begin.value, line2.view_end.value);

    std::optional<Point> point;
    const auto c = a1 * b2 - a2 * b1;
    if(!algorithm::compare(c, 0.)){
        point = {(b1 * c2 - b2 * c1) / c, (c1 * a2 - c2 * a1) / c};
    }

    if(point.has_value() && belongs_to_area_of_line(line1, point.value()) && belongs_to_area_of_line(line2, point.value())){
        return point;
    }
    return {};
}

// Функция проверяет принадлежит ли точка линии
template<c_line_view View, c_point2d_decard Point>
constexpr bool check_point_on_line(const View &line, const Point &point){
    if(algorithm::compare(value_function(line, point), 0.)){
        return belongs_to_area_of_line(line, point);
    }
    return false;
}

//Функция возвращает параллельную прямую, находящиеся на заданом расстоянии от
//данной прямой(если distance < 0, то прямая будет расположена с лево, в других случаях с право)
template<c_line_view View, std::floating_point Type>
constexpr View parallel_line(const View &line, Type distance){
    const auto [a,b,c] = equation_line_quick(line.view_begin.value, line.view_end.value);
    const auto points = point_line<typename View::point>(a, b, c - distance * (-sqrt(a * a + b * b)));
    return {{points.first, false}, {points.second, false}};
}

//Функция возвращает точку основания перпендикуляра, опущенную из заданной точки на прямую
template<c_line_view View, c_point2d_decard Point>
constexpr std::optional<Point> point_perpendicular(const View &line, const Point &point){
    const auto [a,b,_] = equation_line_quick(line.view_begin.value, line.view_end.value);
    const auto points = point_line<typename View::point>(-b, a, b * point.x() - a * point.y());
    return intersection_line(line, View({{points.first, false}, {points.second, false}}));
}

//Функция возвращает координаты точки на отрезки с заданным расстоянием от начало отрезка
template<c_line_view View, std::floating_point Type>
constexpr auto point_on_line(const View &line, Type distance) -> std::optional<typename View::point>{
    if(!line.view_begin.is_view && !line.view_end.is_view){
        return std::nullopt;
    }
    if(!line.view_end.is_view){
        return point_algo::new_point(line.view_begin.value, point_algo::angle(line.view_begin.value, line.view_end.value), distance);
    }
    if(distance > point_algo::distance(line.view_begin.value, line.view_end.value)){
        return std::nullopt;
    }
    return point_algo::new_point(line.view_begin.value, point_algo::angle(line.view_begin.value, line.view_end.value), distance);
}

}

#endif // LINE_ALGORITHM_H
