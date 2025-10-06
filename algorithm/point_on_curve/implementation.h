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
         typename Tag,
         typename CoordinateSystem,
         std::size_t Dimension>
struct point_on_curve{
    inline constexpr static auto get(const Figure &figure, const TypeDistance &distance){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<typename Figure,
         typename TypeDistance,
         typename Point>
struct point_on_curve<Figure,
                      TypeDistance,
                      Point,
                      agl::tag::line::half_line,
                      system_coordinat::cartesian,
                      2>{
    inline constexpr static auto get(const Figure &figure, const TypeDistance &distance){
        using PointStart = traits::traits_half_line::type_property<Figure>::type_start;
        using Direction = traits::traits_half_line::type_property<Figure>::type_direction;
        const auto &start = traits::traits_half_line::access_start<Figure>::get(figure);
        const auto &angle = traits::traits_half_line::access_direction<Figure>::get(figure);
        return agl::algorithm::create_point<PointStart>(start, angle, traits::value<TypeDistance>::get(distance));
    }
};

template<typename Figure,
         typename TypeDistance,
         typename Point>
struct point_on_curve<Figure,
                      TypeDistance,
                      Point,
                      agl::tag::line::line_section,
                      system_coordinat::cartesian,
                      2>{
    inline constexpr static auto get(const Figure &figure, const TypeDistance &distance) -> std::optional<Point>{
        using Property = traits::traits_line_section::type_property<Figure>;
        const auto &t_distance = traits::value<TypeDistance>::get(distance);
        if(t_distance > agl::algorithm::distance(figure)){
            return std::nullopt;
        }
        const auto &start = traits::traits_line_section::access_start<Figure>::get(figure);
        const auto &stop = traits::traits_line_section::access_stop<Figure>::get(figure);
        using Angle = traits::traits_point::type_property<typename Property::type_point>::type_point;
        return agl::algorithm::create_point(start, agl::algorithm::direction<Angle>(start, stop), t_distance);
    }
};

template<typename Figure,
         typename TypeDistance,
         typename Point>
struct point_on_curve<Figure,
                      TypeDistance,
                      Point,
                      agl::tag::elements_circle::arc,
                      system_coordinat::cartesian,
                      2>{
    inline constexpr static auto get(const Figure &figure, const TypeDistance &distance) -> std::optional<Point>{
        const auto &t_distance = traits::value<TypeDistance>::get(distance);
        if(t_distance > agl::algorithm::distance(figure)){
            return std::nullopt;
        }

        const auto center = traits::traits_arc::access_center<Figure>::get(figure);
        const auto &angle = traits::traits_arc::access_angle<Figure, 0>::get(figure);
        const auto &radius = traits::traits_arc::access_radius<Figure>::get(figure);
        const auto point = agl::algorithm::create_point(center, angle, radius);
        return agl::algorithm::rotate(point, t_distance / radius, center);
    }
};

}





namespace agl::algorithm::geometry {

template<typename Figure,
         typename TypeDistance,
         typename Point>
inline constexpr auto point_on_curve(const Figure &figure, const TypeDistance &distance){
    using tag_object = traits::tag<Figure>::type_tag;
    using type_coordinate_system = traits::coordinate_system<Point>::system;
    constexpr auto dimension = traits::dimension<Point>::value();

    static_assert(agl::assert::is_correct<tag_object>(), "Error!");
    static_assert(agl::assert::is_correct<type_coordinate_system>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");

    return dispatch::point_on_curve<Figure,
                                    TypeDistance,
                                    Point,
                                    tag_object,
                                    type_coordinate_system,
                                    dimension>::get(figure, distance);
}

}


#endif // AGL_ALGORITHM_POINT_ON_CURVE_IMPLEMENTATION_H
