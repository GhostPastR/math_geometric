#ifndef AGL_ALGORITHM_MIDPLANE_INTERFACE_H
#define AGL_ALGORITHM_MIDPLANE_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//метод расчитывает координаты новой точки
template<typename Object>
inline constexpr auto midplane(const Object &a, const Object &b){
    return geometry::midplane<Object>(a,b);
}

template<typename Figure>
inline constexpr auto midplane(const Figure &figure){
    return geometry::midplane<Figure>(figure);
}

}

#endif // AGL_ALGORITHM_MIDPLANE_INTERFACE_H
