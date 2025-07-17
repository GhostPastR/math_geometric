#ifndef POINT_ALGORITHM_H
#define POINT_ALGORITHM_H

#include <numeric>

#include "../system/system_concept.h"
#include "../algorithm/matrix_algorithm.h"
#include "math_algorithm.h"


namespace agl::point_algo{

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
    return matrix_algo::module<typename Point::type_coordinate,2>({point2.x() - point1.x(), point2.y() - point1.y()});
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
    using Type = Point::type_coordinate;
    const auto sinAngle = -ClassFunc::sin(angle);
    const auto cosAngle = ClassFunc::cos(angle);
    auto vector = matrix_algo::mul<Type, 2>({cosAngle, -sinAngle, sinAngle, cosAngle},
                                            {point.x() - reference.x(), point.y() - reference.y()});
    return {vector[0] + reference.x(), vector[1] + reference.y()};
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

template<c_point2d_decard Point>
constexpr bool is_co_directional(const Point &start, const Point &stop1, const Point &stop2){
    using Type = Point::type_coordinate;
    return matrix_algo::is_co_directional(std::array<Type, 2>{stop1.x() - start.x(), stop1.y() - start.y()},
                                          std::array<Type, 2>{stop2.x() - start.x(), stop2.y() - start.y()});
}

}

#endif // POINT_ALGORITHM_H
