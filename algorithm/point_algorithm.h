#ifndef POINT_ALGORITHM_H
#define POINT_ALGORITHM_H

#include <numeric>

#include "../system/system_concept.h"
#include "math_algorithm.h"

namespace point_algo{

// возвращает направление отрезка от текущей точки до заданной точки(входной параметр методы).
template<c_point2d_decard Point, c_function_angle<typename Point::type_coordinate> ClassFunc = algorithm::function_angle<typename Point::type_coordinate>>
constexpr auto angle(const Point &point1, const Point &point2){
    using Type = Point::type_coordinate;
    Type temp(ClassFunc::atan2(point2.x() - point1.x(), point2.y() - point1.y()));
    return temp += (temp < 0) ? algorithm::pi_in_2<Type> : 0.0;
}

//возвращает длину между 2-мя точками.
template<c_point2d_decard Point>
constexpr auto distance(const Point &point1, const Point &point2){
    return std::sqrt(std::pow(point2.x() - point1.x(), 2) + std::pow(point2.y() - point1.y(), 2));
}

//метод расчитывает координаты новой точки
template<c_point2d_decard Point, std::floating_point TypeAngle, std::floating_point TypeRange,
         c_function_angle<typename Point::type_coordinate> ClassFunc = algorithm::function_angle<typename Point::type_coordinate>>
constexpr Point new_point(const Point &point, const TypeAngle &angle, const TypeRange &range){
    return {point.x() + range * ClassFunc::sin(angle), point.y() + range * ClassFunc::cos(angle)};
}

//метод преобразует текущие координаты относительно заданной точки и угла поворота
template<c_point2d_decard Point, std::floating_point TypeAngle,
         c_function_angle<typename Point::type_coordinate> ClassFunc = algorithm::function_angle<typename Point::type_coordinate>>
constexpr Point rotate(const Point &point, const TypeAngle &angle, const Point &reference){
    const auto dx = point.x() - reference.x();
    const auto dy = point.y() - reference.y();
    const auto sinAngle = -ClassFunc::sin(angle);
    const auto cosAngle = ClassFunc::cos(angle);
    const auto x = dx * cosAngle - dy * sinAngle;
    const auto y = dx * sinAngle + dy * cosAngle;
    return {x + reference.x(), y + reference.y()};
}

// метод возвращает среднию точку между точками.
template<c_point2d_decard Point>
constexpr Point midplane(const Point &point1, const Point &point2){
    return {std::midpoint(point1.x(), point2.x()), std::midpoint(point1.x(), point2.x())};
}

template<c_point2d_polar Polar, c_point2d_decard Point>
constexpr Polar convert_polar(const Point &point1, const Point &point2){
    return {distance(point1, point2), angle(point1, point2)};
}

template<c_point2d_decard Point, c_polar2d Polar>
constexpr Point convert_decart(const Polar &point, const Point &start){
    return new_point(start, point.fi(), point.psi());
}

}

#endif // POINT_ALGORITHM_H
