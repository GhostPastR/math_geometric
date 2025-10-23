#ifndef AGL_STRUCT_CIRCLE_DECART_CIRCLE_TRAITS_H
#define AGL_STRUCT_CIRCLE_DECART_CIRCLE_TRAITS_H

#include "system/traits.h"
#include "structs/geometric/circle.h"

namespace agl::traits {

// template<typename PointCenter, typename TypeRadius>
// struct tag<agl::circle::circle<PointCenter, TypeRadius>>{
//     using type_tag = agl::tag::elements_circle::circle;
// };

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

template<typename PointCenter, typename TypeRadius>
struct access_create<agl::circle::circle<PointCenter, TypeRadius>>{
    template<typename Point, typename Radius>
    inline constexpr static auto get(Point &&point, Radius &&radius){
        using rm_point = std::remove_cvref_t<Point>;
        auto center = agl::traits::access_create<PointCenter>::get(agl::traits::point::access_point<rm_point, 0>::get(std::forward<Point>(point)),
                                                                   agl::traits::point::access_point<rm_point, 1>::get(std::forward<Point>(point)));
        return agl::circle::circle<PointCenter, TypeRadius>(std::move(center),
                                                            agl::traits::access_create<TypeRadius>::get(radius));
    }

    inline constexpr static auto get(const PointCenter &point, const TypeRadius &radius){
        return agl::circle::circle<PointCenter, TypeRadius>(std::forward<PointCenter>(point), std::forward<TypeRadius>(radius));
    }
};

namespace circle {

template<typename PointCenter, typename TypeRadius>
struct access_types<agl::circle::circle<PointCenter, TypeRadius>>{
    using center = PointCenter;
    using radius = TypeRadius;
};


template<typename PointCenter, typename TypeRadius>
struct access_center<::agl::circle::circle<PointCenter, TypeRadius>>{
    inline constexpr static auto get(const agl::circle::circle<PointCenter, TypeRadius> &circle){
        return circle.center();
    }
};

template<typename PointCenter, typename TypeRadius>
struct access_radius<agl::circle::circle<PointCenter, TypeRadius>>{
    inline constexpr static auto get(const agl::circle::circle<PointCenter, TypeRadius> &circle){
        return agl::traits::value<TypeRadius>::get(circle.radius());
    }
};

}

}

#endif // AGL_STRUCT_CIRCLE_DECART_CIRCLE_TRAITS_H
