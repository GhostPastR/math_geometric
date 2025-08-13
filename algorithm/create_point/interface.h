#ifndef AGL_ALGORITHM_CREATE_POINT_INTERFACE_H
#define AGL_ALGORITHM_CREATE_POINT_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//метод расчитывает координаты новой точки
template<typename Point, typename Turning, typename Range, typename NewPoint = Point>
inline constexpr auto create_point(const Point &point, const Turning &turning, const Range &range){
    return geometry::create_point<Point, Turning, Range, NewPoint>(point, turning, range);
}

}

#endif // AGL_ALGORITHM_CREATE_POINT_INTERFACE_H
