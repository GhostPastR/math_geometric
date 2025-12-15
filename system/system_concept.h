#ifndef SYSTEM_CONCEPT_H
#define SYSTEM_CONCEPT_H

#include "tag.h"
#include "traits.h"
#include <vector>

namespace agl {

template<typename Object>
concept c_value = std::integral<Object> || std::floating_point<Object>;

template<typename Object>
concept c_not_undefined = !std::is_same_v<Object, agl::undefined>;


template<typename Object>
concept c_cartesian = std::is_same_v<typename agl::traits::coordinate_system<Object>::system, agl::system_coordinat::cartesian>;

template<typename Object>
concept c_polar = std::is_same_v<typename agl::traits::coordinate_system<Object>::system, agl::system_coordinat::polar>;

template<typename Object>
concept c_spherical = std::is_same_v<typename agl::traits::coordinate_system<Object>::system, agl::system_coordinat::spherical>;

template<typename Object>
concept c_geographical = std::is_same_v<typename agl::traits::coordinate_system<Object>::system, agl::system_coordinat::geographical>;

template<typename ... Object>
concept c_cartesian_all = (c_cartesian<Object> && ...);

template<typename ... Object>
concept c_polar_all = (c_polar<Object> && ...);

template<typename ... Object>
concept c_geographical_all = (c_geographical<Object> && ...);


template<typename Object>
concept c_geometric = requires(Object object){
    requires c_not_undefined<typename agl::traits::coordinate_system<Object>::system>;
    requires agl::traits::dimension<Object>::value() > 0;
};

template<typename Object, typename ... Args>
concept c_create = requires(Args  ...args){
    {agl::traits::make<Object>::apply(args...)} -> std::same_as<Object>;
};

template<typename Object>
concept c_demension_2 = requires(Object object){
    requires agl::traits::dimension<Object>::value() == 2;
};

template<typename ... Object>
concept c_demension_2_all = (c_demension_2<Object> && ...);

template<typename Object>
concept c_demension_3 = requires(Object object){
    requires agl::traits::dimension<Object>::value() == 3;
};

template<typename ... Object>
concept c_demension_3_all = (c_demension_3<Object> && ...);

template<typename Object>
concept c_unit = requires(Object object){
    {agl::traits::value<Object>::get(object)} -> std::floating_point;

};


template<typename Object, size_t N>
concept c_property_point = requires(Object object){
    requires std::is_same_v<decltype(agl::traits::point::access_point<Object, N>::get(object)),
                            typename std::tuple_element<N, typename agl::traits::point::access_types<Object>::types>::type>;
};

template<typename Object>
concept c_point_2d = requires(Object object){
    requires c_geometric<Object>;
    requires agl::traits::dimension<Object>::value() == 2;
    requires c_property_point<Object, 0>;
    requires c_property_point<Object, 1>;
};

template<typename Object>
concept c_point_3d = requires(Object object){
    requires c_geometric<Object>;
    requires agl::traits::dimension<Object>::value() == 3;
    requires c_property_point<Object, 0>;
    requires c_property_point<Object, 1>;
    requires c_property_point<Object, 2>;
};


template<typename Object>
concept c_circle = requires(Object object){
    requires c_geometric<Object>;
    requires c_not_undefined<typename agl::traits::circle::access_types<Object>::center>;
    requires c_not_undefined<typename agl::traits::circle::access_types<Object>::radius>;
    {agl::traits::circle::access_center<Object>::get(object)} -> c_point_2d;
    {agl::traits::circle::access_radius<Object>::get(object)} -> c_value;
};

template<typename Object>
concept c_arc = requires(Object object){
    requires c_geometric<Object>;
    requires c_not_undefined<typename agl::traits::arc::access_types<Object>::center>;
    requires c_not_undefined<typename agl::traits::arc::access_types<Object>::radius>;
    requires c_not_undefined<typename agl::traits::arc::access_types<Object>::angle>;
    requires agl::traits::dimension<Object>::value() == 2;
    {agl::traits::arc::access_angle<Object, 0>::get(object)} -> std::floating_point;
    {agl::traits::arc::access_angle<Object, 1>::get(object)} -> std::floating_point;
};

template<typename Object>
concept c_straight_line = requires(Object object){
    requires c_geometric<Object>;
    requires c_not_undefined<typename agl::traits::straight_line::access_types<Object>::parameter>;
    requires agl::traits::dimension<Object>::value() == 2;
};

template<typename Object>
concept c_straight_line_3 = requires(Object object){
    requires c_geometric<Object>;
    requires c_not_undefined<typename agl::traits::straight_line::access_types<Object>::parameter>;
    requires agl::traits::dimension<Object>::value() == 3;
};

template<typename Object>
concept c_straight_line_2d = requires(Object object){
    requires c_straight_line<Object>;
    requires c_not_undefined<typename agl::traits::straight_line::access_types<Object>::parameter>;
    {agl::traits::straight_line::access_parameter<Object, 0>::get(object)} -> c_value;
    {agl::traits::straight_line::access_parameter<Object, 1>::get(object)} -> c_value;
    {agl::traits::straight_line::access_parameter<Object, 2>::get(object)} -> c_value;
};

template<typename Object>
concept c_half_line_2d = requires(Object object){
    requires c_geometric<Object>;
    requires c_not_undefined<typename agl::traits::half_line::access_types<Object>::start>;
    requires c_not_undefined<typename agl::traits::half_line::access_types<Object>::direction>;
    requires agl::traits::dimension<Object>::value() == 2;
    {agl::traits::half_line::access_start<Object>::get(object)} -> c_point_2d;
    {agl::traits::half_line::access_direction<Object>::get(object)} -> std::floating_point;
};

// template<typename Object>
// concept c_half_line_to_straight_line_2d = requires(Object object){
//     requires c_half_line_2d<Object>;
//     requires c_not_undefined<typename agl::traits::half_line::access_straight_line<Object>::type>;
// };

template<typename Object>
concept c_line_section = requires(Object object){
    requires c_geometric<Object>;
    requires c_not_undefined<typename agl::traits::line_section::access_types<Object>::point>;
    requires c_not_undefined<typename agl::traits::line_section::access_straight_line<Object>::type>;
    {agl::traits::line_section::access_start<Object>::get(object)} -> c_point_2d;
    {agl::traits::line_section::access_stop<Object>::get(object)} -> c_point_2d;
};

template<typename Object, typename T>
concept c_container = std::is_same_v<Object, std::vector<T>> && c_point_2d<T>;

template<typename Object>
concept c_polygon = requires(Object object){
    requires c_geometric<Object>;
    requires c_not_undefined<typename agl::traits::polygon::access_tag<Object>::type_tag>;
    requires c_not_undefined<typename agl::traits::polygon::access_types<Object>::point>;
    requires c_not_undefined<typename agl::traits::polygon::access_line_section<Object>::type>;
    {agl::traits::polygon::access_points<Object>::get(object)}
          -> c_container<typename agl::traits::polygon::access_types<Object>::point>;
};

template<typename Object>
concept c_create_point_2d = requires(Object object){
    requires c_point_2d<Object>;
    requires c_create<Object,
                      typename std::tuple_element<0, typename agl::traits::point::access_types<Object>::types>::type,
                      typename std::tuple_element<1, typename agl::traits::point::access_types<Object>::types>::type>;
};

template<typename Object>
concept c_create_point_3d = requires(Object object){
    requires c_point_3d<Object>;
    requires c_create<Object,
                      typename std::tuple_element<0, typename agl::traits::point::access_types<Object>::types>::type,
                      typename std::tuple_element<1, typename agl::traits::point::access_types<Object>::types>::type,
                      typename std::tuple_element<2, typename agl::traits::point::access_types<Object>::types>::type>;
};

template<typename Object>
concept c_create_circle = requires(Object object){
    requires c_circle<Object>;
    requires c_create<Object,
                      typename agl::traits::circle::access_types<Object>::center,
                      typename agl::traits::circle::access_types<Object>::radius>;
};

template<typename Object>
concept c_create_arc = requires(Object object){
    requires c_arc<Object>;
    requires c_create<Object,
                      typename agl::traits::arc::access_types<Object>::center,
                      typename agl::traits::arc::access_types<Object>::radius,
                      typename agl::traits::arc::access_types<Object>::angle,
                      typename agl::traits::arc::access_types<Object>::angle>;
};

template<typename Object>
concept c_create_straight_line_2d = requires(Object object){
    requires c_straight_line_2d<Object>;
    requires c_create<Object,
                      typename agl::traits::straight_line::access_types<Object>::parameter,
                      typename agl::traits::straight_line::access_types<Object>::parameter,
                      typename agl::traits::straight_line::access_types<Object>::parameter>;
};

template<typename Object>
concept c_create_half_line_2d = requires(Object object){
    requires c_half_line_2d<Object>;
    requires c_create<Object,
                      typename agl::traits::half_line::access_types<Object>::start,
                      typename agl::traits::half_line::access_types<Object>::direction>;
};

template<typename Object>
concept c_create_line_section = requires(Object object){
    requires c_line_section<Object>;
    requires c_create<Object,
                      typename agl::traits::line_section::access_types<Object>::point,
                      typename agl::traits::line_section::access_types<Object>::point>;
};

template<typename Object>
concept c_create_polygon = requires(Object object){
    requires c_polygon<Object>;
    requires c_create<Object,
                      std::vector<typename agl::traits::polygon::access_types<Object>::point>>;
};


template<typename Object>
concept c_group_point = requires(Object object){
    requires c_point_2d<Object>;
};

template<typename Object>
concept c_group_circle = c_circle<Object> || c_arc<Object>;

template<typename Object>
concept c_group_line = c_straight_line<Object> || c_half_line_2d<Object> || c_line_section<Object>;

template<typename Object>
concept c_group_polygon = c_polygon<Object>;

}

#endif // SYSTEM_CONCEPT_H
