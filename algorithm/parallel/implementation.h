#ifndef AGL_ALGORITHM_PARALLEL_IMPLEMENTATION_H
#define AGL_ALGORITHM_PARALLEL_IMPLEMENTATION_H

#include "algorithm/equation_of_line/interface.h"
#include "system/system_concept.h"
#include "system/traits.h"
#include <cmath>

namespace agl::algorithm::dispatch {

template<c_group_line Figure,
         typename Type,
         typename OutLine>
struct parallel{
    inline constexpr static auto get(const Figure &figure, const Type &distance){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<c_group_line Figure,
         c_unit Type,
         c_create_straight_line_2d OutLine>
    requires c_cartesian_all<Figure, OutLine> && c_demension_2_all<Figure, OutLine>
struct parallel<Figure,
                Type,
                OutLine>{
    inline constexpr static auto get(const Figure &figure, const Type &distance){
        const auto &d = agl::traits::value<Type>::get(distance);
        const auto [a,b,c] = agl::algorithm::equation_of_line(figure);
        return agl::traits::make<OutLine>::apply(a, b, c - d * (-std::sqrt(agl::algorithm::determine(a, -b, b, a))));
    }
};


}

#endif // AGL_ALGORITHM_PARALLEL_IMPLEMENTATION_H
