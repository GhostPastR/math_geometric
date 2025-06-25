#ifndef SYSTEM_CONCEPT_H
#define SYSTEM_CONCEPT_H

#include <iterator>

template<typename View>
struct view{
    View value{};
    const bool is_view;
};

template<typename Type>
concept c_point2d_decard = requires(Type temp){
    typename Type::type_coordinate;
    temp.x(); temp.y();
};

template<typename Type>
concept c_point2d_polar = requires(Type temp){
    typename Type::type_coordinate;
    temp.psi(); temp.fi();
};

template<typename Type>
concept c_point2d_geo = requires(Type temp){
    temp.latitude(); temp.longitude();
};

template<typename Type>
concept c_point2d = c_point2d_decard<Type> || c_point2d_geo<Type>;

template<typename Type>
concept c_point3d_decard = requires(Type temp){
    temp.x(); temp.y(); temp.h();
};

template<typename Type>
concept c_point3d_geo = requires(Type temp){
    temp.latitude(); temp.longitude(); temp.altitude();
};

template<typename Type>
concept c_point3d = c_point3d_decard<Type> || c_point3d_geo<Type>;

template<typename Type>
concept c_polar2d = requires(Type temp){
    temp.psi(); temp.fi();
};

template<typename Type>
concept c_angle = requires(Type type){
    type.radian();
    type.asin(typename Type::type_angle());
    type.acos(typename Type::type_angle());
    type.atan(typename Type::type_angle());
    type.actan(typename Type::type_angle());
    type.sin();
    type.cos();
    type.tan();
    type.ctan();
    type.operator+=(Type());
    type.operator-=(Type());
    operator*(typename Type::type_angle(), Type());
};

template<typename ClassFunctions, typename Type>
concept c_function_angle = requires(){
    ClassFunctions::sin(Type());
    ClassFunctions::cos(Type());
    ClassFunctions::tan(Type());
    ClassFunctions::ctan(Type());

    ClassFunctions::asin(Type());
    ClassFunctions::acos(Type());
    ClassFunctions::atan(Type());
    ClassFunctions::actan(Type());
    ClassFunctions::atan2(Type(), Type());
};

template<typename Type>
concept c_straight_line = requires(Type temp){
    temp.a();
    temp.b();
    temp.c();
};

template<typename Type>
concept c_half_line = requires(Type temp){
    typename Type::type_point;
    {temp.start()} -> std::same_as<typename Type::type_point>;
    temp.direction();
};

template<typename Type>
concept c_line_section = requires(Type temp){
    typename Type::type_point;
    {temp.start()} -> std::same_as<typename Type::type_point>;
    {temp.stop()} -> std::same_as<typename Type::type_point>;
};

template<typename Type>
concept c_arc = requires(Type temp){
    temp.center();
    temp.radius();
    {temp.start()} -> std::floating_point;
    {temp.stop()} -> std::floating_point;
} && std::is_same_v<typename Type::figure, std::false_type>;

template<typename Type>
concept c_circle = requires(Type temp){
    temp.center();
    temp.radius();
} && std::is_same_v<typename Type::figure, std::true_type>;

template<typename Type>
concept c_polugon = requires(Type temp){
    typename Type::type_point;
    std::begin(temp.get_points());
    std::end(temp.get_points());
};

template<typename Type>
concept c_rectangle = requires(Type temp){
    typename Type::type_point;
    std::begin(temp.get_points());
    std::end(temp.get_points());
    temp.get_top_left();
    temp.width();
    temp.height();
};

template<typename Type>
concept c_square = requires(Type temp){
    typename Type::type_point;
    std::begin(temp.get_points());
    std::end(temp.get_points());
    temp.get_top_left();
    temp.lenght();
};

template<typename Type>
concept c_triangle = requires(Type temp){
    typename Type::type_point;
    std::begin(temp.get_points());
    std::end(temp.get_points());
    temp.get_top_left();
    temp.a();
    temp.b();
    temp.c();
};

template<typename Type>
concept c_regular_polygon = requires(Type temp){
    typename Type::type_point;
    std::begin(temp.get_points());
    std::end(temp.get_points());
    temp.get_center();
    temp.get_lenght();
    temp.get_count();
};




#endif // SYSTEM_CONCEPT_H
