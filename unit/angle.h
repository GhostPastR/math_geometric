#ifndef ANGLE_H
#define ANGLE_H

#include "../algorithm/math_algorithm.h"
#include "../system/system_concept.h"

template<std::floating_point Type, c_function_angle<Type> ClassFunc = algorithm::function_angle<Type>>
class angle_impl{
public:
    using type_angle = Type;

    constexpr angle_impl() = default;

    constexpr angle_impl(Type radian){
        setValue(radian);
    }

    template<std::floating_point T>
    constexpr angle_impl(const angle_impl<T> &value){
        radian_ = value.radian();
    }

    constexpr Type radian() const{
        return radian_;
    }
    constexpr Type degrees() const{
        return radian_ / algorithm::pi_on_180<Type>;
    }

    constexpr void setValue(Type radian){
        radian_ = radian;
    }

    constexpr angle_impl &asin(const Type &value){
        if (algorithm::interval_strict(value, -1.0, 1.0)){
            radian_ = algorithm::function_angle<Type>::asin(value);
            return *this;
        }
        else{
            assert(false && "value < -1 || value > 1");
        }
    }
    constexpr angle_impl &acos(const Type &value){
        if(algorithm::interval_strict(value, -1.0, 1.0)){
            radian_ = algorithm::function_angle<Type>::acos(value);
            return *this;
        }
        else{
            assert(false && "value < -1 || value > 1");
        }

    }
    constexpr angle_impl &atan(const Type &value){
        radian_ = algorithm::function_angle<Type>::atan(value);
        return *this;
    }
    constexpr angle_impl &actan(const Type &value){
        radian_ = algorithm::pi_on_2<Type> + algorithm::function_angle<Type>::atan(-value);
        return *this;
    }

    constexpr Type sin() const{
        return algorithm::function_angle<Type>::sin(radian_);
    }
    constexpr Type cos() const{
        return algorithm::function_angle<Type>::cos(radian_);
    }
    constexpr Type tan() const{
        return algorithm::function_angle<Type>::tan(radian_);
    }
    constexpr Type ctan() const{
        return 1.0 / algorithm::function_angle<Type>::tan(radian_);
    }

    template<std::floating_point Type_Value, c_function_angle<Type_Value> Algo_Value = algorithm::function_angle<Type_Value>>
    constexpr angle_impl &operator+=(const angle_impl<Type_Value, Algo_Value> &angle){
        radian_ += angle.radian();
        return *this;
    }

    template<std::floating_point Type_Value, c_function_angle<Type_Value> Algo_Value = algorithm::function_angle<Type_Value>>
    constexpr angle_impl &operator-=(const angle_impl<Type_Value, Algo_Value> &angle){
        radian_ -= angle.radian();
        return *this;
    }

    template<std::floating_point T>
    constexpr angle_impl operator=(const angle_impl<T> &value){
        radian_ = value.radian();
        return *this;
    }

    friend constexpr angle_impl operator*(const Type &value, const angle_impl &angle){
        return angle * value;
    }

private:
    Type radian_{};
};

template<std::floating_point Type1, std::floating_point Type2,
         c_function_angle<Type1> Algo1 = algorithm::function_angle<Type1>,
         c_function_angle<Type2> Algo2 = algorithm::function_angle<Type2>>
inline constexpr bool compare(const angle_impl<Type1, Algo1> &value1, const angle_impl<Type2, Algo2> &value2) {
    return algorithm::compare_common(value1.radian(), value2.radian(), algorithm::epsilon<decltype(value1.radian())>);
}

template<std::floating_point Type, c_function_angle<Type> Algo = algorithm::function_angle<Type>>
constexpr auto operator-(const angle_impl<Type, Algo> &value){
    return angle_impl<Type, Algo>(-value.radian());
}

template<std::floating_point Type1, std::floating_point Type2,
         c_function_angle<Type1> Algo1 = algorithm::function_angle<Type1>,
         c_function_angle<Type2> Algo2 = algorithm::function_angle<Type2>>
constexpr auto operator+(const angle_impl<Type1, Algo1> &value1, const angle_impl<Type2, Algo2> &value2){
    return angle_impl<Type1, Algo1>(value1.radian() + value2.radian());
}

