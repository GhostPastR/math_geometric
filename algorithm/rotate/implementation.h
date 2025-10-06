#ifndef AGL_ALGORITHM_ROTATE_IMPLEMENTATION_H
#define AGL_ALGORITHM_ROTATE_IMPLEMENTATION_H

#include "algorithm/matrix_algorithm.h"
#include "algorithm/tag_algoritm.h"
#include "system/assert.h"
#include "system/traits.h"
#include <cmath>

namespace agl::algorithm::dispatch {

template<typename Object,
         typename ObjectDirection,
         typename Point,
         typename Group,
         typename CoordinateSystem,
         std::size_t Dimension,
         typename TypeObjectDirection>
struct rotate{
    inline constexpr static auto get(const Object &, const ObjectDirection&, const Point&){
        static_assert(false, "No 'rotate' calculations have been implemented for these objects.");
    }
};

//метод преобразует текущие координаты относительно заданной точки и угла поворота
template<typename Object,
         typename ObjectDirection,
         typename Point>
struct rotate<Object,
              ObjectDirection,
              Point,
              agl::group::points,
              system_coordinat::cartesian,
              2,
              direction_angle>{
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

template<typename Object,
         typename ObjectDirection,
         typename Point>
struct rotate<Object,
              ObjectDirection,
              Point,
              agl::group::polygons,
              system_coordinat::cartesian,
              2,
              direction_angle>{
    inline constexpr static auto get(const Object &object, const ObjectDirection &direction, const Point &point){
        using PointPolygon = agl::traits::traits_polygon::type_property<Object>::type_point;
        const auto &points = agl::traits::traits_polygon::access_points<Object>::get(object);
        std::vector<PointPolygon> new_points;
        new_points.reserve(points.size());
        std::ranges::transform(points, std::back_inserter(new_points), [point, direction](const auto &item){
            return rotate<PointPolygon,
                          ObjectDirection,
                          Point,
                          agl::group::points,
                          system_coordinat::cartesian,
                          2,
                          direction_angle>::get(item, direction, point);
        });
        return agl::traits::traits_polygon::access_create<Object>::get(std::move(new_points));
    }
};


// template<c_polugon Polygon, std::floating_point Angle>
// constexpr Polygon rotation(const Polygon &polygon, Angle angle){
//     const auto center = get_centre<typename Polygon::type_point>(polygon);
//     const auto points = polygon.get_points();
//     decltype(polygon.get_points()) new_polugon;
//     new_polugon.reserve(points.size());
//     std::ranges::transform(points, std::back_inserter(new_polugon), [center, angle](const auto &item){
//         return point_algo::rotate(item, angle, center);
//     });
//     return Polygon(new_polugon);
// }

}

namespace agl::algorithm::geometry {

template<typename Object,
         typename ObjectDirection,
         typename Point>
inline constexpr auto rotate(const Object &object, const ObjectDirection &direction, const Point &point){
    using type_coordinate_system = traits::coordinate_system<Object>::system;
    using direction_object = direction_object<ObjectDirection>::type_direction_object;
    using group = traits::group<Object>::type_group;
    constexpr auto dimension = traits::dimension<Object>::value();

    static_assert(agl::assert::is_correct<type_coordinate_system>(), "Error!");
    static_assert(agl::assert::is_correct<direction_object>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");

    return dispatch::rotate<Object,
                            ObjectDirection,
                            Point,
                            group,
                            type_coordinate_system,
                            dimension,
                            direction_object>::get(object, direction, point);
}

}


#endif // AGL_ALGORITHM_ROTATE_IMPLEMENTATION_H
