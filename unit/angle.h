#ifndef AGL_UNIT_ANGLE_H
#define AGL_UNIT_ANGLE_H

#include "system/tag.h"
#include "system/system_unit.h"

namespace agl::unit {

using _angle = enum_unit<0,0,0,0>;

using radian = measure_unit<_angle, 1.>;
using degrees = measure_unit<_angle, 0.01745329251994329577>;

using angle_prefix = std::tuple<
    radian,
    degrees
    >;

template<class AnglePrefix, c_type_value Type, c_basic_value BasicValue>
    requires(c_unit_prefix<AnglePrefix, _angle> && find_type<AnglePrefix>(angle_prefix()))
struct Convert<AnglePrefix, Type, _angle, BasicValue>{
    constexpr static Type convert(Type value) {
        if constexpr(std::is_same_v<BasicValue, basic>){
            return value * AnglePrefix::unit_value;
        }
        else{
            return value / AnglePrefix::unit_value;
        }
    }
};

using angle = unit::Value<unit::_angle, double>;

}

OPERATOR_QM(agl::unit::angle, rad, agl::unit::radian)
OPERATOR_QM(agl::unit::angle, deg, agl::unit::degrees)

constexpr agl::unit::angle operator +(const agl::unit::angle &value1, const agl::unit::angle &value2){
    return agl::unit::angle(value1.value() + value2.value()) ;
}

constexpr agl::unit::angle operator *(const double &value1, const agl::unit::angle &value2){
    return agl::unit::angle(value1 * value2.value()) ;
}

constexpr agl::unit::angle operator *(const agl::unit::angle &value1, const double &value2){
    return value2 * value1;
}

namespace agl::system::tag{

template<> struct value<agl::unit::angle>{
    inline constexpr static auto get(const agl::unit::angle &temp){
        return temp.value();
    }
};

}

// namespace agl {

// template<std::floating_point Type>
// class angle_impl{
// public:
//     using type_angle = Type;

//     constexpr angle_impl() = default;

//     constexpr angle_impl(Type radian){
//         setValue(radian);
//     }

//     template<std::floating_point T>
//     constexpr angle_impl(const angle_impl<T> &value){
//         radian_ = value.radian();
//     }

//     constexpr Type radian() const{
//         return radian_;
//     }
//     constexpr Type degrees() const{
//         return radian_ / algorithm::pi_on_180<Type>;
//     }

//     constexpr void setValue(Type radian){
//         radian_ = radian;
//     }

//     constexpr angle_impl &asin(const Type &value){
//         if (algorithm::interval_strict(value, -1.0, 1.0)){
//             radian_ = function_angle<Type>::asin(value);
//             return *this;
//         }
//         else{
//             assert(false && "value < -1 || value > 1");
//         }
//     }
//     constexpr angle_impl &acos(const Type &value){
//         if(algorithm::interval_strict(value, -1.0, 1.0)){
//             radian_ = function_angle<Type>::acos(value);
//             return *this;
//         }
//         else{
//             assert(false && "value < -1 || value > 1");
//         }

//     }
//     constexpr angle_impl &atan(const Type &value){
//         radian_ = function_angle<Type>::atan(value);
//         return *this;
//     }
//     constexpr angle_impl &actan(const Type &value){
//         radian_ = algorithm::pi_on_2<Type> + function_angle<Type>::atan(-value);
//         return *this;
//     }

//     constexpr Type sin() const{
//         return function_angle<Type>::sin(radian_);
//     }
//     constexpr Type cos() const{
//         return function_angle<Type>::cos(radian_);
//     }
//     constexpr Type tan() const{
//         return function_angle<Type>::tan(radian_);
//     }
//     constexpr Type ctan() const{
//         return 1.0 / function_angle<Type>::tan(radian_);
//     }

//     template<std::floating_point Type_Value>
//     constexpr angle_impl &operator+=(const angle_impl<Type_Value> &angle){
//         radian_ += angle.radian();
//         return *this;
//     }

//     template<std::floating_point Type_Value>
//     constexpr angle_impl &operator-=(const angle_impl<Type_Value> &angle){
//         radian_ -= angle.radian();
//         return *this;
//     }

//     template<std::floating_point T>
//     constexpr angle_impl operator=(const angle_impl<T> &value){
//         radian_ = value.radian();
//         return *this;
//     }

//     friend constexpr angle_impl operator*(const Type &value, const angle_impl &angle){
//         return angle * value;
//     }

// private:
//     Type radian_{};
// };

// template<std::floating_point Type1, std::floating_point Type2>
// inline constexpr bool compare(const angle_impl<Type1> &value1, const angle_impl<Type2> &value2) {
//     return algorithm::compare_common(value1.radian(), value2.radian(), algorithm::epsilon<decltype(value1.radian())>);
// }

// template<std::floating_point Type>
// constexpr auto operator-(const angle_impl<Type> &value){
//     return angle_impl<Type>(-value.radian());
// }

// template<std::floating_point Type1, std::floating_point Type2>
// constexpr auto operator+(const angle_impl<Type1> &value1, const angle_impl<Type2> &value2){
//     return angle_impl<Type1>(value1.radian() + value2.radian());
// }

