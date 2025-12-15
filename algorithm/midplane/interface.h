#ifndef AGL_ALGORITHM_MIDPLANE_INTERFACE_H
#define AGL_ALGORITHM_MIDPLANE_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//метод расчитывает координаты новой точки
template<typename ObjectOut, typename Object>
inline constexpr auto midplane(const Object &a, const Object &b){
    return dispatch::d2::midplane<Object,
                                  ObjectOut>::get(a, b);
}

template<typename Figure>
inline constexpr auto midplane(const Figure &figure){
    return dispatch::d1::midplane<Figure>::get(figure);
}

}

#endif // AGL_ALGORITHM_MIDPLANE_INTERFACE_H
