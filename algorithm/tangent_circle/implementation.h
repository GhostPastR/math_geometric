#ifndef AGL_ALGORITHM_TANGENT_CIRCLE_IMPLEMENTATION_H
#define AGL_ALGORITHM_TANGENT_CIRCLE_IMPLEMENTATION_H

#include <cmath>
#include "system/traits.h"
#include "system/assert.h"
#include "algorithm/tag_algoritm.h"
#include "algorithm/distance/interface.h"
#include "algorithm/direction/interface.h"
#include "algorithm/create_point/interface.h"
#include "algorithm/located_inside/interface.h"

namespace agl::algorithm::dispatch {

template<typename Circle,
         typename Object,
         typename LineSectionOut,
         typename TagTangent,
         typename TagObject,
         typename CoordinateSystem,
         std::size_t Dimension>
struct tangent_circle{
    inline constexpr static auto get(const Circle &circle, const Object &object, TagTangent tag){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<typename Circle,
         typename Object,
         typename LineSectionOut>
struct tangent_circle<Circle,
                      Object,
                      LineSectionOut,
                      agl::algorithm::type_tangent::external,
                      agl::tag::elements_circle::circle,
                      agl::system_coordinat::cartesian,
                      2>{
    inline constexpr static auto get(const Circle &circle, const Object &object, agl::algorithm::type_tangent::external tag)
        -> std::pair<std::optional<LineSectionOut>, std::optional<LineSectionOut>>{
        using Type = agl::traits::traits_circle::type_property<Circle>::type_radius;
        using Point = agl::traits::traits_line_section::type_property<LineSectionOut>::type_point;
        const auto &center1 = traits::traits_circle::access_center<Circle>::get(circle);
        const auto &radius1 = traits::traits_circle::access_radius<Circle>::get(circle);
        const auto &center2 = traits::traits_circle::access_center<Object>::get(object);
        const auto &radius2 = traits::traits_circle::access_radius<Object>::get(object);

        const auto _len = agl::algorithm::distance(center1, center2);
        if(agl::algorithm::compare(_len, 0.) || (fabs(radius1 - radius2) > _len)){
            return {};
        }
        const auto _dradius = radius1 - radius2;
        const auto _angle = (_dradius < 0) ? agl::algorithm::direction<Type>(center1, center2)
                                           : agl::algorithm::direction<Type>(center2, center1);
        const auto dc = (algorithm::pi<Type> - std::acos(fabs(_dradius) / _len));
        return std::pair<LineSectionOut, LineSectionOut>{
            {
                agl::algorithm::create_point<Point>(center1, _angle + dc, radius1),
                agl::algorithm::create_point<Point>(center2, _angle + dc, radius2)
            },
            {
                agl::algorithm::create_point<Point>(center1, _angle - dc, radius1),
                agl::algorithm::create_point<Point>(center2, _angle - dc, radius2)
            },
        };
    }
};

template<typename Circle,
         typename Object,
         typename LineSectionOut>
struct tangent_circle<Circle,
                      Object,
                      LineSectionOut,
                      agl::algorithm::type_tangent::internal,
                      agl::tag::elements_circle::circle,
                      agl::system_coordinat::cartesian,
                      2>{
    inline constexpr static auto get(const Circle &circle, const Object &object, agl::algorithm::type_tangent::internal tag)
    -> std::pair<std::optional<LineSectionOut>, std::optional<LineSectionOut>>{
        using Type = agl::traits::traits_circle::type_property<Circle>::type_radius;
        using Point = agl::traits::traits_line_section::type_property<LineSectionOut>::type_point;
        const auto &center1 = traits::traits_circle::access_center<Circle>::get(circle);
        const auto &radius1 = traits::traits_circle::access_radius<Circle>::get(circle);
        const auto &center2 = traits::traits_circle::access_center<Object>::get(object);
        const auto &radius2 = traits::traits_circle::access_radius<Object>::get(object);

        const auto _len = agl::algorithm::distance(center1, center2);
        if(agl::algorithm::compare(_len, 0.) || (fabs(radius1 + radius2) > _len)){
            return {};
        }
        const bool flag = radius1 > radius2;
        const  auto _course = flag ? agl::algorithm::direction<Type>(center2, center1)
                                   : agl::algorithm::direction<Type>(center1, center2);
        const auto dc = (algorithm::pi<Type> - std::acos((radius1 + radius2) / _len));
        const auto _angle1 = _course + dc;
        const auto _angle2 = _course - dc;
        return std::pair<LineSectionOut, LineSectionOut>{
            {
                agl::algorithm::create_point<Point>(center1, flag ? _angle1 : _angle1 + algorithm::pi<Type>, radius1),
                agl::algorithm::create_point<Point>(center2, !flag ? _angle1 : _angle1 + algorithm::pi<Type>, radius2)
            },
            {
                agl::algorithm::create_point<Point>(center1, flag ? _angle2 : _angle2 + algorithm::pi<Type>, radius1),
                agl::algorithm::create_point<Point>(center2, !flag ? _angle2 : _angle2 + algorithm::pi<Type>, radius2)
            },
        };
    }
};


template<typename Circle,
         typename Object,
         typename LineSectionOut>
struct tangent_circle<Circle,
                      Object,
                      LineSectionOut,
                      agl::algorithm::type_tangent::external,
                      agl::tag::point::point,
                      agl::system_coordinat::cartesian,
                      2>{
    inline constexpr static auto get(const Circle &circle, const Object &object, agl::algorithm::type_tangent::external tag)
    -> std::pair<std::optional<LineSectionOut>, std::optional<LineSectionOut>>{
        using Type = agl::traits::traits_circle::type_property<Circle>::type_radius;
        using Point = agl::traits::traits_line_section::type_property<LineSectionOut>::type_point;
        const auto &center = traits::traits_circle::access_center<Circle>::get(circle);
        const auto &radius = traits::traits_circle::access_radius<Circle>::get(circle);
        if(agl::algorithm::located_inside(circle, object)){
            return {};
        }
        auto angle = agl::algorithm::direction<Type>(center, object);
        auto lenght = agl::algorithm::distance(center, object);
        auto dangle = std::acos(radius / lenght);

        return std::pair<LineSectionOut, LineSectionOut>{
            {agl::algorithm::create_point<Point>(center, angle + dangle, radius), object},
            {agl::algorithm::create_point<Point>(center, angle - dangle, radius), object},
        };
    }
};

}


namespace agl::algorithm::geometry {

template<typename Circle,
         typename Object,
         typename LineSectionOut,
         typename TagTangent>
inline constexpr auto tangent_circle(const Circle &circle, const Object &object, TagTangent tag){
    using type_cs1 = traits::coordinate_system<Circle>::system;
    using type_cs2 = traits::coordinate_system<Object>::system;
    using TagCircle = agl::traits::tag<Circle>::type_tag;
    using Tag = agl::traits::tag<Object>::type_tag;
    constexpr auto dimension1 = traits::dimension<Circle>::value();
    constexpr auto dimension2 = traits::dimension<Object>::value();
    static_assert(std::is_same_v<TagCircle, agl::tag::elements_circle::circle>, "Error!");
    static_assert(agl::assert::is_correct_compare<type_cs1, type_cs2>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension1, dimension2), "Error!");
    return dispatch::tangent_circle<Circle,
                                    Object,
                                    LineSectionOut,
                                    TagTangent,
                                    Tag,
                                    type_cs1,
                                    dimension1>::get(circle, object, tag);
}

}


#endif // AGL_ALGORITHM_TANGENT_CIRCLE_IMPLEMENTATION_H
