#ifndef AGL_STRUCT_CIRCLE_DECART_ARC_TRAITS_H
#define AGL_STRUCT_CIRCLE_DECART_ARC_TRAITS_H

#include "system/traits.h"
#include "structs/geometric/arc.h"

namespace agl::traits {

template<typename PointCenter, typename TypeRadius, typename Angle>
struct tag<::agl::circle::arc<PointCenter, TypeRadius, Angle>>{
    using type_tag = agl::tag::elements_circle::arc;
};

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

}

}

#endif // AGL_STRUCT_CIRCLE_DECART_ARC_TRAITS_H
