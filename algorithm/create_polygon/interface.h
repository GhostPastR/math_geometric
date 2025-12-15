#ifndef AGL_ALGORITHM_CREATE_POLYGON_INTERFACE_H
#define AGL_ALGORITHM_CREATE_POLYGON_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//
template<typename PolygonOut,
         typename Strategy,
         typename ...Args>
inline constexpr auto create_polygon(Args&& ...args){
    using Tag = agl::traits::polygon::access_tag<PolygonOut>::type_tag;
    return dispatch::create_polygon<PolygonOut,
                                    Tag,
                                    Strategy,
                                    Args...>::get(std::forward<Args>(args)...);
}

}

#endif // AGL_ALGORITHM_CREATE_POLYGON_INTERFACE_H
