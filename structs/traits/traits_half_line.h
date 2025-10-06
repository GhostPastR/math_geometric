#ifndef AGL_STRUCT_HALF_LINE_TRAITS_H
#define AGL_STRUCT_HALF_LINE_TRAITS_H

#include "system/traits.h"
#include "structs/geometric/half_line.h"
#include "structs/geometric/straight_line.h"

namespace agl::traits {

template<typename Point, typename Angle>
struct tag<agl::line::half_line<Point, Angle>>{
    using type_tag = agl::tag::line::half_line;
};

template<typename Point, typename Angle>
struct group<agl::line::half_line<Point, Angle>>{
    using type_group = agl::group::lines;
};

template<typename Point, typename Angle>
struct coordinate_system<agl::line::half_line<Point, Angle>>{
    using system = coordinate_system<Point>::system;;
};

template<typename Point, typename Angle>
struct dimension<agl::line::half_line<Point, Angle>>{
    inline static constexpr std::size_t value(){
        return 2;
    }
};

namespace traits_half_line {

template<typename Point, typename Angle>
struct type_straight_line<agl::line::half_line<Point, Angle>>{
    using type = agl::line::straight_line<typename agl::traits::traits_point::type_property<Point>::type_point,
                                   typename agl::traits::coordinate_system<agl::line::half_line<Point, Angle>>::system>;
};

template<typename Point, typename Angle>
struct type_property<agl::line::half_line<Point, Angle>>{
    using type_start = Point;
    using type_direction = agl::traits::type<Angle>::type_value;
};

template<typename Point, typename Angle>
struct access_start<agl::line::half_line<Point, Angle>>{
    inline constexpr static auto get(const agl::line::half_line<Point, Angle> &object){
        return object.start();
    }
};

template<typename Point, typename Angle>
struct access_direction<agl::line::half_line<Point, Angle>>{
    inline constexpr static auto get(const agl::line::half_line<Point, Angle> &object){
        return agl::traits::value<Angle>::get(object.direction());
    }
};

}

}

#endif // AGL_STRUCT_HALF_LINE_TRAITS_H
