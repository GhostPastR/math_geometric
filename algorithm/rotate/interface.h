#ifndef AGL_ALGORITHM_ROTATE_INTERFACE_H
#define AGL_ALGORITHM_ROTATE_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//метод расчитывает координаты новой точки
template<typename Object, typename ObjectDirection, typename Point>
inline constexpr auto rotate(const Object &object, const ObjectDirection &direction, const Point &point){
    return geometry::rotate<Object, ObjectDirection, Point>(object, direction, point);
}

}

#endif // AGL_ALGORITHM_ROTATE_INTERFACE_H
