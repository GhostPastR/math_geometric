#include "unit_test_sa.h"
#include "user_type.h"
#include "special_algorithms/navigation_route/algorithm_route.h"
#include "special_algorithms/navigation_route/figure_route.h"
#include <qtestcase.h>

Unit_Test_SA::Unit_Test_SA(QObject *parent) : QObject{parent}{}

void Unit_Test_SA::test_figure_route(){
    {//itinerary_stage
        {
            agl::Point point1(300, 100);
            agl::Point point2(300, 200);
            agl::Point point3(100, 300);

            auto figures = sa::itinerary_stage(point1, point2, point3, 100);

            for(const auto &i : figures){
                std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
                               [](const agl::LineSection &object) {
                                   QVERIFY(object.start() == agl::Point(200, 300));
                                   QVERIFY(object.stop() == agl::Point(100, 300));
                               },
                               [](const sa::arc_stage &object) {
                                   agl::Arc arc(agl::Point(200, 200), 100., 1.570796, 6.283185);
                                   QVERIFY(object.arc == arc);
                                   QVERIFY(object.direct == agl::algorithm::direct::LEFT);
                               }
                           }, i.figure);
            }
        }

        {
            agl::Point point1(300, 100);
            agl::Point point2(150, 200);
            agl::Point point3(100, 300);

            auto figures = sa::itinerary_stage(point1, point2, point3, 100);
            for(const auto &i : figures){
                std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
                               [](const agl::LineSection &object) {
                                   QVERIFY(object.start() == agl::Point(107.479836, 263.256999));
                                   QVERIFY(object.stop() == agl::Point(100, 300));
                               },
                               [](const sa::arc_stage &object) {
                                   agl::Arc arc(agl::Point(205.470020, 283.205029), 100., 3.729595, 4.511561);
                                   QVERIFY(object.arc == arc);
                                   QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
                               }
                           }, i.figure);
            }
        }

        {
            agl::Point point1(300, 100);
            agl::Point point2(150, 200);
            agl::Point point3(380, 300);

            auto figures = sa::itinerary_stage(point1, point2, point3, 100);
            for(const auto &i : figures){
                std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
                               [](const agl::LineSection &object) {
                                   QVERIFY(object.start() == agl::Point(254.372962, 370.431758));
                                   QVERIFY(object.stop() == agl::Point(380, 300));
                               },
                               [](const sa::arc_stage &object) {
                                   agl::Arc arc(agl::Point(205.470020, 283.205029), 100., 3.729595, 0.510977);
                                   QVERIFY(object.arc == arc);
                                   QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
                               }
                           }, i.figure);
            }
        }

        {
            agl::Point point1(50, 310);
            agl::Point point2(150, 200);
            agl::Point point3(380, 300);

            auto figures = sa::itinerary_stage(point1, point2, point3, 100);
            for(const auto &i : figures){
                std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
                               [](const agl::LineSection &object) {
                                   QVERIFY(object.start() == agl::Point(301.382400, 203.934534));
                                   QVERIFY(object.stop() == agl::Point(380, 300));
                               },
                               [](const sa::arc_stage &object) {
                                   agl::Arc arc(agl::Point(223.994007, 267.267279), 100., 3.974574, 2.256642);
                                   QVERIFY(object.arc == arc);
                                   QVERIFY(object.direct == agl::algorithm::direct::LEFT);
                               }
                           }, i.figure);
            }
        }

        {
            agl::Point point1(200, 100);
            agl::Point point2(200, 200);
            agl::Point point3(200, 300);

            auto figures = sa::itinerary_stage(point1, point2, point3, 100);
            for(const auto &i : figures){
                std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
                               [](const agl::LineSection &object) {
                                   QVERIFY(object.start() == agl::Point(200, 200));
                                   QVERIFY(object.stop() == agl::Point(200, 300));
                               },
                               [](const sa::arc_stage &object) {
                                   QVERIFY(false);
                               }
                           }, i.figure);
            }
        }
    }

    {//through_stage
        {
            agl::Point point1(440, 40);
            agl::Point point2(500, 200);
            agl::Point point3(510, 410);
            auto figures = sa::through_stage(point1, point2, point3, 100);
            int count_arc = 0;
            for(const auto &i : figures){
                std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
                               [](const agl::LineSection &object) {
                                   QVERIFY(object.start() == agl::Point(503.528678, 274.102239));
                                   QVERIFY(object.stop() == agl::Point(510, 410));
                               },
                               [&count_arc](const sa::arc_stage &object) {
                                   ++count_arc;
                                   if(count_arc == 1){
                                       agl::Arc arc(agl::Point(406.367082, 235.112344), 100., 1.929567, 1.398782);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::LEFT);
                                   }
                                   else if(count_arc == 2){
                                       agl::Arc arc(agl::Point(603.415492, 269.345723), 100., -1.742810, -1.523213);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
                                   }
                                   else{
                                       QVERIFY(false);
                                   }
                               }
                           }, i.figure);
            }
        }

        {
            agl::Point point1(720, 350);
            agl::Point point2(440, 350);
            agl::Point point3(150, 510);
            auto figures = sa::through_stage(point1, point2, point3, 100);
            int count_arc = 0;

            for(const auto &i : figures){
                std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
                               [](const agl::LineSection &object) {
                                   QVERIFY(object.start() == agl::Point(336.901640, 406.881854));
                                   QVERIFY(object.stop() == agl::Point(150, 510));
                               },
                               [&count_arc](const sa::arc_stage &object) {
                                   ++count_arc;
                                   if(count_arc == 1){
                                       agl::Arc arc(agl::Point(440, 450), 100., 3.141593, 4.000349);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
                                   }
                                   else if(count_arc == 2){
                                       agl::Arc arc(agl::Point(288.593906, 319.324085), 100., 7.141941, 6.787351);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::LEFT);
                                   }
                                   else{
                                       QVERIFY(false);
                                   }
                               }
                           }, i.figure);
            }
        }

        {
            agl::Point point1(700, 350);
            agl::Point point2(440, 350);
            agl::Point point3(820, 350);
            auto figures = sa::through_stage(point1, point2, point3, 100);
            int count_arc = 0;

            for(const auto &i : figures){
                std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
                               [](const agl::LineSection &object) {
                                   QVERIFY(object.start() == agl::Point(640, 350));
                                   QVERIFY(object.stop() == agl::Point(820, 350));
                               },
                               [&count_arc](const sa::arc_stage &object) {
                                   ++count_arc;
                                   if(count_arc == 1){
                                       agl::Arc arc(agl::Point(440, 450), 100., 3.141593, 1.570796);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
                                   }
                                   else if(count_arc == 2){
                                       agl::Arc arc(agl::Point(640, 450), 100., 4.712389, 3.141592);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::LEFT);
                                   }
                                   else{
                                       QVERIFY(false);
                                   }
                               }
                           }, i.figure);
            }
        }

        {
            agl::Point point1(440, 530);
            agl::Point point2(440, 350);
            agl::Point point3(820, 350);
            auto figures = sa::through_stage(point1, point2, point3, 100);
            int count_arc = 0;

            for(const auto &i : figures){
                std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
                               [](const agl::LineSection &object) {
                                   QVERIFY(object.start() == agl::Point(713.205081, 350));
                                   QVERIFY(object.stop() == agl::Point(820, 350));
                               },
                               [&count_arc](const sa::arc_stage &object) {
                                   ++count_arc;
                                   if(count_arc == 1){
                                       agl::Arc arc(agl::Point(540, 350), 100., 4.712389, 2.094395);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::LEFT);
                                   }
                                   else if(count_arc == 2){
                                       agl::Arc arc(agl::Point(713.205080, 250), 100., -1.047198, 0.);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
                                   }
                                   else{
                                       QVERIFY(false);
                                   }
                               }
                           }, i.figure);
            }
        }

        {
            agl::Point point1(440, 530);
            agl::Point point2(440, 350);
            agl::Point point3(220, 350);
            auto figures = sa::through_stage(point1, point2, point3, 100);
            QVERIFY(figures.empty());
        }

        {
            agl::Point point1(440, 530);
            agl::Point point2(440, 350);
            agl::Point point3(150, 350);
            auto figures = sa::through_stage(point1, point2, point3, 100);
            int count_arc = 0;

            for(const auto &i : figures){
                std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
                               [](const agl::LineSection &object) {
                                   QVERIFY(object.start() == agl::Point(166.794919, 350));
                                   QVERIFY(object.stop() == agl::Point(150, 350));
                               },
                               [&count_arc](const sa::arc_stage &object) {
                                   ++count_arc;
                                   if(count_arc == 1){
                                       agl::Arc arc(agl::Point(340, 350), 100., 1.570796, 4.188790);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
                                   }
                                   else if(count_arc == 2){
                                       agl::Arc arc(agl::Point(166.794919, 250), 100., 7.330383, 6.283185);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::LEFT);
                                   }
                                   else{
                                       QVERIFY(false);
                                   }
                               }
                           }, i.figure);
            }
        }
    }


    {//combine_stage
        {
            agl::Point point1(500, 200);
            agl::Point point2(470, 300);
            agl::Point point3(730, 260);
            auto figures = sa::combine_stage(point1, point2, point3, 50, 80, agl::algorithm::pi<double>, 30);
            int count_arc = 0;
            int count_line = 0;
            for(const auto &i : figures){
                std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
                               [&count_line](const agl::LineSection &object) {
                                    ++count_line;
                                      if(count_line == 1){
                                        QVERIFY(object.start() == agl::Point(515.751054, 364.321566));
                                        QVERIFY(object.stop() == agl::Point(646.575583, 369.926675));
                                      }
                                      else if(count_line == 2){
                                          QVERIFY(object.start() == agl::Point(730, 290));
                                          QVERIFY(object.stop() == agl::Point(730, 260));
                                      }
                                      else{
                                          QVERIFY(false);
                                      }
                               },
                               [&count_arc](const sa::arc_stage &object) {
                                   ++count_arc;
                                   if(count_arc == 1){
                                       agl::Arc arc(agl::Point(517.891314, 314.367394), 50., 4.420932, 6.240367);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
                                   }
                                   else if(count_arc == 2){
                                       agl::Arc arc(agl::Point(650, 290), 80., 6.240367, 1.570796);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
                                   }
                                   else{
                                       QVERIFY(false);
                                   }
                               }
                           }, i.figure);
            }
        }

        {
            agl::Point point1(500, 200);
            agl::Point point2(500, 300);
            agl::Point point3(320, 140);
            auto figures = sa::combine_stage(point1, point2, point3, 50, 80, agl::algorithm::pi<double>, 30);
            int count_arc = 0;
            int count_line = 0;
            for(const auto &i : figures){
                std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
                               [&count_line](const agl::LineSection &object) {
                                   ++count_line;
                                   if(count_line == 1){
                                       QVERIFY(object.start() == agl::Point(408.294042, 327.579215));
                                       QVERIFY(object.stop() == agl::Point(333.270467, 214.126743));
                                   }
                                   else if(count_line == 2){
                                       QVERIFY(object.start() == agl::Point(320, 170));
                                       QVERIFY(object.stop() == agl::Point(320, 140));
                                   }
                                   else{
                                       QVERIFY(false);
                                   }
                               },
                               [&count_arc](const sa::arc_stage &object) {
                                   ++count_arc;
                                   if(count_arc == 1){
                                       agl::Arc arc(agl::Point(450, 300), 50., 1.570796, 5.296651);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::LEFT);
                                   }
                                   else if(count_arc == 2){
                                       agl::Arc arc(agl::Point(400, 170), 80., 5.296651, 4.712389);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::LEFT);
                                   }
                                   else{
                                       QVERIFY(false);
                                   }
                               }
                           }, i.figure);
            }
        }

        {
            agl::Point point1(560, 200);
            agl::Point point2(470, 300);
            agl::Point point3(690, 400);
            auto figures = sa::combine_stage(point1, point2, point3, 50, 80, agl::algorithm::pi<double>, 30);
            int count_arc = 0;
            int count_line = 0;
            for(const auto &i : figures){
                std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
                               [&count_line](const agl::LineSection &object) {
                                   ++count_line;
                                   if(count_line == 1){
                                       QVERIFY(object.start() == agl::Point(465.971088, 361.787004));
                                       QVERIFY(object.stop() == agl::Point(544.090209, 475.342027));
                                   }
                                   else if(count_line == 2){
                                       QVERIFY(object.start() == agl::Point(690, 430));
                                       QVERIFY(object.stop() == agl::Point(690, 400));
                                   }
                                   else{
                                       QVERIFY(false);
                                   }
                               },
                               [&count_arc](const sa::arc_stage &object) {
                                   ++count_arc;
                                   if(count_arc == 1){
                                       agl::Arc arc(agl::Point(507.164707, 333.448237), 50., 3.979574, 5.314976);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
                                   }
                                   else if(count_arc == 2){
                                       agl::Arc arc(agl::Point(610, 430), 80., 5.314976, 1.570796);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
                                   }
                                   else{
                                       QVERIFY(false);
                                   }
                               }
                           }, i.figure);
            }
        }

        {
            agl::Point point1(560, 200);
            agl::Point point2(780, 300);
            agl::Point point3(610, 390);
            auto figures = sa::combine_stage(point1, point2, point3, 50, 80, agl::algorithm::pi<double>, 30);
            int count_arc = 0;
            int count_line = 0;
            for(const auto &i : figures){
                std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
                               [&count_line](const agl::LineSection &object) {
                                   ++count_line;
                                   if(count_line == 1){
                                       QVERIFY(object.start() == agl::Point(804.329323, 367.272572));
                                       QVERIFY(object.stop() == agl::Point(762.031152, 454.806797));
                                   }
                                   else if(count_line == 2){
                                       QVERIFY(object.start() == agl::Point(610, 420));
                                       QVERIFY(object.stop() == agl::Point(610, 390));
                                   }
                                   else{
                                       QVERIFY(false);
                                   }
                               },
                               [&count_arc](const sa::arc_stage &object) {
                                   ++count_arc;
                                   if(count_arc == 1){
                                       agl::Arc arc(agl::Point(759.309853, 345.518324), 50., 2.714965, 1.120664);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::LEFT);
                                   }
                                   else if(count_arc == 2){
                                       agl::Arc arc(agl::Point(690, 420), 80., 1.120664, 4.712389);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::LEFT);
                                   }
                                   else{
                                       QVERIFY(false);
                                   }
                               }
                           }, i.figure);
            }
        }

        {
            agl::Point point1(560, 200);
            agl::Point point2(500, 300);
            agl::Point point3(260, 50);
            auto figures = sa::combine_stage(point1, point2, point3, 50, 80, agl::algorithm::pi<double>, 30);
            int count_arc = 0;
            int count_line = 0;
            for(const auto &i : figures){
                std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
                               [&count_line](const agl::LineSection &object) {
                                   ++count_line;
                                   if(count_line == 1){
                                       QVERIFY(object.start() == agl::Point(418.095359, 305.526764));
                                       QVERIFY(object.stop() == agl::Point(277.552008, 130.002484));
                                   }
                                   else if(count_line == 2){
                                       QVERIFY(object.start() == agl::Point(260, 80));
                                       QVERIFY(object.stop() == agl::Point(260, 50));
                                   }
                                   else{
                                       QVERIFY(false);
                                   }
                               },
                               [&count_arc](const sa::arc_stage &object) {
                                   ++count_arc;
                                   if(count_arc == 1){
                                       agl::Arc arc(agl::Point(457.125354, 274.275212), 50., 1.030377, 5.387560);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::LEFT);
                                   }
                                   else if(count_arc == 2){
                                       agl::Arc arc(agl::Point(340, 80), 80., 5.387560, 4.712389);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::LEFT);
                                   }
                                   else{
                                       QVERIFY(false);
                                   }
                               }
                           }, i.figure);
            }
        }

        {
            agl::Point point1(560, 200);
            agl::Point point2(500, 300);
            agl::Point point3(550, 260);
            auto figures = sa::combine_stage(point1, point2, point3, 50, 80, agl::algorithm::pi<double>, 30);
            int count_arc = 0;
            int count_line = 0;
            for(const auto &i : figures){
                std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
                               [&count_line](const agl::LineSection &object) {
                                   ++count_line;
                                   if(count_line == 1){
                                       QVERIFY(object.start() == agl::Point(579.919865, 292.144261));
                                       QVERIFY(object.stop() == agl::Point(529.272350, 236.271157));
                                   }
                                   else if(count_line == 2){
                                       QVERIFY(object.start() == agl::Point(550, 290));
                                       QVERIFY(object.stop() == agl::Point(550, 260));
                                   }
                                   else{
                                       QVERIFY(false);
                                   }
                               },
                               [&count_arc](const sa::arc_stage &object) {
                                   ++count_arc;
                                   if(count_arc == 1){
                                       agl::Arc arc(agl::Point(542.874646, 325.724788), 50., 4.171969, 2.307177);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
                                   }
                                   else if(count_arc == 2){
                                       agl::Arc arc(agl::Point(470, 290), 80., 2.307177, 1.570796);
                                       QVERIFY(object.arc == arc);
                                       QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
                                   }
                                   else{
                                       QVERIFY(false);
                                   }
                               }
                           }, i.figure);
            }
        }
    }

}
