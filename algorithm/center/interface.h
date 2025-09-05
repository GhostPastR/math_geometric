#ifndef AGL_ALGORITHM_CENTER_INTERFACE_H
#define AGL_ALGORITHM_CENTER_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//
template<typename PointOut, typename Figure>
inline constexpr auto center(const Figure &figure){
    return geometry::center<Figure, PointOut>(figure);
}

}

#endif // AGL_ALGORITHM_CENTER_INTERFACE_H
