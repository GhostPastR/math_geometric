#ifndef AGL_STRUCT_POINT_DECART_POINT3D_TRAITS_H
#define AGL_STRUCT_POINT_DECART_POINT3D_TRAITS_H

#include "system/traits.h"
#include "structs/geometric/decart_point3d.h"

namespace agl::traits {

template<typename Type>
struct coordinate_system<agl::point::decart::point3d<Type>>{
    using system = system_coordinat::cartesian;
};

template<typename Type>
struct dimension<agl::point::decart::point3d<Type>>{
    inline static constexpr std::size_t value(){
        return 3;
    }
};

template<typename Type>
struct access_create<agl::point::decart::point3d<Type>>{
    template<typename Value>
    inline constexpr static auto get(Value &&value1, Value &&value2, Value &&value3){
        using r_value = std::remove_cvref_t<Value>;
        return agl::point::decart::point3d<Type>(agl::traits::value<r_value>::get(std::forward<Value>(value1)),
                                                 agl::traits::value<r_value>::get(std::forward<Value>(value2)),
                                                 agl::traits::value<r_value>::get(std::forward<Value>(value3)));
    }

    inline constexpr static auto get(Type &&value1, Type &&value2, Type &&value3){
        return agl::point::decart::point3d<Type>(std::forward<Type>(value1),
                                                 std::forward<Type>(value2),
                                                 std::forward<Type>(value3));
    }
};

namespace point {

template<typename Type>
struct access_types<agl::point::decart::point3d<Type>>{
    using point = Type;
};

template<typename Type>
struct access_point<agl::point::decart::point3d<Type>, 0>{
    inline constexpr static auto get(const agl::point::decart::point3d<Type> &point){
        return agl::traits::value<Type>::get(point.x());
    }
};

template<typename Type>
struct access_point<agl::point::decart::point3d<Type>, 1>{
    inline constexpr static auto get(const agl::point::decart::point3d<Type> &point){
        return agl::traits::value<Type>::get(point.y());
    }
};

template<typename Type>
struct access_point<agl::point::decart::point3d<Type>, 2>{
    inline constexpr static auto get(const agl::point::decart::point3d<Type> &point){
        return agl::traits::value<Type>::get(point.z());
    }
};

}

}


#endif // AGL_STRUCT_POINT_DECART_POINT3D_TRAITS_H
