#ifndef AGL_ALGORITHM_IS_CORRECT_POLYGON_IMPLEMENTATION_H
#define AGL_ALGORITHM_IS_CORRECT_POLYGON_IMPLEMENTATION_H

#include <cmath>
#include <vector>
#include "system/assert.h"
#include "system/traits.h"
#include "algorithm/distance/interface.h"
#include "algorithm/center/interface.h"


namespace agl::algorithm::dispatch {

template<typename Polygon, typename Tag, typename CoordinateSystem, std::size_t Dimension>
struct is_correct_polygon{
    inline constexpr static auto get(const Polygon &polygon){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<typename Polygon>
struct is_correct_polygon<Polygon, agl::tag::tag_polygon, agl::system_coordinat::cartesian, 2>{
    inline constexpr static auto get(const Polygon &polygon){
        return true;
    }
};


template<typename Polygon>
struct is_correct_polygon<Polygon, agl::tag::tag_convex_polygone, agl::system_coordinat::cartesian, 2>{
    inline constexpr static auto get(const Polygon &polygon){
        using Point = agl::traits::traits_polygon::type_property<Polygon>::type_point;
        const auto &points = agl::traits::traits_polygon::access_points<Polygon>::get(polygon);
        if(points.size() < 3){
            return false;
        }
        auto calc_direct = [](const Point &p1, const Point &p2, const Point &p3){
            using x = agl::traits::traits_point::access_point<Point, 0>;
            using y = agl::traits::traits_point::access_point<Point, 1>;
            const Point v1 = {x::get(p2) - x::get(p1), y::get(p2) - y::get(p1)};
            const Point v2 = {x::get(p3) - x::get(p2), y::get(p3) - y::get(p2)};
            return algorithm::determine(x::get(v1), y::get(v1), x::get(v2), y::get(v2));
        };
        std::size_t direct = calc_direct(*std::prev(points.end()), *points.begin(), *std::next(points.begin())) > 0 ? 1 : -1;
        for(auto begin = std::next(points.begin()), end = std::prev(points.end()); begin != end; ++begin ){
            if(std::exchange(direct,calc_direct(*std::prev(begin), *begin, *std::next(begin)) > 0 ? 1 : -1) != direct){
                return false;
            }
        }
        return true;
    }
};

template<typename Polygon>
struct is_correct_polygon<Polygon, agl::tag::tag_rectangle, agl::system_coordinat::cartesian, 2>{
    inline constexpr static auto get(const Polygon &polygon){
        using Point = agl::traits::traits_polygon::type_property<Polygon>::type_point;
        const auto &points = agl::traits::traits_polygon::access_points<Polygon>::get(polygon);
        if(points.size() != 4){
            return false;
        }
        if((agl::algorithm::distance(points[0], points[1]) == agl::algorithm::distance(points[2], points[3]))
            && (agl::algorithm::distance(points[1], points[2]) == agl::algorithm::distance(points[0], points[3]))){
            using x = agl::traits::traits_point::access_point<Point, 0>;
            using y = agl::traits::traits_point::access_point<Point, 1>;
            const Point point1 = {x::get(points[0]) - x::get(points[1]), y::get(points[0]) - y::get(points[1])};
            const Point point2 = {x::get(points[2]) - x::get(points[1]), y::get(points[2]) - y::get(points[1])};
            return algorithm::compare(algorithm::determine(x::get(point1), y::get(point1), y::get(point2), x::get(point2)), 0.);
        }
        return false;
    }
};

template<typename Polygon>
struct is_correct_polygon<Polygon, agl::tag::tag_triangle, agl::system_coordinat::cartesian, 2>{
    inline constexpr static auto get(const Polygon &polygon){
        const auto &points = agl::traits::traits_polygon::access_points<Polygon>::get(polygon);
        if(points.size() != 3){
            return false;
        }
        const auto l1 = agl::algorithm::distance(points[0], points[1]);
        const auto l2 = agl::algorithm::distance(points[1], points[2]);
        const auto l3 = agl::algorithm::distance(points[0], points[2]);
        return ((l1 < (l2 + l3)) && (l2 < (l1 + l3)) && (l3 < (l1 + l2)));
    }
};

template<typename Polygon>
struct is_correct_polygon<Polygon, agl::tag::tag_regular_polygon, agl::system_coordinat::cartesian, 2>{
    inline constexpr static auto get(const Polygon &polygon){
        using Point = agl::traits::traits_polygon::type_property<Polygon>::type_point;
        using Type = agl::traits::traits_point::type_property<Point>::type_point;
        const auto &points = agl::traits::traits_polygon::access_points<Polygon>::get(polygon);
        if(points.size() < 3){
            return false;
        }
        const auto center = agl::algorithm::center<Point>(polygon);
        std::vector<Type> lenghts;
        lenghts.reserve(points.size());
        std::transform(points.begin(), points.end(), std::back_inserter(lenghts), [center](const auto &item){
            return agl::algorithm::distance(item, center);
        });
        return std::all_of(std::next(lenghts.begin()), lenghts.end(), [lenght = lenghts.front()](const auto &item){
            return agl::algorithm::compare(item, lenght);
        });
    }
};


}


namespace agl::algorithm::geometry {

template<typename Polygon>
inline constexpr auto is_correct_polygon(const Polygon &polygon){
    using tag = traits::tag<Polygon>::type_tag;
    using type_cs = traits::coordinate_system<Polygon>::system;
    constexpr auto dimension = traits::dimension<Polygon>::value();
    static_assert(agl::assert::is_correct<tag>(), "Error!");
    static_assert(agl::assert::is_correct<type_cs>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");
    return dispatch::is_correct_polygon<Polygon, tag, type_cs, dimension>::get(polygon);
}

}


#endif // AGL_ALGORITHM_IS_CORRECT_POLYGON_IMPLEMENTATION_H
