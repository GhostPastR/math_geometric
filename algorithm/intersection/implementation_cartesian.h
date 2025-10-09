#ifndef AGL_ALGORITHM_INTERSECTION_CARTESIAN_IMPLEMENTATION_H
#define AGL_ALGORITHM_INTERSECTION_CARTESIAN_IMPLEMENTATION_H

#include "algorithm/equation_of_line/interface.h"
#include "algorithm/belongs_to_area_of_line/interface.h"
#include "algorithm/contain/interface.h"
#include "algorithm/get_lines/interface.h"
#include <cmath>
#include <ranges>

namespace agl::algorithm::cartesian::d2::dispatch {

template<typename Figure1,
         typename Figure2,
         typename PointOut>
struct intersection{
    inline constexpr static auto get(const Figure1 &figure1, const Figure2 &figure2){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<c_group_line Line1,
         c_group_line Line2,
         c_point_2d PointOut>
struct intersection<Line1,
                    Line2,
                    PointOut>{
    inline constexpr static auto get(const Line1 &line1, const Line2 &line2) -> std::optional<PointOut>{
        const auto [a1,b1,c1] = agl::algorithm::equation_of_line(line1);
        const auto [a2,b2,c2] = agl::algorithm::equation_of_line(line2);
        if(const auto c = algorithm::determine(a1, a2, b1, b2); !algorithm::compare(c, decltype(c){})){
            auto point = agl::traits::point::access_create<PointOut>::get(algorithm::determine(b1, b2, c1, c2) / c,
                                                                          algorithm::determine(c1, c2, a1, a2) / c);
            if(agl::algorithm::belongs_to_area_of_line(line1, point)
                && agl::algorithm::belongs_to_area_of_line(line2, point)){
                return point;
            }
        }
        return std::nullopt;
    }
};

template<c_group_circle ElCircle,
         c_group_line Line,
         c_point_2d PointOut>
struct intersection<ElCircle,
                    Line,
                    PointOut>{
    inline constexpr static auto get(const ElCircle &el_circle, const Line &line)
        -> std::pair<std::optional<PointOut>, std::optional<PointOut>>{
        using Point = agl::traits::circle::access_types<ElCircle>::center;
        using Type = agl::traits::point::access_types<Point>::point;
        const auto &center = traits::circle::access_center<ElCircle>::get(el_circle);
        const auto &radius = traits::circle::access_radius<ElCircle>::get(el_circle);
        const auto &x = traits::point::access_point<Point, 0>::get(center);
        const auto &y = traits::point::access_point<Point, 1>::get(center);

        const auto [a,b,c] = agl::algorithm::equation_of_line(line);
        const auto value = c + b * y;
        const auto roots = algorithm::get_roots_equation(algorithm::quadratic<Type>(
            a * a + b * b,
            2 * (a * value - b * b * x),
            b * b * (x * x - radius * radius) + value * value));

        std::pair<std::optional<PointOut>, std::optional<PointOut>> points;
        if(roots.first.has_value()){
            points.first = PointOut(roots.first.value(), (-a * roots.first.value() - c) / b);
            if(roots.second.has_value()){
                points.second = PointOut(roots.second.value(), (-a * roots.second.value() - c) / b);
            }
        }
        const bool is_point1 = points.first.has_value() && agl::algorithm::contain(line, points.first.value());
        if(!is_point1){
            points.first = std::nullopt;
        }
        const bool is_point2 = points.second.has_value() && agl::algorithm::contain(line, points.second.value());
        if(!is_point2){
            points.second = std::nullopt;
        }
        if(!points.first.has_value()){
            std::swap(points.first, points.second);
        }

        return points;
    }
};

template<c_group_circle ElCircle1,
         c_group_circle ElCircle2,
         c_point_2d PointOut>
struct intersection<ElCircle1,
                    ElCircle2,
                    PointOut>{
    inline constexpr static auto get(const ElCircle1 &el_circle1, const ElCircle2 &el_circle2)
        -> std::pair<std::optional<PointOut>, std::optional<PointOut>>{
        using Point1 = agl::traits::circle::access_types<ElCircle1>::center;
        const auto &center1 = traits::circle::access_center<ElCircle1>::get(el_circle1);
        const auto &radius1 = traits::circle::access_radius<ElCircle1>::get(el_circle1);
        const auto &x1 = traits::point::access_point<Point1, 0>::get(center1);
        const auto &y1 = traits::point::access_point<Point1, 1>::get(center1);

        using Point2 = agl::traits::circle::access_types<ElCircle2>::center;
        const auto &center2 = traits::circle::access_center<ElCircle2>::get(el_circle2);
        const auto &radius2 = traits::circle::access_radius<ElCircle2>::get(el_circle2);
        const auto &x2 = traits::point::access_point<Point2, 0>::get(center2);
        const auto &y2 = traits::point::access_point<Point2, 1>::get(center2);

        const auto d = std::sqrt(std::pow(x1 - x2, 2.) + std::pow(y1 - y2, 2.));
        if(algorithm::compare(d, 0.)){
            return {};
        }
        const auto l = (std::pow(radius1, 2.) - std::pow(radius2, 2.) + std::pow(d,2)) / (2 * d);
        const auto dl = std::pow(radius1, 2.) - std::pow(l, 2.);
        if(dl < 0){
            return {};
        }
        const auto h = std::sqrt(std::pow(radius1, 2.) - std::pow(l, 2.));
        const auto a1 = (l / d);
        const auto a2 = (x2 - x1);
        const auto a3 = (h / d);
        const auto a4 = (y2 - y1);
        std::pair<std::optional<PointOut>, std::optional<PointOut>> points;
        points.first = {a1 * a2 + a3 * a4 + x1, a1 * a4 - a3 * a1 + y1};
        points.second = {a1 * a2 - a3 * a4 + x1, a1 * a4 + a3 * a1 + y1};
        if(points.first == points.second){
            points.second = std::nullopt;
        }
        return points;
    }
};

template<c_polygon Polygon,
         c_group_line Line,
         c_point_2d PointOut>
struct intersection<Polygon,
                    Line,
                    PointOut>{
    inline constexpr static auto get(const Polygon &polygon, const Line &line) -> std::vector<PointOut>{
        using Point = agl::traits::polygon::access_types<Polygon>::point;
        using s_line = agl::traits::polygon::access_line_section<Polygon>::type;
        const auto lines = agl::algorithm::get_lines<s_line>(polygon);
        auto temp = lines | std::ranges::views::transform([line](const auto &item){
                        return agl::algorithm::cartesian::d2::dispatch::intersection<s_line,
                                                                                     Line,
                                                                                     PointOut>::get(item, line);
                    })
                    | std::ranges::views::filter([](const auto &point){ return point.has_value(); })
                    | std::ranges::views::transform([](const auto &p){ return p.value(); });
        std::vector<PointOut> points(temp.begin(), temp.end());
        std::sort(points.begin(), points.end(), [](const auto &p1, const auto &p2){
            const auto &x1 = traits::point::access_point<PointOut, 0>::get(p1);
            const auto &y1 = traits::point::access_point<PointOut, 1>::get(p1);
            const auto &x2 = traits::point::access_point<PointOut, 0>::get(p2);
            const auto &y2 = traits::point::access_point<PointOut, 1>::get(p2);
            return (x1 < x2) || (x1 == x2) && (y1 < y2);
        });
        auto ret = std::ranges::unique(points);
        points.erase(ret.begin(), ret.end());
        return points;
    }
};

// template<c_group_polygon Polygon1,
//          c_group_polygon Polygon2,
//          typename PointOut>
// struct intersection<Polygon1,
//                     Polygon2,
//                     PointOut>{
//     inline constexpr static auto get(const Polygon1 &polygon1, const Polygon2 &polygon2) -> std::vector<PointOut>{
//         // //Функция определяет пересикает ли полигон другой полигон
//         // template<c_polugon Polygon>
//         // constexpr bool polygon_intersect_polygon(const Polygon &polygon1, const Polygon &polygon2){
//         //     auto lines1 = get_lines(polygon1);
//         //     auto lines2 = get_lines(polygon2);
//         //     return std::ranges::any_of(lines1, [&lines2](const auto &line1){
//         //         return std::ranges::any_of(lines2, [&line1](const auto &line2){
//         //             return line_algo::intersection_line(line1, line2).has_value();
//         //         });
//         //     });
//         // }

//         return PointOut{};
//     }
// };

}


namespace agl::algorithm::geometry::cartesian {

template<typename Figure1,
         typename Figure2,
         typename PointOut>
inline constexpr auto intersection(const Figure1 &figure1, const Figure2 &figure2){
    return agl::algorithm::cartesian::d2::dispatch::intersection<Figure1,
                                                                 Figure2,
                                                                 PointOut>::get(figure1, figure2);
}

}


#endif // AGL_ALGORITHM_INTERSECTION_CARTESIAN_IMPLEMENTATION_H
