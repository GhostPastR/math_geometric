#ifndef TRAITS_STANDART_H
#define TRAITS_STANDART_H

#include <concepts>
#include <vector>
#include <array>
#include "traits.h"

namespace agl::traits{

template<typename Point>
struct tag<std::array<Point,2>>{
    using type_tag = agl::tag::line::line_section;
};

template<typename Point>
struct group<std::array<Point,2>>{
    using type_group = agl::group::lines;
};

template<typename Point>
struct coordinate_system<std::array<Point,2>>{
    using system = coordinate_system<Point>::system;;
};

template<typename Point>
struct dimension<std::array<Point,2>>{
    inline static constexpr std::size_t value(){
        return 2;
    }
};

namespace traits_line_section {

template<typename Point>
struct type_property<std::array<Point,2>>{
    using type_point = Point;
};

template<typename Point>
struct access_start<std::array<Point,2>>{
    inline constexpr static auto get(const std::array<Point,2> &object){
        return object[0];
    }
};

template<typename Point>
struct access_stop<std::array<Point,2>>{
    inline constexpr static auto get(const std::array<Point,2> &object){
        return object[1];
    }
};

template<typename PointLine, typename Point>
struct access_create<std::array<PointLine,2>, Point>{
    inline constexpr static auto get(const Point &point1, const Point &point2){
        using type = agl::traits::traits_point::type_property<Point>::type_point;
        auto x1 = agl::traits::traits_point::access_point<Point, 0>::get(point1);
        auto y1 = agl::traits::traits_point::access_point<Point, 1>::get(point1);
        auto x2 = agl::traits::traits_point::access_point<Point, 0>::get(point2);
        auto y2 = agl::traits::traits_point::access_point<Point, 1>::get(point2);
        return std::array<PointLine,2>{agl::traits::traits_point::access_create<PointLine, type, type>::get(std::move(x1), std::move(y1)),
                                       agl::traits::traits_point::access_create<PointLine, type, type>::get(std::move(x2), std::move(y2))};
    }
};

}

}

#endif // TRAITS_STANDART_H
