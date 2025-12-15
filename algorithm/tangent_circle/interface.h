#ifndef AGL_ALGORITHM_TANGENT_CIRCLE_INTERFACE_H
#define AGL_ALGORITHM_TANGENT_CIRCLE_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//
template<typename LineSectionOut,
         typename Circle,
         typename Object,
         typename TagTangent = agl::algorithm::type_tangent::external>
inline constexpr auto tangent_circle(const Circle &circle, const Object &object, TagTangent tag){
    return dispatch::tangent_circle<Circle,
                                    Object,
                                    LineSectionOut,
                                    TagTangent>::get(circle, object, tag);
}

}

#endif // AGL_ALGORITHM_TANGENT_CIRCLE_INTERFACE_H
