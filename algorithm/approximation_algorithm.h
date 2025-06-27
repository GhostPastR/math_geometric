#ifndef APPROXIMATION_ALGORITHM_H
#define APPROXIMATION_ALGORITHM_H

#include <algorithm>
#include <ranges>
#include <vector>

#include "circle_algorithm.h"
#include "line_algorithm.h"

namespace approximation_algo{

template<c_point2d_decard Point>
constexpr std::vector<Point> splitting_evenly(const Point &start, const Point &stop, size_t count_point){
    if(count_point < 2){
        return {start, stop};
    }
    const auto dx = (stop.x() - start.x()) / count_point;
    const auto dy = (stop.y() - start.y()) / count_point;
    std::vector<Point> list;
    const auto numbers = std::ranges::iota_view{size_t(), count_point + 1};
    std::ranges::transform(numbers, std::back_inserter(list), [start, dx,dy](const auto &i){
        return Point(start.x() + i * dx, start.y() + i * dy);
    });
    return list;
}


template<c_line_view Line>
constexpr auto splitting_evenly(const Line &line, size_t count_point) -> std::vector<typename Line::point>{
    return splitting_evenly(line.view_begin.value, line.view_end.value, count_point);
}

template<c_arc Arc>
constexpr auto splitting_evenly(const Arc &arc, size_t count_point) -> std::vector<typename Arc::type_point>{
    using Type = Arc::type_coefficients;
    if(count_point < 2){
        return {point_algo::new_point(arc.center(), arc.start(), arc.radius()),
                point_algo::new_point(arc.center(), arc.stop(), arc.radius())};
    }
    const auto stop = (arc.start() > arc.stop()) ? (arc.stop() + algorithm::pi_in_2<Type>) : arc.stop();
    const auto da = (stop - arc.start()) / count_point;
    std::vector<typename Arc::type_point> list;

    const auto numbers = std::ranges::iota_view{size_t(), count_point + 1};
    std::ranges::transform(numbers, std::back_inserter(list), [arc, da](const auto &i){
        return point_algo::new_point(arc.center(), arc.start() + i * da, arc.radius());
    });
    return list;
}

template<c_circle Circle>
constexpr auto splitting_evenly(const Circle &circle, size_t count_point) -> std::vector<typename Circle::type_point>{
    using Type = Circle::type_coefficients;
    if(count_point < 2){
        return {point_algo::new_point(circle.center(), 0., circle.radius())};
    }
    const auto da = algorithm::pi_in_2<Type> / count_point;
    std::vector<typename Circle::type_point> list;  
    const auto numbers = std::ranges::iota_view{size_t(), count_point + 1};
    std::ranges::transform(numbers, std::back_inserter(list), [circle, da](const auto &i){
        return point_algo::new_point(circle.center(), i * da, circle.radius());
    });
    return list;
}


template<c_point2d_decard Point, std::floating_point Type>
constexpr std::vector<Point> splitting_evenly(const Point &start, const Point &stop, Type interval, Type &prior_remains){
    if(!(interval > 0) || (prior_remains < 0)){
        return {};
    }
    auto dist = point_algo::distance(start, stop);
    if(dist < prior_remains){
        prior_remains -= dist;
        return {};
    }
    Type count_point;
    Point point;
    if(!algorithm::compare(prior_remains, 0.)){
        std::modf(point_algo::distance(start, stop) / (interval - prior_remains), &count_point);
        const auto dx = (stop.x() - start.x()) / count_point;
        const auto dy = (stop.y() - start.y()) / count_point;
        point = {start.x() + dx, start.y() + dy};
    }

    std::modf(point_algo::distance(point, stop) / interval, &count_point);
    const auto dx = (stop.x() - point.x()) / count_point;
    const auto dy = (stop.y() - point.y()) / count_point;
    std::vector<Point> list;

    const auto numbers = std::ranges::iota_view{size_t(), count_point};
    std::ranges::transform(numbers, std::back_inserter(list), [start, dx,dy](const auto &i){
        return Point(start.x() + i * dx, start.y() + i * dy);
    });
    prior_remains = point_algo::distance(list.back(), stop);
    return list;
}

template<c_line_view Line, std::floating_point Type>
constexpr auto splitting_evenly(const Line &line, Type interval, Type &prior_remains) -> std::vector<typename Line::point>{
    return splitting_evenly(line.view_begin.value, line.view_end.value, interval, prior_remains);
}

template<c_arc Arc, std::floating_point Type>
constexpr auto splitting_evenly(const Arc &arc, Type interval, Type &prior_remains) -> std::vector<typename Arc::type_point>{
    using Point = Arc::type_point;
    if(!(interval > 0) || (prior_remains < 0)){
        return {};
    }
    const auto stop = (arc.start() > arc.stop()) ? (arc.stop() + algorithm::pi_in_2<Type>) : arc.stop();
    Type count_point;
    Point point;
    if(!algorithm::compare(prior_remains, 0.)){
        std::modf(circle_algo::length_arc(arc) / (interval - prior_remains), &count_point);
        const  auto da = (stop - arc.start()) / count_point;
        point = point_algo::new_point(arc.center(), arc.start() + da, arc.radius());
    }

    const auto new_arc = Arc(arc.center(), arc.radius(), point_algo::angle(arc.center(), point), arc.stop());
    std::modf(circle_algo::length_arc(new_arc) / (interval - prior_remains), &count_point);
    const auto da = (new_arc.stop() - new_arc.start()) / count_point;
    std::vector<Point> list;
    const auto numbers = std::ranges::iota_view{size_t(), count_point + 1};
    std::ranges::transform(numbers, std::back_inserter(list), [arc, da](const auto &i){
        return point_algo::new_point(arc.center(), arc.start() + i * da, arc.radius());
    });
    prior_remains = circle_algo::length_arc(Arc(new_arc.center(), new_arc.radius(), point_algo::angle(new_arc.center(), list.back()), new_arc.stop()));
    return list;
}

}

#endif // APPROXIMATION_ALGORITHM_H
