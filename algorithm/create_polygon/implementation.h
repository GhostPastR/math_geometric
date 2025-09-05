#ifndef AGL_ALGORITHM_CREATE_POLYGON_IMPLEMENTATION_H
#define AGL_ALGORITHM_CREATE_POLYGON_IMPLEMENTATION_H

#include <cmath>
#include "system/assert.h"
#include "system/traits.h"
#include "algorithm/tag_algoritm.h"
#include "algorithm/rotate/interface.h"



namespace agl::algorithm::dispatch {

using namespace agl::algorithm::strategy;

template<typename PolygonOut,
         typename Tag, std::size_t N_Array,
         typename Strategy,
         typename CoordinateSystem,
         std::size_t Dimension,
         typename ...Args>
struct create_polygon{
    inline constexpr static auto get(Args&& ...args){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<typename PolygonOut,
         typename Point,
         typename Distance>
struct create_polygon<PolygonOut,
                      agl::tag::tag_rectangle,
                      4, create_rectangle_point_sides,
                      agl::system_coordinat::cartesian,
                      2,
                      Point,
                      Distance,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &w, const Distance &h){
        using PointPolyg = agl::traits::traits_polygon::type_property<PolygonOut>::type_point;
        constexpr std::size_t size = agl::traits::traits_polygon::type_property<PolygonOut>::size;
        const auto x = agl::traits::traits_point::access_point<Point, 0>::get(point);
        const auto y = agl::traits::traits_point::access_point<Point, 1>::get(point);
        const auto width = agl::traits::value<Distance>::get(w);
        const auto height = agl::traits::value<Distance>::get(h);
        std::array<PointPolyg, size> temp({{x, y}, {x + width, y}, {x + width, y + height}, {x, y + height}});
        return agl::traits::traits_polygon::access_create<PolygonOut>::get(std::move(temp));
    }
};

template<typename PolygonOut,
         typename Point,
         typename Distance>
struct create_polygon<PolygonOut,
                      agl::tag::tag_rectangle,
                      4,
                      create_rectangle_center_sides,
                      agl::system_coordinat::cartesian,
                      2,
                      Point,
                      Distance,
                      Distance>{
    inline constexpr static auto get(const Point &center, const Distance &w, const Distance &h){
        const auto &x = agl::traits::traits_point::access_point<Point, 0>::get(center);
        const auto &y = agl::traits::traits_point::access_point<Point, 1>::get(center);
        const auto &width = agl::traits::value<Distance>::get(w);
        const auto &height = agl::traits::value<Distance>::get(h);
        return agl::algorithm::dispatch::create_polygon<PolygonOut,
                                                        agl::tag::tag_rectangle,
                                                        4,
                                                        create_rectangle_point_sides,
                                                        agl::system_coordinat::cartesian,
                                                        2,
                                                        Point,
                                                        Distance,
                                                        Distance>::get(
            Point(x - width / 2, y - height / 2), w, h);
    }
};

template<typename PolygonOut,
         typename Point,
         typename Distance>
struct create_polygon<PolygonOut,
                      agl::tag::tag_rectangle,
                      4,
                      create_square_point_sides,
                      agl::system_coordinat::cartesian,
                      2,
                      Point,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &w){
        return agl::algorithm::dispatch::create_polygon<PolygonOut,
                                                        agl::tag::tag_rectangle,
                                                        4,
                                                        create_rectangle_point_sides,
                                                        agl::system_coordinat::cartesian,
                                                        2,
                                                        Point,
                                                        Distance,
                                                        Distance>::get(point, w, w);
    }
};

template<typename PolygonOut,
         typename Point,
         typename Distance>
struct create_polygon<PolygonOut,
                      agl::tag::tag_rectangle,
                      4,
                      create_square_center_sides,
                      agl::system_coordinat::cartesian,
                      2,
                      Point,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &w){
        return agl::algorithm::dispatch::create_polygon<PolygonOut,
                                                        agl::tag::tag_rectangle,
                                                        4,
                                                        create_rectangle_center_sides,
                                                        agl::system_coordinat::cartesian,
                                                        2,
                                                        Point,
                                                        Distance,
                                                        Distance>::get(point, w, w);
    }
};

template<typename PolygonOut,
         typename Point,
         typename Distance>
