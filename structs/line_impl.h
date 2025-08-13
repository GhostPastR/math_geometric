#ifndef LINE_IMPL_H
#define LINE_IMPL_H

#include "point_impl.h"
#include "../unit/angle.h"
#include "../algorithm/line_algorithm.h"
#include "../system/system_concept.h"
#include "../algorithm/math_algorithm.h"
#include <iostream>

namespace agl {

template<std::floating_point Type>
struct straight_line_impl final {
    constexpr straight_line_impl(Type a, Type b, Type c) : a_(a), b_(b), c_(c){}
    constexpr straight_line_impl(const point2<Type> &point1, const point2<Type> &point2){
        auto [a,b,c] = line_algo::equation_line_quick(point1.x(), point1.y(), point2.x(), point2.y());
        a_ = a;
        b_ = b;
        c_ = c;
    }

    auto a() const{
        return a_;
    }
    auto b() const{
        return b_;
    }
    auto c() const{
        return c_;
    }

    friend constexpr bool operator==(const straight_line_impl &line1, const straight_line_impl &line2){
        return line_algo::compare(line1.a_, line1.b_, line1.c_, line2.a_, line2.b_, line2.c_);
    }
private:
    //!Коэффициенты уравнения Ax + By + C = 0
    Type a_{};
    Type b_{};
    Type c_{};
};

template<std::floating_point Type>
struct half_line_impl final {
    constexpr half_line_impl(const point2<Type> &start, const angle_impl<Type> &angle)
        : start_(start), direction_(angle.radian()){}

    auto start() const{
        return start_;
    }
    auto direction() const{
        return direction_;
    }

    friend constexpr bool operator==(const half_line_impl &line1, const half_line_impl &line2){
        return (line1.start_ == line2.start_) && (line1.direction_ == line2.direction_);
    }

private:
    point2<Type> start_;
    angle_impl<Type> direction_;
};

template<std::floating_point Type>
struct line_section_impl final{
    constexpr line_section_impl(const point2<Type> &start, const point2<Type> &stop)
        : start_(start), stop_(stop){}

    auto start() const{
        return start_;
    }
    auto stop() const{
        return stop_;
    }

    friend constexpr bool operator==(const line_section_impl &line1, const line_section_impl &line2){
        return (line1.start_ == line2.start_) && (line1.stop_ == line2.stop_);
    }
private:
    point2<Type> start_;
    point2<Type> stop_;
};



template<std::floating_point Type>
constexpr auto equation_line_quick(const point2<Type> &point1, const point2<Type> &point2) -> std::tuple<Type, Type, Type>{
    return line_algo::equation_line_quick(point1.x(), point1.y(), point2.x(), point2.y());
}

template<std::floating_point Type>
constexpr auto equation_line_quick(const point2<Type> &point, angle_impl<Type> direction) -> std::tuple<Type, Type, Type>{
    return line_algo::equation_line_quick(point.x(), point.y(), direction.radian());
}

template<std::floating_point Type, template<class> class Line>
auto convert_base(const Line<Type> &line){
    if constexpr(std::is_same_v<std::remove_cvref_t<decltype(line)>, straight_line_impl<Type>>){
        return parameter_line{line.a(), line.b(), line.c()};
    }
    else if constexpr(std::is_same_v<std::remove_cvref_t<decltype(line)>, half_line_impl<Type>>){
        return parameter_half_line{line.start().x(), line.start().y(), line.direction().radian()};
    }
    else if constexpr(std::is_same_v<std::remove_cvref_t<decltype(line)>, line_section_impl<Type>>){
        return parameter_line_section{line.start().x(), line.start().y(), line.stop().x(), line.stop().y()};
    }
    else{
        static_assert(false, "No Line");
    }
}

//Функция возвращает значение функции f(x,y) = Ax + By + C
template<class Line, std::floating_point Type>
constexpr Type value_function(const Line &line, const point2<Type> &point){
    return line_algo::value_function(convert_base(line), point.x(), point.y());
}

//Функция возвращает точку пересечения 2-х линий
template<std::floating_point Type, template<class> class Line1, template<class> class Line2>
constexpr auto intersection_line(const Line1<Type> &line1, const Line2<Type> &line2) -> std::optional<point2<Type>>{
    auto p = line_algo::intersection_line(convert_base(line1), convert_base(line2));
    return p.has_value() ? std::optional{point2<Type>{p->first, p->second}} : std::nullopt;
}

//Функция возвращает точку основания перпендикуляра, опущенную из заданной точки на прямую
template<std::floating_point Type, template<class> class Line>
constexpr std::optional<point2<Type>> point_perpendicular(const Line<Type> &line, const point2<Type> &point){
    auto p = line_algo::point_perpendicular(convert_base(line), point.x(), point.y());
    return p.has_value() ? std::optional{point2<Type>{p->first, p->second}} : std::nullopt;
}

//Функция возвращает параллельную прямую, находящиеся на заданом расстоянии от
//данной прямой(если distance < 0, то прямая будет расположена с лево, в других случаях с право)
template<class Line, std::floating_point Type>
constexpr straight_line_impl<Type> parallel_line(const Line &line, Type distance){
    auto temp = line_algo::parallel_line(convert_base(line), distance);
    return {temp.a, temp.b, temp.c};
}

//Функция возвращает координаты точки на отрезки с заданным расстоянием от начало отрезка
template<class Line, std::floating_point Type>
constexpr std::optional<point2<Type>> point_on_line(const Line &line, const Type &distance){
    auto p = line_algo::point_on_line(convert_base(line), distance);
    return p.has_value() ? std::optional{point2<Type>{p->first, p->second}} : std::nullopt;
}

// Функция проверяет принадлежит ли точка линии
template<class Line, std::floating_point Type>
constexpr bool check_point_on_line(const Line &line, const point2<Type> &point){
    return line_algo::check_point_on_line(convert_base(line), point.x(), point.y());
}

//Функция возвращает кратчайшие расстояние от точки до прямой, если значение меньше 0 то точка находится слева, если больше то справа
template<class Line, std::floating_point Type>
constexpr auto distance_to_line(const Line &line, const point2<Type> &point){
    return line_algo::distance_to_line(convert_base(line), point.x(), point.y());
}

}

#endif // LINE_IMPL_H
