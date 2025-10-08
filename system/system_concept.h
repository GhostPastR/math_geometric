#ifndef SYSTEM_CONCEPT_H
#define SYSTEM_CONCEPT_H

#include "traits.h"

namespace agl {

template<typename Object>
concept c_geometric = requires(Object object){
    typename traits::tag<Object>::type_tag;
    typename agl::traits::group<Object>::type_group;
    typename agl::traits::coordinate_system<Object>::system;
    agl::traits::dimension<Object>::value();
};

template<typename Object>
concept c_point_2d = requires(Object object){
    requires c_geometric<Object>;
    typename agl::traits::point::access_types<Object>::point;
    agl::traits::point::access_point<Object, 0>::get(object);
    agl::traits::point::access_point<Object, 1>::get(object);
};

template<typename Object, typename Type>
concept c_create_point_2d = requires(Object object){
    requires c_point_2d<Object>;
    agl::traits::point::access_create<Object>::get(Type{}, Type{});
};

template<typename Object>
concept c_circle = requires(Object object){
    requires c_geometric<Object>;
    typename agl::traits::arc::access_types<Object>::center;
    typename agl::traits::arc::access_types<Object>::radius;
    agl::traits::arc::access_center<Object>::get(object);
    agl::traits::arc::access_radius<Object>::get(object);
};

template<typename Object>
concept c_arc = requires(Object object){
    requires c_circle<Object>;
    typename agl::traits::arc::access_types<Object>::angle;
    agl::traits::arc::access_angle<Object, 0>::get(object);
    agl::traits::arc::access_angle<Object, 1>::get(object);
};

template<typename Object>
concept c_straight_line = requires(Object object){
    requires c_geometric<Object>;
    typename agl::traits::straight_line::access_types<Object>::parameter;
};

template<typename Object>
concept c_straight_line_2d = requires(Object object){
    requires c_straight_line<Object>;
    agl::traits::straight_line::access_parameter<Object, 0>::get(object);
    agl::traits::straight_line::access_parameter<Object, 1>::get(object);
    agl::traits::straight_line::access_parameter<Object, 2>::get(object);
};

template<typename Object>
concept c_half_line_2d = requires(Object object){
    requires c_geometric<Object>;
    typename agl::traits::half_line::access_types<Object>::start;
    typename agl::traits::half_line::access_types<Object>::direction;
    agl::traits::half_line::access_start<Object>::get(object);
    agl::traits::half_line::access_direction<Object>::get(object);
};

template<typename Object>
concept c_half_line_to_straight_line_2d = requires(Object object){
    requires c_half_line_2d<Object>;
    typename agl::traits::half_line::access_straight_line<Object>::type;
};

template<typename Object>
concept c_line_section = requires(Object object){
    requires c_geometric<Object>;
    typename agl::traits::line_section::access_types<Object>::point;
    agl::traits::line_section::access_start<Object>::get(object);
    agl::traits::line_section::access_stop<Object>::get(object);
};

template<typename Object, typename Point>
concept c_create_line_section = requires(Object object){
    requires c_line_section<Object>;
    agl::traits::line_section::access_create<Object>::get(Point{}, Point{});
};

template<typename Object>
concept c_line_section_to_straight_line = requires(Object object){
    requires c_line_section<Object>;
    typename agl::traits::line_section::access_straight_line<Object>::type;
};

template<typename Object>
concept c_polygon = requires(Object object){
    requires c_geometric<Object>;
    typename agl::traits::polygon::access_polygon<Object>::regular;
    typename agl::traits::polygon::access_polygon<Object>::type;
    typename agl::traits::polygon::access_types<Object>::point;
    typename agl::traits::polygon::access_line_section<Object>::type;
    agl::traits::polygon::access_points<Object>::get(object);
};

template<typename Object, typename Point>
concept c_create_polygon = requires(Object object){
    requires c_polygon<Object>;
    typename agl::traits::polygon::access_polygon<Object>::regular;
    typename agl::traits::polygon::access_polygon<Object>::type;
    typename agl::traits::polygon::access_types<Object>::point;
    typename agl::traits::polygon::access_line_section<Object>::type;
    agl::traits::polygon::access_create<Object>::get(std::vector<Point>{});
};

template<typename Object>
concept c_group_line = requires(Object object){
    requires c_geometric<Object>;
    requires std::is_same_v<typename agl::traits::tag<Object>::type_tag, agl::tag::line::straight_line>
                 || std::is_same_v<typename agl::traits::tag<Object>::type_tag, agl::tag::line::half_line>
                 || std::is_same_v<typename agl::traits::tag<Object>::type_tag, agl::tag::line::line_section>;
};

template<typename Object>
concept c_group_polygon = requires(Object object){
    requires c_polygon<Object>;
};

}

#endif // SYSTEM_CONCEPT_H
