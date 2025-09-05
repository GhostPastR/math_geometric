#ifndef AGL_ALGORITHM_DISTANCE_D2_H
#define AGL_ALGORITHM_DISTANCE_D2_H

#include "algorithm/belongs_to_area_of_line/interface.h"
#include "algorithm/equation_of_line/interface.h"
#include "algorithm/distance/implementation_cartesian.h"


#include "system/traits.h"
#include <cmath>

namespace agl::algorithm::dispatch::d2::point_to_object {

namespace dispatch {

template<typename Object1, typename Object2, typename Tag, typename CoordinateSystem, std::size_t Dimension>
struct distance{
    inline constexpr static auto get(const Object1 &point, const Object2 &object){
        static_assert(false, "No 'distance' calculations have been implemented for these points.");
    }
};

template<typename Object1, typename Object2>
struct distance<Object1, Object2, agl::tag::tag_straight_line, agl::system_coordinat::cartesian, 2>{
    inline constexpr static auto get(const Object1 &point, const Object2 &object){
        const auto [a,b,c] = agl::algorithm::equation_of_line(object);
        const auto x = agl::traits::traits_point::access_point<Object1, 0>::get(point);
        const auto y = agl::traits::traits_point::access_point<Object1, 1>::get(point);
        return std::abs(algorithm::determine(a, -b, y, x) + c) / sqrt(algorithm::determine(a, -b, b, a));
    }
};

template<typename Object1, typename Object2>
struct distance<Object1, Object2, agl::tag::tag_half_line, agl::system_coordinat::cartesian, 2>{
    inline constexpr static auto get(const Object1 &point, const Object2 &object){
        const auto [a1,b1,c1] = agl::algorithm::equation_of_line(object);
        const auto x = agl::traits::traits_point::access_point<Object1, 0>::get(point);
        const auto y = agl::traits::traits_point::access_point<Object1, 1>::get(point);
        const auto dist = std::abs(algorithm::determine(a1, -b1, y, x) + c1) / sqrt(algorithm::determine(a1, -b1, b1, a1));
        const auto a2 = -b1;
        const auto b2 = a1;
        const auto c2 = algorithm::determine(b1, a1, x, y);

        if(const auto d = algorithm::determine(a1, a2, b1, b2); !algorithm::compare(d, decltype(d){})){
            auto temp = Object1{algorithm::determine(b1, b2, c1, c2) / d,
                                  algorithm::determine(c1, c2, a1, a2) / d};
            if(!agl::algorithm::belongs_to_area_of_line(object, temp)){
                const auto start = agl::traits::traits_half_line::access_start<Object2>::get(object);
                return agl::algorithm::dispatch::d2::distance_point_algo::distance<Object1, agl::system_coordinat::cartesian, 2>(start, point);
            }
        }
        return dist;
    }
};

template<typename Object1, typename Object2>
struct distance<Object1, Object2, agl::tag::tag_line_section, agl::system_coordinat::cartesian, 2>{
    inline constexpr static auto get(const Object1 &point, const Object2 &object){
        const auto [a1,b1,c1] = agl::algorithm::equation_of_line(object);
        const auto x = agl::traits::traits_point::access_point<Object1, 0>::get(point);
        const auto y = agl::traits::traits_point::access_point<Object1, 1>::get(point);
        const auto dist = std::abs(algorithm::determine(a1, -b1, y, x) + c1) / sqrt(algorithm::determine(a1, -b1, b1, a1));
        const auto a2 = -b1;
        const auto b2 = a1;
        const auto c2 = algorithm::determine(b1, a1, x, y);

        if(const auto d = algorithm::determine(a1, a2, b1, b2); !algorithm::compare(d, decltype(d){})){
            auto temp = Object1{algorithm::determine(b1, b2, c1, c2) / d,
                                algorithm::determine(c1, c2, a1, a2) / d};
            if(!agl::algorithm::belongs_to_area_of_line(object, temp)){
                const auto start = agl::traits::traits_line_section::access_start<Object2>::get(object);
                const auto stop = agl::traits::traits_line_section::access_start<Object2>::get(object);
                return std::min(agl::algorithm::dispatch::d2::distance_point_algo::distance<Object1, agl::system_coordinat::cartesian, 2>(start, point),
                                agl::algorithm::dispatch::d2::distance_point_algo::distance<Object1, agl::system_coordinat::cartesian, 2>(stop, point));
            }
        }
        return dist;
    }
};

}

template<typename Object1, typename Object2, typename Tag, typename CoordinateSystem, std::size_t Dimension>
inline constexpr auto distance(const Object1 &point, const Object2 &object){
    return agl::algorithm::dispatch::d2::point_to_object::dispatch::distance<
        Object1, Object2, Tag, CoordinateSystem, Dimension>::get(point, object);
}

}

#endif // AGL_ALGORITHM_DISTANCE_D2_H
