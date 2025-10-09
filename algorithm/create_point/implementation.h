#ifndef AGL_ALGORITHM_CREATE_POINT_IMPLEMENTATION_H
#define AGL_ALGORITHM_CREATE_POINT_IMPLEMENTATION_H

#include "algorithm/tag_algoritm.h"
#include "system/assert.h"
#include "system/system_concept.h"
#include "system/traits.h"
#include <cmath>

namespace agl::algorithm::dispatch {

template<typename Point,
         typename Turning,
         typename Range,
         typename NewPoint,
         typename CoordinateSystem,
         std::size_t Dimension,
         typename TypeObjectDirection>
struct create_point{
    inline constexpr static auto get(const Point &point, const Turning &angle, const Range &range){
        static_assert(false, "No 'create_point' calculations have been implemented for these objects.");
    }
};

template<c_point_2d Point,
         typename Turning,
         typename Range,
         c_create_point_2d NewPoint>
struct create_point<Point,
                    Turning,
                    Range,
                    NewPoint,
                    system_coordinat::cartesian,
                    2,
                    direction_angle>{
    inline constexpr static auto get(const Point &point, const Turning &turning, const Range &range){
        const auto &x = agl::traits::point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::point::access_point<Point, 1>::get(point);
        const auto &r = agl::traits::value<Range>::get(range);
        const auto &t = agl::traits::value<Turning>::get(turning);
        return agl::traits::point::access_create<NewPoint>::get(x + r * std::sin(t), y + r * std::cos(t));
    }
};

template<typename Point,
         typename Turning,
         typename Range,
         typename NewPoint>
struct create_point<Point,
                    Turning,
                    Range,
                    NewPoint,
                    system_coordinat::geographical,
                    2,
                    direction_angle>{
    inline constexpr static auto get(const Point &point, const Turning &turning, const Range &range){
        // return NewPoint{traits::access_point<Point, 0>::get(point) + range * std::sin(turning),
        //                 traits::access_point<Point, 1>::get(point) + range * std::cos(turning)};
    }
};

template<typename Point,
         typename Turning,
         typename Range,
         typename NewPoint>
struct create_point<Point,
                    Turning,
                    Range,
                    NewPoint,
                    system_coordinat::cartesian,
                    2,
                    direction_vector>{
    inline constexpr static auto get(const Point &point, const Turning &turning, const Range &range){
        static_assert(false, "Not implemented.");
    }
};

template<typename Point,
         typename Turning,
         typename Range,
         typename NewPoint>
struct create_point<Point,
                    Turning,
                    Range,
                    NewPoint,
                    system_coordinat::cartesian,
                    3,
                    direction_vector>{
    inline constexpr static auto get(const Point &point, const Turning &turning, const Range &range){
        static_assert(false, "Not implemented.");
    }
};

}

namespace agl::algorithm::geometry {

template<typename Point,
         typename Turning,
         typename Range,
         typename NewPoint>
inline constexpr auto create_point(const Point &point, const Turning &angle, const Range &range){
    using type_coordinate_system = traits::coordinate_system<Point>::system;
    using direction_object = direction_object<Turning>::type_direction_object;
    constexpr auto dimension = traits::dimension<Point>::value();

    static_assert(agl::assert::is_correct<type_coordinate_system>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");

    return dispatch::create_point<Point,
                                  Turning,
                                  Range,
                                  NewPoint,
                                  type_coordinate_system,
                                  dimension,
                                  direction_object>::get(point, angle, range);
}

}

#endif // AGL_ALGORITHM_CREATE_POINT_IMPLEMENTATION_H
