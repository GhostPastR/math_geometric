#ifndef LINE_ALGORITHM_H
#define LINE_ALGORITHM_H

#include "point_algorithm.h"

namespace agl{

template<std::floating_point Type>
struct parameter_line{
    Type a;
    Type b;
    Type c;
};

template<std::floating_point Type>
struct parameter_half_line{
    Type x;
    Type y;
    Type angle;
};

template<std::floating_point Type>
struct parameter_line_section{
    Type x1;
    Type y1;
    Type x2;
    Type y2;
};



namespace line_algo{

namespace {

template<std::floating_point Type>
constexpr bool belongs_to_area_of_line(const parameter_half_line<Type> &line, const Type &x, const Type &y){
    Type angle{};
    Type d = algorithm::pi_on_2<Type>;
    if(algorithm::interval_left_strict(line.angle, std::exchange(angle, angle + d), angle)){
        return algorithm::less_than_equal(line.x, x) && algorithm::less_than_equal(line.y, y);
    }
    if(algorithm::interval_left_strict(line.angle, std::exchange(angle, angle + d), angle)){
        return algorithm::less_than_equal(line.x, x) && algorithm::greater_than_equal(line.y, y);
    }
    if(algorithm::interval_left_strict(line.angle, std::exchange(angle, angle + d), angle)){
        return algorithm::greater_than_equal(line.x, x) && algorithm::greater_than_equal(line.y, y);
    }
    if(algorithm::interval_left_strict(line.angle, std::exchange(angle, angle + d), angle)){
        return algorithm::greater_than_equal(line.x, x) && algorithm::less_than_equal(line.y, y);
    }
    return false;
}

template<std::floating_point Type>
constexpr bool belongs_to_area_of_line(const parameter_line_section<Type> &line, const Type &x, const Type &y){
    bool flag_x = (line.x1 < line.x2) ? algorithm::interval_strict(x, line.x1, line.x2)
                                      : algorithm::interval_strict(x, line.x2, line.x1);
    bool flag_y = (line.y1 < line.y2) ? algorithm::interval_strict(y, line.y1, line.y2)
                                      : algorithm::interval_strict(y, line.y2, line.y1);
    return flag_x && flag_y;
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

//Уравнение прямой по 2-м точкам
template<std::floating_point Type>
constexpr auto equation_line_quick(const Type &x1, const Type &y1, const Type &x2, const Type &y2) -> std::tuple<Type, Type, Type>{
    const auto a = y1 - y2;
    const auto b = x2 - x1;
    return {a, b, algorithm::determine(-b, a, x1, y1)};
}

template<std::floating_point Type, std::floating_point TypeAngle>
constexpr auto equation_line_quick(const Type &x, const Type &y, TypeAngle direction) -> std::tuple<Type, Type, Type>{
    const auto a = -function_angle<Type>::cos(direction);
    const auto b = function_angle<Type>::sin(direction);
    return {a, b, algorithm::determine(-b, a, x, y)};
}

template<std::floating_point Type, template<class> class Line>
constexpr parameter_line<Type> convert_line(const Line<Type> &line){
    if constexpr(std::is_same_v<std::remove_cvref_t<decltype(line)>, parameter_line<Type>>){
        return line;
    }
    else if constexpr(std::is_same_v<std::remove_cvref_t<decltype(line)>, parameter_half_line<Type>>){
        auto a = -function_angle<Type>::cos(line.angle);
        auto b = function_angle<Type>::sin(line.angle);
        return {a, b, algorithm::determine(-b, a, line.x, line.y)};

    }
    else if constexpr(std::is_same_v<std::remove_cvref_t<decltype(line)>, parameter_line_section<Type>>){
        auto a = line.y1 - line.y2;
        auto b = line.x2 - line.x1;
        return {a, b, algorithm::determine(-b, a, line.x1, line.y1)};
    }
    else{
        static_assert(false, "The line has no borders!");
    }
}

//Уравнение прямой по 2-м точкам
template<std::floating_point Type, template<class> class Line>
constexpr Type value_function(const Line<Type> &line, const Type &x, const Type &y){
    if constexpr(std::is_same_v<std::remove_cvref_t<decltype(line)>, parameter_line<Type>>){
        return algorithm::determine(line.a, -line.b, y, x) + line.c;
    }
    else if constexpr(std::is_same_v<std::remove_cvref_t<decltype(line)>, parameter_half_line<Type>>
                         || std::is_same_v<std::remove_cvref_t<decltype(line)>, parameter_line_section<Type>>){
        const auto &temp = convert_line(line);
        return algorithm::determine(temp.a, -temp.b, y, x) + temp.c;
    }
    else{
        static_assert(false, "No Line");
    }
}

//Функция возвращает точку пересечения 2-х линий
template<std::floating_point Type, template<class> class Line1, template<class> class Line2>
constexpr auto intersection_line(const Line1<Type> &line1, const Line2<Type> &line2) -> std::optional<std::pair<Type,Type>>{
    const auto l1 = convert_line(line1);
    const auto l2 = convert_line(line2);
    constexpr bool is_line1 = std::is_same_v<std::remove_cvref_t<decltype(line1)>, parameter_line<Type>>;
    constexpr bool is_line2 = std::is_same_v<std::remove_cvref_t<decltype(line2)>, parameter_line<Type>>;
    if(const auto c = algorithm::determine(l1.a, l2.a, l1.b, l2.b); !algorithm::compare(c, Type{})){
        std::pair<Type,Type> point = {algorithm::determine(l1.b, l2.b, l1.c, l2.c) / c,
                                       algorithm::determine(l1.c, l2.c, l1.a, l2.a) / c};
        if constexpr(is_line1 && is_line2){
            return point;
        }
        else{
            bool is_point_line1 = true;
            if constexpr(!is_line1){
                is_point_line1 = belongs_to_area_of_line(line1, point.first, point.second);
            }
            bool is_point_line2 = true;
            if constexpr(!is_line2){
                is_point_line2 = belongs_to_area_of_line(line2, point.first, point.second);
            }
            if(is_point_line1 && is_point_line2){
                return point;
            }
        }
    }
    return std::nullopt;
}

//Функция возвращает точку основания перпендикуляра, опущенную из заданной точки на прямую
template<std::floating_point Type, template<class> class Line>
constexpr auto point_perpendicular(const Line<Type> &line, const Type &x, const Type &y) -> std::optional<std::pair<Type,Type>>{
    auto temp = convert_line(line);
    temp = {-temp.b, temp.a, algorithm::determine(temp.b, temp.a, x, y)};
    return line_algo::intersection_line(line, temp);
}

//Функция возвращает параллельную прямую, находящиеся на заданом расстоянии от
//данной прямой(если distance < 0, то прямая будет расположена с лево, в других случаях с право)
template<std::floating_point Type, template<class> class Line>
constexpr parameter_line<Type> parallel_line(const Line<Type> &line, Type distance){
    auto temp = convert_line(line);
    return {temp.a, temp.b, temp.c - distance * (-sqrt(algorithm::determine(temp.a, -temp.b, temp.b, temp.a)))};
}


//Функция возвращает координаты точки на отрезки с заданным расстоянием от начало отрезка
template<std::floating_point Type, template<class> class Line>
constexpr auto point_on_line(const Line<Type> &line, const Type &distance) -> std::optional<std::pair<Type,Type>>{
    if constexpr(std::is_same_v<std::remove_cvref_t<decltype(line)>, parameter_half_line<Type>>){
        return point_algo::new_point(line.x, line.y, line.angle, distance);

    }
    else if constexpr(std::is_same_v<std::remove_cvref_t<decltype(line)>, parameter_line_section<Type>>){
        if(distance > point_algo::distance<Type, 2>({line.x1, line.y1}, {line.x2, line.y2})){
            return std::nullopt;
        }
        return point_algo::new_point(line.x1, line.y1, point_algo::angle(line.x1, line.y1, line.x2, line.y2), distance);
    }
    else{
        static_assert(false, "The line has no borders!");
    }
}

// Функция проверяет принадлежит ли точка линии
template<std::floating_point Type, template<class> class Line>
constexpr bool check_point_on_line(const Line<Type> &line, const Type &x, const Type &y){
    if(algorithm::compare(value_function(line, x, y), 0.)){
        if constexpr(std::is_same_v<std::remove_cvref_t<decltype(line)>, parameter_line<Type>>){
            return true;
        }
        else if constexpr(std::is_same_v<std::remove_cvref_t<decltype(line)>, parameter_half_line<Type>>
                           || std::is_same_v<std::remove_cvref_t<decltype(line)>, parameter_line_section<Type>>){
            return belongs_to_area_of_line(line, x, y);
        }
        else{
            static_assert(false, "No Line");
        }

    }
    return false;
}

//Функция возвращает кратчайшие расстояние от точки до прямой, если значение меньше 0 то точка находится слева, если больше то справа
template<std::floating_point Type, template<class> class Line>
constexpr Type distance_to_line(const Line<Type> &line, const Type &x, const Type &y){
    auto temp = convert_line(line);
    auto dist = (algorithm::determine(temp.a, -temp.b, y, x) + temp.c) / sqrt(algorithm::determine(temp.a, -temp.b, temp.b, temp.a));
    if constexpr(std::is_same_v<std::remove_cvref_t<decltype(line)>, parameter_line<Type>>){
        return dist;
    }
    else if constexpr(std::is_same_v<std::remove_cvref_t<decltype(line)>, parameter_half_line<Type>>){
        return point_perpendicular(line, x, y).has_value() ? dist : point_algo::distance<Type, 2>({line.x, line.y}, {x, y});
    }
    else if constexpr(std::is_same_v<std::remove_cvref_t<decltype(line)>, parameter_line_section<Type>>){
        return point_perpendicular(line, x, y).has_value() ? dist : std::min(point_algo::distance<Type, 2>({line.x1, line.y1}, {x, y}),
                                                                             point_algo::distance<Type, 2>({line.x2, line.y2}, {x, y}));
    }
    else{
        static_assert(false, "The line has no borders!");
    }
}

}

}

#endif // LINE_ALGORITHM_H
