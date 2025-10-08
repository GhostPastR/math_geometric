#ifndef AGL_ALGORITHM_DISTANCE_IMPLEMENTATION_GEO_H
#define AGL_ALGORITHM_DISTANCE_IMPLEMENTATION_GEO_H

#include "algorithm/convert/implementation_geo.h"
#include "system/traits.h"

namespace agl::algorithm::dispatch::d2::geo_distance {

template<typename Point, typename CoordinateSystemGeo, std::size_t Dimension>
struct distance{
    inline constexpr static auto get(const Point &a, const Point &b){
        static_assert(false, "No 'distance' calculations have been implemented for these points.");
    }
};

template<typename Point>
struct distance<Point, agl::system_coordinat::geo::sc_default, 2>{
    inline constexpr static auto get(const Point &a, const Point &b){
        return traits::point::access_point<Point, 0>::get(
            agl::algorithm::dispatch::geo::convert<Point, Point, agl::system_coordinat::geo::sc_default, system_coordinat::polar, 2>(a,b));
    }
};

}

#endif // AGL_ALGORITHM_DISTANCE_IMPLEMENTATION_GEO_H
