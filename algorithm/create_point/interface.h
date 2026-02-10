#ifndef AGL_ALGORITHM_CREATE_POINT_INTERFACE_H
#define AGL_ALGORITHM_CREATE_POINT_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//метод расчитывает координаты новой точки
template<typename OutPoint,
         typename Point,
         typename Range,
         typename ...Turning>
inline constexpr auto create_point(const Point &point, const Range &range, const Turning &...turning){
    return geometry::create_point<OutPoint,
                                  Point,
                                  Range,
                                  Turning...>(point, range, turning...);
}

}

#endif // AGL_ALGORITHM_CREATE_POINT_INTERFACE_H
