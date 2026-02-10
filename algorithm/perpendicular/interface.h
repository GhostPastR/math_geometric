#ifndef AGL_ALGORITHM_PERPENDICULAR_INTERFACE_H
#define AGL_ALGORITHM_PERPENDICULAR_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//
template<typename LineOut,
         typename Figure,
         typename Point>
inline constexpr auto perpendicular(const Figure &figure, const Point &point){
    return dispatch::perpendicular<Figure,
                                   Point,
                                   LineOut>::get(figure, point);
}

}

#endif // AGL_ALGORITHM_PERPENDICULAR_INTERFACE_H
