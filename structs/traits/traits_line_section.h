#ifndef AGL_STRUCT_LINE_SECTION_TRAITS_H
#define AGL_STRUCT_LINE_SECTION_TRAITS_H

#include "system/traits.h"
#include "structs/geometric/straight_line.h"
#include "structs/geometric/line_section.h"

namespace agl::traits {

template<typename Point>
struct tag<agl::line::line_section<Point>>{
    using type_tag = agl::tag::line::line_section;
};

template<typename Point>
struct group<agl::line::line_section<Point>>{
    using type_group = agl::group::lines;
};

template<typename Point>
struct coordinate_system<agl::line::line_section<Point>>{
    using system = coordinate_system<Point>::system;;
};

template<typename Point>
struct dimension<agl::line::line_section<Point>>{
    inline static constexpr std::size_t value(){
        return 2;
    }
};

namespace line_section {

template<typename Point>
struct access_types<agl::line::line_section<Point>>{
    using point = Point;
};


template<typename Point>
struct access_straight_line<agl::line::line_section<Point>>{
    using type = agl::line::straight_line<typename agl::traits::point::access_types<Point>::point,
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

template<typename Point>
struct access_create<agl::line::line_section<Point>>{
    inline constexpr static auto get(const Point &point1, const Point &point2){
        return agl::line::line_section<Point>{point1, point2};
    }
};


}

}

#endif // AGL_STRUCT_LINE_SECTION_TRAITS_H
