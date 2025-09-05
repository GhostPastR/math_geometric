#ifndef AGL_ALGORITHM_EQYATION_OF_LINE_IMPLEMENTATION_H
#define AGL_ALGORITHM_EQYATION_OF_LINE_IMPLEMENTATION_H

#include "algorithm/math_algorithm.h"
#include "algorithm/create_point/interface.h"
#include "system/traits.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>
#include <iostream>

namespace agl::algorithm::geometry {

template<typename Figure> inline constexpr auto equation_of_line(const Figure &figure);
template<typename Object> inline constexpr auto equation_of_line(const Object &a, const Object &b);

}

namespace agl::algorithm{

template<typename Type, std::size_t N>
auto normalized(const std::array<Type, N> &array){
    const auto value = std::accumulate(array.cbegin(), std::prev(array.cend()), Type{}, [](const auto &sum, const auto &item){
        return sum + std::pow(item, 2);
    });
    const auto k = Type{1} / std::sqrt(value) * (array.back() > 0 ? Type{-1} : Type{1});
    std::array<Type, N> temp;
    std::ranges::transform(array, temp.begin(), [k](const auto &item){
        return k * item;
    });
    return temp;
}

}

namespace agl::algorithm::dispatch::d2 {

template<typename Object, typename Tag, typename CoordinateSystem, std::size_t Dimension>
struct equation_of_line{
    inline constexpr static auto get(const Object &a, const Object &b){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<typename Object>
struct equation_of_line<Object, agl::tag::tag_point, system_coordinat::cartesian, 2>{
    inline constexpr static auto get(const Object &a, const Object &b){
        using namespace agl::traits::traits_point;
        using Type = type_property<Object>::type_point;
        const auto &x1 = access_point<Object, 0>::get(a);
        const auto &y1 = access_point<Object, 1>::get(a);
        const auto &x2 = access_point<Object, 0>::get(b);
        const auto &y2 = access_point<Object, 1>::get(b);

        const auto dy = y2 - y1;
        const auto dx = x1 - x2;
        return normalized(std::array<Type, 3>{dy, dx, algorithm::determine(-dx, dy, x1, y1)});
    }
};

}



namespace agl::algorithm::dispatch::d1 {

template<typename Figure, typename Tag, typename CoordinateSystem, std::size_t Dimension>
struct equation_of_line{
    inline constexpr static auto get(const Figure &figure){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<typename Figure>
struct equation_of_line<Figure, agl::tag::tag_straight_line, system_coordinat::cartesian, 2>{
    inline constexpr static auto get(const Figure &figure){
        using namespace agl::traits::traits_straight_line;
        using Type = type_property<Figure>::type_parameter;
        const auto &a = access_parameter<Figure, 0>::get(figure);
        const auto &b = access_parameter<Figure, 1>::get(figure);
        const auto &c = access_parameter<Figure, 2>::get(figure);
        return normalized(std::array<Type, 3>{a, b, c});
    }
};

template<typename Figure>
struct equation_of_line<Figure, agl::tag::tag_half_line, system_coordinat::cartesian, 2>{
    inline constexpr static auto get(const Figure &figure){
        using Angle = agl::traits::traits_half_line::type_property<Figure>::type_direction;
        const auto &start = agl::traits::traits_half_line::access_start<Figure>::get(figure);
        const auto direction = agl::traits::traits_half_line::access_direction<Figure>::get(figure);

        using Point = agl::traits::traits_half_line::type_property<Figure>::type_start;
        using Type = agl::traits::traits_point::type_property<Point>::type_point;
        const auto point = agl::algorithm::create_point(start, direction, 1.);
        return agl::algorithm::dispatch::d2::equation_of_line<Point, agl::tag::tag_point, system_coordinat::cartesian, 2>::get(start, point);
    }
};

template<typename Figure>
struct equation_of_line<Figure, agl::tag::tag_line_section, system_coordinat::cartesian, 2>{
    inline constexpr static auto get(const Figure &figure){
        using namespace agl::traits::traits_line_section;
        const auto &start = access_start<Figure>::get(figure);
        const auto &stop = access_stop<Figure>::get(figure);
        return agl::algorithm::geometry::equation_of_line(start, stop);
    }
};

}


namespace agl::algorithm::geometry {

template<typename Figure>
inline constexpr auto equation_of_line(const Figure &figure){
    using tag_object = traits::tag<Figure>::type_tag;
    using type_coordinate_system = traits::coordinate_system<Figure>::system;
    constexpr auto dimension = traits::dimension<Figure>::value();

    static_assert(agl::assert::is_correct<tag_object>(), "Error!");
    static_assert(agl::assert::is_correct<type_coordinate_system>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");

    return dispatch::d1::equation_of_line<Figure, tag_object, type_coordinate_system, dimension>::get(figure);
}

template<typename Object>
inline constexpr auto equation_of_line(const Object &a, const Object &b){
    using tag_object = traits::tag<Object>::type_tag;
    using type_coordinate_system = traits::coordinate_system<Object>::system;
    constexpr auto dimension = traits::dimension<Object>::value();

    static_assert(agl::assert::is_correct<tag_object>(), "Error!");
    static_assert(agl::assert::is_correct<type_coordinate_system>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");

    return dispatch::d2::equation_of_line<Object, tag_object, type_coordinate_system, dimension>::get(a, b);
}

}







#endif // AGL_ALGORITHM_EQYATION_OF_LINE_IMPLEMENTATION_H
