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
        return agl::point::decart::point3d<Type>(agl::traits::make<Type>::apply(value1),
                                                 agl::traits::make<Type>::apply(value2),
                                                 agl::traits::make<Type>::apply(value3));
    }

    inline constexpr static auto apply(const Type &value1, const Type &value2, const Type &value3){
        return agl::point::decart::point3d<Type>(value1, value2, value3);
    }
};

template<typename Type>
struct access_propery<agl::point::decart::point3d<Type>>{
    inline constexpr static auto get(const agl::point::decart::point3d<Type> &point){
        return std::make_tuple(
            agl::traits::value<Type>::get(point.x()),
            agl::traits::value<Type>::get(point.y()),
            agl::traits::value<Type>::get(point.z())
        );
    }
};

namespace point {

template<typename Type>
struct access_types<agl::point::decart::point3d<Type>>{
    using p_type = agl::traits::type<Type>::type_value;
    using types = std::tuple<p_type, p_type, p_type>;
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
