#ifndef AGL_ALGORITHM_PARALLEL_IMPLEMENTATION_H
#define AGL_ALGORITHM_PARALLEL_IMPLEMENTATION_H

#include "algorithm/equation_of_line/interface.h"
#include "system/system_concept.h"
#include "system/traits.h"
#include <cmath>

namespace agl::algorithm::dispatch {

template<c_group_line Figure,
         typename Type,
         typename OutLine,
         typename CoordinateSystem,
         std::size_t Dimension>
struct parallel{
    inline constexpr static auto get(const Figure &figure, const Type &distance){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<c_group_line Figure,
         typename Type,
         c_create_straight_line_2d OutLine>
struct parallel<Figure,
                Type,
                OutLine,
                agl::system_coordinat::cartesian,
                2>{
    inline constexpr static auto get(const Figure &figure, const Type &distance){
        const auto &d = agl::traits::value<Type>::get(distance);
        const auto [a,b,c] = agl::algorithm::equation_of_line(figure);

        // agl::traits::access_create<OutLine>::get()


        return OutLine{a, b, c - d * (-std::sqrt(agl::algorithm::determine(a, -b, b, a)))};
    }
};


}


namespace agl::algorithm::geometry {

template<typename Figure,
         typename Type,
         typename OutLine>
inline constexpr auto parallel(const Figure &figure, const Type &distance){
    using type_coordinate_system = traits::coordinate_system<Figure>::system;
    constexpr auto dimension = traits::dimension<Figure>::value();

    static_assert(agl::assert::is_correct<type_coordinate_system>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");

    return dispatch::parallel<Figure,
                              Type,
                              OutLine,
                              type_coordinate_system,
                              dimension>::get(figure, distance);
}

}


#endif // AGL_ALGORITHM_PARALLEL_IMPLEMENTATION_H
