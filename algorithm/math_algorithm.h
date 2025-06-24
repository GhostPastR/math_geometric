#ifndef MATH_ALGORITHM_H
#define MATH_ALGORITHM_H

#include <cassert>
#include <cmath>
#include <concepts>
#include <optional>
#include <numbers>
#include <utility>

namespace algorithm {

template <std::floating_point Type> inline constexpr Type epsilon;
template<> inline constexpr long double epsilon<long double> = 0.000001;
template<> inline constexpr double epsilon<double> = 0.000001;
template<> inline constexpr float epsilon<float> = 0.0001;

inline constexpr double epsilon_l = epsilon<long double>;
inline constexpr double epsilon_d = epsilon<double>;
inline constexpr float epsilon_f = epsilon<float>;

template<std::floating_point Type> constexpr static Type pi_on_180 = std::numbers::pi_v<Type> / 180.0;
template<std::floating_point Type> constexpr static Type pi_on_2 = std::numbers::pi_v<Type> / 2.0;
template<std::floating_point Type> constexpr static Type pi_on_4 = std::numbers::pi_v<Type> / 4.0;
template<std::floating_point Type> constexpr static Type pi_on_6 = std::numbers::pi_v<Type> / 6.0;
template<std::floating_point Type> constexpr static Type pi = std::numbers::pi_v<Type>;
template<std::floating_point Type> constexpr static Type pi_in_3_on_2 = 3.0 * std::numbers::pi_v<Type> / 2.0;
template<std::floating_point Type> constexpr static Type pi_in_2 = 2.0 * std::numbers::pi_v<Type>;

template <std::floating_point Type>
struct quadratic{
    Type a;
    Type b;
    Type c;
};

template <std::floating_point Type>
using roots_equation = std::pair<std::optional<Type>, std::optional<Type>>;

template<typename Value>
concept compare_intervel = requires(Value a, Value b){
    a < b;
    a > b;
    a <= b;
    a >= b;
};

//Направление
enum class direct{
    LEFT  = -1,
    RIGHT = 1,
};

template<compare_intervel Value>
inline constexpr bool interval_strict(const Value &value, const Value &left, const Value &right) noexcept{
    return ((left <= value) && (value <= right));
}

template<compare_intervel Value>
inline constexpr bool interval_left_strict(const Value &value, const Value &left, const Value &right) noexcept{
    return ((left <= value) && (value < right));
}

template<compare_intervel Value>
inline constexpr bool interval_right_strict(const Value &value, const Value &left, const Value &right) noexcept{
    return ((left < value) && (value <= right));
}

template<compare_intervel Value>
inline constexpr bool interval_slack(const Value &value, const Value &left, const Value &right) noexcept{
    return ((left < value) && (value < right));
}

template<std::floating_point Value>
inline constexpr bool compare_common(const Value &value1, const Value &value2, const Value &epsilon){
    static_assert(std::is_floating_point_v<typename std::remove_reference<Value>::type>, "Not floating point type");
    // if((value1 == 0) || (value2 == 0)){
        return std::abs(value1 - value2) < epsilon;
    // }
    // return std::abs((value1 - value2) / value2) < epsilon;
}

template<std::floating_point Value>
inline constexpr bool compare(const Value& value1, const Value& value2) {
    if constexpr(std::floating_point<Value>){
        return algorithm::compare_common(value1, value2, algorithm::epsilon<Value>);
    }
    else{
        return value1 == value2;
    }
}

template<compare_intervel Value>
inline constexpr bool less_than_equal(const Value& value1, const Value& value2) {
    return ((value1 < value2) || compare(value1, value2));
}

template<compare_intervel Value>
inline constexpr bool greater_than_equal(const Value& value1, const Value& value2) {
    return ((value1 > value2) || compare(value1, value2));
}


template<std::floating_point Value>
inline constexpr bool is_valid(Value &&value){
    return !std::isnan(value) && !std::isinf(value);
}

template<std::floating_point Type>
inline constexpr Type discriminant(const quadratic<Type> &temp){
    return temp.b * temp.b - 4.0 * temp.a * temp.c;
}

template<std::floating_point Type>
roots_equation<Type> get_roots_equation(const quadratic<Type> &equations){
    if(compare(equations.a, 0.)){
        if(compare(equations.b, 0.)){
            return {};
        }
        return {-equations.c / equations.b, std::nullopt};
    }
    auto d = discriminant(equations);
    if(d < 0){
        return {};
    }
    if(compare(d, 0.)){
        return {-equations.b / (2. * equations.a), std::nullopt};
    }
    return {(equations.b - std::sqrt(d)) / (2. * equations.a),
            (equations.b + std::sqrt(d)) / (2. * equations.a)};
}


template<std::floating_point Type>
struct function_angle{
    inline constexpr static Type sin(Type value) {
        return std::sin(value);
    }
    inline constexpr static Type cos(Type value) {
        return std::cos(value);
    }
    inline constexpr static Type tan(Type value){
        return std::tan(value);
    }
    inline constexpr static Type ctan(Type value){
        return 1.0 / std::tan(value);
    }
    inline constexpr static Type atan2(Type value1, Type value2){
        return std::atan2(value1, value2);
    }

    inline constexpr static Type asin(Type value){
        return std::asin(value);
    }
    inline constexpr static Type acos(Type value){
        return std::acos(value);
    }
    inline constexpr static Type atan(Type value){
        return std::atan(value);
    }
    inline constexpr static Type actan(Type value){
        algorithm::pi_on_2<Type> - std::atan(value);
    }
};


}

#endif // MATH_ALGORITHM_H
