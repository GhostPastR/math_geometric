#ifndef AGL_ALGORITHM_PERPENDICULAR_IMPLEMENTATION_H
#define AGL_ALGORITHM_PERPENDICULAR_IMPLEMENTATION_H

#include "system/traits.h"
#include "algorithm/equation_of_line/interface.h"
#include <cmath>
#include <optional>

namespace agl::algorithm::dispatch {

template<typename Figure, typename Point, typename LineOut, typename Group, typename CoordinateSystem, std::size_t Dimension>
struct perpendicular{
    inline constexpr static auto get(const Figure &figure, const Point &point){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<typename Figure, typename Point, typename LineOut>
struct perpendicular<Figure, Point, LineOut, agl::group::group_line, agl::system_coordinat::cartesian, 2>{
    inline constexpr static auto get(const Figure &figure, const Point &point){
        using namespace traits::traits_point;
        const auto [a,b,c] = agl::algorithm::equation_of_line(figure);
        return LineOut{-b, a, algorithm::determine(b, a, access_point<Point, 0>::get(point), access_point<Point, 1>::get(point))};
    }
};

}


namespace agl::algorithm::geometry {

template<typename Figure, typename Point, typename LineOut>
inline constexpr auto perpendicular(const Figure &figure, const Point &point){
    using type_cs1 = traits::coordinate_system<Figure>::system;
    using type_cs2 = traits::coordinate_system<Point>::system;
    using group = traits::group<Figure>::type_group;
    constexpr auto dimension1 = traits::dimension<Figure>::value();
    constexpr auto dimension2 = traits::dimension<Point>::value();

    static_assert(agl::assert::is_correct_compare<type_cs1, type_cs2>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension1, dimension2), "Error!");

    return dispatch::perpendicular<Figure, Point, LineOut, group, type_cs1, dimension1>::get(figure, point);
}

}


#endif // AGL_ALGORITHM_PERPENDICULAR_IMPLEMENTATION_H
