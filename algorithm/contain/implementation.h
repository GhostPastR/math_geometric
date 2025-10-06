#ifndef AGL_ALGORITHM_CONTAIN_IMPLEMENTATION_H
#define AGL_ALGORITHM_CONTAIN_IMPLEMENTATION_H

#include "algorithm/math_algorithm.h"
#include "algorithm/equation_of_line/interface.h"
#include "algorithm/belongs_to_area_of_line/interface.h"
#include "system/traits.h"
#include <cmath>

namespace agl::algorithm::dispatch {

template<typename Object1,
         typename Object2,
         typename Tag1,
         typename Tag2,
         typename CoordinateSystem,
         std::size_t Dimension>
struct contain{
    inline constexpr static auto get(const Object1 &object1, const Object2 &object2){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<typename Object1,
         typename Object2>
struct contain<Object1,
               Object2,
               agl::tag::line::straight_line,
               agl::tag::point::point,
               agl::system_coordinat::cartesian,
               2>{
    inline constexpr static auto get(const Object1 &object1, const Object2 &object2){
        using namespace agl::traits::traits_straight_line;
        using Type = type_property<Object1>::type_parameter;
        const auto &a = access_parameter<Object1, 0>::get(object1);
        const auto &b = access_parameter<Object1, 1>::get(object1);
        const auto &c = access_parameter<Object1, 2>::get(object1);
        const auto &x = agl::traits::traits_point::access_point<Object2, 0>::get(object2);
        const auto &y = agl::traits::traits_point::access_point<Object2, 1>::get(object2);
        return algorithm::compare(algorithm::determine(a, -b, y, x) + c, 0.);
    }
};

template<typename Object1,
         typename Object2>
struct contain<Object1,
               Object2,
               agl::tag::line::half_line,
               agl::tag::point::point,
               agl::system_coordinat::cartesian,
               2>{
    inline constexpr static auto get(const Object1 &object1, const Object2 &object2){
        const auto [a,b,c] = agl::algorithm::equation_of_line(object1);
        const auto &x = agl::traits::traits_point::access_point<Object2, 0>::get(object2);
        const auto &y = agl::traits::traits_point::access_point<Object2, 1>::get(object2);
        if(algorithm::compare(algorithm::determine(a, -b, y, x) + c, 0.)){
            return agl::algorithm::belongs_to_area_of_line(object1, object2);
        }
        return false;
    }
};

template<typename Object1,
         typename Object2>
struct contain<Object1,
               Object2,
               agl::tag::line::line_section,
               agl::tag::point::point,
               agl::system_coordinat::cartesian,
               2>{
    inline constexpr static auto get(const Object1 &object1, const Object2 &object2){
        return contain<Object1,
                       Object2,
                       agl::tag::line::half_line,
                       agl::tag::point::point,
                       agl::system_coordinat::cartesian,
                       2>::get(object1, object2);
    }
};

}


namespace agl::algorithm::geometry {

template<typename Object1,
         typename Object2>
inline constexpr auto contain(const Object1 &object1, const Object2 &object2){
    using type_cs1 = traits::coordinate_system<Object1>::system;
    using type_cs2 = traits::coordinate_system<Object2>::system;
    using tag1 = traits::tag<Object1>::type_tag;
    using tag2 = traits::tag<Object2>::type_tag;
    constexpr auto dimension1 = traits::dimension<Object1>::value();
    constexpr auto dimension2 = traits::dimension<Object2>::value();

    static_assert(agl::assert::is_correct<tag1>(), "Error!");
    static_assert(agl::assert::is_correct<tag2>(), "Error!");
    static_assert(agl::assert::is_correct_compare<type_cs1, type_cs2>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension1, dimension2), "Error!");

    return dispatch::contain<Object1,
                             Object2,
                             tag1,
                             tag2,
                             type_cs1,
                             dimension1>::get(object1, object2);
}

}


#endif // AGL_ALGORITHM_<>_IMPLEMENTATION_H
