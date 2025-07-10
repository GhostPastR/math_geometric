#ifndef VECTOR_H
#define VECTOR_H

#include <array>
#include <algorithm>
#include <cassert>
// #include <format>
// #include <iostream>

// #include "../iterator/matrix_iterator.h"
#include "../algorithm/matrix_algorithm.h"

namespace agl {

template<typename Type, size_t Count> requires std::is_floating_point_v<Type> || std::is_integral_v<Type>
class vector{
public:
    using type = Type;

    constexpr auto begin(){
        return array_.begin();
    }
    constexpr auto end(){
        return array_.end();
    }
    constexpr auto begin() const{
        return array_.begin();
    }
    constexpr auto end() const{
        return array_.end();
    }
    constexpr auto cbegin() const{
        return array_.cbegin();
    }
    constexpr auto cend() const{
        return array_.cend();
    }

    constexpr vector(){
        std::ranges::fill(*this, Type{});
    }
    constexpr vector(std::initializer_list<Type> list){
        std::ranges::copy(list, begin());
        std::ranges::fill(std::next(begin(), list.size()), end(), Type{});
    }

    constexpr Type get(int index) const{
        return array_[index];
    }

    constexpr auto module() const{
        return matrix_algo::module(*this);
    }

    constexpr friend auto operator+(const vector<Type, Count> &vector_1, const vector<Type, Count> &vector_2) -> vector<Type, Count>{
        vector<Type, Count> temp;
        std::ranges::transform(vector_1, vector_2, temp.begin(), std::plus{});
        return temp;
    }

    constexpr friend auto operator-(const vector<Type, Count> &vector_1, const vector<Type, Count> &vector_2) -> vector<Type, Count>{
        vector<Type, Count> temp;
        std::ranges::transform(vector_1, vector_2, temp.begin(), std::minus{});
        return temp;
    }

    template<typename Value> requires std::is_floating_point_v<Value> || std::is_integral_v<Value>
    constexpr friend auto operator*(const Value &value, vector v) -> vector{
        std::ranges::transform(v, v.begin(), [value](const auto &item){
            return item * value;
        });
        return v;
    }

    template<typename Value> requires std::is_floating_point_v<Value> || std::is_integral_v<Value>
    constexpr friend auto operator*(vector v, const Value &value) -> vector{
        return value * v;
    }

    constexpr friend bool operator==(const vector &vector_1, const vector &vector_2){
        if constexpr(std::is_floating_point_v<Type>){
            return std::ranges::equal(vector_1, vector_2, [](const auto &i, const auto &j){
                return algorithm::compare(i, j);
            });
        }
        else{
            return std::ranges::equal(vector_1, vector_2);
        }

    }
    constexpr friend bool operator!=(const vector &vector_1, const vector &vector_2){
        return !(vector_1 == vector_2);
    }

    constexpr friend std::ostream& operator<<(std::ostream& os, const vector &vec){
        std::ranges::copy(vec.begin(), vec.end(), std::ostream_iterator<Type>(os, " "));
        return os;
    }

private:
    std::array<Type, Count> array_;
};

}

#endif // VECTOR_H
