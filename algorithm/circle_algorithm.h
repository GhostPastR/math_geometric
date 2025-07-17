#ifndef CIRCLE_ALGORITHM_H
#define CIRCLE_ALGORITHM_H

#include "line_algorithm.h"
#include "point_algorithm.h"

namespace agl::circle_algo{

namespace {

template<std::floating_point Type>
constexpr Type magnitude_arc_angle(Type start, Type stop){
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
    return point_algo::rotate(point_algo::new_point(arc.center(), arc.start(), arc.radius()),
                              distance / arc.radius(), arc.center());
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
constexpr bool point_appertain_circle(const Circle &circle, const Point &point){
    const auto value = (point.x() - circle.center().x()) * (point.x() - circle.center().x()) +
                       (point.y() - circle.center().y()) * (point.y() - circle.center().y());
    return algorithm::less_than_equal(value, circle.radius() * circle.radius());
}

//Функция определяет точки пересечения окружности с прямой
template<c_circle Circle, c_line_view View>
constexpr auto line_to_circle(const Circle &circle, const View &line)
    -> std::pair<std::optional<typename Circle::type_point>, std::optional<typename Circle::type_point>>{
    using pair_point = std::pair<std::optional<typename Circle::type_point>, std::optional<typename Circle::type_point>>;
    const auto [a,b,c] = line_algo::equation_line_quick(line.view_begin.value, line.view_end.value);
    const auto value = c + b * circle.center().y();
    const auto roots = algorithm::get_roots_equation(algorithm::quadratic<typename View::type_point>(
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
    const bool is_point1 = points.first.has_value() && line_algo::check_point_on_line(line, points.first.value());
    if(!is_point1){
        points.first = std::nullopt;
    }
    const bool is_point2 = points.second.has_value() && line_algo::check_point_on_line(line, points.second.value());
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
    -> std::pair<std::optional<typename Circle::type_point>, std::optional<typename Circle::type_point>>{
    using Point = Circle::type_point;
    using pair_point = std::pair<std::optional<Point>, std::optional<Point>>;
    const auto d = std::sqrt(std::pow(circle1.center().x() - circle2.center().x(), 2.) + std::pow(circle1.center().y() - circle2.center().y(), 2.));
    if(algorithm::compare(d, 0.)){
        return pair_point();
    }
    const auto l = (std::pow(circle1.radius(), 2.) - std::pow(circle2.radius(), 2.) + std::pow(d,2)) / (2 * d);
    const auto dl = std::pow(circle1.radius(), 2.) - std::pow(l, 2.);
    if(dl < 0){
        return pair_point();
    }
    const auto h = std::sqrt(std::pow(circle1.radius(), 2.) - std::pow(l, 2.));
    const auto a1 = (l / d);
    const auto a2 = (circle2.center().x() - circle1.center().x());
    const auto a3 = (h / d);
    const auto a4 = (circle2.center().y() - circle1.center().y());
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
    const auto _len = point_algo::distance(circle1.center(), circle2.center());
    if(algorithm::compare(_len, 0.) || (fabs(circle1.radius() - circle2.radius()) > _len)){
        return std::nullopt;
    }
    auto d = (dir == algorithm::direct::RIGHT) ? 1 : -1;
    const auto _dradius = circle1.radius() - circle2.radius();
    const auto _angle = (_dradius < 0) ? point_algo::angle(circle1.center(), circle2.center())
                                       : point_algo::angle(circle2.center(), circle1.center());
    const auto _curse = _angle + d * (algorithm::pi<Type> - ClassFunc::acos(fabs(_dradius) / _len));
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
    const auto lenght = point_algo::distance(circle1.center(), circle2.center());
    if(algorithm::compare(lenght, 0.) || (circle1.radius() + circle2.radius()) > lenght){
        return {};
    }
    const auto d = (dir == algorithm::direct::RIGHT) ? 1 : -1;
    const bool flag = circle1.radius() > circle2.radius();
    const  auto _course = flag ? point_algo::angle(circle2.center(), circle1.center())
                               : point_algo::angle(circle1.center(), circle2.center());
    const auto _angle = _course + d * (algorithm::pi<Type> - ClassFunc::acos((circle1.radius() + circle2.radius()) / lenght));
    return line_view{view<Point>{point_algo::new_point(circle1.center(),
                                                       flag ? _angle : _angle + algorithm::pi<Type>, circle1.radius()), true},
                     view<Point>{point_algo::new_point(circle2.center(),
                                                       !flag ? _angle : _angle + algorithm::pi<Type>, circle2.radius()), true}};
}



// MpLineSection MpCircle::scalingTangentInboard( const MpCircle &circle1, const MpCircle &circle2, int direct )
// {
//     if( direct != -1 )
//     {
//         direct = 1;
//     }
//     MpLineSection _lineSection( MpPoint( 0, 0 ), MpPoint( MpBase::mpSundry, MpBase::mpSundry ) );
//     double _course;
//     double _len = circle1.center_.distance( circle2.center_ );
//     if( ( circle1.radius_ + circle2.radius_ ) > _len )
//     {
//         return _lineSection;
//     }
//     if( circle1.radius_ > circle2.radius_ )
//     {
//         _course = MpPoint::angle( circle2.center_, circle1.center_ );
//         double _angle = _course + direct * ( M_PI - acos( ( circle1.radius_ + circle2.radius_ ) / _len ) );
//         _lineSection.setStart( MpPoint::getCoordinate( _angle, circle1.radius_, circle1.center_ ) );
//         _lineSection.setEnd( MpPoint::getCoordinate( _angle + M_PI, circle2.radius_, circle2.center_ ) );
//     }
//     else
//     {
//         _course = MpPoint::angle( circle1.center_, circle2.center_ );
//         double _angle = _course + direct * ( M_PI - acos( ( circle1.radius_ + circle2.radius_ ) / _len ) );

//         _lineSection.setStart( MpPoint::getCoordinate( _angle + M_PI, circle1.radius_, circle1.center_ ) );
//         _lineSection.setEnd( MpPoint::getCoordinate( _angle, circle2.radius_, circle2.center_ ) );
//     }
//     return _lineSection;
// }


//Функция возвращает касательные(ограниченая 2-мя точками) окружности и точки
template<c_circle Circle, c_point2d_decard Point,
         c_function_angle<typename Circle::type_coefficients> ClassFunc = algorithm::function_angle<typename Circle::type_coefficients>>
constexpr auto tangent(const Circle &circle, const Point &point)
    -> std::optional<std::pair<line_view<typename Circle::type_point>,line_view<typename Circle::type_point>>>{
    using Type = Circle::type_point;
    if(point_appertain_circle(circle, point)){
        return std::nullopt;
    }
    auto angle = point_algo::angle(circle.center(), point);
    auto lenght = point_algo::distance(circle.center(), point);
    auto dangle = ClassFunc::acos(circle.radius() / lenght);
    auto view1 = line_view<Type>{view<Point>{point_algo::new_point(circle.center(), angle + dangle, circle.radius())},
                                 view<Point>{point}};
    auto view2 = line_view<Type>{view<Point>{point_algo::new_point(circle.center(), angle - dangle, circle.radius())},
                                 view<Point>{point}};
        // return std::optional<line_view<Type>>(view1);
    return std::pair<line_view<Type>,line_view<Type>>{view1, view2};
}

//Функция возвращает центры окружностей, точки которых образуют
//прямую перпендикулярную заданной прямой и пересекающиеся в заданной точке
template<c_line_view Line, c_point2d_decard Point, std::floating_point Type>
constexpr auto center_circle_in_line(const Line &line, const Point &pointOnLine, Type radius){
    using pair_point = std::pair<Point, Point>;
    const auto _radius = (radius > 0) ? radius : 1.;
    const auto angle = point_algo::angle(line.view_begin.value, line.view_end.value);
    return pair_point{point_algo::new_point(pointOnLine, angle - algorithm::pi_on_2<Type>, _radius),
                      point_algo::new_point(pointOnLine, angle + algorithm::pi_on_2<Type>, _radius)};
}

}

#endif // CIRCLE_ALGORITHM_H
