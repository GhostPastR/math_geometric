#ifndef TRAITS_H
#define TRAITS_H

#include <concepts>
#include <tuple>
#include "tag.h"

namespace agl{

namespace traits {

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

template<typename Object>
struct make{
    template<typename ... Value>
    inline constexpr static auto apply(Value... value){}
};

template<typename Object>
struct access_propery{
    inline constexpr static auto get(const Object &object){}
};

namespace point {

template<typename Object>
struct access_types{
    template<typename ...T>
    using types = std::tuple<T...>;
};

template<typename Object, std::size_t NumberPoint>
struct access_point{
    inline constexpr static auto get(const Object &object){}
};

template<typename Point, std::size_t N>
using element_point_v = std::tuple_element<N, typename agl::traits::point::access_types<Point>::types>::type;


}

namespace arc {

template<typename Object>
struct access_types{
    using center = undefined;
    using radius = undefined;
    using angle = undefined;
};

template<typename Object>
struct access_center{
    inline constexpr static auto get(const Object &object){}
};

template<typename Object>
struct access_radius{
    inline constexpr static auto get(const Object &object){}
};

template<typename Object, std::size_t NumberAngle>
struct access_angle{
    inline constexpr static auto get(const Object &object){}
};

template<typename Object>
struct access_change{
    inline constexpr static auto get(const Object &object){}
};

}

namespace circle {

template<typename Object>
struct access_types{
    using center = undefined;
    using radius = undefined;
};

template<typename Object>
struct access_center{
    inline constexpr static auto get(const Object &object){}
};

template<typename Object>
struct access_radius{
    inline constexpr static auto get(const Object &object){}
};

}



namespace straight_line {

template<typename Object>
struct access_types{
    using parameter = undefined;
};

template<typename Object, std::size_t NumberPoint>
struct access_parameter{
    inline constexpr static auto get(const Object &object){}
};

}

namespace half_line {

template<typename Object>
struct access_types{
    using start = undefined;
    using direction = undefined;
};

template<typename Object>
struct access_straight_line{
    using type = undefined;
};


template<typename Object>
struct access_start{
    inline constexpr static auto get(const Object &object){}
};

template<typename Object>
struct access_direction{
    inline constexpr static auto get(const Object &object){}
};

}

namespace line_section {

template<typename Object>
struct access_types{
    using point = undefined;
};

template<typename Object>
struct access_straight_line{
    using type = undefined;
};


template<typename Object>
struct access_start{
    inline constexpr static auto get(const Object &object){}
};

template<typename Object>
struct access_stop{
    inline constexpr static auto get(const Object &object){}
};

}


namespace polygon {

template<typename Object>
struct access_tag{
    using type_tag = undefined;
};

template<typename Object>
struct access_types{
    using point = undefined;
};

template<typename Object>
struct access_line_section{
    using type = undefined;
};

template<typename Object>
struct access_points{
    inline constexpr static auto get(const Object &object){}
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
    inline constexpr static auto get(const Type &){}
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


template<> struct make<int>{
    template<typename Value>
    inline constexpr static int apply(const Value& value){
        return value;
    }
};

template<> struct make<float>{
    template<typename Value>
    inline constexpr static float apply(const Value& value){
        return value;
    }
};

template<> struct make<double>{
    template<typename Value>
    inline constexpr static double apply(const Value& value){
        return value;
    }
};

template<> struct make<long double>{
    template<typename Value>
    inline constexpr static long double apply(const Value& value){
        return value;
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
