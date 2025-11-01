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
struct make<agl::point::decart::point3d<Type>>{
    template<typename Value>
    inline constexpr static auto apply(const Value &value1, const Value &value2, const Value &value3){
        using r_value = std::remove_cvref_t<Value>;
        return agl::point::decart::point3d<Type>(agl::traits::value<r_value>::get(value1),
                                                 agl::traits::value<r_value>::get(value2),
                                                 agl::traits::value<r_value>::get(value3));
    }

    inline constexpr static auto apply(const Type &value1, const Type &value2, const Type &value3){
        return agl::point::decart::point3d<Type>(value1, value2, value3);
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
