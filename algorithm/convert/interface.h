#ifndef AGL_ALGORITHM_CONVERT_INTERFACE_H
#define AGL_ALGORITHM_CONVERT_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//метод расчитывает координаты новой точки
template<typename Object, typename ObjectOut>
inline constexpr auto convert(const Object &object){
    return geometry::convert<Object, ObjectOut>(object);
}

}

#endif // AGL_ALGORITHM_CONVERT_INTERFACE_H
