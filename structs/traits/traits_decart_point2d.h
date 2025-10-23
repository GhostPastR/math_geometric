#ifndef AGL_STRUCT_POINT_DECART_POINT2D_TRAITS_H
#define AGL_STRUCT_POINT_DECART_POINT2D_TRAITS_H

#include "system/traits.h"
#include "structs/geometric/decart_point2d.h"

namespace agl::traits {

template<typename Type>
struct coordinate_system<agl::point::decart::point2d<Type>>{
    using system = system_coordinat::cartesian;
};

template<typename Type>
struct dimension<agl::point::decart::point2d<Type>>{
    inline static constexpr std::size_t value(){
        return 2;
    }
};

template<typename Type>
struct access_create<agl::point::decart::point2d<Type>>{
    template<typename Value>
    inline constexpr static auto get(Value &&value1, Value &&value2){
        using r_value = std::remove_cvref_t<Value>;
        return agl::point::decart::point2d<Type>(agl::traits::value<r_value>::get(std::forward<Value>(value1)),
                                                 agl::traits::value<r_value>::get(std::forward<Value>(value2)));
    }

    inline constexpr static auto get(Type &&value1, Type &&value2){
        return agl::point::decart::point2d<Type>(std::forward<Type>(value1), std::forward<Type>(value2));
    }
};

namespace point {

template<typename Type>
struct access_types<agl::point::decart::point2d<Type>>{
    using point = Type;
};

template<typename Type>
struct access_point<agl::point::decart::point2d<Type>, 0>{
    inline constexpr static auto get(const agl::point::decart::point2d<Type> &point){
        return agl::traits::value<Type>::get(point.x());
    }
};

template<typename Type>
struct access_point<agl::point::decart::point2d<Type>, 1>{
    inline constexpr static auto get(const agl::point::decart::point2d<Type> &point){
        return agl::traits::value<Type>::get(point.y());
    }
};

}

}

#endif // AGL_STRUCT_POINT_DECART_POINT2D_TRAITS_H