struct create_polygon<PolygonOut,
                      agl::tag::tag_regular_polygon,
                      4,
                      create_square_point_sides,
                      agl::system_coordinat::cartesian,
                      2,
                      Point,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &w){
        return agl::algorithm::dispatch::create_polygon<PolygonOut,
                                                        agl::tag::tag_rectangle,
                                                        4,
                                                        create_rectangle_point_sides,
                                                        agl::system_coordinat::cartesian,
                                                        2,
                                                        Point,
                                                        Distance,
                                                        Distance>::get(point, w, w);
    }
};

template<typename PolygonOut,
         typename Point,
         typename Distance>
struct create_polygon<PolygonOut,
                      agl::tag::tag_regular_polygon,
                      4,
                      create_square_center_sides,
                      agl::system_coordinat::cartesian,
                      2,
                      Point,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &w){
        return agl::algorithm::dispatch::create_polygon<PolygonOut,
                                                        agl::tag::tag_rectangle,
                                                        4,
                                                        create_rectangle_center_sides,
                                                        agl::system_coordinat::cartesian,
                                                        2,
                                                        Point,
                                                        Distance,
                                                        Distance>::get(point, w, w);
    }
};

template<typename PolygonOut,
         typename Point,
         typename Distance>
struct create_polygon<PolygonOut,
                      agl::tag::tag_triangle,
                      3,
                      create_triangle_point_sides,
                      agl::system_coordinat::cartesian,
                      2,
                      Point,
                      Distance,
                      Distance,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &a, const Distance &b, const Distance &c){
        using PointPolyg = agl::traits::traits_polygon::type_property<PolygonOut>::type_point;
        constexpr std::size_t size = agl::traits::traits_polygon::type_property<PolygonOut>::size;
        const auto &x = agl::traits::traits_point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::traits_point::access_point<Point, 1>::get(point);
        const auto &_a = agl::traits::value<Distance>::get(a);
        const auto &_b = agl::traits::value<Distance>::get(b);
        const auto &_c = agl::traits::value<Distance>::get(c);
        const auto _acos = -(std::pow(_c,2) - std::pow(_a,2) - std::pow(_b,2)) / (2*_a*_b);
        if(std::fabs(_acos) > 1){
            throw std::logic_error("Couldn't create convex polygon!");
        }
        const auto p2 = PointPolyg{x + _a, y};
        std::array<PointPolyg, size> temp({{x, y}, p2, agl::algorithm::rotate(PointPolyg{x + _a - b, y}, -acos(_acos), p2)});
        return agl::traits::traits_polygon::access_create<PolygonOut>::get(std::move(temp));
    }
};

//warning
template<typename PolygonOut,
         typename Point,
         typename Distance,
         typename Angle>
struct create_polygon<PolygonOut,
                      agl::tag::tag_triangle,
                      3,
                      create_triangle_point_sides_angle,
                      agl::system_coordinat::cartesian,
                      2,
                      Point,
                      Distance,
                      Distance,
                      Angle>{
    inline constexpr static auto get(const Point &point, const Distance &a, const Distance &c, const Angle &ac){
        using PointPolyg = agl::traits::traits_polygon::type_property<PolygonOut>::type_point;
        constexpr std::size_t size = agl::traits::traits_polygon::type_property<PolygonOut>::size;
        const auto &x = agl::traits::traits_point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::traits_point::access_point<Point, 1>::get(point);
        const auto &_a = agl::traits::value<Distance>::get(a);
        const auto &_c = agl::traits::value<Distance>::get(c);
        const auto &_ac = agl::traits::value<Angle>::get(ac);
        const auto p2 = PointPolyg{x + _a, y};
        std::array<PointPolyg, size> temp({{x, y}, p2, agl::algorithm::rotate(p2, -_ac, point)});
        return agl::traits::traits_polygon::access_create<PolygonOut>::get(std::move(temp));
    }
};

//warning
template<typename PolygonOut,
         typename Point,
         typename Distance,
         typename Angle>
