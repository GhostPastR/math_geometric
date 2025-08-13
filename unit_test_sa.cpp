#include "unit_test_sa.h"
#include "user_type.h"
#include "special_algorithms/navigation_route/algorithm_route.h"
#include "special_algorithms/navigation_route/figure_route.h"
#include <qtestcase.h>

Unit_Test_SA::Unit_Test_SA(QObject *parent) : QObject{parent}{}

void Unit_Test_SA::test_figure_route(){
    // {//itinerary_stage
    //     {
    //         agl::point2d point1(300, 100);
    //         agl::point2d point2(300, 200);
    //         agl::point2d point3(100, 300);

    //         auto figures = sa::itinerary_stage(point1, point2, point3, 100);

    //         for(const auto &i : figures){
    //             std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
    //                            [](const agl::LineSection &object) {
    //                                QVERIFY(object.start() == agl::point2d(200, 300));
    //                                QVERIFY(object.stop() == agl::point2d(100, 300));
    //                            },
    //                            [](const sa::arc_stage &object) {
    //                                agl::Arc arc(agl::point2d(200, 200), 100., 1.570796, 6.283185);
    //                                QVERIFY(object.arc == arc);
    //                                QVERIFY(object.direct == agl::algorithm::direct::LEFT);
    //                            }
    //                        }, i.figure);
    //         }
    //     }

    //     {
    //         agl::point2d point1(300, 100);
    //         agl::point2d point2(150, 200);
    //         agl::point2d point3(100, 300);

    //         auto figures = sa::itinerary_stage(point1, point2, point3, 100);
    //         for(const auto &i : figures){
    //             std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
    //                            [](const agl::LineSection &object) {
    //                                QVERIFY(object.start() == agl::point2d(107.479836, 263.256999));
    //                                QVERIFY(object.stop() == agl::point2d(100, 300));
    //                            },
    //                            [](const sa::arc_stage &object) {
    //                                agl::Arc arc(agl::point2d(205.470020, 283.205029), 100., 3.729595, 4.511561);
    //                                QVERIFY(object.arc == arc);
    //                                QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
    //                            }
    //                        }, i.figure);
    //         }
    //     }

    //     {
    //         agl::point2d point1(300, 100);
    //         agl::point2d point2(150, 200);
    //         agl::point2d point3(380, 300);

    //         auto figures = sa::itinerary_stage(point1, point2, point3, 100);
    //         for(const auto &i : figures){
    //             std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
    //                            [](const agl::LineSection &object) {
    //                                QVERIFY(object.start() == agl::point2d(254.372962, 370.431758));
    //                                QVERIFY(object.stop() == agl::point2d(380, 300));
    //                            },
    //                            [](const sa::arc_stage &object) {
    //                                agl::Arc arc(agl::point2d(205.470020, 283.205029), 100., 3.729595, 0.510977);
    //                                QVERIFY(object.arc == arc);
    //                                QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
    //                            }
    //                        }, i.figure);
    //         }
    //     }

    //     {
    //         agl::point2d point1(50, 310);
    //         agl::point2d point2(150, 200);
    //         agl::point2d point3(380, 300);

    //         auto figures = sa::itinerary_stage(point1, point2, point3, 100);
    //         for(const auto &i : figures){
    //             std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
    //                            [](const agl::LineSection &object) {
    //                                QVERIFY(object.start() == agl::point2d(301.382400, 203.934534));
    //                                QVERIFY(object.stop() == agl::point2d(380, 300));
    //                            },
    //                            [](const sa::arc_stage &object) {
    //                                agl::Arc arc(agl::point2d(223.994007, 267.267279), 100., 3.974574, 2.256642);
    //                                QVERIFY(object.arc == arc);
    //                                QVERIFY(object.direct == agl::algorithm::direct::LEFT);
    //                            }
    //                        }, i.figure);
    //         }
    //     }

    //     {
    //         agl::point2d point1(200, 100);
    //         agl::point2d point2(200, 200);
    //         agl::point2d point3(200, 300);

    //         auto figures = sa::itinerary_stage(point1, point2, point3, 100);
    //         for(const auto &i : figures){
    //             std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
    //                            [](const agl::LineSection &object) {
    //                                QVERIFY(object.start() == agl::point2d(200, 200));
    //                                QVERIFY(object.stop() == agl::point2d(200, 300));
    //                            },
    //                            [](const sa::arc_stage &object) {
    //                                QVERIFY(false);
    //                            }
    //                        }, i.figure);
    //         }
    //     }
    // }

    // {//through_stage
    //     {
    //         agl::point2d point1(440, 40);
    //         agl::point2d point2(500, 200);
    //         agl::point2d point3(510, 410);
    //         auto figures = sa::through_stage(point1, point2, point3, 100);
    //         int count_arc = 0;
    //         for(const auto &i : figures){
    //             std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
    //                            [](const agl::LineSection &object) {
    //                                QVERIFY(object.start() == agl::point2d(503.528678, 274.102239));
    //                                QVERIFY(object.stop() == agl::point2d(510, 410));
    //                            },
    //                            [&count_arc](const sa::arc_stage &object) {
    //                                ++count_arc;
    //                                if(count_arc == 1){
    //                                    agl::Arc arc(agl::point2d(406.367082, 235.112344), 100., 1.929567, 1.398782);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::LEFT);
    //                                }
    //                                else if(count_arc == 2){
    //                                    agl::Arc arc(agl::point2d(603.415492, 269.345723), 100., -1.742810, -1.523213);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
    //                                }
    //                                else{
    //                                    QVERIFY(false);
    //                                }
    //                            }
    //                        }, i.figure);
    //         }
    //     }

    //     {
    //         agl::point2d point1(720, 350);
    //         agl::point2d point2(440, 350);
    //         agl::point2d point3(150, 510);
    //         auto figures = sa::through_stage(point1, point2, point3, 100);
    //         int count_arc = 0;

    //         for(const auto &i : figures){
    //             std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
    //                            [](const agl::LineSection &object) {
    //                                QVERIFY(object.start() == agl::point2d(336.901640, 406.881854));
    //                                QVERIFY(object.stop() == agl::point2d(150, 510));
    //                            },
    //                            [&count_arc](const sa::arc_stage &object) {
    //                                ++count_arc;
    //                                if(count_arc == 1){
    //                                    agl::Arc arc(agl::point2d(440, 450), 100., 3.141593, 4.000349);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
    //                                }
    //                                else if(count_arc == 2){
    //                                    agl::Arc arc(agl::point2d(288.593906, 319.324085), 100., 7.141941, 6.787351);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::LEFT);
    //                                }
    //                                else{
    //                                    QVERIFY(false);
    //                                }
    //                            }
    //                        }, i.figure);
    //         }
    //     }

    //     {
    //         agl::point2d point1(700, 350);
    //         agl::point2d point2(440, 350);
    //         agl::point2d point3(820, 350);
    //         auto figures = sa::through_stage(point1, point2, point3, 100);
    //         int count_arc = 0;

    //         for(const auto &i : figures){
    //             std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
    //                            [](const agl::LineSection &object) {
    //                                QVERIFY(object.start() == agl::point2d(640, 350));
    //                                QVERIFY(object.stop() == agl::point2d(820, 350));
    //                            },
    //                            [&count_arc](const sa::arc_stage &object) {
    //                                ++count_arc;
    //                                if(count_arc == 1){
    //                                    agl::Arc arc(agl::point2d(440, 450), 100., 3.141593, 1.570796);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
    //                                }
    //                                else if(count_arc == 2){
    //                                    agl::Arc arc(agl::point2d(640, 450), 100., 4.712389, 3.141592);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::LEFT);
    //                                }
    //                                else{
    //                                    QVERIFY(false);
    //                                }
    //                            }
    //                        }, i.figure);
    //         }
    //     }

    //     {
    //         agl::point2d point1(440, 530);
    //         agl::point2d point2(440, 350);
    //         agl::point2d point3(820, 350);
    //         auto figures = sa::through_stage(point1, point2, point3, 100);
    //         int count_arc = 0;

    //         for(const auto &i : figures){
    //             std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
    //                            [](const agl::LineSection &object) {
    //                                QVERIFY(object.start() == agl::point2d(713.205081, 350));
    //                                QVERIFY(object.stop() == agl::point2d(820, 350));
    //                            },
    //                            [&count_arc](const sa::arc_stage &object) {
    //                                ++count_arc;
    //                                if(count_arc == 1){
    //                                    agl::Arc arc(agl::point2d(540, 350), 100., 4.712389, 2.094395);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::LEFT);
    //                                }
    //                                else if(count_arc == 2){
    //                                    agl::Arc arc(agl::point2d(713.205080, 250), 100., -1.047198, 0.);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
    //                                }
    //                                else{
    //                                    QVERIFY(false);
    //                                }
    //                            }
    //                        }, i.figure);
    //         }
    //     }

    //     {
    //         agl::point2d point1(440, 530);
    //         agl::point2d point2(440, 350);
    //         agl::point2d point3(220, 350);
    //         auto figures = sa::through_stage(point1, point2, point3, 100);
    //         QVERIFY(figures.empty());
    //     }

    //     {
    //         agl::point2d point1(440, 530);
    //         agl::point2d point2(440, 350);
    //         agl::point2d point3(150, 350);
    //         auto figures = sa::through_stage(point1, point2, point3, 100);
    //         int count_arc = 0;

    //         for(const auto &i : figures){
    //             std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
    //                            [](const agl::LineSection &object) {
    //                                QVERIFY(object.start() == agl::point2d(166.794919, 350));
    //                                QVERIFY(object.stop() == agl::point2d(150, 350));
    //                            },
    //                            [&count_arc](const sa::arc_stage &object) {
    //                                ++count_arc;
    //                                if(count_arc == 1){
    //                                    agl::Arc arc(agl::point2d(340, 350), 100., 1.570796, 4.188790);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
    //                                }
    //                                else if(count_arc == 2){
    //                                    agl::Arc arc(agl::point2d(166.794919, 250), 100., 7.330383, 6.283185);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::LEFT);
    //                                }
    //                                else{
    //                                    QVERIFY(false);
    //                                }
    //                            }
    //                        }, i.figure);
    //         }
    //     }
    // }


    // {//combine_stage
    //     {
    //         agl::point2d point1(500, 200);
    //         agl::point2d point2(470, 300);
    //         agl::point2d point3(730, 260);
    //         auto figures = sa::combine_stage(point1, point2, point3, 50, 80, agl::algorithm::pi<double>, 30);
    //         int count_arc = 0;
    //         int count_line = 0;
    //         for(const auto &i : figures){
    //             std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
    //                            [&count_line](const agl::LineSection &object) {
    //                                 ++count_line;
    //                                   if(count_line == 1){
    //                                     QVERIFY(object.start() == agl::point2d(515.751054, 364.321566));
    //                                     QVERIFY(object.stop() == agl::point2d(646.575583, 369.926675));
    //                                   }
    //                                   else if(count_line == 2){
    //                                       QVERIFY(object.start() == agl::point2d(730, 290));
    //                                       QVERIFY(object.stop() == agl::point2d(730, 260));
    //                                   }
    //                                   else{
    //                                       QVERIFY(false);
    //                                   }
    //                            },
    //                            [&count_arc](const sa::arc_stage &object) {
    //                                ++count_arc;
    //                                if(count_arc == 1){
    //                                    agl::Arc arc(agl::point2d(517.891314, 314.367394), 50., 4.420932, 6.240367);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
    //                                }
    //                                else if(count_arc == 2){
    //                                    agl::Arc arc(agl::point2d(650, 290), 80., 6.240367, 1.570796);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
    //                                }
    //                                else{
    //                                    QVERIFY(false);
    //                                }
    //                            }
    //                        }, i.figure);
    //         }
    //     }

    //     {
    //         agl::point2d point1(500, 200);
    //         agl::point2d point2(500, 300);
    //         agl::point2d point3(320, 140);
    //         auto figures = sa::combine_stage(point1, point2, point3, 50, 80, agl::algorithm::pi<double>, 30);
    //         int count_arc = 0;
    //         int count_line = 0;
    //         for(const auto &i : figures){
    //             std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
    //                            [&count_line](const agl::LineSection &object) {
    //                                ++count_line;
    //                                if(count_line == 1){
    //                                    QVERIFY(object.start() == agl::point2d(408.294042, 327.579215));
    //                                    QVERIFY(object.stop() == agl::point2d(333.270467, 214.126743));
    //                                }
    //                                else if(count_line == 2){
    //                                    QVERIFY(object.start() == agl::point2d(320, 170));
    //                                    QVERIFY(object.stop() == agl::point2d(320, 140));
    //                                }
    //                                else{
    //                                    QVERIFY(false);
    //                                }
    //                            },
    //                            [&count_arc](const sa::arc_stage &object) {
    //                                ++count_arc;
    //                                if(count_arc == 1){
    //                                    agl::Arc arc(agl::point2d(450, 300), 50., 1.570796, 5.296651);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::LEFT);
    //                                }
    //                                else if(count_arc == 2){
    //                                    agl::Arc arc(agl::point2d(400, 170), 80., 5.296651, 4.712389);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::LEFT);
    //                                }
    //                                else{
    //                                    QVERIFY(false);
    //                                }
    //                            }
    //                        }, i.figure);
    //         }
    //     }

    //     {
    //         agl::point2d point1(560, 200);
    //         agl::point2d point2(470, 300);
    //         agl::point2d point3(690, 400);
    //         auto figures = sa::combine_stage(point1, point2, point3, 50, 80, agl::algorithm::pi<double>, 30);
    //         int count_arc = 0;
    //         int count_line = 0;
    //         for(const auto &i : figures){
    //             std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
    //                            [&count_line](const agl::LineSection &object) {
    //                                ++count_line;
    //                                if(count_line == 1){
    //                                    QVERIFY(object.start() == agl::point2d(465.971088, 361.787004));
    //                                    QVERIFY(object.stop() == agl::point2d(544.090209, 475.342027));
    //                                }
    //                                else if(count_line == 2){
    //                                    QVERIFY(object.start() == agl::point2d(690, 430));
    //                                    QVERIFY(object.stop() == agl::point2d(690, 400));
    //                                }
    //                                else{
    //                                    QVERIFY(false);
    //                                }
    //                            },
    //                            [&count_arc](const sa::arc_stage &object) {
    //                                ++count_arc;
    //                                if(count_arc == 1){
    //                                    agl::Arc arc(agl::point2d(507.164707, 333.448237), 50., 3.979574, 5.314976);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
    //                                }
    //                                else if(count_arc == 2){
    //                                    agl::Arc arc(agl::point2d(610, 430), 80., 5.314976, 1.570796);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
    //                                }
    //                                else{
    //                                    QVERIFY(false);
    //                                }
    //                            }
    //                        }, i.figure);
    //         }
    //     }

    //     {
    //         agl::point2d point1(560, 200);
    //         agl::point2d point2(780, 300);
    //         agl::point2d point3(610, 390);
    //         auto figures = sa::combine_stage(point1, point2, point3, 50, 80, agl::algorithm::pi<double>, 30);
    //         int count_arc = 0;
    //         int count_line = 0;
    //         for(const auto &i : figures){
    //             std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
    //                            [&count_line](const agl::LineSection &object) {
    //                                ++count_line;
    //                                if(count_line == 1){
    //                                    QVERIFY(object.start() == agl::point2d(804.329323, 367.272572));
    //                                    QVERIFY(object.stop() == agl::point2d(762.031152, 454.806797));
    //                                }
    //                                else if(count_line == 2){
    //                                    QVERIFY(object.start() == agl::point2d(610, 420));
    //                                    QVERIFY(object.stop() == agl::point2d(610, 390));
    //                                }
    //                                else{
    //                                    QVERIFY(false);
    //                                }
    //                            },
    //                            [&count_arc](const sa::arc_stage &object) {
    //                                ++count_arc;
    //                                if(count_arc == 1){
    //                                    agl::Arc arc(agl::point2d(759.309853, 345.518324), 50., 2.714965, 1.120664);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::LEFT);
    //                                }
    //                                else if(count_arc == 2){
    //                                    agl::Arc arc(agl::point2d(690, 420), 80., 1.120664, 4.712389);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::LEFT);
    //                                }
    //                                else{
    //                                    QVERIFY(false);
    //                                }
    //                            }
    //                        }, i.figure);
    //         }
    //     }

    //     {
    //         agl::point2d point1(560, 200);
    //         agl::point2d point2(500, 300);
    //         agl::point2d point3(260, 50);
    //         auto figures = sa::combine_stage(point1, point2, point3, 50, 80, agl::algorithm::pi<double>, 30);
    //         int count_arc = 0;
    //         int count_line = 0;
    //         for(const auto &i : figures){
    //             std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
    //                            [&count_line](const agl::LineSection &object) {
    //                                ++count_line;
    //                                if(count_line == 1){
    //                                    QVERIFY(object.start() == agl::point2d(418.095359, 305.526764));
    //                                    QVERIFY(object.stop() == agl::point2d(277.552008, 130.002484));
    //                                }
    //                                else if(count_line == 2){
    //                                    QVERIFY(object.start() == agl::point2d(260, 80));
    //                                    QVERIFY(object.stop() == agl::point2d(260, 50));
    //                                }
    //                                else{
    //                                    QVERIFY(false);
    //                                }
    //                            },
    //                            [&count_arc](const sa::arc_stage &object) {
    //                                ++count_arc;
    //                                if(count_arc == 1){
    //                                    agl::Arc arc(agl::point2d(457.125354, 274.275212), 50., 1.030377, 5.387560);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::LEFT);
    //                                }
    //                                else if(count_arc == 2){
    //                                    agl::Arc arc(agl::point2d(340, 80), 80., 5.387560, 4.712389);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::LEFT);
    //                                }
    //                                else{
    //                                    QVERIFY(false);
    //                                }
    //                            }
    //                        }, i.figure);
    //         }
    //     }

    //     {
    //         agl::point2d point1(560, 200);
    //         agl::point2d point2(500, 300);
    //         agl::point2d point3(550, 260);
    //         auto figures = sa::combine_stage(point1, point2, point3, 50, 80, agl::algorithm::pi<double>, 30);
    //         int count_arc = 0;
    //         int count_line = 0;
    //         for(const auto &i : figures){
    //             std::visit(sa::overloaded{[](auto arg) { static_assert(false, "non-exhaustive visitor!"); },
    //                            [&count_line](const agl::LineSection &object) {
    //                                ++count_line;
    //                                if(count_line == 1){
    //                                    QVERIFY(object.start() == agl::point2d(579.919865, 292.144261));
    //                                    QVERIFY(object.stop() == agl::point2d(529.272350, 236.271157));
    //                                }
    //                                else if(count_line == 2){
    //                                    QVERIFY(object.start() == agl::point2d(550, 290));
    //                                    QVERIFY(object.stop() == agl::point2d(550, 260));
    //                                }
    //                                else{
    //                                    QVERIFY(false);
    //                                }
    //                            },
    //                            [&count_arc](const sa::arc_stage &object) {
    //                                ++count_arc;
    //                                if(count_arc == 1){
    //                                    agl::Arc arc(agl::point2d(542.874646, 325.724788), 50., 4.171969, 2.307177);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
    //                                }
    //                                else if(count_arc == 2){
    //                                    agl::Arc arc(agl::point2d(470, 290), 80., 2.307177, 1.570796);
    //                                    QVERIFY(object.arc == arc);
    //                                    QVERIFY(object.direct == agl::algorithm::direct::RIGHT);
    //                                }
    //                                else{
    //                                    QVERIFY(false);
    //                                }
    //                            }
    //                        }, i.figure);
    //         }
    //     }
    // }

}
