#ifndef AGL_ALGORITHM_INTERSECTION_INTERFACE_H
#define AGL_ALGORITHM_INTERSECTION_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//
template<typename PointOut, typename Figure1, typename Figure2>
inline constexpr auto intersection(const Figure1 &figure1, const Figure2 &figure2){
    return geometry::intersection<Figure1, Figure2, PointOut>(figure1, figure2);
}

}

#endif // AGL_ALGORITHM_INTERSECTION_INTERFACE_H
