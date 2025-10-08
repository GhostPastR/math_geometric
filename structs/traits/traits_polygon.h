#ifndef AGL_STRUCT_POLYGON_TRAITS_H
#define AGL_STRUCT_POLYGON_TRAITS_H

#include "system/traits.h"
#include "structs/geometric/line_section.h"
#include "structs/geometric/polygon.h"

namespace agl::traits{

template<typename Point, typename Tag>
struct tag<agl::figure::polygon<Point, Tag>>{
    using type_tag = Tag;
};

template<typename Point, typename Tag>
struct group<agl::figure::polygon<Point, Tag>>{
    using type_group = agl::group::polygons;
};

template<typename Point, typename Tag>
struct coordinate_system<agl::figure::polygon<Point, Tag>>{
    using system = agl::traits::coordinate_system<Point>::system;
};

template<typename Point, typename Tag>
struct dimension<agl::figure::polygon<Point, Tag>>{
    inline static constexpr std::size_t value(){
        return 2;
    }
};

namespace polygon {

template<typename Point, typename Tag>
struct access_polygon<agl::figure::polygon<Point, Tag>>{
    using regular = std::false_type;
    using type = undefined;
};

template<typename Point, typename Tag>
struct access_types<agl::figure::polygon<Point, Tag>>{
    using point = Point;
};

template<typename Point, typename Tag>
struct access_line_section<agl::figure::polygon<Point, Tag>>{
    using type = agl::line::line_section<Point>;
};

template<typename Point, typename Tag>
struct access_points<agl::figure::polygon<Point, Tag>>{
    inline constexpr static auto get(const agl::figure::polygon<Point, Tag> &object){
        return object.points();
    }
};

template<typename Point, typename Tag>
struct access_create<agl::figure::polygon<Point, Tag>>{
    inline constexpr static auto get(std::vector<Point> &&points){
        return agl::figure::polygon<Point, Tag>(std::forward<std::vector<Point>>(points));
    }
};

}

}

#endif // POLYGON_TRAITS_H
