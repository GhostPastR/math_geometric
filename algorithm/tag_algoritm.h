#ifndef AGL_ALGORITM_TAG_H
#define AGL_ALGORITM_TAG_H

#include "system/traits.h"

namespace agl::algorithm {

struct direction_angle final{};
struct direction_vector final{};

template<typename Type>
struct direction_object{
    using type_direction_object = undefined;
};

template<> struct direction_object<float>{
    using type_direction_object = direction_angle;
};

template<> struct direction_object<double>{
    using type_direction_object = direction_angle;
};

template<> struct direction_object<long double>{
    using type_direction_object = direction_angle;
};



namespace tag::intersection {

struct line_to_line final{};
struct line_to_circle final{};
struct circle_to_circle final{};

template<typename Figure1, typename Figure2>
struct tag{
    using object_to_object = undefined;
};

template<>
struct tag<group::lines, group::lines>{
    using object_to_object = line_to_line;
};

template<>
struct tag<group::elements_circles, group::elements_circles>{
    using object_to_object = line_to_circle;
};

template<>
struct tag<group::lines, group::elements_circles>{
    using object_to_object = line_to_circle;
};

template<>
struct tag<group::elements_circles, group::lines>{
    using object_to_object = line_to_circle;
};

}



namespace strategy {

struct create_rectangle_point_sides final{};
struct create_rectangle_center_sides final{};

struct create_square_point_sides final{};
struct create_square_center_sides final{};

struct create_triangle_point_sides final{};
struct create_triangle_point_sides_angle final{};
struct create_triangle_point_sides_angles final{};
struct create_triangle_rectangular_sides final{};
struct create_triangle_rectangular_sides_angles final{};
struct create_triangle_isosceles_sides final{};
struct create_triangle_isosceles_sides_angles final{};
struct create_triangle_regular final{};

struct create_polygon_regular final{};


struct create_circle_angle_point final{};

}

namespace type_tangent {

struct external final{};
struct internal final{};

}

}

#endif // AGL_ALGORITM_TAG_H
