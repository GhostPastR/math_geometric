#ifndef AGL_ALGORITHM_INTERSECTION_IMPLEMENTATION_H
#define AGL_ALGORITHM_INTERSECTION_IMPLEMENTATION_H

#include "system/assert.h"
#include "system/traits.h"
#include "implementation_cartesian.h"

namespace agl::algorithm::dispatch {

template<typename Figure1,
         typename Figure2,
         typename PointOut,
         typename SystemCoorinate,
         std::size_t Dimension>
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
                    agl::system_coordinat::cartesian,
                    2>{
    inline constexpr static auto get(const Figure1 &figure1, const Figure2 &figure2){
        return agl::algorithm::geometry::cartesian::intersection<Figure1,
                                                                 Figure2,
                                                                 PointOut>(figure1, figure2);
    }
};



}


namespace agl::algorithm::geometry {

template<typename Figure1,
         typename Figure2,
         typename PointOut>
inline constexpr auto intersection(const Figure1 &figure1, const Figure2 &figure2){
    using type_cs1 = traits::coordinate_system<Figure1>::system;
    using type_cs2 = traits::coordinate_system<Figure2>::system;
    constexpr auto dimension1 = traits::dimension<Figure1>::value();
    constexpr auto dimension2 = traits::dimension<Figure2>::value();
    static_assert(agl::assert::is_correct_compare<type_cs1, type_cs2>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension1, dimension2), "Error!");
    return dispatch::intersection<Figure1,
                                  Figure2,
                                  PointOut,
                                  type_cs1,
                                  dimension1>::get(figure1, figure2);
}

}


#endif // AGL_ALGORITHM_INTERSECTION_IMPLEMENTATION_H