struct create_polygon<PolygonOut,
                      agl::tag::tag_triangle,
                      3,
                      create_triangle_point_sides_angles,
                      agl::system_coordinat::cartesian,
                      2,
                      Point,
                      Distance,
                      Angle,
                      Angle>{
    inline constexpr static auto get(const Point &point, const Distance &a, const Angle &ac, const Angle &ab){
        using PointPolyg = agl::traits::traits_polygon::type_property<PolygonOut>::type_point;
        using Type = agl::traits::type<Angle>::type_value;
        constexpr std::size_t size = agl::traits::traits_polygon::type_property<PolygonOut>::size;
        const auto &x = agl::traits::traits_point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::traits_point::access_point<Point, 1>::get(point);
        const auto &_a = agl::traits::value<Distance>::get(a);
        const auto &_ac = agl::traits::value<Angle>::get(ac);
        const auto &_ab = agl::traits::value<Angle>::get(ab);
        const auto p2 = PointPolyg{x + _a, y};
        const auto b = _a * std::sin(_ab) / std::sin(agl::algorithm::pi<Type> - _ac - _ab);
        std::array<PointPolyg, size> temp({{x, y}, p2, agl::algorithm::rotate(PointPolyg{x - b, y}, _ac, p2)});
        return agl::traits::traits_polygon::access_create<PolygonOut>::get(std::move(temp));
    }
};

template<typename PolygonOut,
         typename Point,
         typename Distance>
struct create_polygon<PolygonOut,
                      agl::tag::tag_triangle,
                      3,
                      create_triangle_rectangular_sides,
                      agl::system_coordinat::cartesian,
                      2,
                      Point,
                      Distance,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &w, const Distance &h){
        using PointPolyg = agl::traits::traits_polygon::type_property<PolygonOut>::type_point;
        constexpr std::size_t size = agl::traits::traits_polygon::type_property<PolygonOut>::size;
        const auto &x = agl::traits::traits_point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::traits_point::access_point<Point, 1>::get(point);
        const auto &_w = agl::traits::value<Distance>::get(w);
        const auto &_h = agl::traits::value<Distance>::get(h);
        std::array<PointPolyg, size> temp({{x, y}, {x + _w, y}, {x, y + _h}});
        return agl::traits::traits_polygon::access_create<PolygonOut>::get(std::move(temp));
    }
};

template<typename PolygonOut,
         typename Point,
         typename Distance,
         typename Angle>
struct create_polygon<PolygonOut,
                      agl::tag::tag_triangle,
                      3,
                      create_triangle_rectangular_sides_angles,
                      agl::system_coordinat::cartesian,
                      2,
                      Point,
                      Distance,
                      Angle>{
    inline constexpr static auto get(const Point &point, const Distance &w, const Angle &angle){
        using PointPolyg = agl::traits::traits_polygon::type_property<PolygonOut>::type_point;
        constexpr std::size_t size = agl::traits::traits_polygon::type_property<PolygonOut>::size;
        const auto &x = agl::traits::traits_point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::traits_point::access_point<Point, 1>::get(point);
        const auto &_w = agl::traits::value<Distance>::get(w);
        const auto &_angle = agl::traits::value<Angle>::get(angle);
        const auto height = _w * std::tan(_angle);
        std::array<PointPolyg, size> temp({{x, y}, {x + _w, y}, {x, y + height}});
        return agl::traits::traits_polygon::access_create<PolygonOut>::get(std::move(temp));
    }
};


//throw
template<typename PolygonOut,
         typename Point,
         typename Distance>
struct create_polygon<PolygonOut,
                      agl::tag::tag_triangle,
                      3,
                      create_triangle_isosceles_sides,
                      agl::system_coordinat::cartesian,
                      2,
                      Point,
                      Distance,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &a, const Distance &c){
        return agl::algorithm::dispatch::create_polygon<PolygonOut,
                                                        agl::tag::tag_triangle,
                                                        3,
                                                        create_triangle_point_sides,
                                                        agl::system_coordinat::cartesian,
                                                        2,
                                                        Point,
                                                        Distance,
                                                        Distance,
                                                        Distance>::get(point, a, a, c);
    }
};

template<typename PolygonOut,
         typename Point,
         typename Distance,
         typename Angle>
struct create_polygon<PolygonOut,
                      agl::tag::tag_triangle,
                      3,
                      create_triangle_isosceles_sides_angles,
                      agl::system_coordinat::cartesian,
                      2,
                      Point,
                      Distance,
                      Angle>{
    inline constexpr static auto get(const Point &point, const Distance &a, const Angle &angle){
        return agl::algorithm::dispatch::create_polygon<PolygonOut,
                                                        agl::tag::tag_triangle,
                                                        3,
                                                        create_triangle_point_sides_angle,
                                                        agl::system_coordinat::cartesian,
                                                        2,
                                                        Point,
                                                        Distance,
                                                        Distance,
                                                        Angle>::get(point, a, a, angle);
    }
};

