#ifndef AGL_ALGORITHM_POINT_ON_CURVE_INTERFACE_H
#define AGL_ALGORITHM_POINT_ON_CURVE_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//
template<typename Point, typename Figure, typename TypeDistance>
inline constexpr auto point_on_curve(const Figure &figure, const TypeDistance &distance){
    return geometry::point_on_curve<Figure, TypeDistance, Point>(figure, distance);
}

}

#endif // AGL_ALGORITHM_POINT_ON_CURVE_INTERFACE_H
