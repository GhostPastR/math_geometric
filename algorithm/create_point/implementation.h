#ifndef AGL_ALGORITHM_CREATE_POINT_IMPLEMENTATION_H
#define AGL_ALGORITHM_CREATE_POINT_IMPLEMENTATION_H

#include "algorithm/tag_algoritm.h"
#include "system/assert.h"
#include "system/traits.h"
#include <cmath>

namespace agl::algorithm::dispatch {

template<typename Point, typename Turning, typename Range, typename NewPoint, typename CoordinateSystem, std::size_t Dimension, typename TypeObjectDirection>
struct create_point{
    inline constexpr static auto get(const Point &point, const Turning &angle, const Range &range){
        static_assert(false, "No 'create_point' calculations have been implemented for these objects.");
    }
};

template<typename Point, typename Turning, typename Range, typename NewPoint>
struct create_point<Point, Turning, Range, NewPoint, system_coordinat::cartesian, 2, direction_angle>{
    inline constexpr static auto get(const Point &point, const Turning &turning, const Range &range){
        return NewPoint{traits::traits_point::access_point<Point, 0>::get(point)
                            + traits::value<Range>::get(range)
                                  * std::sin(traits::value<Turning>::get(turning)),
                        traits::traits_point::access_point<Point, 1>::get(point)
                            + traits::value<Range>::get(range)
                                  * std::cos(traits::value<Turning>::get(turning))};
    }
};

template<typename Point, typename Turning, typename Range, typename NewPoint>
struct create_point<Point, Turning, Range, NewPoint, system_coordinat::geographical, 2, direction_angle>{
    inline constexpr static auto get(const Point &point, const Turning &turning, const Range &range){
        // return NewPoint{traits::access_point<Point, 0>::get(point) + range * std::sin(turning),
        //                 traits::access_point<Point, 1>::get(point) + range * std::cos(turning)};
    }
};

template<typename Point, typename Turning, typename Range, typename NewPoint>
struct create_point<Point, Turning, Range, NewPoint, system_coordinat::cartesian, 2, direction_vector>{
    inline constexpr static auto get(const Point &point, const Turning &turning, const Range &range){
        static_assert(false, "Not implemented.");
    }
};

template<typename Point, typename Turning, typename Range, typename NewPoint>
struct create_point<Point, Turning, Range, NewPoint, system_coordinat::cartesian, 3, direction_vector>{
    inline constexpr static auto get(const Point &point, const Turning &turning, const Range &range){
        static_assert(false, "Not implemented.");
    }
};


}


namespace agl::algorithm::geometry {

template<typename Point, typename Turning, typename Range, typename NewPoint>
inline constexpr auto create_point(const Point &point, const Turning &angle, const Range &range){
    using type_coordinate_system = traits::coordinate_system<Point>::system;
    using direction_object = direction_object<Turning>::type_direction_object;
    constexpr auto dimension = traits::dimension<Point>::value();

    static_assert(agl::assert::is_correct<type_coordinate_system>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");

    return dispatch::create_point<Point, Turning, Range, NewPoint,
                                  type_coordinate_system, dimension, direction_object>::get(point, angle, range);
}

}

#endif // AGL_ALGORITHM_CREATE_POINT_IMPLEMENTATION_H
