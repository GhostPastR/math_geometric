#ifndef MATRIX_ALGORITHM_H
#define MATRIX_ALGORITHM_H

#include <algorithm>
#include <iterator>
#include <numeric>
#include <ranges>

#include "../iterator/matrix_iterator.h"
#include "math_algorithm.h"

template<template<typename, size_t, size_t> class Type, typename T, size_t N, size_t M>
concept c_matrix = requires(Type<T,N,M> temp){
    typename Type<T,N,M>::type;
    temp.begin();
    temp.end();
    temp.cbegin();
    temp.cend();

    temp.begin_row();
    temp.end_row();
    temp.cbegin_row();
    temp.cend_row();

    temp.begin_column();
    temp.end_column();
    temp.cbegin_column();
    temp.cend_column();
};

namespace matrix_algo{

template<template<typename, size_t, size_t> class Matrix, std::floating_point Type> requires c_matrix<Matrix, Type, 1,1>
auto determinant(Matrix<Type,1,1> m) -> Matrix<Type,1,1>::type{
    return *m.begin();
}

template<template<typename, size_t, size_t> class Matrix, std::floating_point Type> requires c_matrix<Matrix, Type, 2,2>
auto determinant(Matrix<Type,2,2> m) -> Matrix<Type,2,2>::type{
    auto begin = m.begin();
    auto end = m.end();
    return (*begin) * (*std::prev(end)) - (*std::next(begin)) * (*std::prev(end,2));
}

template<std::floating_point Type>
Type determinant(const Type &a11, const Type &a12, const Type &a21, const Type &a22){
    return a11 * a22 - a12 * a21;
}

// Type det = 1.0;
// for (int i = 0; i < m.rows(); i++) {
//     int pivot = i;
//     for (int j = i + 1; j < m.rows(); j++) {
//         if (abs(m.value(j,i)) > abs(m.value(pivot, i))) {
//             pivot = j;
//         }
//     }
//     if (pivot != i) {
//         m.swap_row(i, pivot);
//         det *= -1;
//     }
//     if (m.value(i, i) == 0) {
//         return 0;
//     }
//     det *= m.value(i, i);
//     for (int j = i + 1; j < m.rows(); j++) {
//         Type factor = m.value(j, i) / m.value(i, i);
//         for (int k = i + 1; k < m.rows(); k++) {
//             m.value(j, k) -= factor * m.value(i, k);
//         }
//     }
// }
// return det;

template<template<typename, size_t, size_t> class Matrix, std::floating_point Type, size_t N> requires c_matrix<Matrix, Type, N, N>
auto determinant(Matrix<Type,N,N> m) -> Matrix<Type,N,N>::type{    
    auto numbers = std::ranges::iota_view(size_t(), N);
    return std::accumulate(numbers.begin(), numbers.end(), 1.0, [&m](auto sum, auto i){
        auto pivot = std::distance(m.begin_row(i), std::max_element(std::next(m.begin_row(i), i), m.end_row(i)));
        if (pivot != i) {
            m.swap_row(i, pivot);
            sum *= -1;
        }
        if (algorithm::compare(m.value(i, i), Type{})) {
            return Type{};
        }
        sum *= m.value(i, i);

        auto begin_row = convert_row_interator(std::next(m.begin_column(i + 1), i));
        for(auto item = begin_row; item < m.end_row(i); ++item){
            Type factor = *item / m.value(i, i);
            auto in = std::next(convert_column_interator(std::prev(begin_row)));
            auto out = std::next(convert_column_interator(item));
            std::transform(in, m.end_column(i), out, out, [factor](const auto &a, const auto &b){
                return b - factor * a;
            });
        }
        return sum;
    });
}


// for (int i = 0; i < R1; i++) {
//     for (int j = 0; j < C2; j++) {
//         for (int k = 0; k < R2; k++) {
//             temp.value(i, j) += m1.value(i, k) * m2.value(k, j);
//         }
//     }
// }
template<template<typename, size_t, size_t> class Matrix, typename Value1, typename Value2, size_t R1, size_t C1, size_t R2, size_t C2>
    requires c_matrix<Matrix, Value1, R1, C1> && c_matrix<Matrix, Value2, R2, C2> && (C1 == R2)
             && (std::is_floating_point_v<Value1> || std::is_integral_v<Value1>)
             && (std::is_floating_point_v<Value2> || std::is_integral_v<Value2>)
auto mul(const Matrix<Value1, R1, C1> &m1, const Matrix<Value2, R2, C2> &m2) -> Matrix<Value1, R1, C2>{
    Matrix<Value1, R1, C2> temp;
    std::ranges::for_each(std::ranges::iota_view(size_t(), R1), [&temp,&m1,&m2](auto i){
        std::ranges::transform(std::ranges::iota_view(size_t(), C2), temp.begin_column(i), [&m1,&m2,i](auto j){
            return std::inner_product(m1.begin_column(i), m1.end_column(i), m2.begin_row(j), 0);
        });
    });
    return temp;
}

template<template<typename, size_t, size_t> class Matrix, typename Value, size_t R, size_t C>
    requires c_matrix<Matrix, Value, R, C> && (std::is_floating_point_v<Value> || std::is_integral_v<Value>)
auto transposed(const Matrix<Value, R, C> &matrix) -> Matrix<Value,C,R>{
    Matrix<Value,C,R> temp;
    std::ranges::for_each(std::ranges::iota_view(size_t{}, R), [&matrix, &temp](const auto &i){
        std::ranges::copy(matrix.cbegin_column(i), matrix.cend_column(i), temp.begin_row(i));
    });
    return temp;
}

template<template<typename, size_t, size_t>  class Matrix, typename Value, size_t N>
    requires c_matrix<Matrix, Value, N, N> && (std::is_floating_point_v<Value> || std::is_integral_v<Value>)
auto identity_matrix() -> Matrix<Value,N,N>{
    Matrix<Value, N, N> temp;
    std::ranges::for_each(std::ranges::iota_view(size_t(), N), [&temp](auto i){
        temp.value(i,i) = Value(1);
    });
    return temp;
}

template<template<typename, size_t, size_t>  class Matrix, typename Value, size_t N>
    requires c_matrix<Matrix, Value, N, N> && (std::is_floating_point_v<Value> || std::is_integral_v<Value>) && (N > 1)
auto minor(const Matrix<Value,N,N> &matrix, size_t row, size_t column) -> Matrix<Value,N-1,N-1>{
    Matrix<Value, N-1, N-1> temp;
    auto numbers = std::ranges::iota_view(size_t(), N * N) | std::ranges::views::filter([row,column](const auto &i){
        return (i % N != column) && !algorithm::interval_left_strict(i, row * N, (row + 1) * N);
    });
    std::ranges::transform(numbers, temp.begin(), [&matrix](auto i){
        return *std::next(matrix.begin(), i);
    });
    return temp;
}

template<template<typename, size_t, size_t>  class Matrix, typename Value, size_t N>
    requires c_matrix<Matrix, Value, N, N> && (std::is_floating_point_v<Value> || std::is_integral_v<Value>) && (N > 1)
auto matrix_algebraic_additions(const Matrix<Value, N, N> &matrix){
    Matrix<Value, N, N> temp;
    std::ranges::transform(std::ranges::iota_view(size_t(), N * N), temp.begin(), [&matrix](auto i){
        int sign = (i % 2 == 0) ? 1 : -1;
        return sign * determinant(minor(matrix, i / N, i % N));
    });
    return temp;
}


template<template<typename, size_t, size_t>  class Matrix, typename Value, size_t N>
    requires c_matrix<Matrix, Value, N, N> && (std::is_floating_point_v<Value> || std::is_integral_v<Value>) && (N > 1)
auto inverse_matrix(const Matrix<Value, N, N> &matrix) -> std::optional<Matrix<Value, N, N>>{
    auto det = determinant(matrix);
    if(algorithm::compare(det, 0)){
        return std::nullopt;
    }
    return (1.0 / det) * transposed(matrix_algebraic_additions(matrix));
}

template<template<typename, size_t, size_t>  class Matrix, typename Value, size_t R, size_t C>
    requires c_matrix<Matrix, Value, R, C> && (std::is_floating_point_v<Value> || std::is_integral_v<Value>)
size_t rang(Matrix<Value, R, C> matrix){
    int rank = C;
    for (int row = 0; row < rank; row++){
        if (!algorithm::compare(matrix.value(row,row), 0)){
            for(auto item = matrix.begin_row(row); item < matrix.end_row(row); ++item){
                auto col = std::distance(matrix.begin_row(row), item);
                if (col != row){
                    auto factor = *item / matrix.value(row,row);
                    auto out = matrix.begin_column(col);
                    std::transform(matrix.begin_column(row), matrix.end_column(row), out, out, [factor](const auto &a, const auto &b){
                        return b - factor * a;
                    });
                }
            }
        }
        else{
            auto reduse = std::ranges::find_if(std::next(matrix.begin_row(row), row + 1), matrix.end_row(row), [](const auto &i){
                return !algorithm::compare(i, 0);
            });
            if(reduse != matrix.end_row(row)){
                matrix.swap_row(row, std::distance(matrix.begin_row(row), reduse));
            }
            else{
                rank--;
                matrix.copy_column(row, rank);
            }
            row--;
        }
    }
    return rank;
}

}

#endif // MATRIX_ALGORITHM_H