// template<std::floating_point Type1, std::floating_point Type2>
// constexpr auto operator-(const angle_impl<Type1> &value1, const angle_impl<Type2> &value2){
//     return angle_impl<Type1>(value1.radian() - value2.radian());
// }

// template<typename T>
// concept c_multiplier = std::floating_point<T> || std::integral<T>;

// template<std::floating_point Type1, c_multiplier Type2>
// constexpr auto operator*(const angle_impl<Type1> &value1, const Type2 &value2){
//     return angle_impl<Type1>(value1.radian() * value2);
// }

// template<std::floating_point Type1, c_multiplier Type2>
// constexpr auto operator/(const angle_impl<Type1> &value1, const Type2 &value2){
//     return angle_impl<Type1>(value1.radian() / value2);
// }

// template<std::floating_point Type1, std::floating_point Type2>
// constexpr auto operator/(const angle_impl<Type1> &value1, const angle_impl<Type2> &value2){
//     return value1.radian() / value2.radian();
// }

// template<std::floating_point Type1, std::floating_point Type2>
// constexpr auto operator<=>(const angle_impl<Type1> &value1, const angle_impl<Type2> &value2){
//     return value1.radian() <=> value2.radian();
// }

// template<std::floating_point Type1, std::floating_point Type2>
// constexpr bool operator==(const angle_impl<Type1> &value1, const angle_impl<Type2> &value2){
//     if constexpr(sizeof(Type1) < sizeof(Type2)){
//         return algorithm::compare(static_cast<Type2>(value1.radian()), value2.radian());
//     }
//     else if constexpr(sizeof(Type1) > sizeof(Type2)){
//         return algorithm::compare(value1.radian(), static_cast<Type1>(value2.radian()));
//     }
//     else{
//         return algorithm::compare(value1.radian(), value2.radian());
//     }
// }

// template<std::floating_point Type1>
// constexpr bool operator==(const angle_impl<Type1> &value1, const Type1 &value2){
//     return algorithm::compare(value1.radian(), value2);
// }

// }

// constexpr auto operator "" _deg(unsigned long long deg){
//     return agl::angle_impl<long double>(deg * agl::algorithm::pi_on_180<long double>);
// }

// constexpr auto operator "" _rad(unsigned long long rad){
//     return agl::angle_impl<long double>(rad);
// }

// constexpr auto operator "" _deg(long double deg){
//     return agl::angle_impl<long double>(deg * agl::algorithm::pi_on_180<long double>);
// }

// constexpr auto operator "" _rad(long double rad){
//     return agl::angle_impl<long double>(rad);
// }

// template<std::floating_point Type> constexpr static agl::angle_impl<Type> ang_pi_on_180 = angle_impl<Type>(agl::algorithm::pi_on_180<Type>);
// template<std::floating_point Type> constexpr static agl::angle_impl<Type> ang_pi_on_2 = angle_impl<Type>(agl::algorithm::pi_on_2<Type>);
// template<std::floating_point Type> constexpr static agl::angle_impl<Type> ang_pi_on_4 = angle_impl<Type>(agl::algorithm::pi_on_4<Type>);
// template<std::floating_point Type> constexpr static agl::angle_impl<Type> ang_pi_on_6 = angle_impl<Type>(agl::algorithm::pi_on_6<Type>);
// template<std::floating_point Type> constexpr static agl::angle_impl<Type> ang_pi = angle_impl<Type>(agl::algorithm::pi<Type>);
// template<std::floating_point Type> constexpr static agl::angle_impl<Type> ang_pi_in_3_on_2 = angle_impl<Type>(agl::algorithm::pi_in_3_on_2<Type>);
// template<std::floating_point Type> constexpr static agl::angle_impl<Type> ang_pi_in_2 = angle_impl<Type>(agl::algorithm::pi_in_2<Type>);


// template<typename Type> requires requires(Type angle){angle.radian();}
// struct function_angle<agl::angle_impl<Type>>{
//     inline constexpr static Type sin(agl::angle_impl<Type> value) {
//         return std::sin(value.radian());
//     }
//     inline constexpr static Type cos(agl::angle_impl<Type> value) {
//         return std::cos(value.radian());
//     }
//     inline constexpr static Type tan(agl::angle_impl<Type> value){
//         return std::tan(value.radian());
//     }
//     inline constexpr static Type ctan(agl::angle_impl<Type> value){
//         return 1.0 / std::tan(value.radian());
//     }
//     inline constexpr static Type atan2(agl::angle_impl<Type> value1, agl::angle_impl<Type> value2){
//         return std::atan2(value1.radian(), value2.radian());
//     }

//     inline constexpr static Type asin(agl::angle_impl<Type> value){
//         return std::asin(value.radian());
//     }
//     inline constexpr static Type acos(agl::angle_impl<Type> value){
//         return std::acos(value.radian());
//     }
//     inline constexpr static Type atan(agl::angle_impl<Type> value){
//         return std::atan(value.radian());
//     }
//     inline constexpr static Type actan(agl::angle_impl<Type> value){
//         return agl::algorithm::pi_on_2<Type> - std::atan(value.radian());
//     }
// };

#endif // AGL_UNIT_ANGLE_H
