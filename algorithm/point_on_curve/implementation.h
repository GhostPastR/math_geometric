#ifndef AGL_ALGORITHM_POINT_ON_CURVE_IMPLEMENTATION_H
#define AGL_ALGORITHM_POINT_ON_CURVE_IMPLEMENTATION_H

#include "algorithm/create_point/interface.h"
#include "algorithm/distance/interface.h"
#include "algorithm/direction/interface.h"
#include "algorithm/rotate/interface.h"
#include "system/traits.h"
#include <cmath>

namespace agl::algorithm::dispatch {

template<typename Figure,
         typename TypeDistance,
         typename Point,
         typename CoordinateSystem,
         std::size_t Dimension>
struct point_on_curve{
    inline constexpr static auto get(const Figure &figure, const TypeDistance &distance){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<c_half_line_2d Figure,
         typename TypeDistance,
         typename Point>
struct point_on_curve<Figure,
                      TypeDistance,
                      Point,
                      system_coordinat::cartesian,
                      2>{
    inline constexpr static auto get(const Figure &figure, const TypeDistance &distance){
        using PointStart = traits::half_line::access_types<Figure>::start;
        using Direction = traits::half_line::access_types<Figure>::direction;
        const auto &start = traits::half_line::access_start<Figure>::get(figure);
        const auto &angle = traits::half_line::access_direction<Figure>::get(figure);
        return agl::algorithm::create_point<PointStart>(start, traits::value<TypeDistance>::get(distance), angle);
    }
};

template<c_line_section Figure,
         typename TypeDistance,
         typename Point>
struct point_on_curve<Figure,
                      TypeDistance,
                      Point,
                      system_coordinat::cartesian,
                      2>{
    inline constexpr static auto get(const Figure &figure, const TypeDistance &distance) -> std::optional<Point>{
        using Property = traits::line_section::access_types<Figure>;
        using PointLine = traits::line_section::access_types<Figure>::point;
        const auto &t_distance = traits::value<TypeDistance>::get(distance);
        if(t_distance > agl::algorithm::distance(figure)){
            return std::nullopt;
        }
        const auto &start = traits::line_section::access_start<Figure>::get(figure);
        const auto &stop = traits::line_section::access_stop<Figure>::get(figure);
        using Angle = traits::point::access_types<typename Property::point>::point;
        return agl::algorithm::create_point<PointLine>(start, t_distance, agl::algorithm::direction<Angle>(start, stop));
    }
};

template<c_arc Figure,
         typename TypeDistance,
         typename Point>
struct point_on_curve<Figure,
                      TypeDistance,
                      Point,
                      system_coordinat::cartesian,
                      2>{
    inline constexpr static auto get(const Figure &figure, const TypeDistance &distance) -> std::optional<Point>{
        const auto &t_distance = traits::value<TypeDistance>::get(distance);
        if(t_distance > agl::algorithm::distance(figure)){
            return std::nullopt;
        }
        using Center = traits::arc::access_types<Figure>::center;
        const auto center = traits::arc::access_center<Figure>::get(figure);
        const auto &angle = traits::arc::access_angle<Figure, 0>::get(figure);
        const auto &radius = traits::arc::access_radius<Figure>::get(figure);
        const auto point = agl::algorithm::create_point<Center>(center, radius, angle);
        return agl::algorithm::rotate(point, t_distance / radius, center);
    }
};

}





namespace agl::algorithm::geometry {

template<typename Figure,
         typename TypeDistance,
         typename Point>
inline constexpr auto point_on_curve(const Figure &figure, const TypeDistance &distance){
    using type_coordinate_system = traits::coordinate_system<Point>::system;
    constexpr auto dimension = traits::dimension<Point>::value();

    static_assert(agl::assert::is_correct<type_coordinate_system>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");

    return dispatch::point_on_curve<Figure,
                                    TypeDistance,
                                    Point,
                                    type_coordinate_system,
                                    dimension>::get(figure, distance);
}

}


#endif // AGL_ALGORITHM_POINT_ON_CURVE_IMPLEMENTATION_H
