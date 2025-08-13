#ifndef TAG_ALGORITM_DISTANCE_H
#define TAG_ALGORITM_DISTANCE_H

#include "algorithm/traits.h"

namespace agl::algorithm {

struct distance_point final{};

template<typename Object1, typename Object2>
struct algorithm_distance{
    using type_algorithm = undefined;
};

template<> struct algorithm_distance<object_point, object_point>{
    using type_algorithm = distance_point;
};



struct direction_angle final{};
struct direction_vector final{};

template<typename Type>
struct direction_object{
    using type_direction_object = undefined;
};

template<> struct direction_object<float>{
    using type_direction_object = direction_angle;
};

template<> struct direction_object<double>{
    using type_direction_object = direction_angle;
};

template<> struct direction_object<long double>{
    using type_direction_object = direction_angle;
};



}

#endif // TAG_ALGORITM_DISTANCE_H
