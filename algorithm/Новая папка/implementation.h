#ifndef AGL_ALGORITHM_<>_IMPLEMENTATION_H
#define AGL_ALGORITHM_<>_IMPLEMENTATION_H

#include "algorithm/tag_algoritm.h"
#include "algorithm/traits.h"
#include <cmath>

namespace agl::algorithm::dispatch {

template<>
struct <>{
    inline constexpr static auto get(){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

}


namespace agl::algorithm::geometry {

template<>
inline constexpr auto <>(){
    using type_coordinate_system = traits::coordinate_system<Point>::system;
    constexpr auto dimension = traits::dimension<Point>::value();

    static_assert(std::is_same_v<type_coordinate_system, agl::undefined>, "Error!");
    static_assert((dimension > decltype(dimension){}), "Error!");

    return dispatch::<><P>::get();
}

}


#endif // AGL_ALGORITHM_<>_IMPLEMENTATION_H
