#ifndef AGL_ALGORITHM_IS_CORRECT_POLYGON_IMPLEMENTATION_H
#define AGL_ALGORITHM_IS_CORRECT_POLYGON_IMPLEMENTATION_H

#include <cmath>
#include <vector>
#include "system/traits.h"
#include "algorithm/distance/interface.h"
#include "algorithm/center/interface.h"


namespace agl::algorithm::dispatch {

template<typename Polygon,
         typename Tag>
struct is_correct_polygon{
    inline constexpr static auto get(const Polygon &polygon){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

// template<typename Polygon>
// struct is_correct_polygon<Polygon, agl::tag::tag_polygon, agl::system_coordinat::cartesian, 2>{
//     inline constexpr static auto get(const Polygon &polygon){
//         return true;
//     }
// };


template<c_polygon Polygon>
    requires c_cartesian<Polygon> && c_demension_2<Polygon>
struct is_correct_polygon<Polygon,
                          agl::tag::polygon::convex>{
    inline constexpr static auto get(const Polygon &polygon){
        using Point = agl::traits::polygon::access_types<Polygon>::point;
        const auto &points = agl::traits::polygon::access_points<Polygon>::get(polygon);
        if(points.size() < 3){
            return false;
        }
        auto calc_direct = [](const Point &p1, const Point &p2, const Point &p3){
            const auto[x1, y1] = agl::traits::access_propery<Point>::get(p1);
            const auto[x2, y2] = agl::traits::access_propery<Point>::get(p2);
            const auto[x3, y3] = agl::traits::access_propery<Point>::get(p3);
            const auto v1 = agl::traits::make<Point>::apply(x2 - x1, y2 - y1);
            const auto v2 = agl::traits::make<Point>::apply(x3 - x2, y3 - y2);
            const auto[vx1, vy1] = agl::traits::access_propery<Point>::get(v1);
            const auto[vx2, vy2] = agl::traits::access_propery<Point>::get(v2);
            return algorithm::determine(vx1, vy1, vx2, vy2);
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

template<c_polygon Polygon>
    requires c_geographical<Polygon> && c_demension_2<Polygon>
struct is_correct_polygon<Polygon,
                          agl::tag::polygon::convex>{
    inline constexpr static auto get(const Polygon &polygon){
        using Point = agl::traits::polygon::access_types<Polygon>::point;
        const auto &points = agl::traits::polygon::access_points<Polygon>::get(polygon);
        if(points.size() < 3){
            return false;
        }
        // auto calc_direct = [](const Point &p1, const Point &p2, const Point &p3){
        //     using x = agl::traits::point::access_point<Point, 0>;
        //     using y = agl::traits::point::access_point<Point, 1>;
        //     const Point v1 = {x::get(p2) - x::get(p1), y::get(p2) - y::get(p1)};
        //     const Point v2 = {x::get(p3) - x::get(p2), y::get(p3) - y::get(p2)};
        //     return algorithm::determine(x::get(v1), y::get(v1), x::get(v2), y::get(v2));
        // };
        // std::size_t direct = calc_direct(*std::prev(points.end()), *points.begin(), *std::next(points.begin())) > 0 ? 1 : -1;
        // for(auto begin = std::next(points.begin()), end = std::prev(points.end()); begin != end; ++begin ){
        //     if(std::exchange(direct,calc_direct(*std::prev(begin), *begin, *std::next(begin)) > 0 ? 1 : -1) != direct){
        //         return false;
        //     }
        // }
        return true;
    }
};

template<c_polygon Polygon>
    requires c_cartesian<Polygon> && c_demension_2<Polygon>
struct is_correct_polygon<Polygon,
                          agl::tag::polygon::rectangle>{
    inline constexpr static auto get(const Polygon &polygon){
        using Point = agl::traits::polygon::access_types<Polygon>::point;
        const auto &points = agl::traits::polygon::access_points<Polygon>::get(polygon);
        if(points.size() != 4){
            return false;
        }
        if((agl::algorithm::distance(points[0], points[1]) == agl::algorithm::distance(points[2], points[3]))
            && (agl::algorithm::distance(points[1], points[2]) == agl::algorithm::distance(points[0], points[3]))){
            const auto[x1, y1] = agl::traits::access_propery<Point>::get(points[0]);
            const auto[x2, y2] = agl::traits::access_propery<Point>::get(points[1]);
            const auto[x3, y3] = agl::traits::access_propery<Point>::get(points[2]);
            const auto point1 = agl::traits::make<Point>::apply(x1 - x2, y1 - y2);
            const auto point2 = agl::traits::make<Point>::apply(x3 - x2, y3 - y2);
            const auto[px1, py1] = agl::traits::access_propery<Point>::get(point1);
            const auto[px2, py2] = agl::traits::access_propery<Point>::get(point2);
            return algorithm::compare(algorithm::determine(px1, py1, py2, px2), 0.);
        }
        return false;
    }
};

//Для треугольников
template<c_polygon Polygon,
         typename Tag>
    requires (!std::is_same_v<Tag, agl::tag::polygon::regular>) && c_cartesian<Polygon> && c_demension_2<Polygon>
struct is_correct_polygon<Polygon,
                          Tag>{
    inline constexpr static auto get(const Polygon &polygon){
        const auto &points = agl::traits::polygon::access_points<Polygon>::get(polygon);
        const auto l1 = agl::algorithm::distance(points[0], points[1]);
        const auto l2 = agl::algorithm::distance(points[1], points[2]);
        const auto l3 = agl::algorithm::distance(points[0], points[2]);
        return ((l1 < (l2 + l3)) && (l2 < (l1 + l3)) && (l3 < (l1 + l2)));
    }
};

template<c_polygon Polygon>
    requires c_cartesian<Polygon> && c_demension_2<Polygon>
struct is_correct_polygon<Polygon,
                          agl::tag::polygon::regular>{
    inline constexpr static auto get(const Polygon &polygon){
        using Point = agl::traits::polygon::access_types<Polygon>::point;
        using Type = agl::traits::point::element_point_v<Point, 0>;

        const auto &points = agl::traits::polygon::access_points<Polygon>::get(polygon);
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

#endif // AGL_ALGORITHM_IS_CORRECT_POLYGON_IMPLEMENTATION_H