template<typename PolygonOut,
         typename Point,
         typename Distance>
struct create_polygon<PolygonOut,
                      agl::tag::tag_triangle,
                      3,
                      create_triangle_regular,
                      agl::system_coordinat::cartesian,
                      2,
                      Point,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &a){
        using PointPolyg = agl::traits::traits_polygon::type_property<PolygonOut>::type_point;
        constexpr std::size_t size = agl::traits::traits_polygon::type_property<PolygonOut>::size;
        using Type = agl::traits::type<Distance>::type_value;
        const auto &x = agl::traits::traits_point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::traits_point::access_point<Point, 1>::get(point);
        const auto &_a = agl::traits::value<Distance>::get(a);
        const auto p2 = PointPolyg{x + _a, y};
        std::array<PointPolyg, size> temp({{x, y}, p2, agl::algorithm::rotate(PointPolyg{x, y}, -agl::algorithm::pi<Type> / 6, p2)});
        return agl::traits::traits_polygon::access_create<PolygonOut>::get(std::move(temp));
    }
};

template<typename PolygonOut,
         typename Point,
         typename Distance>
struct create_polygon<PolygonOut,
                      agl::tag::tag_regular_polygon,
                      3,
                      create_triangle_regular,
                      agl::system_coordinat::cartesian,
                      2,
                      Point,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &a){
        return agl::algorithm::dispatch::create_polygon<PolygonOut,
                                                        agl::tag::tag_triangle,
                                                        3,
                                                        create_triangle_regular,
                                                        agl::system_coordinat::cartesian,
                                                        2,
                                                        Point,
                                                        Distance>::get(point, a);
    }
};


template<typename PolygonOut,
         std::size_t N_Array,
         typename Point,
         typename Distance>
struct create_polygon<PolygonOut,
                      agl::tag::tag_regular_polygon,
                      N_Array,
                      create_polygon_regular,
                      agl::system_coordinat::cartesian,
                      2,
                      Point,
                      Distance>{
    inline constexpr static auto get(const Point &center, const Distance &length){
        using PointPolyg = agl::traits::traits_polygon::type_property<PolygonOut>::type_point;
        constexpr std::size_t size = agl::traits::traits_polygon::type_property<PolygonOut>::size;
        using Type = agl::traits::type<Distance>::type_value;
        const auto &_length = agl::traits::value<Distance>::get(length);
        Type angle = algorithm::pi_in_2<Type> / static_cast<Type>(N_Array);
        const auto radius = _length / (2 * std::sin(angle / 2));

        std::array<PointPolyg, size> points;
        const auto numbers = std::ranges::iota_view{size_t(), N_Array};
        std::ranges::transform(numbers, points.begin(), [center, radius, angle](const auto &i){
            const auto &x = agl::traits::traits_point::access_point<Point, 0>::get(center);
            const auto &y = agl::traits::traits_point::access_point<Point, 1>::get(center);
            return Point{x + radius * std::sin(i * angle), y + radius * std::cos(i * angle)};
        });
        return agl::traits::traits_polygon::access_create<PolygonOut>::get(std::move(points));
    }
};


}

namespace agl::algorithm::geometry {

template<typename PolygonOut,
         typename Strategy,
         typename ...Args>
inline constexpr auto create_polygon(Args&& ...args){
    using type_cs = traits::coordinate_system<PolygonOut>::system;
    using Tag = agl::traits::tag<PolygonOut>::type_tag;
    constexpr std::size_t n_array = agl::traits::traits_polygon::type_property<PolygonOut>::size;
    constexpr auto dimension = traits::dimension<PolygonOut>::value();
    static_assert(n_array > 2, "Error!");
    static_assert(agl::assert::is_correct<type_cs>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");
    return dispatch::create_polygon<PolygonOut,
                                    Tag,
                                    n_array,
                                    Strategy,
                                    type_cs,
                                    dimension,
                                    Args...>::get(std::forward<Args>(args)...);
}

}

#endif // AGL_ALGORITHM_CREATE_POLYGON_IMPLEMENTATION_H
