#ifndef AGL_STRUCT_CIRCLE_DECART_ARC_TRAITS_H
#define AGL_STRUCT_CIRCLE_DECART_ARC_TRAITS_H

#include "system/traits.h"
#include "structs/geometric/arc.h"

namespace agl::traits {

template<typename PointCenter, typename TypeRadius, typename Angle>
struct coordinate_system<::agl::circle::arc<PointCenter, TypeRadius, Angle>>{
    using system = coordinate_system<PointCenter>::system;
};

template<typename PointCenter, typename TypeRadius, typename Angle>
struct dimension<::agl::circle::arc<PointCenter, TypeRadius, Angle>>{
    inline static constexpr std::size_t value(){
        return 2;
    }
};

template<typename PointCenter, typename TypeRadius, typename Angle>
struct make<::agl::circle::arc<PointCenter, TypeRadius, Angle>>{
    template<typename Point, typename Radius, typename AngleArc>
    inline constexpr static auto apply(const Point &center, const Radius &radius, const AngleArc &start, const AngleArc &stop){
        auto new_center = agl::traits::make<PointCenter>::apply(agl::traits::point::access_point<Point, 0>::get(center),
                                                                agl::traits::point::access_point<Point, 1>::get(center));
        return ::agl::circle::arc<PointCenter, TypeRadius, Angle>(std::move(new_center),
                                                                  agl::traits::make<TypeRadius>::apply(radius),
                                                                  agl::traits::make<Angle>::apply(start),
                                                                  agl::traits::make<Angle>::apply(stop));
    }

    inline constexpr static auto apply(const PointCenter &center, const TypeRadius &radius, const Angle &start, const Angle &stop){
        return ::agl::circle::arc<PointCenter, TypeRadius, Angle>(center, radius, start, stop);
    }
};

template<typename PointCenter, typename TypeRadius, typename Angle>
struct access_propery<agl::circle::arc<PointCenter, TypeRadius, Angle>>{
    inline constexpr static auto get(const agl::circle::arc<PointCenter, TypeRadius, Angle> &arc){
        return std::make_tuple(
            arc.center(),
            agl::traits::value<TypeRadius>::get(arc.radius()),
            agl::traits::value<Angle>::get(arc.start()),
            agl::traits::value<Angle>::get(arc.stop())
        );
    }
};



namespace arc {

template<typename PointCenter, typename TypeRadius, typename Angle>
struct access_types<::agl::circle::arc<PointCenter, TypeRadius, Angle>>{
    using center = PointCenter;
    using radius = TypeRadius;
    using angle = Angle;
};

template<typename PointCenter, typename TypeRadius, typename Angle>
struct access_center<::agl::circle::arc<PointCenter, TypeRadius, Angle>>{
    inline constexpr static auto get(const ::agl::circle::arc<PointCenter, TypeRadius, Angle> &arc){
        return arc.center();
    }
};


template<typename PointCenter, typename TypeRadius, typename Angle>
struct access_radius<::agl::circle::arc<PointCenter, TypeRadius, Angle>>{
    inline constexpr static auto get(const ::agl::circle::arc<PointCenter, TypeRadius, Angle> &arc){
        return agl::traits::value<TypeRadius>::get(arc.radius());
    }
};

template<typename PointCenter, typename TypeRadius, typename Angle>
struct access_angle<::agl::circle::arc<PointCenter, TypeRadius, Angle>, 0>{
    inline constexpr static auto get(const ::agl::circle::arc<PointCenter, TypeRadius, Angle> &arc){
        return agl::traits::value<Angle>::get(arc.start());
    }
};

template<typename PointCenter, typename TypeRadius, typename Angle>
struct access_angle<::agl::circle::arc<PointCenter, TypeRadius, Angle>, 1>{
    inline constexpr static auto get(const ::agl::circle::arc<PointCenter, TypeRadius, Angle> &arc){
        return agl::traits::value<Angle>::get(arc.stop());
    }
};

template<typename PointCenter, typename TypeRadius, typename Angle>
struct access_change<::agl::circle::arc<PointCenter, TypeRadius, Angle>>{
    inline constexpr static auto get(const ::agl::circle::arc<PointCenter, TypeRadius, Angle> &arc){
        return agl::circle::arc<PointCenter, TypeRadius, Angle>(arc.center(), arc.radius(), arc.stop(), arc.start());
    }
};

}

}

#endif // AGL_STRUCT_CIRCLE_DECART_ARC_TRAITS_H
