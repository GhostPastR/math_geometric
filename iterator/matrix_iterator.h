#ifndef MATRIX_ITERATOR_H
#define MATRIX_ITERATOR_H

#include <iterator>

template<typename Type, size_t Row, size_t Column>
struct matrix_iterator{
    using iterator_category = std::contiguous_iterator_tag;
    using value_type = Type;
    using difference_type = std::ptrdiff_t;
    using pointer = Type*;
    using reference = Type&;

    matrix_iterator() = default;
    matrix_iterator(pointer p) : p_(p){}
    matrix_iterator(const matrix_iterator &it): p_(it.p_){}

    pointer get() const{
        return p_;
    }

    bool operator!=(const matrix_iterator& other) const{
        return p_ != other.p_;
    }
    bool operator==(const matrix_iterator& other) const{
        return p_ == other.p_;
    }
    reference operator*(){
        return *p_;
    }
    reference operator*() const{
        return *p_;
    }
    pointer operator->(){
        return p_;
    }

    matrix_iterator& operator++(){
        ++p_;
        return *this;
    }
    matrix_iterator operator++(int){
        matrix_iterator tmp = *this;
        ++(*this);
        return tmp;
    }
    matrix_iterator& operator--(){
        --p_;
        return *this;
    }

    matrix_iterator &operator+=(int value){
        p_ += value;
        return *this;
    }

    friend int operator-(const matrix_iterator& temp1, const matrix_iterator& temp2){
        return temp1.p_ - temp2.p_;
    }

private:
    pointer p_{};
};



template<typename Type, size_t Row, size_t Column>
struct matrix_row_iterator{
    using iterator_category = std::random_access_iterator_tag;
    using value_type = Type;
    using difference_type = std::ptrdiff_t;
    using pointer = Type*;
    using reference = Type&;

    matrix_row_iterator() = default;
    matrix_row_iterator(pointer p) : p_(p){}
    matrix_row_iterator(const matrix_row_iterator &it): p_(it.p_){}

    pointer get() const{
        return p_;
    }

    bool operator!=(const matrix_row_iterator& other) const{
        return p_ != other.p_;
    }
    bool operator==(const matrix_row_iterator& other) const{
        return p_ == other.p_;
    }
    auto operator<=>(const matrix_row_iterator& other) const{
        return p_ <=> other.p_;
    }
    reference operator*(){
        return *p_;
    }
    reference operator*() const{
        return *p_;
    }
    pointer operator->(){
        return p_;
    }

    matrix_row_iterator& operator++(){
        p_ += Column;
        return *this;
    }
    matrix_row_iterator operator++(int){
        matrix_row_iterator tmp = *this;
        ++(*this);
        return tmp;
    }
    matrix_row_iterator& operator--(){
        p_ -= Column;
        return *this;
    }
    matrix_row_iterator operator--(int){
        matrix_row_iterator tmp = *this;
        --(*this);
        return tmp;
    }

    matrix_row_iterator &operator+=(int value){
        p_ += Column * value;
        return *this;
    }
    matrix_row_iterator &operator-=(int value){
        p_ += Column * value;
        return *this;
    }

    friend int operator-(const matrix_row_iterator& temp1, const matrix_row_iterator& temp2){
        return (temp1.p_ - temp2.p_) / Column;
    }

private:
    pointer p_{};
};



template<typename ValueType, size_t Row, size_t Column>
struct matrix_column_iterator{
    using iterator_category = std::contiguous_iterator_tag;
    using value_type = ValueType;
    using difference_type = std::ptrdiff_t;
    using pointer = ValueType*;
    using reference = ValueType&;

    matrix_column_iterator() = default;
    matrix_column_iterator(pointer p) : p_(p){}
    matrix_column_iterator(const matrix_column_iterator &it): p_(it.p_){}

    pointer get() const{
        return p_;
    }

    bool operator!=(const matrix_column_iterator& other) const{
        return p_ != other.p_;
    }
    bool operator==(const matrix_column_iterator& other) const{
        return p_ == other.p_;
    }
    auto operator<=>(const matrix_column_iterator& other) const{
        return p_ <=> other.p_;
    }
    reference operator*(){
        return *p_;
    }
    reference operator*() const{
        return *p_;
    }
    pointer operator->(){
        return p_;
    }

    matrix_column_iterator& operator++(){
        ++p_;
        return *this;
    }
    matrix_column_iterator operator++(int){
        matrix_column_iterator tmp = *this;
        ++(*this);
        return tmp;
    }
    matrix_column_iterator& operator--(){
        --p_;
        return *this;
    }
    matrix_column_iterator operator--(int){
        matrix_column_iterator tmp = *this;
        --(*this);
        return tmp;
    }

    matrix_column_iterator &operator+=(int value){
        p_ += value;
        return *this;
    }
    matrix_column_iterator &operator-=(int value){
        p_ += value;
        return *this;
    }

    friend int operator-(const matrix_column_iterator& temp1, const matrix_column_iterator& temp2){
        return temp1.p_ - temp2.p_;
    }

private:
    pointer p_{};
};



template<typename Type, size_t Row, size_t Column>
auto convert_interator(matrix_row_iterator<Type,Row,Column> iterator) -> matrix_iterator<Type,Row,Column>{
    return matrix_iterator<Type,Row,Column>(iterator.get());
}

template<typename Type, size_t Row, size_t Column>
auto convert_interator(matrix_column_iterator<Type,Row,Column> iterator) -> matrix_iterator<Type,Row,Column>{
    return matrix_iterator<Type,Row,Column>(iterator.get());
}

template<typename Type, size_t Row, size_t Column>
auto convert_row_interator(matrix_iterator<Type,Row,Column> iterator) -> matrix_row_iterator<Type,Row,Column>{
    return matrix_row_iterator<Type,Row,Column>(iterator.get());
}

template<typename Type, size_t Row, size_t Column>
auto convert_row_interator(matrix_column_iterator<Type,Row,Column> iterator) -> matrix_row_iterator<Type,Row,Column>{
    return matrix_row_iterator<Type,Row,Column>(iterator.get());
}

template<typename Type, size_t Row, size_t Column>
auto convert_column_interator(matrix_iterator<Type,Row,Column> iterator) -> matrix_column_iterator<Type,Row,Column>{
    return matrix_column_iterator<Type,Row,Column>(iterator.get());
}

template<typename Type, size_t Row, size_t Column>
auto convert_column_interator(matrix_row_iterator<Type,Row,Column> iterator) -> matrix_column_iterator<Type,Row,Column>{
    return matrix_column_iterator<Type,Row,Column>(iterator.get());
}

#endif // MATRIX_ITERATOR_H
