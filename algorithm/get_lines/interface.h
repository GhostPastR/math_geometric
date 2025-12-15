#ifndef AGL_ALGORITHM_GET_LINES_INTERFACE_H
#define AGL_ALGORITHM_GET_LINES_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//
template<typename OutObject, typename Figure>
inline constexpr auto get_lines(const Figure &figure){
    return dispatch::get_lines<Figure,
                               OutObject>::get(figure);
}

}

#endif // AGL_ALGORITHM_GET_LINES_INTERFACE_H
