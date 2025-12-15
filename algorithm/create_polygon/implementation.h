#ifndef AGL_ALGORITHM_CREATE_POLYGON_IMPLEMENTATION_H
#define AGL_ALGORITHM_CREATE_POLYGON_IMPLEMENTATION_H

#include <cmath>
#include "system/traits.h"
#include "algorithm/tag_algoritm.h"
#include "algorithm/rotate/interface.h"

namespace agl::algorithm::dispatch {

using namespace agl::algorithm::strategy;

template<typename T>
class Temp;

template<typename PolygonOut,
         typename Tag,
         typename Strategy,
         typename ...Args>
struct create_polygon{
    inline constexpr static auto get(Args&& ...args){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<c_create_polygon PolygonOut,
         c_point_2d Point,
         c_unit Distance>
requires c_cartesian<PolygonOut> && c_cartesian<Point> && c_demension_2<PolygonOut>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::rectangle,
                      agl::algorithm::strategy::create_rectangle_point_sides,
                      Point,
                      Distance,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &w, const Distance &h){
        using PointPolyg = agl::traits::polygon::access_types<PolygonOut>::point;
        const auto x = agl::traits::point::access_point<Point, 0>::get(point);
        const auto y = agl::traits::point::access_point<Point, 1>::get(point);
        const auto width = agl::traits::value<Distance>::get(w);
        const auto height = agl::traits::value<Distance>::get(h);
        std::vector<PointPolyg> temp({{x, y}, {x + width, y}, {x + width, y + height}, {x, y + height}});
        return agl::traits::make<PolygonOut>::apply(std::move(temp));
    }
};

template<c_create_polygon PolygonOut,
         c_point_2d Point,
         c_unit Distance>
requires c_cartesian<PolygonOut> && c_cartesian<Point> && c_demension_2<PolygonOut>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::rectangle,
                      agl::algorithm::strategy::create_rectangle_center_sides,
                      Point,
                      Distance,
                      Distance>{
    inline constexpr static auto get(const Point &center, const Distance &w, const Distance &h){
        const auto &x = agl::traits::point::access_point<Point, 0>::get(center);
        const auto &y = agl::traits::point::access_point<Point, 1>::get(center);
        const auto &width = agl::traits::value<Distance>::get(w);
        const auto &height = agl::traits::value<Distance>::get(h);
        return agl::algorithm::dispatch::create_polygon<PolygonOut,
                                                        agl::tag::polygon::rectangle,
                                                        create_rectangle_point_sides,
                                                        Point,
                                                        Distance,
                                                        Distance>::get(
            Point(x - width / 2, y - height / 2), w, h);
    }
};

template<c_create_polygon PolygonOut,
         c_point_2d Point,
         c_unit Distance>
requires c_cartesian<PolygonOut> && c_cartesian<Point> && c_demension_2<PolygonOut>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::regular,
                      create_square_point_sides,
                      Point,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &w){
        return agl::algorithm::dispatch::create_polygon<PolygonOut,
                                                        agl::tag::polygon::rectangle,
                                                        create_rectangle_point_sides,
                                                        Point,
                                                        Distance,
                                                        Distance>::get(point, w, w);
    }
};

template<c_create_polygon PolygonOut,
         c_point_2d Point,
         c_unit Distance>
requires c_cartesian<PolygonOut> && c_cartesian<Point> && c_demension_2<PolygonOut>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::regular,
                      create_square_center_sides,
                      Point,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &w){
        return agl::algorithm::dispatch::create_polygon<PolygonOut,
                                                        agl::tag::polygon::rectangle,
                                                        create_rectangle_center_sides,
                                                        Point,
                                                        Distance,
                                                        Distance>::get(point, w, w);
    }
};

template<c_create_polygon PolygonOut,
         c_point_2d Point,
         c_unit Distance>
requires c_cartesian<PolygonOut> && c_cartesian<Point> && c_demension_2<PolygonOut>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::triangle,
                      create_triangle_point_sides,
                      Point,
                      Distance,
                      Distance,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &a, const Distance &b, const Distance &c){
        using PointPolyg = agl::traits::polygon::access_types<PolygonOut>::point;
        const auto &x = agl::traits::point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::point::access_point<Point, 1>::get(point);
        const auto &_a = agl::traits::value<Distance>::get(a);
        const auto &_b = agl::traits::value<Distance>::get(b);
        const auto &_c = agl::traits::value<Distance>::get(c);
        const auto _acos = -(std::pow(_c,2) - std::pow(_a,2) - std::pow(_b,2)) / (2*_a*_b);
        if(std::fabs(_acos) > 1){
            throw std::logic_error("Couldn't create convex polygon!");
        }
        const auto p2 = PointPolyg{x + _a, y};
        std::vector<PointPolyg> temp({{x, y}, p2, agl::algorithm::rotate(PointPolyg{x + _a - b, y}, -acos(_acos), p2)});
        return agl::traits::make<PolygonOut>::apply(std::move(temp));
    }
};

