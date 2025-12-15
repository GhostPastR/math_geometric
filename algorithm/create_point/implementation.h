#ifndef AGL_ALGORITHM_CREATE_POINT_IMPLEMENTATION_H
#define AGL_ALGORITHM_CREATE_POINT_IMPLEMENTATION_H

#include "algorithm/tag_algoritm.h"
#include "system/assert.h"
#include "system/system_concept.h"
#include "system/traits.h"
#include <cmath>

namespace agl::algorithm::dispatch {

template<typename OutPoint,
         typename TypeObjectDirection,
         typename Point,
         typename Range,
         typename ...Turning>
struct create_point{
    inline constexpr static auto get(const Point &point, const Range &range, const Turning &...angle){
        static_assert(false, "No 'create_point' calculations have been implemented for these objects.");
    }
};

template<c_create_point_2d OutPoint,
         c_point_2d Point,
         typename Range,
         typename Turning>
struct create_point<OutPoint,
                    direction_angle,
                    Point,
                    Range,
                    Turning>{
    inline constexpr static auto get(const Point &point, const Range &range, const Turning &turning){
        const auto &x = agl::traits::point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::point::access_point<Point, 1>::get(point);
        const auto &r = agl::traits::value<Range>::get(range);
        const auto &t = agl::traits::value<Turning>::get(turning);
        return agl::traits::make<OutPoint>::apply(x + r * std::sin(t), y + r * std::cos(t));
    }
};

template<c_create_point_3d OutPoint,
         c_point_3d Point,
         typename Range,
         typename Turning>
struct create_point<OutPoint,
                    direction_angle,
                    Point,
                    Range,
                    Turning,
                    Turning>{
    inline constexpr static auto get(const Point &point, const Range &range, const Turning &turning1, const Turning &turning2){
        const auto &x = agl::traits::point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::point::access_point<Point, 1>::get(point);
        const auto &z = agl::traits::point::access_point<Point, 2>::get(point);
        const auto &r = agl::traits::value<Range>::get(range);
        const auto &t1 = agl::traits::value<Turning>::get(turning1);
        const auto &t2 = agl::traits::value<Turning>::get(turning2);
        const auto dr = r * std::cos(t2);
        return agl::traits::make<OutPoint>::apply(x + dr * std::sin(t1), y + dr * std::cos(t1), z + dr);
    }
};

// template<typename Point,
//          typename Turning,
//          typename Range,
//          typename NewPoint>
// struct create_point<Point,
//                     Turning,
//                     Range,
//                     NewPoint,
//                     system_coordinat::geographical,
//                     2,
//                     direction_angle>{
//     inline constexpr static auto get(const Point &point, const Turning &turning, const Range &range){
//         // return NewPoint{traits::access_point<Point, 0>::get(point) + range * std::sin(turning),
//         //                 traits::access_point<Point, 1>::get(point) + range * std::cos(turning)};
//     }
// };

// template<typename Point,
//          typename Turning,
//          typename Range,
//          typename NewPoint>
// struct create_point<Point,
//                     Turning,
//                     Range,
//                     NewPoint,
//                     system_coordinat::cartesian,
//                     2,
//                     direction_vector>{
//     inline constexpr static auto get(const Point &point, const Turning &turning, const Range &range){
//         static_assert(false, "Not implemented.");
//     }
// };

// template<typename Point,
//          typename Turning,
//          typename Range,
//          typename NewPoint>
// struct create_point<Point,
//                     Turning,
//                     Range,
//                     NewPoint,
//                     system_coordinat::cartesian,
//                     3,
//                     direction_vector>{
//     inline constexpr static auto get(const Point &point, const Turning &turning, const Range &range){
//         static_assert(false, "Not implemented.");
//     }
// };

}

namespace agl::algorithm::geometry {

template<typename OutPoint,
         typename Point,
         typename Range,
         typename ...Turning>
inline constexpr auto create_point(const Point &point, const Range &range, const Turning &...angle){
    using type_coordinate_system = traits::coordinate_system<Point>::system;
    constexpr auto dimension = traits::dimension<Point>::value();

    static_assert(agl::assert::is_correct<type_coordinate_system>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");

    return dispatch::create_point<OutPoint,
                                  direction_angle,
                                  Point,
                                  Range,
                                  Turning...>::get(point, range, angle...);
}

}

#endif // AGL_ALGORITHM_CREATE_POINT_IMPLEMENTATION_H
