#ifndef TAG_ALGORITM_H
#define TAG_ALGORITM_H

#include "system/traits.h"

namespace agl::algorithm {

struct distance_point final{};

template<typename Object1, typename Object2>
struct algorithm{
    using type_algorithm = undefined;
};

template<> struct algorithm<object_point, object_point>{
    using type_algorithm = distance_point;
};


}

#endif // TAG_ALGORITM_H
