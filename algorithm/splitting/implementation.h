#ifndef AGL_ALGORITHM_SPLITTING_IMPLEMENTATION_H
#define AGL_ALGORITHM_SPLITTING_IMPLEMENTATION_H

#include <ranges>
#include <algorithm>
#include "algorithm/direction/interface.h"
#include "algorithm/distance/interface.h"
#include "system/system_concept.h"

namespace agl::algorithm::dispatch {

template<typename Object>
struct splitting{
    inline constexpr static auto get(const Object &object, size_t count_point, algorithm::direct direct){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

namespace d2 {

template<c_point_2d Point>
struct splitting{
    inline constexpr static auto get(const Point &start, const Point &stop, size_t count_point)
        -> std::vector<Point>{
        if(count_point < 2){
            return {start, stop};
        }
        const auto[x1, y1] = agl::traits::access_propery<Point>::get(start);
        const auto[x2, y2] = agl::traits::access_propery<Point>::get(stop);
        const auto dx = (x2 - x1) / count_point;
        const auto dy = (y2 - y1) / count_point;
        std::vector<Point> points;
        const auto numbers = std::ranges::iota_view{size_t(), count_point + 1};
        points.reserve(count_point + 1);
        std::ranges::transform(numbers, std::back_inserter(points), [x=x1,y=y1,dx=dx,dy=dy](const auto &i){
            return agl::traits::make<Point>::apply(x + i * dx, y + i * dy);
        });
        return points;
    }

    template<std::floating_point Type>
    inline constexpr static auto get(const Point &start, const Point &stop, Type interval, Type &prior_remains)
        -> std::vector<Point>{
        if(!(interval > 0) || (prior_remains < 0)){
            return {};
        }
        auto dist = agl::algorithm::distance(start, stop);
        if(dist < prior_remains){
            prior_remains -= dist;
            return {};
        }
        const auto[x1, y1] = agl::traits::access_propery<Point>::get(start);
        const auto[x2, y2] = agl::traits::access_propery<Point>::get(stop);

        Type count_point;
        Point point;
        if(!algorithm::compare(prior_remains, 0.)){
            std::modf(agl::algorithm::distance(start, stop) / (interval - prior_remains), &count_point);
            point = agl::traits::make<Point>::apply(x1 + (x2 - x1) / count_point,
                                                    y1 + (y2 - y1) / count_point);
        }

        std::modf(agl::algorithm::distance(point, stop) / interval, &count_point);
        const auto[px, py] = agl::traits::access_propery<Point>::get(point);
        const auto dx = (x2 - px) / count_point;
        const auto dy = (y2 - py) / count_point;

        std::vector<Point> points;
        const auto numbers = std::ranges::iota_view{size_t(), count_point};
        points.reserve(count_point + 1);
        std::ranges::transform(numbers, std::back_inserter(points), [x=x1,y=y1,dx=dx,dy=dy](const auto &i){
            return agl::traits::make<Point>::apply(x + i * dx, y + i * dy);
        });
        prior_remains = agl::algorithm::distance(points.back(), stop);
        return points;
    }

};

}

template<c_line_section Line>
struct splitting<Line>{
    inline constexpr static auto get(const Line &line, size_t count_point, algorithm::direct){
        using Point = agl::traits::line_section::access_types<Line>::point;
        auto [start, stop] = agl::traits::access_propery<Line>::get(line);
        return d2::splitting<Point>::get(start, stop, count_point);
    }
};

template<c_arc Arc>
struct splitting<Arc>{
    inline constexpr static auto get(const Arc &arc, size_t count_point, algorithm::direct direct = algorithm::direct::RIGHT)
        -> std::vector<typename agl::traits::arc::access_types<Arc>::center>{
        using Point = agl::traits::arc::access_types<Arc>::center;
        using Type = agl::traits::arc::access_types<Arc>::radius;
        auto mod_arc = (direct == algorithm::direct::RIGHT) ? arc : agl::traits::arc::access_change<Arc>::get(arc);
        auto [center, radius, start, stop] = agl::traits::access_propery<Arc>::get(mod_arc);
        if(count_point < 2){
            return {agl::algorithm::create_point<Point>(center, radius, start),
                    agl::algorithm::create_point<Point>(center, radius, stop)};
        }
        const auto temp_stop = (start > stop) ? (stop + algorithm::pi_in_2<Type>) : stop;
        const auto da = (temp_stop - start) / count_point;

        std::vector<Point> points;
        const auto numbers = std::ranges::iota_view{size_t(), count_point + 1};
        points.reserve(count_point + 1);
        std::ranges::transform(numbers, std::back_inserter(points), [center=center, radius=radius, start=start, da=da](const auto &i){
            return agl::algorithm::create_point<Point>(center, radius, start + da * i);
        });
        return points;
    }
};

template<c_circle Circle>
struct splitting<Circle>{
    inline constexpr static auto get(const Circle &circle, size_t count_point, algorithm::direct)
    -> std::vector<typename agl::traits::circle::access_types<Circle>::center>{
        using Point = agl::traits::circle::access_types<Circle>::center;
        using Type = agl::traits::circle::access_types<Circle>::radius;
        auto [center, radius] = agl::traits::access_propery<Circle>::get(circle);
        if(count_point < 2){
            return {agl::algorithm::create_point<Point>(center, radius, Type{})};
        }
        const auto da = algorithm::pi_in_2<Type> / count_point;

        std::vector<Point> points;
        const auto numbers = std::ranges::iota_view{size_t(), count_point + 1};
        std::ranges::transform(numbers, std::back_inserter(points), [center=center, radius=radius, da=da](const auto &i){
            return agl::algorithm::create_point<Point>(center, radius, da * i);
        });
        return points;
    }
};

}



namespace agl::algorithm::dispatch::remains {

template<typename Object,
         typename Type>
struct splitting{
    inline constexpr static auto get(const Object &object, Type interval, Type &prior_remains, algorithm::direct direct){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<c_line_section Line,
         std::floating_point Type>
struct splitting<Line,
                 Type>{
    inline constexpr static auto get(const Line &line, Type interval, Type &prior_remains, algorithm::direct){
        using Point = agl::traits::line_section::access_types<Line>::point;
        auto [start, stop] = agl::traits::access_propery<Line>::get(line);
        return d2::splitting<Point>::get(start, stop, interval, prior_remains);
    }
};

template<typename T>
class Temp;

template<c_arc Arc,
         std::floating_point Type>
struct splitting<Arc,
                 Type>{
    inline constexpr static auto get(const Arc &arc, Type interval, Type &prior_remains, algorithm::direct direct = algorithm::direct::RIGHT)
        -> std::vector<typename agl::traits::arc::access_types<Arc>::center>{
        using Point = agl::traits::arc::access_types<Arc>::center;
        using Radius = agl::traits::arc::access_types<Arc>::radius;
        using Angle = agl::traits::arc::access_types<Arc>::angle;
        auto mod_arc = (direct == algorithm::direct::RIGHT) ? arc : agl::traits::arc::access_change<Arc>::get(arc);
        auto [center, radius, start, stop] = agl::traits::access_propery<Arc>::get(mod_arc);
        if(!(interval > 0) || (prior_remains < 0) || (prior_remains >= interval)){
            return {};
        }
        const auto temp_stop = (start > stop) ? (stop + algorithm::pi_in_2<Type>) : stop;
        Type count_point;
        auto angle_start = start;
        if(!algorithm::compare(prior_remains, 0.)){
            const auto da = (interval - prior_remains) / radius;
            auto point = agl::algorithm::create_point<Point>(center, radius, start + da);
            angle_start = agl::algorithm::direction<decltype(angle_start)>(center, point);
        }
        const auto new_arc = agl::traits::make<Arc>::apply(center, radius, angle_start, temp_stop);
        std::modf((agl::algorithm::distance(new_arc) - prior_remains) / interval, &count_point);

        std::vector<Point> points;
        const auto numbers = std::ranges::iota_view{size_t(), count_point + 1};
        points.reserve(count_point + 1);
        std::ranges::transform(numbers, std::back_inserter(points), [center=center, radius=radius, start=angle_start, da=interval / radius](const auto &i){
            return agl::algorithm::create_point<Point>(center, radius, start + da * i);
        });
        const auto temp_arc = agl::traits::make<Arc>::apply(center, radius,
                                                            agl::algorithm::direction<decltype(angle_start)>(center, points.back()), temp_stop);
        prior_remains = agl::algorithm::distance(temp_arc);
        return points;
    }
};

}

#endif // AGL_ALGORITHM_SPLITTING_IMPLEMENTATION_H
