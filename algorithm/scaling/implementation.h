#ifndef AGL_ALGORITHM_<>_IMPLEMENTATION_H
#define AGL_ALGORITHM_<>_IMPLEMENTATION_H

#include "algorithm/tag_algoritm.h"

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
    using tag1 = traits::tag<Object1>::type_tag;
    using tag2 = traits::tag<Object2>::type_tag;
    using type_coordinate_system1 = traits::coordinate_system<Object1>::system;
    using type_coordinate_system2 = traits::coordinate_system<Object2>::system;
    constexpr auto dimension1 = traits::dimension<Object1>::value();
    constexpr auto dimension2 = traits::dimension<Object2>::value();

    static_assert(agl::assert::is_correct<tag1>(), "Error!");
    static_assert(agl::assert::is_correct<tag2>(), "Error!");
    static_assert(agl::assert::is_correct_compare<type_coordinate_system1, type_coordinate_system2>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension1, dimension2), "Error!");

    return dispatch::<><>::get();
}

}


#endif // AGL_ALGORITHM_<>_IMPLEMENTATION_H
