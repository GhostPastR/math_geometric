#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <algorithm>
#include <cassert>
#include <format>
#include <iostream>

#include "../iterator/matrix_iterator.h"
#include "../algorithm/matrix_algorithm.h"

namespace agl {

template<typename Type, size_t Row, size_t Col> requires std::is_floating_point_v<Type> || std::is_integral_v<Type>
class matrix{
public:
    using type = Type;

    using matrix_array = std::array<std::array<Type,Col>, Row>;
    using iterator = matrix_iterator<Type, Row, Col>;
    using const_iterator = matrix_iterator<const Type, Row, Col>;

    using iterator_row = matrix_row_iterator<Type, Row, Col>;
    using const_iterator_row  = matrix_row_iterator<const Type, Row, Col>;

    using iterator_column = matrix_column_iterator<Type, Row, Col>;
    using const_iterator_column = matrix_column_iterator<const Type, Row, Col>;

    constexpr iterator begin(){
        return iterator(std::begin(*data_.begin()));
    }
    constexpr iterator end(){
        return iterator(std::begin(*data_.end()));
    }
    constexpr const_iterator begin() const{
        return const_iterator(std::begin(*data_.begin()));
    }
    constexpr const_iterator end() const{
        return const_iterator(std::begin(*data_.end()));
    }
    constexpr const_iterator cbegin() const{
        return begin();
    }
    constexpr const_iterator cend() const{
        return end();
    }

    constexpr iterator_row begin_row(size_t column = 0){
        return iterator_row(std::next(std::begin(*data_.begin()), column));
    }
    constexpr iterator_row end_row(size_t column = 0){
        return iterator_row(std::next(std::begin(*data_.end()), column));
    }
    constexpr const_iterator_row begin_row(size_t column = 0) const{
        return const_iterator_row(std::next(std::begin(*data_.begin()), column));
    }
    constexpr const_iterator_row end_row(size_t column = 0) const{
        return const_iterator_row(std::next(std::begin(*data_.end()), column));
    }
    constexpr const_iterator_row cbegin_row(size_t column = 0) const{
        return begin_row(column);
    }
    constexpr const_iterator_row cend_row(size_t column = 0) const{
        return end_row(column);
    }

    constexpr iterator_column begin_column(size_t row = 0){
        return iterator_column(std::begin(*std::next(data_.begin(), row)));
    }
    constexpr iterator_column end_column(size_t row = 0){
        return iterator_column(std::next(std::begin(*std::next(data_.begin(), row)), Col));
    }
    constexpr const_iterator_column begin_column(size_t row = 0) const{
        return const_iterator_column(std::begin(*std::next(data_.begin(), row)));
    }
    constexpr const_iterator_column end_column(size_t row = 0) const{
        return const_iterator_column(std::next(std::begin(*std::next(data_.begin(), row)), Col));
    }
    constexpr const_iterator_column cbegin_column(size_t row = 0) const{
        return begin_column(row);
    }
    constexpr const_iterator_column cend_column(size_t row = 0) const{
       return end_column(row);
    }

    constexpr matrix(){
        std::ranges::fill(*this, Type{});
    }
    constexpr matrix(std::initializer_list<Type> list){
        if(list.size() < Row * Col){
            std::copy(list.begin(), list.end(), begin());
            std::fill(std::next(begin(), list.size()), end(), Type{});
        }
        else{
            std::copy(list.begin(), std::next(list.begin(), Row * Col), begin());
        }
    }

    constexpr size_t rows() const{
        return Row;
    }
    constexpr size_t columns() const{
        return Col;
    }

    constexpr matrix_array get(){
        return data_;
    }

    constexpr std::array<Type, Col> row(size_t r) const{
        if(r >= Row){
            throw std::logic_error(std::format("Index error row = {}", r));
        }
        std::array<Type, Col> array;
        std::ranges::copy(begin_column(r), end_column(r), std::begin(array));
        return array;
    }
    constexpr std::array<Type, Row> column(size_t c) const{
        if(c >= Col){
            throw std::logic_error(std::format("Index error row = {}", c));
        }
        std::array<Type, Row> array;
        std::ranges::transform(begin_row(c), end_row(c), std::begin(array), [](const auto &item){
            return item;
        });
        return array;
    }

