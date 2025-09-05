#ifndef AGL_ALGORITHM_CONTAIN_INTERFACE_H
#define AGL_ALGORITHM_CONTAIN_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//
template<typename Object1, typename Object2>
inline constexpr auto contain(const Object1 &object1, const Object2 &object2){
    return geometry::contain<Object1, Object2>(object1, object2);
}

}

#endif // AGL_ALGORITHM_CONTAIN_INTERFACE_H
