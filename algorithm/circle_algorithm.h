// #ifndef CIRCLE_ALGORITHM_H
// #define CIRCLE_ALGORITHM_H

// #include "line_algorithm.h"
// #include "point_algorithm.h"

// namespace agl::circle_algo{


// //Функция возвращает одну из внешних касательных(ограниченая 2-мя точками) 2-х окружностей
// template<c_circle Circle>
// constexpr auto scaling_tangent_out(const Circle &circle1, const Circle &circle2, algorithm::direct dir)
//     -> std::optional<line_view<typename Circle::type_point>>{
//     using Type = Circle::type_coefficients;
//     using Point = Circle::type_point;
//     const auto _len = point_algo::distance(circle1.center(), circle2.center());
//     if(algorithm::compare(_len, 0.) || (fabs(circle1.radius() - circle2.radius()) > _len)){
//         return std::nullopt;
//     }
//     auto d = (dir == algorithm::direct::RIGHT) ? 1 : -1;
//     const auto _dradius = circle1.radius() - circle2.radius();
//     const auto _angle = (_dradius < 0) ? point_algo::angle(circle1.center(), circle2.center())
//                                        : point_algo::angle(circle2.center(), circle1.center());
//     const auto _curse = _angle + d * (algorithm::pi<Type> - function_angle<Type>::acos(fabs(_dradius) / _len));
//     return line_view{view<Point>{point_algo::new_point(circle1.center(), _curse, circle1.radius()), true},
//                      view<Point>{point_algo::new_point(circle2.center(), _curse, circle2.radius()), true}};
// }

// //Функция возвращает одну из внутрених касательных(ограниченая 2-мя точками) 2-х окружностей
// template<c_circle Circle>
// constexpr auto scaling_tangent_inboard(const Circle &circle1, const Circle &circle2, algorithm::direct dir)
//     -> std::optional<line_view<typename Circle::type_point>>{
//     using Type = Circle::type_coefficients;
//     using Point = Circle::type_point;
//     const auto lenght = point_algo::distance(circle1.center(), circle2.center());
//     if(algorithm::compare(lenght, 0.) || (circle1.radius() + circle2.radius()) > lenght){
//         return {};
//     }
//     const auto d = (dir == algorithm::direct::RIGHT) ? 1 : -1;
//     const bool flag = circle1.radius() > circle2.radius();
//     const  auto _course = flag ? point_algo::angle(circle2.center(), circle1.center())
//                                : point_algo::angle(circle1.center(), circle2.center());
//     const auto _angle = _course + d * (algorithm::pi<Type> - function_angle<Type>::acos((circle1.radius() + circle2.radius()) / lenght));
//     return line_view{view<Point>{point_algo::new_point(circle1.center(),
//                                                        flag ? _angle : _angle + algorithm::pi<Type>, circle1.radius()), true},
//                      view<Point>{point_algo::new_point(circle2.center(),
//                                                        !flag ? _angle : _angle + algorithm::pi<Type>, circle2.radius()), true}};
// }

// //Функция возвращает касательные(ограниченая 2-мя точками) окружности и точки
// template<c_circle Circle, c_point2d_decard Point>
// constexpr auto tangent(const Circle &circle, const Point &point)
//     -> std::optional<std::pair<line_view<typename Circle::type_point>,line_view<typename Circle::type_point>>>{
//     using Type = Circle::type_coefficients;
//     using CPoint = Circle::type_point;
//     if(point_appertain_circle(circle, point)){
//         return std::nullopt;
//     }
//     auto angle = point_algo::angle(circle.center(), point);
//     auto lenght = point_algo::distance(circle.center(), point);
//     auto dangle = function_angle<Type>::acos(circle.radius() / lenght);
//     auto view1 = line_view<CPoint>{view<Point>{point_algo::new_point(circle.center(), angle + dangle, circle.radius())},
//                                  view<Point>{point}};
//     auto view2 = line_view<CPoint>{view<Point>{point_algo::new_point(circle.center(), angle - dangle, circle.radius())},
//                                  view<Point>{point}};
//     return std::pair<line_view<CPoint>,line_view<CPoint>>{view1, view2};
// }

// //Функция возвращает центры окружностей, точки которых образуют
// //прямую перпендикулярную заданной прямой и пересекающиеся в заданной точке
// template<c_line_view Line, c_point2d_decard Point, std::floating_point Type>
// constexpr auto center_circle_in_line(const Line &line, const Point &pointOnLine, Type radius){
//     using pair_point = std::pair<Point, Point>;
//     const auto _radius = (radius > 0) ? radius : 1.;
//     const auto angle = point_algo::angle(line.view_begin.value, line.view_end.value);
//     return pair_point{point_algo::new_point(pointOnLine, angle - algorithm::pi_on_2<Type>, _radius),
//                       point_algo::new_point(pointOnLine, angle + algorithm::pi_on_2<Type>, _radius)};
// }

// }

// #endif // CIRCLE_ALGORITHM_H
