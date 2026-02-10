#ifndef ASSERT_H
#define ASSERT_H

#include <type_traits>
#include "tag.h"


namespace agl::assert {

template<typename Type>
consteval bool is_correct(){
    return !std::is_same_v<Type, agl::undefined>;
}

template<typename Type1, typename Type2>
consteval bool is_correct_compare(){
    return is_correct<Type1>() && std::is_same_v<Type1, Type2>;
}

consteval bool is_correct_dimension(std::size_t dimension){
    return dimension > 0;
}

consteval bool is_correct_dimension(std::size_t dimension1, std::size_t dimension2){
    return is_correct_dimension(dimension1) && dimension1 == dimension2;
}

}

#endif // ASSERT_H
