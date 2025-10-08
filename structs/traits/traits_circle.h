#ifndef AGL_STRUCT_CIRCLE_DECART_CIRCLE_TRAITS_H
#define AGL_STRUCT_CIRCLE_DECART_CIRCLE_TRAITS_H

#include "system/traits.h"
#include "structs/geometric/circle.h"

namespace agl::traits {

template<typename PointCenter, typename TypeRadius>
struct tag<agl::circle::circle<PointCenter, TypeRadius>>{
    using type_tag = agl::tag::elements_circle::circle;
};

template<typename PointCenter, typename TypeRadius>
struct group<agl::circle::circle<PointCenter, TypeRadius>>{
    using type_group = agl::group::elements_circles;
};

template<typename PointCenter, typename TypeRadius>
struct coordinate_system<agl::circle::circle<PointCenter, TypeRadius>>{
    using system = coordinate_system<PointCenter>::system;
};

template<typename PointCenter, typename TypeRadius>
struct dimension<agl::circle::circle<PointCenter, TypeRadius>>{
    inline static constexpr std::size_t value(){
        return 2;
    }
};

namespace circle {

template<typename PointCenter, typename TypeRadius>
struct access_types<::agl::circle::circle<PointCenter, TypeRadius>>{
    using center = PointCenter;
    using radius = TypeRadius;
};


template<typename PointCenter, typename TypeRadius>
struct access_center<::agl::circle::circle<PointCenter, TypeRadius>>{
    inline constexpr static auto get(const ::agl::circle::circle<PointCenter, TypeRadius> &circle){
        return circle.center();
    }
};

template<typename PointCenter, typename TypeRadius>
struct access_radius<::agl::circle::circle<PointCenter, TypeRadius>>{
    inline constexpr static auto get(const ::agl::circle::circle<PointCenter, TypeRadius> &circle){
        return ::agl::traits::value<TypeRadius>::get(circle.radius());
    }
};

}

}

#endif // AGL_STRUCT_CIRCLE_DECART_CIRCLE_TRAITS_H
