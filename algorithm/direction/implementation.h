#ifndef AGL_ALGORITHM_DIRECTION_IMPLEMENTATION_H
#define AGL_ALGORITHM_DIRECTION_IMPLEMENTATION_H

#include <cmath>
#include "algorithm/tag_algoritm.h"
#include "algorithm/traits.h"
#include "algorithm/math_algorithm.h"

namespace agl::algorithm::dispatch {

template<typename Object1, typename Object2, typename ObjectOut, typename CoordinateSystem, std::size_t Dimension, typename TypeObjectOut>
struct direction{
    inline constexpr static auto get(const Object1 &a, const Object2 &b){
        static_assert(false, "No 'direction' calculations have been implemented for these objects.");
    }
};

template<typename Point, typename ObjectOut>
struct direction<Point, Point, ObjectOut, cartesian, 2, direction_angle>{
    inline constexpr static auto get(const Point &a, const Point &b){
        ObjectOut temp(std::atan2(traits::traits_point::access_point<Point, 0>::get(b) - traits::traits_point::access_point<Point, 0>::get(a),
                              traits::traits_point::access_point<Point, 1>::get(b) - traits::traits_point::access_point<Point, 1>::get(a)));
        if(temp < ObjectOut{}){
            return temp += algorithm::pi_in_2<typename traits::traits_point::type_property<Point>::type>;
        }
        return temp;
    }
};

template<typename Point, typename ObjectOut>
struct direction<Point, Point, ObjectOut, cartesian, 2, direction_vector>{
    inline constexpr static auto get(const Point &a, const Point &b){
        static_assert(false, "Not implemented.");
    }
};

template<typename Point, typename ObjectOut>
struct direction<Point, Point, ObjectOut, cartesian, 3, direction_vector>{
    inline constexpr static auto get(const Point &a, const Point &b){
        static_assert(false, "Not implemented.");
    }
};

}



namespace agl::algorithm::geometry {

template<typename Object1, typename Object2, typename ObjectOut>
inline constexpr auto direction(const Object1 &a, const Object2 &b){
    using type_coordinate_system1 = traits::coordinate_system<Object1>::system;
    using type_coordinate_system2 = traits::coordinate_system<Object2>::system;
    using direction_object = direction_object<ObjectOut>::type_direction_object;
    constexpr auto dimension1 = traits::dimension<Object1>::value();
    constexpr auto dimension2 = traits::dimension<Object2>::value();

    static_assert(std::is_same_v<type_coordinate_system1, type_coordinate_system2>, "Error!");
    static_assert(!std::is_same_v<direction_object, undefined>, "Error!");
    static_assert((dimension1 == dimension2) && (dimension1 > decltype(dimension1){}), "Error!");

    return dispatch::direction<Object1, Object2, ObjectOut, type_coordinate_system1, dimension1, direction_object>::get(a,b);
}

}


#endif // AGL_ALGORITHM_DIRECTION_IMPLEMENTATION_H
