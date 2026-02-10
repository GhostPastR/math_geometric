#ifndef AGL_ALGORITHM_CREATE_CIRCLE_IMPLEMENTATION_H
#define AGL_ALGORITHM_CREATE_CIRCLE_IMPLEMENTATION_H

#include <cmath>
#include <optional>
#include "system/system_concept.h"
#include "system/traits.h"
#include "algorithm/math_algorithm.h"
#include "algorithm/tag_algoritm.h"
#include "algorithm/create_point/interface.h"


namespace agl::algorithm::dispatch {

template<typename CircleOut,
         typename Strategy,
         typename ...Args>
struct create_circle{
    inline constexpr static auto get(Args&& ...args){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<c_create_circle CircleOut,
         c_unit Angle,
         c_point_2d Point,
         c_unit Radius>
    requires c_cartesian<CircleOut> && c_cartesian<Point> && c_demension_2<CircleOut>
struct create_circle<CircleOut,
                     agl::algorithm::strategy::create_circle_angle_point,
                     Angle,
                     Point,
                     Radius>{
    inline constexpr static auto get(const Angle &angle, const Point &point, const Radius &radius)
        -> std::pair<std::optional<CircleOut>, std::optional<CircleOut>>{
        using Type = agl::traits::type<Angle>::type_value;
        using Center = agl::traits::circle::access_types<CircleOut>::center;
        using make = agl::traits::make<CircleOut>;
        const auto &_angle = agl::traits::value<Angle>::get(angle);
        const auto &_radius = agl::traits::value<Radius>::get(radius);
        if(_radius > 0){
            return std::pair<CircleOut, CircleOut>{
                make::apply(agl::algorithm::create_point<Center>(point, _radius, angle - algorithm::pi_on_2<Type>), _radius),
                make::apply(agl::algorithm::create_point<Center>(point, _radius, angle + algorithm::pi_on_2<Type>), _radius)
            };
        }
        return {};
    }
};


//Построение окружности по 3-м точкам

}

#endif // AGL_ALGORITHM_CREATE_CIRCLE_IMPLEMENTATION_H
