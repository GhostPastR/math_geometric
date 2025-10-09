#ifndef AGL_ALGORITHM_DIRECTION_IMPLEMENTATION_H
#define AGL_ALGORITHM_DIRECTION_IMPLEMENTATION_H

#include <cmath>
#include "algorithm/tag_algoritm.h"
#include "system/assert.h"
#include "system/system_concept.h"
#include "system/traits.h"
#include "algorithm/math_algorithm.h"

namespace agl::algorithm::dispatch {

template<typename Object1,
         typename Object2,
         typename ObjectOut,
         typename CoordinateSystem,
         std::size_t Dimension,
         typename TypeObjectOut>
struct direction{
    inline constexpr static auto get(const Object1 &a, const Object2 &b){
        static_assert(false, "No 'direction' calculations have been implemented for these objects.");
    }
};

template<c_point_2d Point,
         typename ObjectOut>
struct direction<Point,
                 Point,
                 ObjectOut,
                 system_coordinat::cartesian,
                 2,
                 direction_angle>{
    inline constexpr static auto get(const Point &a, const Point &b){
        ObjectOut temp(std::atan2(traits::point::access_point<Point, 0>::get(b) - traits::point::access_point<Point, 0>::get(a),
                              traits::point::access_point<Point, 1>::get(b) - traits::point::access_point<Point, 1>::get(a)));
        using Type = agl::traits::type<ObjectOut>::type_value;
        if(temp < ObjectOut{}){
            return temp += agl::algorithm::pi_in_2<Type>;
        }
        return temp;
    }
};

template<typename Point,
         typename ObjectOut>
struct direction<Point,
                 Point,
                 ObjectOut,
                 system_coordinat::cartesian,
                 2,
                 direction_vector>{
    inline constexpr static auto get(const Point &a, const Point &b){
        static_assert(false, "Not implemented.");
    }
};

template<typename Point,
         typename ObjectOut>
struct direction<Point,
                 Point,
                 ObjectOut,
                 system_coordinat::cartesian,
                 3,
                 direction_vector>{
    inline constexpr static auto get(const Point &a, const Point &b){
        static_assert(false, "Not implemented.");
    }
};

}



namespace agl::algorithm::geometry {

template<typename Object1,
         typename Object2,
         typename ObjectOut>
inline constexpr auto direction(const Object1 &a, const Object2 &b){
    using type_cs1 = traits::coordinate_system<Object1>::system;
    using type_cs2 = traits::coordinate_system<Object2>::system;
    using direction_object = direction_object<ObjectOut>::type_direction_object;
    constexpr auto dimension1 = traits::dimension<Object1>::value();
    constexpr auto dimension2 = traits::dimension<Object2>::value();

    static_assert(agl::assert::is_correct<direction_object>(), "Error!");
    static_assert(agl::assert::is_correct_compare<type_cs1, type_cs2>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension1, dimension2), "Error!");

    return dispatch::direction<Object1, Object2, ObjectOut, type_cs1, dimension1, direction_object>::get(a,b);
}

}


#endif // AGL_ALGORITHM_DIRECTION_IMPLEMENTATION_H
