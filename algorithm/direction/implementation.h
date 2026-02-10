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
                 direction_angle>{
    inline constexpr static auto get(const Point &a, const Point &b){
        const auto[x1, y1] = agl::traits::access_propery<Point>::get(a);
        const auto[x2, y2] = agl::traits::access_propery<Point>::get(b);
        ObjectOut temp(std::atan2(x2 - x1, y2 - y1));
        using Type = agl::traits::type<ObjectOut>::type_value;
        if(temp < ObjectOut{}){
            return temp += agl::algorithm::pi_in_2<Type>;
        }
        return temp;
    }
};

// template<typename Point,
//          typename ObjectOut>
// struct direction<Point,
//                  Point,
//                  ObjectOut,
//                  direction_vector>{
//     inline constexpr static auto get(const Point &a, const Point &b){
//         static_assert(false, "Not implemented.");
//     }
// };

// template<typename Point,
//          typename ObjectOut>
// struct direction<Point,
//                  Point,
//                  ObjectOut,
//                  direction_vector>{
//     inline constexpr static auto get(const Point &a, const Point &b){
//         static_assert(false, "Not implemented.");
//     }
// };

}



namespace agl::algorithm::geometry {

template<typename Object1,
         typename Object2,
         typename ObjectOut>
inline constexpr auto direction(const Object1 &a, const Object2 &b){
    using direction_object = direction_object<ObjectOut>::type_direction_object;

    static_assert(agl::assert::is_correct<direction_object>(), "Error!");

    return dispatch::direction<Object1,
                               Object2,
                               ObjectOut,
                               direction_object>::get(a,b);
}

}


#endif // AGL_ALGORITHM_DIRECTION_IMPLEMENTATION_H
