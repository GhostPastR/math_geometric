#ifndef CIRCLE_ALGORITHM_H
#define CIRCLE_ALGORITHM_H

#include "line_algorithm.h"
#include "point_algorithm.h"

namespace circle_algo{

namespace {

template<std::floating_point Type>
Type magnitude_arc_angle(Type start, Type stop){
    auto a = stop - start;
    if(start > stop){
        a += algorithm::pi_in_2<Type>;
    }
    return a;
}

}

//Функция возвращает длину дуги
template<c_arc Arc>
constexpr auto length_arc(const Arc &arc) -> Arc::type_coefficients{
    if(algorithm::compare(arc.start(), arc.stop())){
        return 0.;
    }
    return magnitude_arc_angle(arc.start(), arc.stop()) * arc.radius();
}

//Функция возвращает координаты точки на дуге с заданным расстоянием от начало
template<c_arc Arc, std::floating_point Type>
constexpr auto point_on_arc(const Arc &arc, Type distance) -> std::optional<typename Arc::type_point>{
    if(distance > length_arc(arc)){
        return {};
    }
    auto angle = distance / arc.radius();
    return point_algo::rotate(point_algo::new_point(arc.center(), arc.start(), arc.radius()),
                              angle, arc.center());
}

//Функция возвращает координаты средней точки на дуге
template<c_arc Arc>
constexpr auto midplane(const Arc &arc) -> Arc::type_point{
    return point_algo::new_point(arc.center(),
                                 magnitude_arc_angle(arc.start(), arc.stop()) / 2.,
                                 arc.radius());
}


//Функция определяет попадает ли точка в окружность
template<c_circle Circle, c_point2d_decard Point>
constexpr bool point_appertain_circle(const Circle &circle, const Point &point)
{
    auto value = (point.x() - circle.center().x()) * (point.x() - circle.center().x()) +
                 (point.y() - circle.center().y()) * (point.y() - circle.center().y());
    return algorithm::less_than_equal(value, circle.radius() * circle.radius());
}

//Функция определяет точки пересечения окружности с прямой
template<c_circle Circle, c_line_view View>
constexpr auto line_to_circle(const Circle &circle, const View &line)
    -> std::pair<std::optional<typename Circle::type_point>, std::optional<typename Circle::type_point>>{
    using pair_point = std::pair<std::optional<typename Circle::type_point>, std::optional<typename Circle::type_point>>;
    auto [a,b,c] = line_algo::equation_line_quick(line.view_begin.value, line.view_end.value);
    auto value = c + b * circle.center().y();
    auto roots = algorithm::get_roots_equation(algorithm::quadratic<typename View::type_point>(
        a * a + b * b,
        2 * (a * value - b * b * circle.center().x()),
        b * b * (circle.center().x() * circle.center().x() - circle.radius() * circle.radius()) + value * value));

    pair_point points;
    if(roots.first.has_value()){
        points.first = {roots.first.value(), (-a * roots.first.value() - c) / b};
        if(roots.second.has_value()){
            points.second = {roots.second.value(), (-a * roots.second.value() - c) / b};
        }
    }
    bool is_point1 = points.first.has_value() && line_algo::check_point_on_line(line, points.first.value());
    if(!is_point1){
        points.first = std::nullopt;
    }
    bool is_point2 = points.second.has_value() && line_algo::check_point_on_line(line, points.second.value());
    if(!is_point2){
        points.second = std::nullopt;
    }
    if(!points.first.has_value()){
        std::swap(points.first, points.second);
    }

    return points;
}

//Функция находит точки пересечение окружности с окружностью
template<c_circle Circle>
constexpr auto circle_to_circle(const Circle &circle1, const Circle &circle2)
    -> std::pair<std::optional<typename Circle::type_point>, std::optional<typename Circle::type_point>>
{
    using Point = Circle::type_point;
    using pair_point = std::pair<std::optional<Point>, std::optional<Point>>;
    auto d = std::sqrt(std::pow(circle1.center().x() - circle2.center().x(), 2.) + std::pow(circle1.center().y() - circle2.center().y(), 2.));
    if(algorithm::compare(d, 0.)){
        return pair_point();
    }
    auto l = (std::pow(circle1.radius(), 2.) - std::pow(circle2.radius(), 2.) + std::pow(d,2)) / (2 * d);
    auto dl = std::pow(circle1.radius(), 2.) - std::pow(l, 2.);
    if(dl < 0){
        return pair_point();
    }
    auto h = std::sqrt(std::pow(circle1.radius(), 2.) - std::pow(l, 2.));
    auto a1 = (l / d);
    auto a2 = (circle2.center().x() - circle1.center().x());
    auto a3 = (h / d);
    auto a4 = (circle2.center().y() - circle1.center().y());
    pair_point points;
    points.first = {a1 * a2 + a3 * a4 + circle1.center().x(), a1 * a4 - a3 * a1 + circle1.center().y()};
    points.second = {a1 * a2 - a3 * a4 + circle1.center().x(), a1 * a4 + a3 * a1 + circle1.center().y()};
    if(points.first == points.second){
        points.second = std::nullopt;
    }
    return points;
}

//Функция возвращает одну из внешних касательных(ограниченая 2-мя точками) 2-х окружностей
template<c_circle Circle,
         c_function_angle<typename Circle::type_coefficients> ClassFunc = algorithm::function_angle<typename Circle::type_coefficients>>
constexpr auto scaling_tangent_out(const Circle &circle1, const Circle &circle2, algorithm::direct dir)
    -> std::optional<line_view<typename Circle::type_point>>{
    using Type = Circle::type_coefficients;
    using Point = Circle::type_point;
    auto _len = point_algo::distance(circle1.center(), circle2.center());
    if(algorithm::compare(_len, 0.) || (fabs(circle1.radius() - circle2.radius()) > _len)){
        return std::nullopt;
    }
    auto d = (dir == algorithm::direct::RIGHT) ? -1 : 1;
    auto _dradius = circle1.radius() - circle2.radius();
    auto _angle = (_dradius < 0) ? point_algo::angle(circle1.center(), circle2.center())
                                 : point_algo::angle(circle2.center(), circle1.center());
    auto _curse = _angle + d * (algorithm::pi<Type> - ClassFunc::acos(fabs(_dradius) / _len));
    return line_view{view<Point>{point_algo::new_point(circle1.center(), _curse, circle1.radius()), true},
                     view<Point>{point_algo::new_point(circle2.center(), _curse, circle2.radius()), true}};
}

//Функция возвращает одну из внутрених касательных(ограниченая 2-мя точками) 2-х окружностей
template<c_circle Circle,
         c_function_angle<typename Circle::type_coefficients> ClassFunc = algorithm::function_angle<typename Circle::type_coefficients>>
constexpr auto scaling_tangent_inboard(const Circle &circle1, const Circle &circle2, algorithm::direct dir)
    -> std::optional<line_view<typename Circle::type_point>>{
    using Type = Circle::type_coefficients;
    using Point = Circle::type_point;
    auto _len = point_algo::distance(circle1.center(), circle2.center());
    if(algorithm::compare(_len, 0.) || (circle1.radius() + circle2.radius()) > _len){
        return {};
    }
    auto d = (dir == algorithm::direct::RIGHT) ? -1 : 1;
    bool flag = circle1.radius() > circle2.radius();
    auto _course = flag ? point_algo::angle(circle1.center(), circle2.center())
                        : point_algo::angle(circle2.center(), circle1.center());
    auto _angle = _course + d * (algorithm::pi<Type> - ClassFunc::acos((circle1.radius() + circle2.radius()) / _len));
    return line_view{view<Point>{point_algo::new_point(circle1.center(),
                                                       flag ? _angle : _angle + algorithm::pi<Type>, circle1.radius()), true},
                     view<Point>{point_algo::new_point(circle2.center(),
                                                       !flag ? _angle : _angle + algorithm::pi<Type>, circle2.radius()), true}};
}

//Функция возвращает центры окружностей, точки которых образуют
//прямую перпендикулярную заданной прямой и пересекающиеся в заданной точке
template<c_line_view Line, c_point2d_decard Point, std::floating_point Type>
constexpr auto center_circle_in_line(const Line &line, const Point &pointOnLine, Type radius){
    using pair_point = std::pair<Point, Point>;
    auto _radius = (radius > 0) ? radius : 1.;
    auto angle = point_algo::angle(line.view_begin.value, line.view_end.value);
    return pair_point{point_algo::new_point(pointOnLine, angle - algorithm::pi_on_2<Type>, _radius),
                      point_algo::new_point(pointOnLine, angle + algorithm::pi_on_2<Type>, _radius)};
}

}

#endif // CIRCLE_ALGORITHM_H
