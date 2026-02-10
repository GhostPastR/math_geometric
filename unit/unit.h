#ifndef UNIT_SYSTEM_H
#define UNIT_SYSTEM_H

#include "system/traits.h"
#include "algorithm/math_algorithm.h"
#include <format>
#include <utility>
#include <tuple>

namespace agl::unit {

template <int M, int K, int S, int T>
struct enum_unit{
    enum{
        length = M,
        mass = K,
        time = S,
        temperature = T
    };
};

struct derivative : std::integer_sequence<int,  0>{};
struct basic : std::integer_sequence<int,  1>{};

template<class T>
concept c_basic_value = std::is_same_v<T, basic> || std::is_same_v<T, derivative>;

template<class T>
concept c_type_value = std::is_floating_point_v<T>;

template<class V, int M, int K, int S, int T>
concept c_unit_value = std::is_same_v<V, enum_unit<M,K,S,T>>;

template<class Prefix, class UnitValue>
concept c_unit_prefix = std::is_same_v<UnitValue, typename Prefix::Type>;



template<class UnitValue, double unit>
    requires c_unit_value<UnitValue,UnitValue::length, UnitValue::mass, UnitValue::time, UnitValue::temperature>
struct measure_unit final : std::integer_sequence<double,  unit>{
    using Type = UnitValue;
    inline constexpr static double unit_value = unit;
};

template<class UnitValue, double unit1, double unit2, double unit3>
    requires c_unit_value<UnitValue,UnitValue::length, UnitValue::mass, UnitValue::time, UnitValue::temperature>
struct measure_unit_2 final : std::integer_sequence<double,  unit1, unit2, unit3>{
    using Type = UnitValue;
    inline constexpr static double unit_value_1 = unit1;
    inline constexpr static double unit_value_2 = unit2;
    inline constexpr static double unit_value_3 = unit3;
};

template<typename UnitPrefix, c_type_value TypeValue, typename UnitValue, c_basic_value BasicValue>
    requires(c_unit_value<UnitValue,UnitValue::length,UnitValue::mass, UnitValue::time, UnitValue::temperature>
             && c_unit_prefix<UnitPrefix, UnitValue>)
struct Convert final{
    constexpr static TypeValue convert(TypeValue value);
};

template<typename UnitValue, c_type_value TypeValue>
    requires c_unit_value<UnitValue,UnitValue::length,UnitValue::mass, UnitValue::time, UnitValue::temperature>
struct Value final{
    using type_value = TypeValue;
    using unit_value = UnitValue;

    constexpr Value() {}
    constexpr explicit Value(TypeValue value) : value_(value){}

    template<typename UnitPrefix>
    constexpr void set_value(TypeValue value){
        if constexpr(std::is_same_v<UnitValue, typename UnitPrefix::Type>){
            value_ = Convert<UnitPrefix, TypeValue, UnitValue, basic>::convert(value);
        }
        else{
            static_assert(false, "Error UnitPrefix");
        }
    }

    constexpr auto &value() const{
        return value_;
    }

    template<typename UnitPrefix>
    constexpr auto value() const{
        if constexpr(std::is_same_v<UnitValue, typename UnitPrefix::Type>){
            return Convert<UnitPrefix, TypeValue, UnitValue, derivative>::convert(value_);
        }
        else{
            static_assert(false, "Error UnitPrefix");
        }
    }

    constexpr const Value &operator+=(const Value &value){
        value_ += value.value_;
        return *this;
    }

    constexpr const Value &operator-=(const Value &value){
        value_ -= value.value_;
        return *this;
    }

    template<std::floating_point Type>
    constexpr const Value &operator+=(const Type &value){
        value_ += value;
        return *this;
    }

    template<std::floating_point Type>
    constexpr const Value &operator-=(const Type &value){
        value_ -= value;
        return *this;
    }

    friend constexpr bool operator==(const Value &value1, const Value &value2){
        return algorithm::compare(value1.value_, value2.value_);
    }

    friend constexpr auto operator<=>(const Value &value1, const Value &value2){
        return value1.value_ <=> value2.value_;
    }

    friend constexpr Value operator+(const Value &value1, const Value &value2){
        return Value(value1.value_ + value2.value_);
    }

    friend constexpr Value operator-(const Value &value1, const Value &value2){
        return Value(value1.value_ - value2.value_);
    }

    friend constexpr Value operator-(const Value &value){
        return Value(-value.value_);
    }

    template<std::floating_point Type>
    friend constexpr Value operator+(const Value &value1, const Type &value2){
        return Value(value1.value_ + value2);
    }

    template<std::floating_point Type>
    friend constexpr Value operator-(const Value &value1, const Type &value2){
        return Value(value1.value_ - value2);
    }

    template<typename D1, typename D2>
    friend auto operator*(Value<D1, TypeValue> value1, Value<D2, TypeValue> value2);

    template<typename D1, typename D2>
    friend auto operator/(Value<D1, TypeValue> value1, Value<D2, TypeValue> value2);

    template<typename Type> requires (std::floating_point<Type> || std::integral<Type>)
    friend constexpr Value operator*(const Value &value1, const Type &value2){
        return Value(value1.value_ * value2);
    }

