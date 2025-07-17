#ifndef FIGURE_ROUTE_H
#define FIGURE_ROUTE_H

#include <variant>
#include "../../user_type.h"
#include "../../algorithm/approximation_algorithm.h"

#include <iostream>

namespace sa {

struct arc_stage{
    agl::Arc arc;
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


struct figure_route : figure_route_impl<agl::LineSection, arc_stage>{
    std::vector<agl::Point> draw_point() const{
        std::vector<agl::Point> points;
        std::visit(overloaded{[](auto arg) {
                                  static_assert(false, "non-exhaustive visitor!");
                              },
                              [&points](const agl::LineSection &object) {
                                  std::cout << "line" << std::endl;
                                  std::cout << object.start() << std::endl;
                                  std::cout << object.stop() << std::endl;

                                  points.push_back(object.start());
                                  points.push_back(object.stop());
                              },
                              [&points](const arc_stage &object) {
                                  std::cout << "arc" << std::endl;
                                  std::cout << object.arc << std::endl;
                                  std::cout << (int)object.direct << std::endl;
                                  auto point = agl::approximation_algo::splitting_evenly(object.arc, 20, object.direct);
                                  for(auto &i : point){
                                      points.push_back(i);
                                  }
                              }
                   }, figure);
        return points;
    }
};

}


#endif // FIGURE_ROUTE_H
