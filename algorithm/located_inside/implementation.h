#ifndef AGL_ALGORITHM_LOCATED_INSIDE_IMPLEMENTATION_H
#define AGL_ALGORITHM_LOCATED_INSIDE_IMPLEMENTATION_H

#include "system/assert.h"
#include "system/traits.h"
#include <cmath>
#include "algorithm/located_inside/implementation_circle.h"

namespace agl::algorithm::dispatch {

template<typename Object1, typename Object2, typename Tag1, typename Tag2, typename SystemCoorinate, std::size_t Dimension>
struct located_inside{
    inline constexpr static auto get(const Object1 &a, const Object2 &b){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<typename Object1, typename Object2, typename Tag, typename SystemCoorinate, std::size_t Dimension>
struct located_inside<Object1, Object2, agl::tag::tag_circle, Tag, SystemCoorinate, Dimension>{
    inline constexpr static auto get(const Object1 &a, const Object2 &b){
        return agl::algorithm::inside_circle::located_inside<Object1, Object2, Tag, SystemCoorinate, Dimension>(a, b);
    }
};


}


namespace agl::algorithm::geometry {

template<typename Object1, typename Object2>
inline constexpr auto located_inside(const Object1 &a, const Object2 &b){
    using type_cs1 = traits::coordinate_system<Object1>::system;
    using type_cs2 = traits::coordinate_system<Object2>::system;
    using tag1 = traits::tag<Object1>::type_tag;
    using tag2 = traits::tag<Object2>::type_tag;
    constexpr auto dimension1 = traits::dimension<Object1>::value();
    constexpr auto dimension2 = traits::dimension<Object2>::value();
    static_assert(agl::assert::is_correct_compare<type_cs1, type_cs2>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension1, dimension2), "Error!");
    return dispatch::located_inside<Object1, Object2, tag1, tag2, type_cs1, dimension1>::get(a, b);
}

}


#endif // AGL_ALGORITHM_LOCATED_INSIDE_IMPLEMENTATION_H
