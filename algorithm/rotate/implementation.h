#ifndef AGL_ALGORITHM_ROTATE_IMPLEMENTATION_H
#define AGL_ALGORITHM_ROTATE_IMPLEMENTATION_H

#include "algorithm/matrix_algorithm.h"
#include "algorithm/tag_algoritm.h"
#include "system/assert.h"
#include "system/traits.h"
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
struct rotate<Object, ObjectDirection, Point, agl::tag::tag_point, system_coordinat::cartesian, 2, direction_angle>{
    inline constexpr static auto get(const Object &object, const ObjectDirection &direction, const Point &point){
        using Type = traits::traits_point::type_property<Object>::type_point;
        const auto x = traits::traits_point::access_point<Point, 0>::get(object);
        const auto y = traits::traits_point::access_point<Point, 1>::get(object);
        const auto rx = traits::traits_point::access_point<Point, 0>::get(point);
        const auto ry = traits::traits_point::access_point<Point, 1>::get(point);

        const auto sinAngle = -std::sin(traits::value<ObjectDirection>::get(direction));
        const auto cosAngle = std::cos(traits::value<ObjectDirection>::get(direction));
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
    using tag = traits::tag<Object>::type_tag;
    constexpr auto dimension = traits::dimension<Object>::value();

    static_assert(agl::assert::is_correct<type_coordinate_system>(), "Error!");
    static_assert(agl::assert::is_correct<direction_object>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");

    return dispatch::rotate<Object, ObjectDirection, Point, tag,
                            type_coordinate_system, dimension, direction_object>::get(object, direction, point);
}

}


#endif // AGL_ALGORITHM_ROTATE_IMPLEMENTATION_H
