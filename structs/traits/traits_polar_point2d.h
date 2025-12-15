#ifndef AGL_STRUCT_POINT_POLAR_POINT2D_TRAITS_H
#define AGL_STRUCT_POINT_POLAR_POINT2D_TRAITS_H

#include "system/traits.h"
#include "structs/geometric/polar_point2d.h"

namespace agl::traits {

template<typename TypePsi, typename TypeFi>
struct coordinate_system<agl::point::polar::polar2d<TypePsi, TypeFi>>{
    using system = system_coordinat::polar;
};

template<typename TypePsi, typename TypeFi>
struct dimension<agl::point::polar::polar2d<TypePsi, TypeFi>>{
    inline static constexpr std::size_t value(){
        return 2;
    }
};

template<typename TypePsi, typename TypeFi>
struct make<agl::point::polar::polar2d<TypePsi, TypeFi>>{
    template<typename Value1, typename Value2>
    inline constexpr static auto apply(const Value1 &value1, const Value2 &value2){
        return agl::point::polar::polar2d<TypePsi, TypeFi>(
            agl::traits::make<TypePsi>::apply(value1),
            agl::traits::make<TypeFi>::apply(value2));
    }

    inline constexpr static auto apply(const TypePsi &value1, const TypeFi &value2){
        return agl::point::polar::polar2d<TypePsi, TypeFi>(value1, value2);
    }
};

namespace point {

template<typename TypePsi, typename TypeFi>
struct access_types<agl::point::polar::polar2d<TypePsi, TypeFi>>{
    using types = std::tuple<typename agl::traits::type<TypePsi>::type_value,
                             typename agl::traits::type<TypeFi>::type_value>;
};

template<typename TypePsi, typename TypeFi>
struct access_point<agl::point::polar::polar2d<TypePsi, TypeFi>, 0>{
    inline constexpr static auto get(const agl::point::polar::polar2d<TypePsi, TypeFi> &point){
        return agl::traits::value<TypePsi>::get(point.psi());
    }
};

template<typename TypePsi, typename TypeFi>
struct access_point<agl::point::polar::polar2d<TypePsi, TypeFi>, 1>{
    inline constexpr static auto get(const agl::point::polar::polar2d<TypePsi, TypeFi> &point){
        return agl::traits::value<TypeFi>::get(point.fi());
    }
};

}

}

#endif // AGL_STRUCT_POINT_POLAR_POINT2D_TRAITS_H
