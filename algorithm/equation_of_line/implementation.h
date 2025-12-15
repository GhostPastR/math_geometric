#ifndef AGL_ALGORITHM_EQYATION_OF_LINE_IMPLEMENTATION_H
#define AGL_ALGORITHM_EQYATION_OF_LINE_IMPLEMENTATION_H

#include "algorithm/math_algorithm.h"
#include "algorithm/create_point/interface.h"
#include "system/traits.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>

namespace agl::algorithm::geometry {

template<typename Figure> inline constexpr auto equation_of_line(const Figure &figure);
template<typename Object> inline constexpr auto equation_of_line(const Object &a, const Object &b);

}

namespace agl::algorithm{

template<typename Type,
         std::size_t N>
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

namespace agl::algorithm::dispatch::d2::default_data {

template<typename Object,
         typename CoordinateSystem,
         std::size_t Dimension>
struct equation_of_line{
    inline constexpr static auto get(const Object &a, const Object &b){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<c_point_2d Object>
struct equation_of_line<Object,
                        system_coordinat::cartesian,
                        2>{
    inline constexpr static auto get(const Object &a, const Object &b){
        using namespace agl::traits::point;
        // using Type = access_types<Object>::point;
        using Type = std::tuple_element<0, typename access_types<Object>::types>::type;
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



namespace agl::algorithm::dispatch::d2::out_data {

template<c_point_2d Object,
         typename OutLine,
         typename CoordinateSystem,
         std::size_t Dimension>
struct equation_of_line{
    inline constexpr static auto get(const Object &a, const Object &b){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<c_point_2d Object,
         typename OutLine>
struct equation_of_line<Object,
                        OutLine,
                        system_coordinat::cartesian,
                        2>{
    inline constexpr static auto get(const Object &p1, const Object &p2){
        const auto [a,b,c] = default_data::equation_of_line<Object,
                                                        system_coordinat::cartesian,
                                                        2>::get(p1, p2);
        return agl::traits::make<OutLine>::apply(a,b,c);
    }
};

}





namespace agl::algorithm::dispatch::d1::default_data {

template<typename Figure,
         typename CoordinateSystem,
         std::size_t Dimension>
struct equation_of_line{
    inline constexpr static auto get(const Figure &figure){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<c_straight_line_2d Figure>
struct equation_of_line<Figure,
                        system_coordinat::cartesian,
                        2>{
    inline constexpr static auto get(const Figure &figure){
        using namespace agl::traits::straight_line;
        using Type = access_types<Figure>::parameter;
        const auto &a = access_parameter<Figure, 0>::get(figure);
        const auto &b = access_parameter<Figure, 1>::get(figure);
        const auto &c = access_parameter<Figure, 2>::get(figure);
        return normalized(std::array<Type, 3>{a, b, c});
    }
};

template<c_half_line_2d Figure>
struct equation_of_line<Figure,
                        system_coordinat::cartesian,
                        2>{
    inline constexpr static auto get(const Figure &figure){
        using Angle = agl::traits::half_line::access_types<Figure>::direction;
        using Point = agl::traits::half_line::access_types<Figure>::start;
        const auto &start = agl::traits::half_line::access_start<Figure>::get(figure);
        const auto direction = agl::traits::half_line::access_direction<Figure>::get(figure);

        using Point = agl::traits::half_line::access_types<Figure>::start;
        // using Type = agl::traits::point::access_types<Point>::point;
        using Type = std::tuple_element<0, typename agl::traits::point::access_types<Point>::types>::type;
        const auto point = agl::algorithm::create_point<Point>(start, 1., direction);
        return agl::algorithm::dispatch::d2::default_data::equation_of_line<Point,
                                                                            system_coordinat::cartesian,
                                                                            2>::get(start, point);
    }
};

template<c_line_section Figure>
struct equation_of_line<Figure,
                        system_coordinat::cartesian,
                        2>{
    inline constexpr static auto get(const Figure &figure){
        using namespace agl::traits::line_section;
        const auto &start = access_start<Figure>::get(figure);
        const auto &stop = access_stop<Figure>::get(figure);
        return agl::algorithm::geometry::equation_of_line(start, stop);
    }
};

}



namespace agl::algorithm::dispatch::d1::out_data {

template<typename Figure,
         typename OutLine,
         typename CoordinateSystem,
         std::size_t Dimension>
struct equation_of_line{
    inline constexpr static auto get(const Figure &figure){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<c_straight_line_2d Figure,
         typename OutLine>
struct equation_of_line<Figure,
                        OutLine,
                        system_coordinat::cartesian,
                        2>{
    inline constexpr static auto get(const Figure &figure){
        const auto &a = traits::straight_line::access_parameter<Figure, 0>::get(figure);
        const auto &b = traits::straight_line::access_parameter<Figure, 1>::get(figure);
        const auto &c = traits::straight_line::access_parameter<Figure, 2>::get(figure);
        return agl::traits::make<OutLine>::apply(a,b,c);
    }
};

template<c_half_line_2d Figure,
         typename OutLine>
struct equation_of_line<Figure,
                        OutLine,
                        system_coordinat::cartesian,
                        2>{
    inline constexpr static auto get(const Figure &figure){
        const auto [a,b,c] = default_data::equation_of_line<Figure,
                                                              system_coordinat::cartesian,
                                                              2>::get(figure);
        return agl::traits::make<OutLine>::apply(a,b,c);
    }
};

template<c_line_section Figure,
         typename OutLine>
struct equation_of_line<Figure,
                        OutLine,
                        system_coordinat::cartesian,
                        2>{
    inline constexpr static auto get(const Figure &figure){
        const auto [a,b,c] = default_data::equation_of_line<Figure,
                                                              system_coordinat::cartesian,
                                                              2>::get(figure);
        return agl::traits::make<OutLine>::apply(0,0,0);
    }
};

}


namespace agl::algorithm::geometry {

template<typename Figure>
inline constexpr auto equation_of_line(const Figure &figure){
    using type_coordinate_system = traits::coordinate_system<Figure>::system;
    constexpr auto dimension = traits::dimension<Figure>::value();

    static_assert(agl::assert::is_correct<type_coordinate_system>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");

    return dispatch::d1::default_data::equation_of_line<Figure,
                                                        type_coordinate_system,
                                                        dimension>::get(figure);
}

template<typename Object>
inline constexpr auto equation_of_line(const Object &a, const Object &b){
    using type_coordinate_system = traits::coordinate_system<Object>::system;
    constexpr auto dimension = traits::dimension<Object>::value();

    static_assert(agl::assert::is_correct<type_coordinate_system>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");

    return dispatch::d2::default_data::equation_of_line<Object,
                                                        type_coordinate_system,
                                                        dimension>::get(a, b);
}

template<typename Figure, typename OutLine>
inline constexpr auto equation_of_line(const Figure &figure){
    using type_coordinate_system = traits::coordinate_system<Figure>::system;
    constexpr auto dimension = traits::dimension<Figure>::value();

    static_assert(agl::assert::is_correct<type_coordinate_system>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");

    return dispatch::d1::out_data::equation_of_line<Figure,
                                                    OutLine,
                                                    type_coordinate_system,
                                                    dimension>::get(figure);
}

template<typename Object, typename OutLine>
inline constexpr auto equation_of_line(const Object &a, const Object &b){
    using type_coordinate_system = traits::coordinate_system<Object>::system;
    constexpr auto dimension = traits::dimension<Object>::value();

    static_assert(agl::assert::is_correct<type_coordinate_system>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");

    return dispatch::d2::out_data::equation_of_line<Object,
                                                    OutLine,
                                                    type_coordinate_system,
                                                    dimension>::get(a, b);
}

}

#endif // AGL_ALGORITHM_EQYATION_OF_LINE_IMPLEMENTATION_H
