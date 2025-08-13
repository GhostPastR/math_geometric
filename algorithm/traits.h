#ifndef TRAITS_H
#define TRAITS_H

#include <cstddef>

namespace agl{

struct undefined final{};

struct cartesian final{};
struct polar final{};
struct spherical final{};

struct object_point final{};
struct object_line final{};

struct tag_point final{};

namespace traits {

template<typename Object>
struct type_coordinate{
    using type = undefined;
};

template<typename Point, std::size_t Property>
struct access_point{
    inline constexpr static auto get(const Point &point){
        static_assert(false, "Access is not implemented for this object.");
    }
};

template<typename Object>
struct tag{
    using type_tag = undefined;
};

template<typename Object>
struct coordinate_system{
    using system = undefined;
};

template<typename Object>
struct dimension{
    inline static constexpr std::size_t value(){
        return 0;
    }
};

}

}

#endif // TRAITS_H