    constexpr void swap_row(size_t row1, size_t row2){
        if(row1 >= Row){
            throw std::logic_error(std::format("Index error row = {}", row1));
        }
        if(row2 >= Row){
            throw std::logic_error(std::format("Index error row = {}", row2));
        }
        data_[row1].swap(data_[row2]);
    }
    constexpr void swap_column(size_t col1, size_t col2){
        if(col1 >= Col){
            throw std::logic_error(std::format("Index error row = {}", col1));
        }
        if(col2 >= Col){
            throw std::logic_error(std::format("Index error row = {}", col2));
        }
        std::swap_ranges(begin_row(col1), end_row(col1), begin_row(col2));
    }

    constexpr void copy_row(size_t row1, size_t row2){
        if(row1 >= Row){
            throw std::logic_error(std::format("Index error row = {}", row1));
        }
        if(row2 >= Row){
            throw std::logic_error(std::format("Index error row = {}", row2));
        }
        data_[row1] = data_[row2];
    }
    constexpr void copy_row(size_t row, const std::array<Type, Col> &array){
        if(row >= Row){
            throw std::logic_error(std::format("Index error row = {}", row));
        }
        data_[row] = array;
    }
    constexpr void copy_column(size_t col1, size_t col2){
        if(col1 >= Col){
            throw std::logic_error(std::format("Index error row = {}", col1));
        }
        if(col2 >= Col){
            throw std::logic_error(std::format("Index error row = {}", col2));
        }
        std::ranges::copy(begin_row(col2), end_row(col2), begin_row(col1));
    }
    constexpr void copy_column(size_t col, const std::array<Type, Row> &array){
        if(col >= Col){
            throw std::logic_error(std::format("Index error row = {}", col));
        }
        std::ranges::copy(array, begin_row(col));
    }

    constexpr Type &value(size_t r, size_t c){
        if((r >= Row) || (c >= Col)){
            throw std::logic_error(std::format("Index error row = {}, column = {}", r, c));
        }
        return data_.at(r).at(c);
    }
    constexpr Type value(size_t r, size_t c) const{
        if((r >= Row) || (c >= Col)){
            throw std::logic_error(std::format("Index error row = {}, column = {}", r, c));
        }
        return data_.at(r).at(c);
    }

    constexpr Type determinant() const requires (Row == Col){
        return matrix_algo::determinant(*this);
    }

    constexpr matrix<Type,Col,Row> transposed() const{
        return matrix_algo::transposed(*this);
    }

    constexpr friend auto operator+(const matrix<Type, Row, Col> &m1, const matrix<Type, Row, Col> &m2) -> matrix<Type, Row, Col>{
        matrix<Type, Row, Col> temp;
        std::ranges::transform(m1, m2, temp.begin(), std::plus{});
        return temp;
    }

    constexpr friend auto operator-(const matrix<Type, Row, Col> &m1, const matrix<Type, Row, Col> &m2) -> matrix<Type, Row, Col>{
        matrix<Type, Row, Col> temp;
        std::ranges::transform(m1, m2, temp.begin(), std::minus{});
        return temp;
    }

    template<typename Value, size_t Col2> requires std::is_floating_point_v<Value> || std::is_integral_v<Value>
    constexpr friend auto operator*(const matrix<Type, Row, Col> &m1, const matrix<Value, Col, Col2> &m2) -> matrix<Type, Row, Col2>{
        return matrix_algo::mul(m1,m2);
    }

    template<typename Value> requires std::is_floating_point_v<Value> || std::is_integral_v<Value>
    constexpr friend auto operator*(const Value &value, matrix m) -> matrix{
        std::ranges::transform(m, m.begin(), [value](const auto &item){
            return item * value;
        });
        return m;
    }

    template<typename Value> requires std::is_floating_point_v<Value> || std::is_integral_v<Value>
    constexpr friend auto operator*(matrix m, const Value &value) -> matrix{
        return value * m;
    }

    constexpr friend bool operator==(const matrix &m1, const matrix &m2){
        if constexpr(std::is_floating_point_v<Type>){
            return std::ranges::equal(m1, m2, [](const auto &i, const auto &j){
                return algorithm::compare(i, j);
            });
        }
        else{
            return std::ranges::equal(m1, m2);
        }
    }
    constexpr friend bool operator!=(const matrix &m1, const matrix &m2){
        return !(m1 == m2);
    }

    constexpr friend std::ostream& operator<<(std::ostream& os, const matrix &m){
        for(auto &i : m.data_){
            std::copy(i.begin(), i.end(), std::ostream_iterator<Type>(os, " "));
            os << "\n";
        }
        return os;
    }

private:
    matrix_array data_;
};

}

#endif // MATRIX_H