//warning
template<c_create_polygon PolygonOut,
         c_point_2d Point,
         c_unit Distance,
         c_unit Angle>
requires c_cartesian<PolygonOut> && c_cartesian<Point> && c_demension_2<PolygonOut>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::triangle,
                      create_triangle_point_sides_angle,
                      Point,
                      Distance,
                      Distance,
                      Angle>{
    inline constexpr static auto get(const Point &point, const Distance &a, const Distance &c, const Angle &ac){
        using PointPolyg = agl::traits::polygon::access_types<PolygonOut>::point;
        const auto &x = agl::traits::point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::point::access_point<Point, 1>::get(point);
        const auto &_a = agl::traits::value<Distance>::get(a);
        const auto &_c = agl::traits::value<Distance>::get(c);
        const auto &_ac = agl::traits::value<Angle>::get(ac);
        const auto p2 = PointPolyg{x + _a, y};
        std::vector<PointPolyg> temp({{x, y}, p2, agl::algorithm::rotate(p2, -_ac, point)});
        return agl::traits::make<PolygonOut>::apply(std::move(temp));
    }
};

//warning
template<c_create_polygon PolygonOut,
         c_point_2d Point,
         c_unit Distance,
         c_unit Angle>
requires c_cartesian<PolygonOut> && c_cartesian<Point> && c_demension_2<PolygonOut>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::triangle,
                      create_triangle_point_sides_angles,
                      Point,
                      Distance,
                      Angle,
                      Angle>{
    inline constexpr static auto get(const Point &point, const Distance &a, const Angle &ac, const Angle &ab){
        using PointPolyg = agl::traits::polygon::access_types<PolygonOut>::point;
        using Type = agl::traits::type<Angle>::type_value;
        const auto &x = agl::traits::point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::point::access_point<Point, 1>::get(point);
        const auto &_a = agl::traits::value<Distance>::get(a);
        const auto &_ac = agl::traits::value<Angle>::get(ac);
        const auto &_ab = agl::traits::value<Angle>::get(ab);
        const auto p2 = PointPolyg{x + _a, y};
        const auto b = _a * std::sin(_ab) / std::sin(agl::algorithm::pi<Type> - _ac - _ab);
        std::vector<PointPolyg> temp({{x, y}, p2, agl::algorithm::rotate(PointPolyg{x - b, y}, _ac, p2)});
        return agl::traits::make<PolygonOut>::apply(std::move(temp));
    }
};

template<c_create_polygon PolygonOut,
         c_point_2d Point,
         c_unit Distance>
requires c_cartesian<PolygonOut> && c_cartesian<Point> && c_demension_2<PolygonOut>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::triangle,
                      create_triangle_rectangular_sides,
                      Point,
                      Distance,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &w, const Distance &h){
        using PointPolyg = agl::traits::polygon::access_types<PolygonOut>::point;
        const auto &x = agl::traits::point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::point::access_point<Point, 1>::get(point);
        const auto &_w = agl::traits::value<Distance>::get(w);
        const auto &_h = agl::traits::value<Distance>::get(h);
        std::vector<PointPolyg> temp({{x, y}, {x + _w, y}, {x, y + _h}});
        return agl::traits::make<PolygonOut>::apply(std::move(temp));
    }
};

template<c_create_polygon PolygonOut,
         c_point_2d Point,
         c_unit Distance,
         c_unit Angle>
requires c_cartesian<PolygonOut> && c_cartesian<Point> && c_demension_2<PolygonOut>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::triangle,
                      create_triangle_rectangular_sides_angles,
                      Point,
                      Distance,
                      Angle>{
    inline constexpr static auto get(const Point &point, const Distance &w, const Angle &angle){
        using PointPolyg = agl::traits::polygon::access_types<PolygonOut>::point;
        const auto &x = agl::traits::point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::point::access_point<Point, 1>::get(point);
        const auto &_w = agl::traits::value<Distance>::get(w);
        const auto &_angle = agl::traits::value<Angle>::get(angle);
        const auto height = _w * std::tan(_angle);
        std::vector<PointPolyg> temp({{x, y}, {x + _w, y}, {x, y + height}});
        return agl::traits::make<PolygonOut>::apply(std::move(temp));
    }
};


