#ifndef AGL_ALGORITHM_CENTER_INTERFACE_H
#define AGL_ALGORITHM_CENTER_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//Функция возвращает центр фигуры
template<typename PointOut,
         typename Figure>
inline constexpr auto center(const Figure &figure){
    return dispatch::center<Figure,
                            PointOut>::get(figure);
}

}

#endif // AGL_ALGORITHM_CENTER_INTERFACE_H
