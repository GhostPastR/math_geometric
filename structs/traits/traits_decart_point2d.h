#ifndef AGL_STRUCT_POINT_DECART_POINT2D_TRAITS_H
#define AGL_STRUCT_POINT_DECART_POINT2D_TRAITS_H

#include "system/traits.h"
#include "structs/geometric/decart_point2d.h"

namespace agl::traits {

template<typename Type>
struct tag<point::decart::point2d<Type>>{
    using type_tag = agl::tag::point::point;
};

template<typename Type>
struct group<point::decart::point2d<Type>>{
    using type_group = agl::group::points;
};

template<typename Type>
struct coordinate_system<point::decart::point2d<Type>>{
    using system = system_coordinat::cartesian;
};

template<typename Type>
struct dimension<point::decart::point2d<Type>>{
    inline static constexpr std::size_t value(){
        return 2;
    }
};

namespace traits_point {

template<typename Type>
struct type_property<point::decart::point2d<Type>>{
    using type_point = Type;
};

template<typename Type>
struct access_point<point::decart::point2d<Type>, 0>{
    inline constexpr static auto get(const point::decart::point2d<Type> &point){
        return agl::traits::value<Type>::get(point.x());
    }
};

template<typename Type>
struct access_point<point::decart::point2d<Type>, 1>{
    inline constexpr static auto get(const point::decart::point2d<Type> &point){
        return agl::traits::value<Type>::get(point.y());
    }
};

template<typename Type, typename Value>
struct access_create<point::decart::point2d<Type>, Value, Value>{
    inline constexpr static auto get(Value&& value1, Value&& value2){
        return point::decart::point2d<Type>(agl::traits::value<Value>::get(value1), agl::traits::value<Value>::get(value2));
    }
};

}

}

#endif // AGL_STRUCT_POINT_DECART_POINT2D_TRAITS_H
