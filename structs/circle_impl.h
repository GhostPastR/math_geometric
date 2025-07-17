#ifndef CIRCLE_IMPL_H
#define CIRCLE_IMPL_H

#include "../system/system_concept.h"
#include "../algorithm/math_algorithm.h"
#include <format>

namespace agl {

template<std::floating_point Type, c_point2d_decard Point>
struct circle_impl final {
    using type_coefficients = Type;
    using type_point = Point;
    using figure = std::true_type;

    constexpr circle_impl(const Point &center, Type radius)
        : center_(center), radius_(radius){}

    Point center() const{
        return center_;
    }
    Type radius() const{
        return radius_;
    }

private:
    Point center_;
    Type radius_{};
};

template<std::floating_point Type, c_point2d_decard Point, c_angle Angle>
struct arc_impl final {
    using type_coefficients = Type;
    using type_point = Point;
    using figure = std::false_type;

    constexpr arc_impl(const Point &center, Type radius, Type start, Type stop)
        : center_(center), radius_(radius), start_(start), stop_(stop){}
    constexpr arc_impl(const Point &center, Type radius, const Angle &start, const Angle &stop)
        : center_(center), radius_(radius), start_(start.radian()), stop_(stop.radian()){}

    constexpr Point center() const{
        return center_;
    }
    constexpr Type radius() const{
        return radius_;
    }
    constexpr Type start() const{
        return start_;
    }
    constexpr Angle start_angle() const{
        return Angle(start_);
    }
    constexpr Type stop() const{
        return stop_;
    }
    constexpr Angle stop_angle() const{
        return Angle(stop_);
    }

    friend constexpr bool operator==(const arc_impl &arc1, const arc_impl &arc2){
        return (arc1.center_ == arc2.center_) && algorithm::compare(arc1.radius_, arc2.radius_)
             && algorithm::compare(arc1.start_, arc2.start_) && algorithm::compare(arc1.stop_, arc2.stop_);
    }

private:
    Point center_;
    Type radius_{};

    Type start_{};
    Type stop_{};
};

}

template<std::floating_point Type, agl::c_point2d_decard Point, agl::c_angle Angle>
constexpr std::ostream& operator<<(std::ostream& os, const agl::arc_impl<Type, Point, Angle> &arc){
    os << std::format("{} {} {} {} {}", arc.center().x(), arc.center().y(), arc.start(), arc.stop(), arc.radius());
    return os;
}

#endif // CIRCLE_IMPL_H
