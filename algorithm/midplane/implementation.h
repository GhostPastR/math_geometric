#ifndef AGL_ALGORITHM_MIDPLANE_IMPLEMENTATION_H
#define AGL_ALGORITHM_MIDPLANE_IMPLEMENTATION_H

#include <numeric>
#include "algorithm/math_algorithm.h"
#include "system/traits.h"
#include "algorithm/create_point/interface.h"

namespace agl::algorithm::dispatch::d2 {

template<typename Object,
         typename CoordinateSystem,
         std::size_t Dimension>
struct midplane{
    inline constexpr static auto get(const Object &a, const Object &b){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<typename Object>
struct midplane<Object,
                system_coordinat::cartesian,
                2>{
    inline constexpr static auto get(const Object &a, const Object &b){
        using namespace traits::traits_point;
        return Object{std::midpoint(access_point<Object, 0>::get(a), access_point<Object, 0>::get(b)),
                      std::midpoint(access_point<Object, 1>::get(a), access_point<Object, 1>::get(b))};
    }
};

template<typename Object>
struct midplane<Object,
                system_coordinat::cartesian,
                3>{
    inline constexpr static auto get(const Object &a, const Object &b){
        using namespace traits::traits_point;
        return Object{std::midpoint(access_point<Object, 0>::get(a), access_point<Object, 0>::get(b)),
                      std::midpoint(access_point<Object, 1>::get(a), access_point<Object, 1>::get(b)),
                      std::midpoint(access_point<Object, 2>::get(a), access_point<Object, 2>::get(b))};
    }
};

}



namespace agl::algorithm::dispatch::d1 {

template<typename Figure,
         typename Tag,
         typename CoordinateSystem,
         std::size_t Dimension>
struct midplane{
    inline constexpr static auto get(const Figure &figure){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<typename Figure>
struct midplane<Figure,
                agl::tag::elements_circle::arc,
                system_coordinat::cartesian,
                2>{
    inline constexpr static auto get(const Figure &figure){
        using Point = traits::traits_arc::type_property<Figure>::type_center;
        using Type = traits::traits_point::type_property<Point>::type_point;

        const auto &start = traits::traits_arc::access_angle<Figure, 0>::get(figure);
        const auto &stop = traits::traits_arc::access_angle<Figure, 1>::get(figure);
        const auto &radius = traits::traits_arc::access_radius<Figure>::get(figure);
        const auto &center = traits::traits_arc::access_center<Figure>::get(figure);

        auto a = stop - start;
        if(start > stop){
            a += algorithm::pi_in_2<Type>;
        }
        return agl::algorithm::create_point(center, a / 2., radius);
    }
};


}


namespace agl::algorithm::geometry {

template<typename Object>
inline constexpr auto midplane(const Object &a, const Object &b){
    using type_coordinate_system = traits::coordinate_system<Object>::system;
    constexpr auto dimension = traits::dimension<Object>::value();

    static_assert(agl::assert::is_correct<type_coordinate_system>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");


    static_assert(!std::is_same_v<type_coordinate_system, agl::undefined>, "Error!");
    static_assert((dimension > decltype(dimension){}), "Error!");

    return dispatch::d2::midplane<Object, type_coordinate_system, dimension>::get(a, b);
}

template<typename Figure>
inline constexpr auto midplane(const Figure &figure){
    using tag_object = traits::tag<Figure>::type_tag;
    using type_coordinate_system = traits::coordinate_system<Figure>::system;
    constexpr auto dimension = traits::dimension<Figure>::value();

    static_assert(agl::assert::is_correct<tag_object>(), "Error!");
    static_assert(agl::assert::is_correct<type_coordinate_system>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");

    return dispatch::d1::midplane<Figure, tag_object, type_coordinate_system, dimension>::get(figure);
}

}


#endif // AGL_ALGORITHM_MIDPLANE_IMPLEMENTATION_H
