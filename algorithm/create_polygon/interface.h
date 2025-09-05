#ifndef AGL_ALGORITHM_CREATE_POLYGON_INTERFACE_H
#define AGL_ALGORITHM_CREATE_POLYGON_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//
template<typename PolygonOut, typename Strategy, typename ...Args>
inline constexpr auto create_polygon(Args&& ...args){
    return geometry::create_polygon<PolygonOut, Strategy, Args...>(std::forward<Args>(args)...);
}

}

#endif // AGL_ALGORITHM_CREATE_POLYGON_INTERFACE_H
