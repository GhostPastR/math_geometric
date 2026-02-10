#ifndef AGL_ALGORITHM_IS_CORRECT_POLYGON_INTERFACE_H
#define AGL_ALGORITHM_IS_CORRECT_POLYGON_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//
template<typename Polygon>
inline constexpr auto is_correct_polygon(const Polygon &polygon){
    using tag = traits::polygon::access_tag<Polygon>::type_tag;
    static_assert(agl::assert::is_correct<tag>(), "Error!");
    return dispatch::is_correct_polygon<Polygon,
                                        tag>::get(polygon);
}

}

#endif // AGL_ALGORITHM_IS_CORRECT_POLYGON_INTERFACE_H
