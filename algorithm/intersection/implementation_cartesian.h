#ifndef AGL_ALGORITHM_INTERSECTION_CARTESIAN_IMPLEMENTATION_H
#define AGL_ALGORITHM_INTERSECTION_CARTESIAN_IMPLEMENTATION_H

#include "algorithm/equation_of_line/interface.h"
#include "algorithm/belongs_to_area_of_line/interface.h"
#include "algorithm/contain/interface.h"
#include <cmath>

namespace agl::algorithm::cartesian::d2::dispatch {

template<typename Figure1,
         typename Figure2,
         typename PointOut,
         typename Group1,
         typename Group2>
struct intersection{
    inline constexpr static auto get(const Figure1 &figure1, const Figure2 &figure2){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<typename Figure1,
         typename Figure2,
         typename PointOut>
struct intersection<Figure1,
                    Figure2,
                    PointOut,
                    agl::group::lines,
                    agl::group::lines>{
    inline constexpr static auto get(const Figure1 &figure1, const Figure2 &figure2) -> std::optional<PointOut>{
        const auto [a1,b1,c1] = agl::algorithm::equation_of_line(figure1);
        const auto [a2,b2,c2] = agl::algorithm::equation_of_line(figure2);
        if(const auto c = algorithm::determine(a1, a2, b1, b2); !algorithm::compare(c, decltype(c){})){
            auto point = PointOut{algorithm::determine(b1, b2, c1, c2) / c,
                                  algorithm::determine(c1, c2, a1, a2) / c};
            if(agl::algorithm::belongs_to_area_of_line(figure1, point)
                && agl::algorithm::belongs_to_area_of_line(figure2, point)){
                return point;
            }
        }
        return std::nullopt;
    }
};

template<typename Figure1,
         typename Figure2,
         typename PointOut>
struct intersection<Figure1,
                    Figure2,
                    PointOut,
                    agl::group::elements_circles,
                    agl::group::lines>{
    inline constexpr static auto get(const Figure1 &figure1, const Figure2 &figure2)
        -> std::pair<std::optional<PointOut>, std::optional<PointOut>>{
        using Point = agl::traits::traits_circle::type_property<Figure1>::type_center;
        using Type = agl::traits::traits_point::type_property<Point>::type_point;
        const auto &center = traits::traits_circle::access_center<Figure1>::get(figure1);
        const auto &radius = traits::traits_circle::access_radius<Figure1>::get(figure1);
        const auto &x = traits::traits_point::access_point<Point, 0>::get(center);
        const auto &y = traits::traits_point::access_point<Point, 1>::get(center);

        const auto [a,b,c] = agl::algorithm::equation_of_line(figure2);
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
        const bool is_point1 = points.first.has_value() && agl::algorithm::contain(figure2, points.first.value());
        if(!is_point1){
            points.first = std::nullopt;
        }
        const bool is_point2 = points.second.has_value() && agl::algorithm::contain(figure2, points.second.value());
        if(!is_point2){
            points.second = std::nullopt;
        }
        if(!points.first.has_value()){
            std::swap(points.first, points.second);
        }

        return points;
    }
};

template<typename Figure1,
         typename Figure2,
         typename PointOut>
struct intersection<Figure1,
                    Figure2,
                    PointOut,
                    agl::group::elements_circles,
                    agl::group::elements_circles>{
    inline constexpr static auto get(const Figure1 &figure1, const Figure2 &figure2)
        -> std::pair<std::optional<PointOut>, std::optional<PointOut>>{
        using Point1 = agl::traits::traits_circle::type_property<Figure1>::type_center;
        const auto &center1 = traits::traits_circle::access_center<Figure1>::get(figure1);
        const auto &radius1 = traits::traits_circle::access_radius<Figure1>::get(figure1);
        const auto &x1 = traits::traits_point::access_point<Point1, 0>::get(center1);
        const auto &y1 = traits::traits_point::access_point<Point1, 1>::get(center1);

        using Point2 = agl::traits::traits_circle::type_property<Figure2>::type_center;
        const auto &center2 = traits::traits_circle::access_center<Figure2>::get(figure2);
        const auto &radius2 = traits::traits_circle::access_radius<Figure2>::get(figure2);
        const auto &x2 = traits::traits_point::access_point<Point2, 0>::get(center2);
        const auto &y2 = traits::traits_point::access_point<Point2, 1>::get(center2);

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

}


namespace agl::algorithm::geometry::cartesian {

template<typename Figure1,
         typename Figure2,
         typename PointOut,
         typename Group1,
         typename Group2>
inline constexpr auto intersection(const Figure1 &figure1, const Figure2 &figure2){
    return agl::algorithm::cartesian::d2::dispatch::intersection<Figure1,
                                                                 Figure2,
                                                                 PointOut,
                                                                 Group1,
                                                                 Group2>::get(figure1, figure2);
}

}


#endif // AGL_ALGORITHM_INTERSECTION_CARTESIAN_IMPLEMENTATION_H
