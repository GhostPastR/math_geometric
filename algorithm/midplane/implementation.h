#ifndef AGL_ALGORITHM_MIDPLANE_IMPLEMENTATION_H
#define AGL_ALGORITHM_MIDPLANE_IMPLEMENTATION_H

#include <numeric>
#include "algorithm/math_algorithm.h"
#include "system/traits.h"
#include "algorithm/create_point/interface.h"

namespace agl::algorithm::dispatch::d2 {

template<typename T>
class Temp;

template<typename Object,
         typename ObjectOut>
struct midplane{
    inline constexpr static auto get(const Object &a, const Object &b){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<c_point_2d Point,
         c_create_point_2d PointOut>
    requires c_cartesian_all<Point, PointOut> && c_demension_2_all<Point, PointOut>
struct midplane<Point,
                PointOut>{
    inline constexpr static auto get(const Point &a, const Point &b){
        using namespace traits::point;
        return traits::make<PointOut>::apply(std::midpoint(access_point<Point, 0>::get(a), access_point<Point, 0>::get(b)),
                                             std::midpoint(access_point<Point, 1>::get(a), access_point<Point, 1>::get(b)));
    }
};

template<typename Point,
         c_create_point_3d PointOut>
    requires c_cartesian_all<Point, PointOut> && c_demension_3_all<Point, PointOut>
struct midplane<Point,
                PointOut>{
    inline constexpr static auto get(const Point &a, const Point &b){
        using namespace traits::point;

        return traits::make<PointOut>::apply(std::midpoint(access_point<Point, 0>::get(a), access_point<Point, 0>::get(b)),
                                             std::midpoint(access_point<Point, 1>::get(a), access_point<Point, 1>::get(b)),
                                             std::midpoint(access_point<Point, 2>::get(a), access_point<Point, 2>::get(b)));
    }
};

}



namespace agl::algorithm::dispatch::d1 {

template<typename Figure>
struct midplane{
    inline constexpr static auto get(const Figure &figure){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<c_arc Figure>
    requires c_cartesian<Figure> && c_demension_2<Figure>
struct midplane<Figure>{
    inline constexpr static auto get(const Figure &figure){
        using Point = traits::arc::access_types<Figure>::center;
        using Type = agl::traits::point::element_point_v<Point, 0>;

        const auto &start = traits::arc::access_angle<Figure, 0>::get(figure);
        const auto &stop = traits::arc::access_angle<Figure, 1>::get(figure);
        const auto &radius = traits::arc::access_radius<Figure>::get(figure);
        const auto &center = traits::arc::access_center<Figure>::get(figure);

        auto a = stop - start;
        if(start > stop){
            a += algorithm::pi_in_2<Type>;
        }
        return agl::algorithm::create_point<Point>(center, radius, a / 2.);
    }
};

}

#endif // AGL_ALGORITHM_MIDPLANE_IMPLEMENTATION_H
