#ifndef AGL_ALGORITHM_CREATE_CIRCLE_IMPLEMENTATION_H
#define AGL_ALGORITHM_CREATE_CIRCLE_IMPLEMENTATION_H

#include <cmath>
#include <optional>
#include "system/system_concept.h"
#include "system/traits.h"
#include "system/assert.h"
#include "algorithm/math_algorithm.h"
#include "algorithm/tag_algoritm.h"
#include "algorithm/create_point/interface.h"


namespace agl::algorithm::dispatch {

template<typename CircleOut,
         typename Strategy,
         typename CoordinateSystem,
         std::size_t Dimension,
         typename ...Args>
struct create_circle{
    inline constexpr static auto get(Args&& ...args){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<c_create_circle CircleOut,
         typename Angle,
         c_point_2d Point,
         typename Radius>
struct create_circle<CircleOut,
                     agl::algorithm::strategy::create_circle_angle_point,
                     agl::system_coordinat::cartesian,
                     2,
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

}

// create_circle




namespace agl::algorithm::geometry {

template<typename CircleOut,
         typename Strategy,
         typename ...Args>
inline constexpr auto create_circle(Args ...args){
    using type_cs = traits::coordinate_system<CircleOut>::system;
    constexpr auto dimension = traits::dimension<CircleOut>::value();
    static_assert(agl::assert::is_correct<type_cs>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");
    return dispatch::create_circle<CircleOut,
                                   Strategy,
                                   type_cs,
                                   dimension,
                                   Args...>::get(std::forward<Args>(args)...);
}

}


#endif // AGL_ALGORITHM_CREATE_CIRCLE_IMPLEMENTATION_H
