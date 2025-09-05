#ifndef AGL_ALGORITHM_IS_CORRECT_POLYGON_INTERFACE_H
#define AGL_ALGORITHM_IS_CORRECT_POLYGON_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//
template<typename Polygon>
inline constexpr auto is_correct_polygon(const Polygon &polygon){
    return geometry::is_correct_polygon<Polygon>(polygon);
}

}

#endif // AGL_ALGORITHM_IS_CORRECT_POLYGON_INTERFACE_H
