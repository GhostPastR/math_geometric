#ifndef AGL_ALGORITHM_PERPENDICULAR_IMPLEMENTATION_H
#define AGL_ALGORITHM_PERPENDICULAR_IMPLEMENTATION_H

#include "system/system_concept.h"
#include "system/traits.h"
#include "algorithm/equation_of_line/interface.h"
#include <cmath>

namespace agl::algorithm::dispatch {

template<typename Figure,
         typename Point,
         typename LineOut,
         typename CoordinateSystem,
         std::size_t Dimension>
struct perpendicular{
    inline constexpr static auto get(const Figure &figure, const Point &point){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

//Переделать!!!
template<c_group_line Line,
         c_point_2d Point,
         c_straight_line LineOut>
struct perpendicular<Line,
                     Point,
                     LineOut,
                     agl::system_coordinat::cartesian,
                     2>{
    inline constexpr static auto get(const Line &line, const Point &point){
        using namespace traits::point;
        const auto [a,b,c] = agl::algorithm::equation_of_line(line);
        const auto x = agl::traits::point::access_point<Point, 0>::get(point);
        const auto y = agl::traits::point::access_point<Point, 1>::get(point);

        using array = std::array<std::remove_const_t<decltype(a)>,3>;
        const auto [na,nb,nc] = agl::algorithm::normalized(array{b, -a, algorithm::determine(a, b, x, y)});
        return agl::traits::straight_line::access_create<LineOut>::get(na, nb, nc);
    }
};

}


namespace agl::algorithm::geometry {

template<typename Figure,
         typename Point,
         typename LineOut>
inline constexpr auto perpendicular(const Figure &figure, const Point &point){
    using type_cs1 = traits::coordinate_system<Figure>::system;
    using type_cs2 = traits::coordinate_system<Point>::system;
    constexpr auto dimension1 = traits::dimension<Figure>::value();
    constexpr auto dimension2 = traits::dimension<Point>::value();

    static_assert(agl::assert::is_correct_compare<type_cs1, type_cs2>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension1, dimension2), "Error!");

    return dispatch::perpendicular<Figure,
                                   Point,
                                   LineOut,
                                   type_cs1,
                                   dimension1>::get(figure, point);
}

}


#endif // AGL_ALGORITHM_PERPENDICULAR_IMPLEMENTATION_H
