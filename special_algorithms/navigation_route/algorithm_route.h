#ifndef ALGORITHM_ROUTE_H
#define ALGORITHM_ROUTE_H

#include "figure_route.h"
#include "../../algorithm/circle_algorithm.h"
#include "../../structs/vector.h"

namespace sa {

namespace {

agl::Point get_center(const std::pair<agl::Point, agl::Point> &centrs, const agl::Point &point){
    auto lenght1 = agl::point_algo::distance(centrs.first, point);
    auto lenght2 = agl::point_algo::distance(centrs.second, point);
    if(agl::algorithm::compare(lenght1, lenght2)){
        return centrs.first;
    }
    return (lenght1 < lenght2) ? centrs.first : centrs.second;
}

double lenght_arc(const arc_stage &arc){
    if(arc.direct == agl::algorithm::direct::RIGHT){
        return agl::circle_algo::length_arc(arc.arc);
    }
    return agl::circle_algo::length_arc(agl::Arc(arc.arc.center(), arc.arc.radius(), arc.arc.stop(), arc.arc.start()));
}

double lenght_stage(const arc_stage &arc1, const arc_stage &arc2, const agl::LineSection &line){
    return lenght_arc(arc1) + agl::line_algo::distance(view_line(line)) + lenght_arc(arc2);
}

}


std::vector<figure_route> line_stage(const agl::Point &prior_point, const agl::Point &next_point){
    std::vector<figure_route> figures;
    figures.push_back({agl::LineSection(prior_point, next_point)});
    return figures;
}

std::vector<figure_route> itinerary_stage(const agl::Point &prior_start, const agl::Point &prior_stop,
                                          const agl::Point &next_point, double radius){
    if(agl::point_algo::is_co_directional(prior_start, prior_stop, next_point)){
        std::vector<figure_route> figures;
        figures.push_back({agl::LineSection(prior_stop, next_point)});
        return figures;
    }
    agl::Line line(prior_start, prior_stop);
    auto center = get_center(agl::circle_algo::center_circle_in_line(view_line(line), prior_stop, radius), next_point);
    auto view = agl::circle_algo::tangent(agl::Circle(center, radius), next_point);
    if(!view.has_value()){
        return {};
    }
    agl::vector<double, 3> vect11{prior_stop.x() - prior_start.x(), prior_stop.y() - prior_start.y(), 0};
    agl::vector<double, 3> vect12{prior_stop.x() - center.x(), prior_stop.y() - center.y(), 0};
    auto v_p = agl::matrix_algo::vector_product(vect11, vect12);

    const auto point1 = view->first.view_begin.value;
    agl::vector<double, 3> vect21{next_point.x() - point1.x(), next_point.y() - point1.y(), 0};
    agl::vector<double, 3> vect22{point1.x() - center.x(), point1.y() - center.y(), 0};
    auto v_p2 = agl::matrix_algo::vector_product(vect21, vect22);

    const auto point2 = view->second.view_begin.value;
    agl::vector<double, 3> vect31{next_point.x() - point2.x(), next_point.y() - point2.y(), 0};
    agl::vector<double, 3> vect32{point2.x() - center.x(), point2.y() - center.y(), 0};
    auto v_p3 = agl::matrix_algo::vector_product(vect31, vect32);

    std::vector<figure_route> figures;
    if(auto direct = agl::algorithm::is_same_sign(v_p.get(2), v_p2.get(2)); direct != 0){
        agl::Arc arc(center, radius, agl::point_algo::angle(center, prior_stop), agl::point_algo::angle(center, point1));
        figures.push_back({arc_stage{arc, (direct > 0) ? agl::algorithm::direct::RIGHT : agl::algorithm::direct::LEFT}});
        figures.push_back({agl::LineSection(point1, next_point)});
    }
    else if(auto direct = agl::algorithm::is_same_sign(v_p.get(2), v_p3.get(2)); direct != 0){
        agl::Arc arc(center, radius, agl::point_algo::angle(center, prior_stop), agl::point_algo::angle(center, point2));
        figures.push_back({arc_stage{arc, (direct > 0) ? agl::algorithm::direct::RIGHT : agl::algorithm::direct::LEFT}});
        figures.push_back({agl::LineSection(point2, next_point)});
    }
    return figures;
}

std::vector<figure_route> through_stage(const agl::Point &prior_start, const agl::Point &prior_stop,
                                        const agl::Point &next_point, double radius){
    if(agl::point_algo::is_co_directional(prior_start, prior_stop, next_point)){
        std::vector<figure_route> figures;
        figures.push_back({agl::LineSection(prior_stop, next_point)});
        return figures;
    }
    agl::Line line(prior_start, prior_stop);
    auto center = get_center(agl::circle_algo::center_circle_in_line(view_line(line), prior_stop, radius), next_point);
    agl::vector<double, 3> vect11{prior_stop.x() - prior_start.x(), prior_stop.y() - prior_start.y(), 0};
    agl::vector<double, 3> vect12{prior_stop.x() - center.x(), prior_stop.y() - center.y(), 0};
    auto direct1 = (agl::matrix_algo::vector_product(vect11, vect12).get(2) < 0) ? -1 : 1;

    auto lenght_line = std::abs(agl::line_algo::distance_to_line(view_line(agl::Line(prior_stop, next_point)), center));

    agl::vector<double, 3> vect21{prior_stop.x() - center.x(), prior_stop.y() - center.y(), 0};
    agl::vector<double, 3> vect22{prior_stop.x() - next_point.x(), prior_stop.y() - next_point.y(), 0};
    auto direct2 = (agl::matrix_algo::vector_product(vect21, vect22).get(2) < 0) ? -1 : 1;

    auto direct = agl::algorithm::is_same_sign(direct1, direct2);
    auto d = (direct != 0) ? (radius + lenght_line) : (radius - lenght_line);

    auto angle_stop2 = agl::point_algo::angle(prior_stop, next_point) + direct1 * agl::algorithm::pi_on_2<double>;
    auto angle_start2 = angle_stop2 + direct1 * std::acos(d / (2 * radius));
    auto angle_stop1 = std::fmod(angle_start2 + agl::algorithm::pi<double>, agl::algorithm::pi_in_2<double>);
    auto angle_start1 = std::fmod(agl::point_algo::angle(prior_stop, center) + agl::algorithm::pi<double>, agl::algorithm::pi_in_2<double>);
    auto center2 = agl::point_algo::new_point(center, angle_stop1, 2 * radius);

    std::vector<figure_route> figures;
    agl::Arc arc1(center, radius, angle_start1, angle_stop1);
    figures.push_back({arc_stage{arc1, (direct1 > 0) ? agl::algorithm::direct::RIGHT : agl::algorithm::direct::LEFT}});
    agl::Arc arc2(center2, radius, angle_start2, angle_stop2);
    figures.push_back({arc_stage{arc2, (direct1 > 0) ? agl::algorithm::direct::LEFT : agl::algorithm::direct::RIGHT}});
    auto line_start = agl::point_algo::new_point(center2, angle_stop2, radius);
    figures.push_back({agl::LineSection(line_start, next_point)});
    if(agl::point_algo::distance(prior_stop, next_point) < agl::point_algo::distance(prior_stop, line_start)){
        return {};
    }
    return figures;
}

std::vector<figure_route> combine_stage(const agl::Point &prior_start, const agl::Point &prior_stop,
                                        const agl::Point &next_point, double radius1, double radius2,
                                        double course, double range){
    using namespace agl::algorithm;

    if(agl::point_algo::is_co_directional(prior_start, prior_stop, next_point)){
        std::vector<figure_route> figures;
        figures.push_back({agl::LineSection(prior_stop, next_point)});
        return figures;
    }

    agl::LineSection line(agl::point_algo::new_point(next_point, course + agl::algorithm::pi<double>, range), next_point);
    auto turning1 = agl::circle_algo::center_circle_in_line(view_line(agl::Line(prior_start, prior_stop)), prior_stop, radius1);
    auto turning2 = agl::circle_algo::center_circle_in_line(view_line(line), line.start(), radius2);
    std::array<agl::Circle, 4> circles({
        {turning1.first, radius1},
        {turning1.second, radius1},
        {turning2.first, radius2},
        {turning2.second, radius2}
    });

    agl::vector<double, 3> vect1{prior_stop.x() - prior_start.x(), prior_stop.y() - prior_start.y(), 0};
    agl::vector<double, 3> vect11{prior_stop.x() - turning1.first.x(), prior_stop.y() - turning1.first.y(), 0};
    agl::vector<double, 3> vect12{prior_stop.x() - turning1.second.x(), prior_stop.y() - turning1.second.y(), 0};
    auto direct11 = (agl::matrix_algo::vector_product(vect1, vect11).get(2) < 0) ? -1 : 1;
    auto direct12 = (agl::matrix_algo::vector_product(vect1, vect12).get(2) < 0) ? -1 : 1;

    agl::vector<double, 3> vect2{next_point.x() - line.start().x(), next_point.y() - line.start().y(), 0};
    agl::vector<double, 3> vect21{line.start().x() - turning2.first.x(), line.start().y() - turning2.first.y(), 0};
    agl::vector<double, 3> vect22{line.start().x() - turning2.second.x(), line.start().y() - turning2.second.y(), 0};
    auto direct21 = (agl::matrix_algo::vector_product(vect2, vect21).get(2) < 0) ? -1 : 1;
    auto direct22 = (agl::matrix_algo::vector_product(vect2, vect22).get(2) < 0) ? -1 : 1;

    std::array<std::optional<agl::LineSection>, 4> lines;
    auto get_lines = [](int dir1, int dir2, agl::Circle circle1, agl::Circle circle2, direct direcr){
        auto view = (dir1 != dir2) ? agl::circle_algo::scaling_tangent_inboard(circle1, circle2, direcr) :
                        agl::circle_algo::scaling_tangent_out(circle1, circle2, direcr);
        return view.has_value() ? std::optional<agl::LineSection>(agl::LineSection(view.value().view_begin.value, view.value().view_end.value)) : std::nullopt;
    };
    lines[0] = get_lines(direct11, direct21, circles[0], circles[2], direct::RIGHT);
    lines[1] = get_lines(direct11, direct22, circles[0], circles[3], direct::LEFT);
    lines[2] = get_lines(direct12, direct21, circles[1], circles[2], direct::RIGHT);
    lines[3] = get_lines(direct12, direct22, circles[1], circles[3], direct::LEFT);

    auto angle_start1 = agl::point_algo::angle(circles[0].center(), prior_stop);
    auto angle_start2 = agl::point_algo::angle(circles[1].center(), prior_stop);
    std::array<std::optional<arc_stage>, 8> arcs;
    auto append_arc = [&](int arc_index, agl::Point center1, agl::Point center2, int l_index, direct d1, direct d2, double angle){
        if(lines[l_index].has_value()){
            arcs[arc_index] = {{center1, radius1, angle, agl::point_algo::angle(center1, lines[l_index].value().start())}, d1};
            arcs[arc_index+1] = {{center2, radius2, agl::point_algo::angle(center2, lines[l_index].value().stop()),
                                    agl::point_algo::angle(center2, line.start())}, d2};
        }
        else{
            arcs[arc_index] = std::nullopt;
            arcs[arc_index+1] = std::nullopt;
        }
    };
    append_arc(0, circles[0].center(), circles[2].center(), 0, (direct11 == direct21) ? direct::LEFT : direct::RIGHT, direct::LEFT, angle_start1);
    append_arc(2, circles[0].center(), circles[3].center(), 1, (direct11 == direct22) ? direct::RIGHT : direct::LEFT, direct::RIGHT, angle_start1);
    append_arc(4, circles[1].center(), circles[2].center(), 2, (direct12 == direct21) ? direct::LEFT : direct::RIGHT, direct::LEFT, angle_start2);
    append_arc(6, circles[1].center(), circles[3].center(), 3, (direct12 == direct22) ? direct::RIGHT : direct::LEFT, direct::RIGHT, angle_start2);

    std::array<double, 4> lenghts;
    auto get_lenght = [](std::optional<arc_stage> &arc1, std::optional<arc_stage> arc2, std::optional<agl::LineSection> line){
        return (arc1.has_value() && line.has_value() && arc2.has_value()) ?
                   lenght_stage(arc1.value(), arc2.value(), line.value()) : std::numeric_limits<double>::infinity();
    };
    lenghts[0] = get_lenght(arcs[0], arcs[1], lines[0]);
    lenghts[1] = get_lenght(arcs[2], arcs[3], lines[1]);
    lenghts[2] = get_lenght(arcs[4], arcs[5], lines[2]);
    lenghts[3] = get_lenght(arcs[6], arcs[7], lines[3]);

    auto index = std::distance(lenghts.begin(), std::ranges::min_element(lenghts));
    std::vector<figure_route> figures;
    figures.push_back({arcs[2 * index].value()});
    figures.push_back({lines[index].value()});
    figures.push_back({arcs[2 * index + 1].value()});
    figures.push_back({line});
    return figures;
}

}

#endif // ALGORITHM_ROUTE_H
