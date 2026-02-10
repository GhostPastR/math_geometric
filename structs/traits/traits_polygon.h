#ifndef AGL_STRUCT_POLYGON_TRAITS_H
#define AGL_STRUCT_POLYGON_TRAITS_H

#include "system/traits.h"
#include "structs/geometric/line_section.h"
#include "structs/geometric/polygon.h"

namespace agl::traits{

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

template<typename Point, typename Tag>
struct make<agl::figure::polygon<Point, Tag>>{
    inline constexpr static auto apply(const std::vector<Point> &points){
        return agl::figure::polygon<Point, Tag>(points);
    }

    template<typename TPoint>
    inline constexpr static auto apply(const std::vector<TPoint> &points){
        std::vector<Point> temp;
        temp.reserve(points.size());
        std::ranges::transform(points, std::back_inserter(temp), [](auto &&item){
            return agl::traits::make<Point>::apply(agl::traits::point::access_point<TPoint, 0>::get(item),
                                                   agl::traits::point::access_point<TPoint, 1>::get(item));
        });
        return agl::figure::polygon<Point, Tag>(std::move(temp));
    }
};

namespace polygon {

template<typename Point, typename Tag>
struct access_tag<agl::figure::polygon<Point, Tag>>{
    using type_tag = Tag;
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

}

}

#endif // POLYGON_TRAITS_H
