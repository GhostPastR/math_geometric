#ifndef AGL_STRUCT_LINE_SECTION_TRAITS_H
#define AGL_STRUCT_LINE_SECTION_TRAITS_H

#include "system/traits.h"
#include "structs/geometric/straight_line.h"
#include "structs/geometric/line_section.h"

namespace agl::traits {

template<typename Point>
struct coordinate_system<agl::line::line_section<Point>>{
    using system = coordinate_system<Point>::system;
};

template<typename Point>
struct dimension<agl::line::line_section<Point>>{
    inline static constexpr std::size_t value(){
        return agl::traits::dimension<Point>::value();
    }
};

template<typename Point>
struct make<agl::line::line_section<Point>>{
    inline constexpr static auto apply(const Point &point1, const Point &point2){
        return agl::line::line_section<Point>{point1, point2};
    }

    template<typename TPoint>
    inline constexpr static auto apply(const TPoint &point1, const TPoint &point2){
        auto p1 = agl::traits::make<Point>::apply(agl::traits::point::access_point<TPoint, 0>::get(point1),
                                                  agl::traits::point::access_point<TPoint, 1>::get(point1));
        auto p2 = agl::traits::make<Point>::apply(agl::traits::point::access_point<TPoint, 0>::get(point2),
                                                  agl::traits::point::access_point<TPoint, 1>::get(point2));
        return agl::line::line_section<Point>(std::move(p1), std::move(p2));
    }
};

template<typename Point>
struct access_propery<agl::line::line_section<Point>>{
    inline constexpr static auto get(const agl::line::line_section<Point> &line){
        return std::tuple<Point, Point>{
            line.start(), line.stop()
        };
    }
};

namespace line_section {

template<typename Point>
struct access_types<agl::line::line_section<Point>>{
    using point = Point;
};


template<typename Point>
struct access_straight_line<agl::line::line_section<Point>>{
    using type = agl::line::straight_line<typename agl::traits::point::element_point_v<Point, 0>,
                                          typename agl::traits::coordinate_system<agl::line::line_section<Point>>::system>;
};


template<typename Point>
struct access_start<agl::line::line_section<Point>>{
    inline constexpr static auto get(const agl::line::line_section<Point> &object){
        return object.start();
    }
};

template<typename Point>
struct access_stop<agl::line::line_section<Point>>{
    inline constexpr static auto get(const agl::line::line_section<Point> &object){
        return object.stop();
    }
};

}

}

#endif // AGL_STRUCT_LINE_SECTION_TRAITS_H
