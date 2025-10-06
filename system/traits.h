#ifndef TRAITS_H
#define TRAITS_H

#include <concepts>
#include <vector>
#include "tag.h"

namespace agl{

namespace traits {

template<typename Object>
struct tag{
    using type_tag = undefined;
};

template<typename Object>
struct group{
    using type_group = undefined;
};

template<typename Object>
struct coordinate_system{
    using system = undefined;
};

template<typename Object>
struct dimension{
    inline static constexpr std::size_t value(){
        return 0;
    }
};

template<typename Object>
struct geo_coordinate_system{
    using system = agl::system_coordinat::geo::sc_default;
};

namespace traits_point {

template<typename Object>
struct type_property{
    using type_point = undefined;
};

template<typename Object, std::size_t NumberPoint>
struct access_point{
    inline constexpr static auto get(const Object &object){
        static_assert(false, "Access is not implemented for this object.");
    }
};

template<typename Object, typename ... Value>
struct access_create{
    inline constexpr static auto get(Value&&... value){
        static_assert(false, "Access is not implemented for this object.");
    }
};

}

namespace traits_arc {

template<typename Object>
struct type_property{
    using type_center = undefined;
    using type_radius = undefined;
    using type_angle = undefined;
};

template<typename Object>
struct access_center{
    inline constexpr static auto get(const Object &object){
        static_assert(false, "Access is not implemented for this object.");
    }
};

template<typename Object>
struct access_radius{
    inline constexpr static auto get(const Object &object){
        static_assert(false, "Access is not implemented for this object.");
    }
};

template<typename Object, std::size_t NumberAngle>
struct access_angle{
    inline constexpr static auto get(const Object &object){
        static_assert(false, "Access is not implemented for this object.");
    }
};

}

namespace traits_circle {

template<typename Object>
struct type_property{
    using type_center = undefined;
    using type_radius = undefined;
};

template<typename Object>
struct access_center{
    inline constexpr static auto get(const Object &object){
        static_assert(false, "Access is not implemented for this object.");
    }
};

template<typename Object>
struct access_radius{
    inline constexpr static auto get(const Object &object){
        static_assert(false, "Access is not implemented for this object.");
    }
};

}



namespace traits_straight_line {

template<typename Object>
struct type_property{
    using type_parameter = undefined;
};

template<typename Object, std::size_t NumberPoint>
struct access_parameter{
    inline constexpr static auto get(const Object &object){
        static_assert(false, "Access is not implemented for this object.");
    }
};

template<typename Object>
struct access_create{
    template<typename Type>
    inline constexpr static auto get(Type &&a, Type &&b, Type &&c){
        static_assert(false, "Access is not implemented for this object.");
    }
};


}

namespace traits_half_line {

template<typename Object>
struct type_property{
    using type_start = undefined;
    using type_direction = undefined;
};

template<typename Object>
struct type_straight_line{
    using type = undefined;
};


template<typename Object>
struct access_start{
    inline constexpr static auto get(const Object &object){
        static_assert(false, "Access is not implemented for this object.");
    }
};

template<typename Object>
struct access_direction{
    inline constexpr static auto get(const Object &object){
        static_assert(false, "Access is not implemented for this object.");
    }
};

}

namespace traits_line_section {

template<typename Object>
struct type_property{
    using type_point = undefined;
};

template<typename Object>
struct type_straight_line{
    using type = undefined;
};


template<typename Object>
struct access_start{
    inline constexpr static auto get(const Object &object){
        static_assert(false, "Access is not implemented for this object.");
    }
};

template<typename Object>
struct access_stop{
    inline constexpr static auto get(const Object &object){
        static_assert(false, "Access is not implemented for this object.");
    }
};

template<typename Object, typename Point>
struct access_create{
    inline constexpr static auto get(const Point &point1, const Point &point2){
        static_assert(false, "Access is not implemented for this object.");
    }
};

}


namespace traits_polygon {

template<typename Object>
struct type_polygon{
    using regular = std::false_type;
    using type = undefined;
};

template<typename Object>
struct type_property{
    using type_point = undefined;
};

template<typename Object>
struct type_line_section{
    using type = undefined;
};

template<typename Object>
struct access_points{
    inline constexpr static auto get(const Object &object){
        static_assert(false, "Access is not implemented for this object.");
    }
};

template<typename Object>
struct access_create{
    inline constexpr static auto get(std::vector<typename type_property<Object>::type_point> &&points){
        static_assert(false, "Access is not implemented for this object.");
    }
};

}

}


namespace traits {

template<typename Type>
struct type{
    using type_value = undefined;
};

template<> struct type<float>{
    using type_value = float;
};

template<> struct type<double>{
    using type_value = double;
};

template<> struct type<long double>{
    using type_value = long double;
};


template<typename Type>
struct value{
    inline constexpr static auto get(const Type &){
        static_assert(false, "Error value!");
    }
};

template<> struct value<int>{
    inline constexpr static auto get(int temp){
        return temp;
    }
};

template<> struct value<float>{
    inline constexpr static auto get(float temp){
        return temp;
    }
};

template<> struct value<double>{
    inline constexpr static auto get(double temp){
        return temp;
    }
};

template<> struct value<long double>{
    inline constexpr static auto get(const long double &temp){
        return temp;
    }
};

}

namespace axis{

template <std::floating_point Type> inline constexpr Type semiminor_axis;
template<> inline constexpr double semiminor_axis<long double> = 6356751.362;
template<> inline constexpr double semiminor_axis<double> = 6356751.362;
template<> inline constexpr float semiminor_axis<float> = 6356751.362;

template <std::floating_point Type> inline constexpr Type semimajor_axis;
template<> inline constexpr double semimajor_axis<long double> = 6378136.;
template<> inline constexpr double semimajor_axis<double> = 6378136.;
template<> inline constexpr float semimajor_axis<float> = 6378136.;

template<std::floating_point Type>
constexpr Type eccentricity2_1(){
    return (semiminor_axis<Type> * semiminor_axis<Type> - semimajor_axis<Type> * semimajor_axis<Type>)
    / (semiminor_axis<Type> * semiminor_axis<Type>);
}

template<std::floating_point Type>
constexpr Type eccentricity2_2(){
    return (semimajor_axis<Type> * semimajor_axis<Type> - semiminor_axis<Type> * semiminor_axis<Type>)
    / (semiminor_axis<Type> * semiminor_axis<Type>);
}

}





}




#endif // TRAITS_H
