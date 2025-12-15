#ifndef AGL_ALGORITHM_CONVERT_INTERFACE_H
#define AGL_ALGORITHM_CONVERT_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//метод расчитывает координаты новой точки
template<typename ObjectOut,
         typename Object>
inline constexpr auto convert(const Object &object){
    return dispatch::convert<Object,
                             ObjectOut>::get(object);
}

}

#endif // AGL_ALGORITHM_CONVERT_INTERFACE_H
