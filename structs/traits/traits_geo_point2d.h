#ifndef AGL_STRUCT_POINT_GEO_POINT2D_TRAITS_H
#define AGL_STRUCT_POINT_GEO_POINT2D_TRAITS_H

#include "system/traits.h"
#include "structs/geometric/geo_point2d.h"

namespace agl::traits {

template<typename Type>
struct coordinate_system<agl::point::geo::point_geo2d<Type>>{
    using system = system_coordinat::geographical;
};

template<typename Type>
struct dimension<agl::point::geo::point_geo2d<Type>>{
    inline static constexpr std::size_t value(){
        return 2;
    }
};

template<typename Type>
struct make<agl::point::geo::point_geo2d<Type>>{
    template<typename Value>
    inline constexpr static auto apply(const Value &value1, const Value &value2){
        return agl::point::geo::point_geo2d<Type>(agl::traits::make<Type>::apply(value1),
                                                  agl::traits::make<Type>::apply(value2));
    }

    inline constexpr static auto apply(const Type &value1, const Type &value2){
        return agl::point::geo::point_geo2d<Type>(value1, value2);
    }
};

namespace point {

template<typename Type>
struct access_types<agl::point::geo::point_geo2d<Type>>{
    using p_type = agl::traits::type<Type>::type_value;
    using types = std::tuple<p_type, p_type>;
};

template<typename Type>
struct access_point<agl::point::geo::point_geo2d<Type>, 0>{
    inline constexpr static auto get(const agl::point::geo::point_geo2d<Type> &point){
        return agl::traits::value<Type>::get(point.latitude());
    }
};

template<typename Type>
struct access_point<agl::point::geo::point_geo2d<Type>, 1>{
    inline constexpr static auto get(const agl::point::geo::point_geo2d<Type> &point){
        return agl::traits::value<Type>::get(point.longitude());
    }
};

}

}


#endif // AGL_STRUCT_POINT_GEO_POINT2D_TRAITS_H
