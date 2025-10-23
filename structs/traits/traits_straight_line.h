#ifndef AGL_STRUCT_STRAIGHT_LINE_TRAITS_H
#define AGL_STRUCT_STRAIGHT_LINE_TRAITS_H

#include "system/traits.h"
#include "structs/geometric/straight_line.h"

namespace agl::traits {

template<typename Type, typename CoordinateSystem>
struct coordinate_system<agl::line::straight_line<Type,CoordinateSystem>>{
    using system = CoordinateSystem;
};

template<typename Type, typename CoordinateSystem>
struct dimension<agl::line::straight_line<Type,CoordinateSystem>>{
    inline static constexpr std::size_t value(){
        return 2;
    }
};

template<typename Type, typename CoordinateSystem>
struct access_create<agl::line::straight_line<Type,CoordinateSystem>>{
    inline constexpr static auto get(const Type &a, const Type &b, const Type &c){
        return agl::line::straight_line<Type,CoordinateSystem>(a, b, c);
    }

    template<typename Value>
    inline constexpr static auto get(const Value &a, const Value &b, const Value &c){
        return agl::line::straight_line<Type,CoordinateSystem>(agl::traits::value<Value>::get(a),
                                                                agl::traits::value<Value>::get(b),
                                                                agl::traits::value<Value>::get(c));
    }
};

namespace straight_line {

template<typename Type, typename CoordinateSystem>
struct access_types<agl::line::straight_line<Type,CoordinateSystem>>{
    using parameter = Type;
};

template<typename Type, typename CoordinateSystem>
struct access_parameter<agl::line::straight_line<Type,CoordinateSystem>, 0>{
    inline constexpr static auto get(const agl::line::straight_line<Type,CoordinateSystem> &object){
        return object.a();
    }
};

template<typename Type, typename CoordinateSystem>
struct access_parameter<agl::line::straight_line<Type,CoordinateSystem>, 1>{
    inline constexpr static auto get(const agl::line::straight_line<Type,CoordinateSystem> &object){
        return object.b();
    }
};

template<typename Type, typename CoordinateSystem>
struct access_parameter<agl::line::straight_line<Type,CoordinateSystem>, 2>{
    inline constexpr static auto get(const agl::line::straight_line<Type,CoordinateSystem> &object){
        return object.c();
    }
};

}

}

#endif // AGL_STRUCT_STRAIGHT_LINE_TRAITS_H
