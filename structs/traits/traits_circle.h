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
struct make<agl::circle::circle<PointCenter, TypeRadius>>{
    template<typename Point, typename Radius>
    inline constexpr static auto apply(const Point &point, const Radius &radius){
        auto center = agl::traits::make<PointCenter>::apply(agl::traits::point::access_point<Point, 0>::get(point),
                                                            agl::traits::point::access_point<Point, 1>::get(point));
        return agl::circle::circle<PointCenter, TypeRadius>(std::move(center),
                                                            agl::traits::make<TypeRadius>::apply(radius));
    }

    inline constexpr static auto apply(const PointCenter &point, const TypeRadius &radius){
        return agl::circle::circle<PointCenter, TypeRadius>(point, radius);
    }
};

template<typename PointCenter, typename TypeRadius>
struct access_propery<agl::circle::circle<PointCenter, TypeRadius>>{
    inline constexpr static auto get(const agl::circle::circle<PointCenter, TypeRadius> &circle){
        return std::make_tuple(
            circle.center(),
            agl::traits::value<TypeRadius>::get(circle.radius())
        );
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
