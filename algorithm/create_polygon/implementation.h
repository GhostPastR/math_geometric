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
         typename Tag,
         typename CoordinateSystem,
         std::size_t Dimension,
         typename Strategy,
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
                      agl::tag::polygon::rectangle,
                      agl::system_coordinat::cartesian,
                      2,
                      agl::algorithm::strategy::create_rectangle_point_sides,
                      Point,
                      Distance,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &w, const Distance &h){
        using PointPolyg = agl::traits::traits_polygon::type_property<PolygonOut>::type_point;
        const auto x = agl::traits::traits_point::access_point<Point, 0>::get(point);
        const auto y = agl::traits::traits_point::access_point<Point, 1>::get(point);
        const auto width = agl::traits::value<Distance>::get(w);
        const auto height = agl::traits::value<Distance>::get(h);
        std::vector<PointPolyg> temp({{x, y}, {x + width, y}, {x + width, y + height}, {x, y + height}});
        return agl::traits::traits_polygon::access_create<PolygonOut>::get(std::move(temp));
    }
};

template<typename PolygonOut,
         typename Point,
         typename Distance>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::rectangle,
                      agl::system_coordinat::cartesian,
                      2,
                      agl::algorithm::strategy::create_rectangle_center_sides,
                      Point,
                      Distance,
                      Distance>{
    inline constexpr static auto get(const Point &center, const Distance &w, const Distance &h){
        const auto &x = agl::traits::traits_point::access_point<Point, 0>::get(center);
        const auto &y = agl::traits::traits_point::access_point<Point, 1>::get(center);
        const auto &width = agl::traits::value<Distance>::get(w);
        const auto &height = agl::traits::value<Distance>::get(h);
        return agl::algorithm::dispatch::create_polygon<PolygonOut,
                                                        agl::tag::polygon::rectangle,
                                                        agl::system_coordinat::cartesian,
                                                        2,
                                                        create_rectangle_point_sides,
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
                      agl::tag::polygon::regular,
                      agl::system_coordinat::cartesian,
                      2,
                      create_square_point_sides,
                      Point,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &w){
        return agl::algorithm::dispatch::create_polygon<PolygonOut,
                                                        agl::tag::polygon::rectangle,
                                                        agl::system_coordinat::cartesian,
                                                        2,
                                                        create_rectangle_point_sides,
                                                        Point,
                                                        Distance,
                                                        Distance>::get(point, w, w);
    }
};

template<typename PolygonOut,
         typename Point,
         typename Distance>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::regular,
                      agl::system_coordinat::cartesian,
                      2,
                      create_square_center_sides,
                      Point,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &w){
        return agl::algorithm::dispatch::create_polygon<PolygonOut,
                                                        agl::tag::polygon::rectangle,
                                                        agl::system_coordinat::cartesian,
                                                        2,
                                                        create_rectangle_center_sides,
                                                        Point,
                                                        Distance,
                                                        Distance>::get(point, w, w);
    }
};

template<typename PolygonOut,
         typename Point,
         typename Distance>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::triangle,
                      agl::system_coordinat::cartesian,
                      2,
                      create_triangle_point_sides,
                      Point,
                      Distance,
                      Distance,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &a, const Distance &b, const Distance &c){
        using PointPolyg = agl::traits::traits_polygon::type_property<PolygonOut>::type_point;
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
        std::vector<PointPolyg> temp({{x, y}, p2, agl::algorithm::rotate(PointPolyg{x + _a - b, y}, -acos(_acos), p2)});
        return agl::traits::traits_polygon::access_create<PolygonOut>::get(std::move(temp));
    }
};

//warning
template<typename PolygonOut,
         typename Point,
         typename Distance,
         typename Angle>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::triangle,
                      agl::system_coordinat::cartesian,
                      2,
                      create_triangle_point_sides_angle,
                      Point,
                      Distance,
                      Distance,
                      Angle>{
    inline constexpr static auto get(const Point &point, const Distance &a, const Distance &c, const Angle &ac){
        using PointPolyg = agl::traits::traits_polygon::type_property<PolygonOut>::type_point;
        const auto &x = agl::traits::traits_point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::traits_point::access_point<Point, 1>::get(point);
        const auto &_a = agl::traits::value<Distance>::get(a);
        const auto &_c = agl::traits::value<Distance>::get(c);
        const auto &_ac = agl::traits::value<Angle>::get(ac);
        const auto p2 = PointPolyg{x + _a, y};
        std::vector<PointPolyg> temp({{x, y}, p2, agl::algorithm::rotate(p2, -_ac, point)});
        return agl::traits::traits_polygon::access_create<PolygonOut>::get(std::move(temp));
    }
};

//warning
template<typename PolygonOut,
         typename Point,
         typename Distance,
         typename Angle>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::triangle,
                      agl::system_coordinat::cartesian,
                      2,
                      create_triangle_point_sides_angles,
                      Point,
                      Distance,
                      Angle,
                      Angle>{
    inline constexpr static auto get(const Point &point, const Distance &a, const Angle &ac, const Angle &ab){
        using PointPolyg = agl::traits::traits_polygon::type_property<PolygonOut>::type_point;
        using Type = agl::traits::type<Angle>::type_value;
        const auto &x = agl::traits::traits_point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::traits_point::access_point<Point, 1>::get(point);
        const auto &_a = agl::traits::value<Distance>::get(a);
        const auto &_ac = agl::traits::value<Angle>::get(ac);
        const auto &_ab = agl::traits::value<Angle>::get(ab);
        const auto p2 = PointPolyg{x + _a, y};
        const auto b = _a * std::sin(_ab) / std::sin(agl::algorithm::pi<Type> - _ac - _ab);
        std::vector<PointPolyg> temp({{x, y}, p2, agl::algorithm::rotate(PointPolyg{x - b, y}, _ac, p2)});
        return agl::traits::traits_polygon::access_create<PolygonOut>::get(std::move(temp));
    }
};

