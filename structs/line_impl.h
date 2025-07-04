#ifndef LINE_IMPL_H
#define LINE_IMPL_H

#include "../algorithm/line_algorithm.h"
#include "../system/system_concept.h"
#include "../algorithm/math_algorithm.h"

namespace agl {

template<std::floating_point Type, c_point2d Point>
struct straight_line_impl final {
    using type_coefficients = Type;
    using type_point = Point;
    using line_view = line_view<type_point>;

    constexpr straight_line_impl(Type a, Type b, Type c) : a_(a), b_(b), c_(c){}
    constexpr straight_line_impl(const Point &point1, const Point &point2){
        auto [a,b,c] = line_algo::equation_line_quick(point1, point2);
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

    line_view view_confines() const{
        auto points = line_algo::point_line<Point>(a_, b_, c_);
        return {view<Point>{points.first, false}, view<Point>{points.second, false}};
    }

    friend constexpr bool operator==(const straight_line_impl &line1, const straight_line_impl &line2){
        return line_algo::compare(line1.a_, line1.b_, line1.c_, line2.a_, line2.b_, line2.c_);
    }
private:
    Type a_{};  //!Коэффициент A уравнения Ax + By + C = 0
    Type b_{};  //!Коэффициент B уравнения Ax + By + C = 0
    Type c_{};  //!Коэффициент C уравнения Ax + By + C = 0
};

template<std::floating_point Type, c_point2d Point, c_angle Angle>
struct half_line_impl final {
    using type_coefficients = Type;
    using type_point = Point;
    using line_view = line_view<type_point>;

    constexpr half_line_impl(const Point &start, Type direction)
        : start_(start), direction_(direction){}
    constexpr half_line_impl(const Point &start, const Angle &angle)
        : start_(start), direction_(angle.radian()){}

    auto start() const{
        return start_;
    }
    auto direction() const{
        return direction_;
    }
    auto direction_angle() const{
        return Angle(direction_);
    }

    line_view view_confines() const{
        return {view<Point>{start_, true}, view<Point>{point_algo::new_point(start_, direction_, 1.), false}};
    }

    friend constexpr bool operator==(const half_line_impl &line1, const half_line_impl &line2){
        return (line1.start_ == line2.start_) && algorithm::compare(line1.direction_, line2.direction_);
    }

private:
    Point start_;
    Type direction_;
};

template<c_point2d Point>
struct line_section_impl final{
    using type_coefficients = Point::type_coordinate;
    using type_point = Point;
    using line_view = line_view<type_point>;

    constexpr line_section_impl(const Point &start, const Point &stop)
        : start_(start), stop_(stop){}

    auto start() const{
        return start_;
    }
    auto stop() const{
        return stop_;
    }

    line_view view_confines() const{
        return {view<Point>{start_, true}, view<Point>{stop_, true}};
    }

    friend constexpr bool operator==(const line_section_impl &line1, const line_section_impl &line2){
        return (line1.start_ == line2.start_) && (line1.stop_ == line2.stop_);
    }
private:
    Point start_;
    Point stop_;
};

}

#endif // LINE_IMPL_H
