#ifndef AGL_ALGORITHM_INTERSECTION_IMPLEMENTATION_H
#define AGL_ALGORITHM_INTERSECTION_IMPLEMENTATION_H

#include "implementation_cartesian.h"

namespace agl::algorithm::dispatch {

template<typename Figure1,
         typename Figure2,
         typename PointOut>
struct intersection{
    inline constexpr static auto get(const Figure1 &figure1, const Figure2 &figure2){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<typename Figure1,
         typename Figure2,
         typename PointOut>
    requires c_cartesian_all<Figure1, Figure2, PointOut> && c_demension_2_all<Figure1, Figure2, PointOut>
struct intersection<Figure1,
                    Figure2,
                    PointOut>{
    inline constexpr static auto get(const Figure1 &figure1, const Figure2 &figure2){
        return agl::algorithm::cartesian::d2::dispatch::intersection<Figure1,
                                                                     Figure2,
                                                                     PointOut>::get(figure1, figure2);
    }
};



}

#endif // AGL_ALGORITHM_INTERSECTION_IMPLEMENTATION_H
