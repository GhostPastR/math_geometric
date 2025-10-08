#ifndef AGL_ALGORITHM_DISTANCE_IMPLEMENTATION_ARC_CARTESIAN_H
#define AGL_ALGORITHM_DISTANCE_IMPLEMENTATION_ARC_CARTESIAN_H

#include "algorithm/math_algorithm.h"
#include "system/traits.h"
#include <cmath>

namespace agl::algorithm::dispatch::d1::distance_arc_algo {

template<typename Figure, typename Tag, typename CoordinateSystem, std::size_t Dimension>
struct distance{
    inline constexpr static auto get(const Figure &figure){
        static_assert(false, "No 'distance' calculations have been implemented for these points.");
    }
};

template<typename Figure>
struct distance<Figure, agl::tag::elements_circle::arc, system_coordinat::cartesian, 2>{
    inline constexpr static auto get(const Figure &figure){
        using Point = traits::arc::access_types<Figure>::center;
        using Angle = traits::arc::access_types<Figure>::angle;
        using Type = agl::traits::type<Angle>::type_value;

        const auto &start = traits::arc::access_angle<Figure, 0>::get(figure);
        const auto &stop = traits::arc::access_angle<Figure, 1>::get(figure);
        const auto &radius = traits::arc::access_radius<Figure>::get(figure);

        if(algorithm::compare(start, stop)){
            return 0.;
        }
        auto a = stop - start;
        if(start > stop){
            a += algorithm::pi_in_2<Type>;
        }
        return a * radius;
    }
};


}

#endif // AGL_ALGORITHM_DISTANCE_IMPLEMENTATION_CARTESIAN_H
