#ifndef CIRCLE_IMPL_H
#define CIRCLE_IMPL_H

#include "../system/system_concept.h"

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

    Point center() const{
        return center_;
    }
    Type radius() const{
        return radius_;
    }
    Type start() const{
        return start_;
    }
    Angle start_angle() const{
        return Angle(start_);
    }
    Type stop() const{
        return stop_;
    }
    Angle stop_angle() const{
        return Angle(stop_);
    }

private:
    Point center_;
    Type radius_{};

    Type start_{};
    Type stop_{};
};

// template<std::floating_point Type>
// using arc_impl = arc_abstract<Type, point2d_impl<Type>>;

// template<std::floating_point Type>
// using arc_geo_impl = arc_abstract<Type, point_geo2d_impl<Type>>;

// template<std::floating_point Type>
// using circle_impl = circle_abstract<Type, point2d_impl<Type>>;

// template<std::floating_point Type, c_angle Angle>
// using circle_geo_impl = circle_abstract<Type, point_geo2d_impl<Angle>>;

#endif // CIRCLE_IMPL_H
