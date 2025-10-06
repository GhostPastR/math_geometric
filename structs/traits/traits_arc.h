#ifndef AGL_STRUCT_CIRCLE_DECART_ARC_TRAITS_H
#define AGL_STRUCT_CIRCLE_DECART_ARC_TRAITS_H

#include "system/traits.h"
#include "structs/geometric/arc.h"

namespace agl::traits {

template<typename PointCenter, typename TypeRadius, typename Angle>
struct tag<circle::arc<PointCenter, TypeRadius, Angle>>{
    using type_tag = agl::tag::elements_circle::arc;
};

template<typename PointCenter, typename TypeRadius, typename Angle>
struct group<circle::arc<PointCenter, TypeRadius, Angle>>{
    using type_group = agl::group::elements_circles;
};


template<typename PointCenter, typename TypeRadius, typename Angle>
struct coordinate_system<circle::arc<PointCenter, TypeRadius, Angle>>{
    using system = coordinate_system<PointCenter>::system;
};

template<typename PointCenter, typename TypeRadius, typename Angle>
struct dimension<circle::arc<PointCenter, TypeRadius, Angle>>{
    inline static constexpr std::size_t value(){
        return 2;
    }
};

namespace traits_arc {

template<typename PointCenter, typename TypeRadius, typename Angle>
struct type_property<circle::arc<PointCenter, TypeRadius, Angle>>{
    using type_center = PointCenter;
    using type_radius = TypeRadius;
    using type_angle = Angle;
};

template<typename PointCenter, typename TypeRadius, typename Angle>
struct access_center<circle::arc<PointCenter, TypeRadius, Angle>>{
    inline constexpr static auto get(const circle::arc<PointCenter, TypeRadius, Angle> &arc){
        return arc.center();
    }
};


template<typename PointCenter, typename TypeRadius, typename Angle>
struct access_radius<circle::arc<PointCenter, TypeRadius, Angle>>{
    inline constexpr static auto get(const circle::arc<PointCenter, TypeRadius, Angle> &arc){
        return agl::traits::value<TypeRadius>::get(arc.radius());
    }
};

template<typename PointCenter, typename TypeRadius, typename Angle>
struct access_angle<circle::arc<PointCenter, TypeRadius, Angle>, 0>{
    inline constexpr static auto get(const circle::arc<PointCenter, TypeRadius, Angle> &arc){
        return agl::traits::value<Angle>::get(arc.start());
    }
};

template<typename PointCenter, typename TypeRadius, typename Angle>
struct access_angle<circle::arc<PointCenter, TypeRadius, Angle>, 1>{
    inline constexpr static auto get(const circle::arc<PointCenter, TypeRadius, Angle> &arc){
        return agl::traits::value<Angle>::get(arc.stop());
    }
};

}

}

#endif // AGL_STRUCT_CIRCLE_DECART_ARC_TRAITS_H