    template<typename Type> requires (std::floating_point<Type> || std::integral<Type>)
    friend constexpr Value operator/(const Value &value1, const Type &value2){
        return Value(value1.value_ / value2);
    }

private:
    TypeValue value_{};
};

template<int M1, int K1, int S1, int T1, int M2, int K2, int S2, int T2>
auto multiply(enum_unit<M1,K1,S1,T1>, enum_unit<M2,K2,S2,T2>) -> decltype(enum_unit<M1+M2, K1+K2, S1+S2, T1+T2>());

template<int M1, int K1, int S1, int T1, int M2, int K2, int S2, int T2>
auto divide(enum_unit<M1,K1,S1,T1>, enum_unit<M2,K2,S2,T2>) -> decltype(enum_unit<M1-M2, K1-K2, S1-S2, T1-T2>());

template<typename D1, typename D2, typename Type>
auto operator*(Value<D1, Type> value1, Value<D2, Type> value2){
    using D = decltype(multiply(std::declval<D1>(), std::declval<D2>()));
    return Value<D, Type>(value1.value_ * value2.value_);
}

template<typename D1, typename D2, typename Type>
auto operator/(Value<D1, Type> value1, Value<D2, Type> value2){
    using D = decltype(divide(std::declval<D1>(), std::declval<D2>()));
    return Value<D, Type>(value1.value_ / value2.value_);
}

template<typename UnitPrefix, typename Tuple, std::size_t L = std::tuple_size_v<Tuple> - 1>
constexpr bool find_type(const Tuple &tuple){
    if constexpr(L == 0){
        return std::is_same_v<std::remove_cvref_t<decltype(std::get<0>(tuple))>, UnitPrefix>;
    }
    else if constexpr (L > 0){
        if constexpr(std::is_same_v<std::remove_cvref_t<decltype(std::get<L>(tuple))>, UnitPrefix>){
            return true;
        }
        return find_type<UnitPrefix, Tuple, L - 1>(tuple);
    }
    else{
        static_assert(false, "L < 0");
    }
}

}

template<typename UnitValue, agl::unit::c_type_value TypeValue>
    requires agl::unit::c_unit_value<UnitValue,UnitValue::length,UnitValue::mass, UnitValue::time, UnitValue::temperature>
struct agl::traits::type<agl::unit::Value<UnitValue, TypeValue>>{
    using type_value = TypeValue;
};

template<typename UnitValue, agl::unit::c_type_value TypeValue>
    requires agl::unit::c_unit_value<UnitValue,UnitValue::length,UnitValue::mass, UnitValue::time, UnitValue::temperature>
struct agl::traits::value<agl::unit::Value<UnitValue, TypeValue>>{
    inline constexpr static auto get(const agl::unit::Value<UnitValue, TypeValue> &temp){
        return temp.value();
    }
};

template<typename UnitValue, agl::unit::c_type_value TypeValue>
    requires agl::unit::c_unit_value<UnitValue,UnitValue::length,UnitValue::mass, UnitValue::time, UnitValue::temperature>
struct agl::traits::make<agl::unit::Value<UnitValue, TypeValue>>{
    template<typename Value>
    inline constexpr static auto apply(const Value& value){
        return agl::unit::Value<UnitValue, TypeValue>(value);
    }
};

template<typename UnitValue, agl::unit::c_type_value TypeValue>
    requires agl::unit::c_unit_value<UnitValue,UnitValue::length,UnitValue::mass, UnitValue::time, UnitValue::temperature>
struct std::formatter<agl::unit::Value<UnitValue, TypeValue>> {
    std::formatter<std::string> _formatter;
    constexpr auto parse(std::format_parse_context& parse_context) {
        return _formatter.parse(parse_context);
    }

    auto format(const agl::unit::Value<UnitValue, TypeValue>& value, std::format_context& format_context) const {
        return _formatter.format(std::format("{}", value.value()), format_context);
    }
};

template<typename UnitValue, agl::unit::c_type_value TypeValue>
    requires agl::unit::c_unit_value<UnitValue,UnitValue::length,UnitValue::mass, UnitValue::time, UnitValue::temperature>
constexpr std::ostream& operator<<(std::ostream& os, const agl::unit::Value<UnitValue, TypeValue>& value){
    os << std::format("{}", value);
    return os;
}





#define OPERATOR_QM(VALUE, PREFIX, UNIT_PREFIX) \
inline constexpr VALUE operator ""_##PREFIX (long double value){ \
        return VALUE(agl::unit::Convert<UNIT_PREFIX, VALUE::type_value, VALUE::unit_value, agl::unit::basic>::convert(value)); \
} \
\
inline constexpr VALUE operator ""_##PREFIX (unsigned long long value){ \
        return VALUE(agl::unit::Convert<UNIT_PREFIX, VALUE::type_value, VALUE::unit_value, agl::unit::basic>::convert(value)); \
} \

#define CASE_VALUE(PREFIX, UNIT_STR, UNIT_TEMLATE) \
if(attributes == PREFIX){ \
        return std::format_to(out, "{}_"#UNIT_STR, value.value<UNIT_TEMLATE>()); \
} \

#endif // UNIT_SYSTEM_H
