#ifndef AGL_STRUCT_POINT_POLAR_POINT2D_TRAITS_H
#define AGL_STRUCT_POINT_POLAR_POINT2D_TRAITS_H

#include "system/traits.h"
#include "structs/geometric/polar_point2d.h"

namespace agl::traits {

// template<typename TypePsi, typename TypeFi>
// struct type_coordinate<point::polar::polar2d<TypePsi, TypeFi>>{
//     using type_psi = TypePsi;
//     using type_fi = TypeFi;
// };

// template<typename TypePsi, typename TypeFi>
// struct access_point<point::polar::polar2d<TypePsi, TypeFi>, 0>{
//     inline constexpr static auto get(const point::polar::polar2d<TypePsi, TypeFi> &point){
//         return agl::system::tag::value<TypePsi>::get(point.psi());
//     }
// };

// template<typename TypePsi, typename TypeFi>
// struct access_point<point::polar::polar2d<TypePsi, TypeFi>, 1>{
//     inline constexpr static auto get(const point::polar::polar2d<TypePsi, TypeFi> &point){
//         return agl::system::tag::value<TypeFi>::get(point.fi());
//     }
// };

template<typename TypePsi, typename TypeFi>
struct tag<agl::point::polar::polar2d<TypePsi, TypeFi>>{
    using type_tag = agl::tag::point::point;
};

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

}

#endif // AGL_STRUCT_POINT_POLAR_POINT2D_TRAITS_H
