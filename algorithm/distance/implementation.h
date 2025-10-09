#ifndef AGL_ALGORITHM_DISTANCE_IMPLEMENTATION_H
#define AGL_ALGORITHM_DISTANCE_IMPLEMENTATION_H

#include <cmath>
#include "algorithm/distance/implementation_cartesian.h"
#include "algorithm/distance/implementation_geo.h"
#include "algorithm/distance/implementation_arc_cartesian.h"
#include "algorithm/distance/implementation_line_cartesian.h"
#include "algorithm/distance/implementation_d2.h"
#include "system/assert.h"

namespace agl::algorithm::dispatch::d1 {

template<typename Figure,
         typename CoordinateSystem,
         std::size_t Dimension>
struct distance{
    inline constexpr static auto get(const Figure &figure){
        static_assert(false, "No 'distance' calculations have been implemented for these objects.");
    }
};

template<c_group_circle ElCircle,
         typename CoordinateSystem,
         std::size_t Dimension>
struct distance<ElCircle,
                CoordinateSystem,
                Dimension>{
    inline constexpr static auto get(const ElCircle &figure){
        return distance_arc_algo::distance<ElCircle,
                                           CoordinateSystem,
                                           Dimension>::get(figure);
    }
};

template<c_group_line Line,
         typename CoordinateSystem,
         std::size_t Dimension>
struct distance<Line,
                CoordinateSystem,
                Dimension>{
    inline constexpr static auto get(const Line &line){
        return distance_line_algo::distance<Line,
                                            CoordinateSystem,
                                            Dimension>::get(line);
    }
};

}


namespace agl::algorithm::dispatch::d2 {

template<typename Object1,
         typename Object2,
         typename Tag1,
         typename Tag2,
         typename CoordinateSystem,
         std::size_t Dimension>
struct distance{
    inline constexpr static auto get(const Object1 &a, const Object2 &b){
        static_assert(false, "No 'distance' calculations have been implemented for these objects.");
    }
};

template<c_point_2d Point,
         typename CoordinateSystem,
         std::size_t Dimension>
struct distance<Point,
                Point,
                agl::tag::point::point,
                agl::tag::point::point,
                CoordinateSystem,
                Dimension>{
    inline constexpr static auto get(const Point &a, const Point &b){
        return distance_point_algo::distance<Point,
                                             CoordinateSystem,
                                             Dimension>(a, b);
    }
};

template<typename Point,
         std::size_t Dimension>
struct distance<Point,
                Point,
                agl::tag::point::point,
                agl::tag::point::point,
                system_coordinat::geographical,
                Dimension>{
    inline constexpr static auto get(const Point &a, const Point &b){
        using system = traits::geo_coordinate_system<Point>::system;
        return geo_distance::distance<Point,
                                      system,
                                      Dimension>(a, b);
    }
};

template<typename Object1,
         typename Object2,
         typename Tag,
         typename CoordinateSystem,
         std::size_t Dimension>
struct distance<Object1,
                Object2,
                agl::tag::point::point,
                Tag,
                CoordinateSystem,
                Dimension>{
    inline constexpr static auto get(const Object1 &a, const Object2 &b){
        return agl::algorithm::dispatch::d2::point_to_object::distance<Object1,
                                                                       Object2,
                                                                       Tag,
                                                                       CoordinateSystem,
                                                                       Dimension>(a, b);
    }
};

template<typename Object1,
         typename Object2,
         typename Tag,
         typename CoordinateSystem,
         std::size_t Dimension>
struct distance<Object1,
                Object2,
                Tag,
                agl::tag::point::point,
                CoordinateSystem,
                Dimension>{
    inline constexpr static auto get(const Object1 &a, const Object2 &b){
        return agl::algorithm::dispatch::d2::point_to_object::distance<Object2,
                                                                       Object1,
                                                                       Tag,
                                                                       CoordinateSystem,
                                                                       Dimension>(b, a);
    }
};

}


namespace agl::algorithm::geometry {

template<typename Object1,
         typename Object2>
inline constexpr auto distance(const Object1 &a, const Object2 &b){
    using tag1 = traits::tag<Object1>::type_tag;
    using tag2 = traits::tag<Object2>::type_tag;
    using type_coordinate_system1 = traits::coordinate_system<Object1>::system;
    using type_coordinate_system2 = traits::coordinate_system<Object2>::system;
    constexpr auto dimension1 = traits::dimension<Object1>::value();
    constexpr auto dimension2 = traits::dimension<Object2>::value();

    static_assert(agl::assert::is_correct<tag1>(), "Error!");
    static_assert(agl::assert::is_correct<tag2>(), "Error!");
    static_assert(agl::assert::is_correct_compare<type_coordinate_system1, type_coordinate_system2>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension1, dimension2), "Error!");
    return dispatch::d2::distance<Object1,
                                  Object2,
                                  tag1,
                                  tag2,
                                  type_coordinate_system1,
                                  dimension1>::get(a,b);
}

template<typename Figure>
inline constexpr auto distance(const Figure &figure){
    using type_coordinate_system = traits::coordinate_system<Figure>::system;
    constexpr auto dimension = traits::dimension<Figure>::value();

    static_assert(agl::assert::is_correct<type_coordinate_system>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");

    return dispatch::d1::distance<Figure,
                                  type_coordinate_system,
                                  dimension>::get(figure);
}

}


#endif // AGL_ALGORITHM_DISTANCE_IMPLEMENTATION_H
