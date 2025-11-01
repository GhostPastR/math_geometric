#ifndef AGL_ALGORITHM_BELONGS_TO_AREA_OF_LINE_INTERFACE_H
#define AGL_ALGORITHM_BELONGS_TO_AREA_OF_LINE_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//Функция определяет попадает ли объект в область линии
template<typename Line,
         typename Object>
inline constexpr bool belongs_to_area_of_line(const Line &line,
                                              const Object &object){
    return dispatch::belongs_to_area_of_line<Line, Object>::get(line, object);
}



}

#endif // AGL_ALGORITHM_BELONGS_TO_AREA_OF_LINE_INTERFACE_H
