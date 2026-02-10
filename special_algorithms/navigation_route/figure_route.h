#ifndef FIGURE_ROUTE_H
#define FIGURE_ROUTE_H

#include <variant>
#include <vector>
#include "algorithm/math_algorithm.h"
#include "system/system_concept.h"
// #include "../../user_type.h"
// #include "../../algorithm/approximation_algorithm.h"

#include <iostream>

namespace sa {

template<agl::c_arc Arc>
struct arc_stage{
    Arc arc;
    agl::algorithm::direct direct;
};

template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };

template<typename ...Args>
struct figure_route_impl{
    template<typename T>
    figure_route_impl(const T &object) : figure(object){}

    std::variant<Args...> figure;
};

template<agl::c_arc Arc,
         agl::c_line_section Line>
struct figure_route : figure_route_impl<Line, arc_stage<Arc>>{
    using Point = agl::traits::line_section::access_types<Line>::point;

    std::vector<Point> draw_point() const{
        std::vector<Point> points;
        std::visit(overloaded{[](auto arg) {
                                  static_assert(false, "non-exhaustive visitor!");
                              },
                              [&points](const Line &object) {
                                  std::cout << "line" << std::endl;
                                  std::cout << object.start() << std::endl;
                                  std::cout << object.stop() << std::endl;

                                  points.push_back(object.start());
                                  points.push_back(object.stop());
                              },
                              [&points](const arc_stage<Arc> &object) {
                                  std::cout << "arc" << std::endl;
                                  std::cout << object.arc << std::endl;
                                  std::cout << (int)object.direct << std::endl;
                                  // auto point = agl::approximation_algo::splitting_evenly(object.arc, 20, object.direct);
                                  // for(auto &i : point){
                                  //     points.push_back(i);
                                  // }
                              }
                   }, this->figure);
        return points;
    }
};

}


#endif // FIGURE_ROUTE_H
