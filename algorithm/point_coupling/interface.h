#ifndef AGL_ALGORITHM_POINT_COUPLING_INTERFACE_H
#define AGL_ALGORITHM_POINT_COUPLING_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//
template<typename Figure, typename Point>
inline constexpr auto point_coupling(const Figure &figure, const Point &point, bool is_perpendicular = true){
    return geometry::point_coupling<Figure, Point>(figure, point, is_perpendicular);
}

}

#endif // AGL_ALGORITHM_POINT_COUPLING_INTERFACE_H
