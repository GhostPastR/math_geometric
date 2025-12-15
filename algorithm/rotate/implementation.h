#ifndef AGL_ALGORITHM_ROTATE_IMPLEMENTATION_H
#define AGL_ALGORITHM_ROTATE_IMPLEMENTATION_H

#include "algorithm/matrix_algorithm.h"
#include "algorithm/tag_algoritm.h"
#include "system/assert.h"
#include "system/system_concept.h"
#include "system/traits.h"
#include <cmath>

namespace agl::algorithm::dispatch {

template<typename Object,
         typename ObjectDirection,
         typename Point,
         typename TypeObjectDirection>
struct rotate{
    inline constexpr static auto get(const Object &, const ObjectDirection&, const Point&){
        static_assert(false, "No 'rotate' calculations have been implemented for these objects.");
    }
};

//метод преобразует текущие координаты относительно заданной точки и угла поворота
template<c_point_2d PointIn,
         typename ObjectDirection,
         c_point_2d Point>
    requires c_cartesian_all<PointIn, Point> && c_demension_2_all<PointIn, Point>
struct rotate<PointIn,
              ObjectDirection,
              Point,
              direction_angle>{
    inline constexpr static auto get(const PointIn &point_in, const ObjectDirection &direction, const Point &point){
        using Type = std::tuple_element<0, typename agl::traits::point::access_types<PointIn>::types>::type;
        // using Type = traits::point::access_types<PointIn>::point;
        const auto x = traits::point::access_point<Point, 0>::get(point_in);
        const auto y = traits::point::access_point<Point, 1>::get(point_in);
        const auto rx = traits::point::access_point<Point, 0>::get(point);
        const auto ry = traits::point::access_point<Point, 1>::get(point);

        const auto sinAngle = -std::sin(traits::value<ObjectDirection>::get(direction));
        const auto cosAngle = std::cos(traits::value<ObjectDirection>::get(direction));
        auto vector = matrix_algo::mul<Type, 2>({cosAngle, -sinAngle, sinAngle, cosAngle}, {x - rx, y - ry});
        return agl::traits::make<PointIn>::apply(vector[0] + rx, vector[1] + ry);
    }
};

template<c_polygon Polygon,
         typename ObjectDirection,
         c_point_2d Point>
    requires c_cartesian_all<Polygon, Point> && c_demension_2_all<Polygon, Point>
struct rotate<Polygon,
              ObjectDirection,
              Point,
              direction_angle>{
    inline constexpr static auto get(const Polygon &polygon, const ObjectDirection &direction, const Point &point){
        using PointPolygon = agl::traits::polygon::access_types<Polygon>::point;
        const auto &points = agl::traits::polygon::access_points<Polygon>::get(polygon);
        std::vector<PointPolygon> new_points;
        new_points.reserve(points.size());
        std::ranges::transform(points, std::back_inserter(new_points), [point, direction](const auto &item){
            return rotate<PointPolygon,
                          ObjectDirection,
                          Point,
                          direction_angle>::get(item, direction, point);
        });
        return agl::traits::make<Polygon>::get(std::move(new_points));
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
    using direction_object = direction_object<ObjectDirection>::type_direction_object;

    static_assert(agl::assert::is_correct<direction_object>(), "Error!");

    return dispatch::rotate<Object,
                            ObjectDirection,
                            Point,
                            direction_object>::get(object, direction, point);
}

}


#endif // AGL_ALGORITHM_ROTATE_IMPLEMENTATION_H