template<std::floating_point Type1, std::floating_point Type2,
         c_function_angle<Type1> Algo1 = algorithm::function_angle<Type1>,
         c_function_angle<Type2> Algo2 = algorithm::function_angle<Type2>>
constexpr auto operator-(const angle_impl<Type1, Algo1> &value1, const angle_impl<Type2, Algo2> &value2){
    return angle_impl<Type1, Algo1>(value1.radian() - value2.radian());
}

template<typename T>
concept c_multiplier = std::floating_point<T> || std::integral<T>;

template<std::floating_point Type1, c_multiplier Type2, c_function_angle<Type1> Algo = algorithm::function_angle<Type1>>
constexpr auto operator*(const angle_impl<Type1, Algo> &value1, const Type2 &value2){
    return angle_impl<Type1, Algo>(value1.radian() * value2);
}

template<std::floating_point Type1, c_multiplier Type2, c_function_angle<Type1> Algo = algorithm::function_angle<Type1>>
constexpr auto operator/(const angle_impl<Type1, Algo> &value1, const Type2 &value2){
    return angle_impl<Type1, Algo>(value1.radian() / value2);
}

template<std::floating_point Type1, std::floating_point Type2,
         c_function_angle<Type1> Algo1 = algorithm::function_angle<Type1>,
         c_function_angle<Type2> Algo2 = algorithm::function_angle<Type2>>
constexpr auto operator/(const angle_impl<Type1, Algo1> &value1, const angle_impl<Type2, Algo2> &value2){
    return value1.radian() / value2.radian();
}

template<std::floating_point Type1, std::floating_point Type2,
         c_function_angle<Type1> Algo1 = algorithm::function_angle<Type1>,
         c_function_angle<Type2> Algo2 = algorithm::function_angle<Type2>>
constexpr auto operator<=>(const angle_impl<Type1, Algo1> &value1, const angle_impl<Type2, Algo2> &value2){
    return value1.radian() <=> value2.radian();
}

template<std::floating_point Type1, std::floating_point Type2,
         c_function_angle<Type1> Algo1 = algorithm::function_angle<Type1>,
         c_function_angle<Type2> Algo2 = algorithm::function_angle<Type2>>
constexpr bool operator==(const angle_impl<Type1, Algo1> &value1, const angle_impl<Type2, Algo2> &value2){
    if constexpr(sizeof(Type1) < sizeof(Type2)){
        return algorithm::compare(static_cast<Type2>(value1.radian()), value2.radian());
    }
    else if constexpr(sizeof(Type1) > sizeof(Type2)){
        return algorithm::compare(value1.radian(), static_cast<Type1>(value2.radian()));
    }
    else{
        return algorithm::compare(value1.radian(), value2.radian());
    }
}

constexpr auto operator "" _deg(unsigned long long deg){
    return angle_impl<long double>(deg * algorithm::pi_on_180<long double>);
}

constexpr auto operator "" _rad(unsigned long long rad){
    return angle_impl<long double>(rad);
}

constexpr auto operator "" _deg(long double deg){
    return angle_impl<long double>(deg * algorithm::pi_on_180<long double>);
}

constexpr auto operator "" _rad(long double rad){
    return angle_impl<long double>(rad);
}

template<std::floating_point Type> constexpr static angle_impl<Type> ang_pi_on_180 = angle_impl<Type>(algorithm::pi_on_180<Type>);
template<std::floating_point Type> constexpr static angle_impl<Type> ang_pi_on_2 = angle_impl<Type>(algorithm::pi_on_2<Type>);
template<std::floating_point Type> constexpr static angle_impl<Type> ang_pi_on_4 = angle_impl<Type>(algorithm::pi_on_4<Type>);
template<std::floating_point Type> constexpr static angle_impl<Type> ang_pi_on_6 = angle_impl<Type>(algorithm::pi_on_6<Type>);
template<std::floating_point Type> constexpr static angle_impl<Type> ang_pi = angle_impl<Type>(algorithm::pi<Type>);
template<std::floating_point Type> constexpr static angle_impl<Type> ang_pi_in_3_on_2 = angle_impl<Type>(algorithm::pi_in_3_on_2<Type>);
template<std::floating_point Type> constexpr static angle_impl<Type> ang_pi_in_2 = angle_impl<Type>(algorithm::pi_in_2<Type>);

#endif // ANGLE_H
