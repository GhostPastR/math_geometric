#ifndef TRAITS_STANDART_H
#define TRAITS_STANDART_H

#include <concepts>
#include <vector>
#include <array>
#include "traits.h"

namespace agl::traits{

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

template<typename PointLine>
struct make<std::array<PointLine,2>>{
    template<typename Point>
    inline constexpr static auto get(const Point &point1, const Point &point2){
        using type = agl::traits::point::access_types<Point>::point;
        auto x1 = agl::traits::point::access_point<Point, 0>::get(point1);
        auto y1 = agl::traits::point::access_point<Point, 1>::get(point1);
        auto x2 = agl::traits::point::access_point<Point, 0>::get(point2);
        auto y2 = agl::traits::point::access_point<Point, 1>::get(point2);
        return std::array<PointLine,2>{agl::traits::make<PointLine>::apply(x1, y1),
                                        agl::traits::make<PointLine>::apply(x2, y2)};
    }
};


namespace line_section {

template<typename Point>
struct access_types<std::array<Point,2>>{
    using point = Point;
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

}

}

#endif // TRAITS_STANDART_H
