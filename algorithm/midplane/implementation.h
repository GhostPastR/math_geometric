#ifndef AGL_ALGORITHM_MIDPLANE_IMPLEMENTATION_H
#define AGL_ALGORITHM_MIDPLANE_IMPLEMENTATION_H

#include "algorithm/traits.h"
#include <numeric>

namespace agl::algorithm::dispatch {

template<typename Object, typename CoordinateSystem, std::size_t Dimension>
struct midplane{
    inline constexpr static auto get(const Object &a, const Object &b){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<typename Object>
struct midplane<Object, cartesian, 2>{
    inline constexpr static auto get(const Object &a, const Object &b){
        return Object{std::midpoint(traits::traits_point::access_point<Object, 0>::get(a), traits::traits_point::access_point<Object, 0>::get(b)),
                      std::midpoint(traits::traits_point::access_point<Object, 1>::get(a), traits::traits_point::access_point<Object, 1>::get(b))};
    }
};

template<typename Object>
struct midplane<Object, cartesian, 3>{
    inline constexpr static auto get(const Object &a, const Object &b){
        return Object{std::midpoint(traits::traits_point::access_point<Object, 0>::get(a), traits::traits_point::access_point<Object, 0>::get(b)),
                      std::midpoint(traits::traits_point::access_point<Object, 1>::get(a), traits::traits_point::access_point<Object, 1>::get(b)),
                      std::midpoint(traits::traits_point::access_point<Object, 2>::get(a), traits::traits_point::access_point<Object, 2>::get(b))};
    }
};

}


namespace agl::algorithm::geometry {

template<typename Object>
inline constexpr auto midplane(const Object &a, const Object &b){
    using type_coordinate_system = traits::coordinate_system<Object>::system;
    constexpr auto dimension = traits::dimension<Object>::value();

    static_assert(!std::is_same_v<type_coordinate_system, agl::undefined>, "Error!");
    static_assert((dimension > decltype(dimension){}), "Error!");

    return dispatch::midplane<Object, type_coordinate_system, dimension>::get(a, b);
}

}


#endif // AGL_ALGORITHM_MIDPLANE_IMPLEMENTATION_H
