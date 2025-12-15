#ifndef AGL_ALGORITHM_PERPENDICULAR_IMPLEMENTATION_H
#define AGL_ALGORITHM_PERPENDICULAR_IMPLEMENTATION_H

#include "system/system_concept.h"
#include "system/traits.h"
#include "algorithm/equation_of_line/interface.h"
#include <cmath>

namespace agl::algorithm::dispatch {

template<typename Figure,
         typename Point,
         typename LineOut>
struct perpendicular{
    inline constexpr static auto get(const Figure &figure, const Point &point){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

//Переделать!!! Не понятно для прямой и луча как делать перпендикуляр
template<c_group_line Line,
         c_point_2d Point,
         c_straight_line LineOut>
    requires c_cartesian_all<Line, Point, LineOut> && c_demension_2_all<Line, Point, LineOut>
struct perpendicular<Line,
                     Point,
                     LineOut>{
    inline constexpr static auto get(const Line &line, const Point &point){
        using namespace traits::point;
        const auto [a,b,c] = agl::algorithm::equation_of_line(line);
        const auto x = agl::traits::point::access_point<Point, 0>::get(point);
        const auto y = agl::traits::point::access_point<Point, 1>::get(point);

        using array = std::array<std::remove_const_t<decltype(a)>,3>;
        const auto [na,nb,nc] = agl::algorithm::normalized(array{b, -a, algorithm::determine(a, b, x, y)});
        return agl::traits::make<LineOut>::apply(na, nb, nc);
    }
};

}

#endif // AGL_ALGORITHM_PERPENDICULAR_IMPLEMENTATION_H