template<typename PolygonOut,
         typename Point,
         typename Distance>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::triangle,
                      agl::system_coordinat::cartesian,
                      2,
                      create_triangle_rectangular_sides,
                      Point,
                      Distance,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &w, const Distance &h){
        using PointPolyg = agl::traits::traits_polygon::type_property<PolygonOut>::type_point;
        const auto &x = agl::traits::traits_point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::traits_point::access_point<Point, 1>::get(point);
        const auto &_w = agl::traits::value<Distance>::get(w);
        const auto &_h = agl::traits::value<Distance>::get(h);
        std::vector<PointPolyg> temp({{x, y}, {x + _w, y}, {x, y + _h}});
        return agl::traits::traits_polygon::access_create<PolygonOut>::get(std::move(temp));
    }
};

template<typename PolygonOut,
         typename Point,
         typename Distance,
         typename Angle>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::triangle,
                      agl::system_coordinat::cartesian,
                      2,
                      create_triangle_rectangular_sides_angles,
                      Point,
                      Distance,
                      Angle>{
    inline constexpr static auto get(const Point &point, const Distance &w, const Angle &angle){
        using PointPolyg = agl::traits::traits_polygon::type_property<PolygonOut>::type_point;
        const auto &x = agl::traits::traits_point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::traits_point::access_point<Point, 1>::get(point);
        const auto &_w = agl::traits::value<Distance>::get(w);
        const auto &_angle = agl::traits::value<Angle>::get(angle);
        const auto height = _w * std::tan(_angle);
        std::vector<PointPolyg> temp({{x, y}, {x + _w, y}, {x, y + height}});
        return agl::traits::traits_polygon::access_create<PolygonOut>::get(std::move(temp));
    }
};


//throw
template<typename PolygonOut,
         typename Point,
         typename Distance>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::triangle,
                      agl::system_coordinat::cartesian,
                      2,
                      create_triangle_isosceles_sides,
                      Point,
                      Distance,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &a, const Distance &c){
        return agl::algorithm::dispatch::create_polygon<PolygonOut,
                                                        agl::tag::polygon::triangle,
                                                        agl::system_coordinat::cartesian,
                                                        2,
                                                        create_triangle_point_sides,
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
                      agl::tag::polygon::triangle,
                      agl::system_coordinat::cartesian,
                      2,
                      create_triangle_isosceles_sides_angles,
                      Point,
                      Distance,
                      Angle>{
    inline constexpr static auto get(const Point &point, const Distance &a, const Angle &angle){
        return agl::algorithm::dispatch::create_polygon<PolygonOut,
                                                        agl::tag::polygon::triangle,
                                                        agl::system_coordinat::cartesian,
                                                        2,
                                                        create_triangle_point_sides_angle,
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
                      agl::tag::polygon::triangle,
                      agl::system_coordinat::cartesian,
                      2,
                      create_triangle_regular,
                      Point,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &a){
        using PointPolyg = agl::traits::traits_polygon::type_property<PolygonOut>::type_point;
        using Type = agl::traits::type<Distance>::type_value;
        const auto &x = agl::traits::traits_point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::traits_point::access_point<Point, 1>::get(point);
        const auto &_a = agl::traits::value<Distance>::get(a);
        const auto p2 = PointPolyg{x + _a, y};
        std::vector<PointPolyg> temp({{x, y}, p2, agl::algorithm::rotate(PointPolyg{x, y}, -agl::algorithm::pi<Type> / 6, p2)});
        return agl::traits::traits_polygon::access_create<PolygonOut>::get(std::move(temp));
    }
};

template<typename PolygonOut,
         typename Point,
         typename Distance>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::regular,
                      agl::system_coordinat::cartesian,
                      2,
                      create_triangle_regular,
                      Point,
                      Distance,
                      int> {
    inline constexpr static auto get(const Point &point, const Distance &a, int count){
        return agl::algorithm::dispatch::create_polygon<PolygonOut,
                                                        agl::tag::polygon::triangle,
                                                        agl::system_coordinat::cartesian,
                                                        2,
                                                        create_triangle_regular,
                                                        Point,
                                                        Distance>::get(point, a);
    }
};


template<typename PolygonOut,
         typename Point,
         typename Distance>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::regular,
                      agl::system_coordinat::cartesian,
                      2,
                      create_polygon_regular,
                      Point,
                      Distance,
                      int>{
    inline constexpr static auto get(const Point &center, const Distance &length, int count){
        using PointPolyg = agl::traits::traits_polygon::type_property<PolygonOut>::type_point;
        using Type = agl::traits::type<Distance>::type_value;
        const auto &_length = agl::traits::value<Distance>::get(length);
        Type angle = algorithm::pi_in_2<Type> / static_cast<Type>(count);
        const auto radius = _length / (2 * std::sin(angle / 2));

        std::vector<PointPolyg> points;
        points.reserve(count);
        const auto numbers = std::ranges::iota_view{int{}, count};
        std::ranges::transform(numbers, std::back_inserter(points), [center, radius, angle](const auto &i){
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
    constexpr auto dimension = traits::dimension<PolygonOut>::value();
    static_assert(agl::assert::is_correct<type_cs>(), "Error!");
    static_assert(agl::assert::is_correct_dimension(dimension), "Error!");
    return dispatch::create_polygon<PolygonOut,
                                    Tag,
                                    type_cs,
                                    dimension,
                                    Strategy,
                                    Args...>::get(std::forward<Args>(args)...);
}

}

#endif // AGL_ALGORITHM_CREATE_POLYGON_IMPLEMENTATION_H