//throw
template<c_create_polygon PolygonOut,
         c_point_2d Point,
         c_unit Distance>
requires c_cartesian<PolygonOut> && c_cartesian<Point> && c_demension_2<PolygonOut>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::triangle,
                      create_triangle_isosceles_sides,
                      Point,
                      Distance,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &a, const Distance &c){
        return agl::algorithm::dispatch::create_polygon<PolygonOut,
                                                        agl::tag::polygon::triangle,
                                                        create_triangle_point_sides,
                                                        Point,
                                                        Distance,
                                                        Distance,
                                                        Distance>::get(point, a, a, c);
    }
};

template<c_create_polygon PolygonOut,
         c_point_2d Point,
         c_unit Distance,
         c_unit Angle>
requires c_cartesian<PolygonOut> && c_cartesian<Point> && c_demension_2<PolygonOut>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::triangle,
                      create_triangle_isosceles_sides_angles,
                      Point,
                      Distance,
                      Angle>{
    inline constexpr static auto get(const Point &point, const Distance &a, const Angle &angle){
        return agl::algorithm::dispatch::create_polygon<PolygonOut,
                                                        agl::tag::polygon::triangle,
                                                        create_triangle_point_sides_angle,
                                                        Point,
                                                        Distance,
                                                        Distance,
                                                        Angle>::get(point, a, a, angle);
    }
};

template<c_create_polygon PolygonOut,
         c_point_2d Point,
         c_unit Distance>
requires c_cartesian<PolygonOut> && c_cartesian<Point> && c_demension_2<PolygonOut>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::triangle,
                      create_triangle_regular,
                      Point,
                      Distance>{
    inline constexpr static auto get(const Point &point, const Distance &a){
        using PointPolyg = agl::traits::polygon::access_types<PolygonOut>::point;
        using Type = agl::traits::type<Distance>::type_value;
        const auto &x = agl::traits::point::access_point<Point, 0>::get(point);
        const auto &y = agl::traits::point::access_point<Point, 1>::get(point);
        const auto &_a = agl::traits::value<Distance>::get(a);
        const auto p2 = PointPolyg{x + _a, y};
        std::vector<PointPolyg> temp({{x, y}, p2, agl::algorithm::rotate(PointPolyg{x, y}, -agl::algorithm::pi<Type> / 6, p2)});
        return agl::traits::make<PolygonOut>::apply(std::move(temp));
    }
};

template<c_create_polygon PolygonOut,
         c_point_2d Point,
         c_unit Distance>
requires c_cartesian<PolygonOut> && c_cartesian<Point> && c_demension_2<PolygonOut>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::regular,
                      create_triangle_regular,
                      Point,
                      Distance,
                      int> {
    inline constexpr static auto get(const Point &point, const Distance &a, int count){
        return agl::algorithm::dispatch::create_polygon<PolygonOut,
                                                        agl::tag::polygon::triangle,
                                                        create_triangle_regular,
                                                        Point,
                                                        Distance>::get(point, a);
    }
};


template<c_create_polygon PolygonOut,
         c_point_2d Point,
         c_unit Distance>
requires c_cartesian<PolygonOut> && c_cartesian<Point> && c_demension_2<PolygonOut>
struct create_polygon<PolygonOut,
                      agl::tag::polygon::regular,
                      create_polygon_regular,
                      Point,
                      Distance,
                      int>{
    inline constexpr static auto get(const Point &center, const Distance &length, int count){
        using PointPolyg = agl::traits::polygon::access_types<PolygonOut>::point;
        using Type = agl::traits::type<Distance>::type_value;
        const auto &_length = agl::traits::value<Distance>::get(length);
        Type angle = algorithm::pi_in_2<Type> / static_cast<Type>(count);
        const auto radius = _length / (2 * std::sin(angle / 2));

        std::vector<PointPolyg> points;
        points.reserve(count);
        const auto numbers = std::ranges::iota_view{int{}, count};
        std::ranges::transform(numbers, std::back_inserter(points), [center, radius, angle](const auto &i){
            const auto &x = agl::traits::point::access_point<Point, 0>::get(center);
            const auto &y = agl::traits::point::access_point<Point, 1>::get(center);
            return Point{x + radius * std::sin(i * angle), y + radius * std::cos(i * angle)};
        });
        return agl::traits::make<PolygonOut>::apply(std::move(points));
    }
};


}

#endif // AGL_ALGORITHM_CREATE_POLYGON_IMPLEMENTATION_H
