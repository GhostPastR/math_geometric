#ifndef AGL_ALGORITHM_PARALLEL_INTERFACE_H
#define AGL_ALGORITHM_PARALLEL_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//
template<typename OutLine, typename Figure, typename Type>
inline constexpr auto parallel(const Figure &figure, const Type &distance){
    return dispatch::parallel<Figure,
                              Type,
                              OutLine>::get(figure, distance);
}

}

#endif // AGL_ALGORITHM_PARALLEL_INTERFACE_H
