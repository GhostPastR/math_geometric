#ifndef AGL_ALGORITHM_BELONGS_TO_AREA_OF_LINE_INTERFACE_H
#define AGL_ALGORITHM_BELONGS_TO_AREA_OF_LINE_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

template<typename Border,
         typename Point>
inline constexpr auto belongs_to_area_of_line(const Border &left, const Border &right, const Point &point){
    return geometry::belongs_to_area_of_line<Border, Point>(left, right, point);
}


//
template<typename Line,
         typename Object>
inline constexpr bool belongs_to_area_of_line(const Line &line,
                                              const Object &object){
    return geometry::belongs_to_area_of_line<Line,
                                             Object>(line, object);
}



}

#endif // AGL_ALGORITHM_BELONGS_TO_AREA_OF_LINE_INTERFACE_H
