#ifndef AGL_ALGORITHM_ROTATE_IMPLEMENTATION_H
#define AGL_ALGORITHM_ROTATE_IMPLEMENTATION_H

#include "algorithm/matrix_algorithm.h"
#include "algorithm/tag_algoritm.h"
#include "algorithm/traits.h"
#include <cmath>

namespace agl::algorithm::dispatch {

template<typename Object, typename ObjectDirection, typename Point, typename Tag, typename CoordinateSystem, std::size_t Dimension, typename TypeObjectDirection>
struct rotate{
    inline constexpr static auto get(const Object &, const ObjectDirection&, const Point&){
        static_assert(false, "No 'rotate' calculations have been implemented for these objects.");
    }
};

//метод преобразует текущие координаты относительно заданной точки и угла поворота
template<typename Object, typename ObjectDirection, typename Point>
struct rotate<Object, ObjectDirection, Point, tag_point, cartesian, 2, direction_angle>{
    inline constexpr static auto get(const Object &object, const ObjectDirection &direction, const Point &point){
        using Type = traits::type_coordinate<Object>::type;
        const auto x = traits::access_point<Point, 0>::get(object);
        const auto y = traits::access_point<Point, 1>::get(object);
        const auto rx = traits::access_point<Point, 0>::get(point);
        const auto ry = traits::access_point<Point, 1>::get(point);

        const auto sinAngle = -std::sin(direction);
        const auto cosAngle = std::cos(direction);
        auto vector = matrix_algo::mul<Type, 2>({cosAngle, -sinAngle, sinAngle, cosAngle}, {x - rx, y - ry});
        return Object{vector[0] + rx, vector[1] + ry};
    }
};

}


namespace agl::algorithm::geometry {

template<typename Object, typename ObjectDirection, typename Point>
inline constexpr auto rotate(const Object &object, const ObjectDirection &direction, const Point &point){
    using type_coordinate_system = traits::coordinate_system<Object>::system;
    using direction_object = direction_object<ObjectDirection>::type_direction_object;
    using tag = traits::tag<ObjectDirection>::type_tag;
    constexpr auto dimension = traits::dimension<Object>::value();

    static_assert(!std::is_same_v<type_coordinate_system, agl::undefined>, "Error!");
    static_assert(!std::is_same_v<direction_object, undefined>, "Error!");
    static_assert((dimension > decltype(dimension){}), "Error!");

    return dispatch::rotate<Object, ObjectDirection, Point, tag,
                            type_coordinate_system, dimension, direction_object>::get(object, direction, point);
}

}


#endif // AGL_ALGORITHM_ROTATE_IMPLEMENTATION_H
