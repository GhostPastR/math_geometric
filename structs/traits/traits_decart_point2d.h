#ifndef AGL_STRUCT_POINT_DECART_POINT2D_TRAITS_H
#define AGL_STRUCT_POINT_DECART_POINT2D_TRAITS_H

#include "system/traits.h"
#include "structs/geometric/decart_point2d.h"

namespace agl::traits {

template<typename Type>
struct coordinate_system<agl::point::decart::point2<Type>>{
    using system = system_coordinat::cartesian;
};

template<typename Type>
struct dimension<agl::point::decart::point2<Type>>{
    inline static constexpr std::size_t value(){
        return 2;
    }
};

template<typename Type>
struct make<agl::point::decart::point2<Type>>{
    template<typename Value>
    inline constexpr static auto apply(const Value &value1, const Value &value2){
        return agl::point::decart::point2<Type>(agl::traits::make<Type>::apply(value1),
                                                agl::traits::make<Type>::apply(value2));
    }

    inline constexpr static auto apply(const Type &value1, const Type &value2){
        return agl::point::decart::point2<Type>(value1, value2);
    }
};

namespace point {

template<typename Type>
struct access_types<agl::point::decart::point2<Type>>{
    using p_type = agl::traits::type<Type>::type_value;
    using types = std::tuple<p_type, p_type>;
};

template<typename Type>
struct access_point<agl::point::decart::point2<Type>, 0>{
    inline constexpr static auto get(const agl::point::decart::point2<Type> &point){
        return agl::traits::value<Type>::get(point.x());
    }
};

template<typename Type>
struct access_point<agl::point::decart::point2<Type>, 1>{
    inline constexpr static auto get(const agl::point::decart::point2<Type> &point){
        return agl::traits::value<Type>::get(point.y());
    }
};

}

}

#endif // AGL_STRUCT_POINT_DECART_POINT2D_TRAITS_H
