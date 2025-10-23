#include "testalgorithm.h"
#include <QtTest/QTest>
#include "algorithm/algorithm.h"
#include <user_type.h>

#include <iostream>


TestAlgorithm::TestAlgorithm(QObject *parent)
    : QObject{parent}
{}

void TestAlgorithm::test_distance()
{
    {
        agl::point2_d point1{0,0};
        agl::point2_d point2{5,5};
        auto value = agl::algorithm::distance(point1, point2);
        QVERIFY(agl::algorithm::compare(value, 5 * std::sqrt(2)));
    }
    {
        agl::arc2_d arc{{1.,1.}, 5., 0_deg, 90_deg};
        auto dist = agl::algorithm::distance(arc);
        QVERIFY(agl::algorithm::compare(dist, 7.853982));
    }
    {
        agl::arc2_d arc{{1.,1.}, 5., 90_deg, 0_deg};
        auto dist = agl::algorithm::distance(arc);
        QVERIFY(agl::algorithm::compare(dist, 23.561945));
    }
    {
        {
            auto line = agl::straight_line2_d(agl::point2_d{0.,0.},
                                                          agl::point2_d{0.,10.});
            auto dist = agl::algorithm::distance(agl::point2_d{5.,5.}, line);
            QVERIFY(agl::algorithm::compare(dist, 5.));

            dist = agl::algorithm::distance(line, agl::point2_d{-5,-5});
            QVERIFY(agl::algorithm::compare(dist, 5.));
        }
        {
            auto half_line = agl::half_line2_d(agl::point2_d{3.,2.}, 50_deg);
            auto dist = agl::algorithm::distance(agl::point2_d{5.,5.}, half_line);
            QVERIFY(agl::algorithm::compare(dist, 1.012558));

            dist = agl::algorithm::distance(half_line, agl::point2_d{-5.,-5.});
            QVERIFY(agl::algorithm::compare(dist, 10.630146));
        }
        {
            auto line_section = agl::line_section2_d(agl::point2_d{1.,2.},
                                                        agl::point2_d{5.,2.});
            auto dist = agl::algorithm::distance(agl::point2_d{5.,5.}, line_section);
            QVERIFY(agl::algorithm::compare(dist, 3));

            dist = agl::algorithm::distance(line_section, agl::point2_d{-5.,-5.});
            QVERIFY(agl::algorithm::compare(dist, 9.219544));
        }
    }
}

void TestAlgorithm::test_direction()
{
    {
        {
            agl::point2_d point1{0,0};
            agl::point2_d point2{5,5};
            auto value = agl::algorithm::direction<agl::unit::angle>(point1, point2);
            QVERIFY(value == 45_deg);
        }
        {
            agl::point::decart::point2d<agl::unit::distance> point1{0_m,0_m};
            agl::point::decart::point2d<agl::unit::distance> point2{5_m,5_m};
            auto value = agl::algorithm::direction<agl::unit::angle>(point1, point2);
            QVERIFY(value == 45_deg);
        }
    }
}

void TestAlgorithm::test_create_point()
{
    {//create_point
        {
            agl::point2_d point{10,10};
            auto value = agl::algorithm::create_point(point, 90_deg, 10.);
            QVERIFY(agl::algorithm::compare(value.x(), 20.));
            QVERIFY(agl::algorithm::compare(value.y(), 10.));
        }
        {
            agl::point2_d point{10,10};
            auto value = agl::algorithm::create_point(point, 0_deg, 10.);
            QVERIFY(agl::algorithm::compare(value.x(), 10.));
            QVERIFY(agl::algorithm::compare(value.y(), 20.));
        }
        {
            agl::point2_d point{10,10};
            auto value = agl::algorithm::create_point(point, 180_deg, 10.);
            QVERIFY(agl::algorithm::compare(value.x(), 10.));
            QVERIFY(agl::algorithm::compare(value.y(), 0.));
        }
        {
            agl::point2_d point{10,10};
            auto value = agl::algorithm::create_point(point, 270_deg, 10.);
            QVERIFY(agl::algorithm::compare(value.x(), 0.));
            QVERIFY(agl::algorithm::compare(value.y(), 10.));
        }
    }
}

void TestAlgorithm::test_rotate()
{
    {
        agl::point2_d point{10,10};
        auto value = agl::algorithm::rotate(point, 90_deg, agl::point2_d{5,5});
        QVERIFY(agl::algorithm::compare(value.x(), 10.));
        QVERIFY(agl::algorithm::compare(value.y(), 0.));
    }
    {
        agl::point2_d point{10,10};
        auto value = agl::algorithm::rotate(point, 90_deg, agl::point2_d{5,5});
        QVERIFY(agl::algorithm::compare(value.x(), 10.));
        QVERIFY(agl::algorithm::compare(value.y(), 0.));
    }

    // {
    //     auto polygon = agl::polygon({agl::point2_d(0,10),
    //                                                                                                          agl::point2_d(10,10),
    //                                                                                                          agl::point2_d(10,0),
    //                                                                                                          agl::point2_d(0,0)});
    //     auto center = agl::algorithm::center<agl::point2_d>(polygon);
    //     auto new_polygon = agl::algorithm::rotate(polygon, 90_deg, center);

    //     QVERIFY(new_polygon.points()[0] == agl::point2_d(10,10));
    //     QVERIFY(new_polygon.points()[1] == agl::point2_d(10,0));
    //     QVERIFY(new_polygon.points()[2] == agl::point2_d(0,0));
    //     QVERIFY(new_polygon.points()[3] == agl::point2_d(0,10));
    // }
    // {
    //     auto polygon = agl::polygon({agl::point2_d(0,10),
    //                                                                                                          agl::point2_d(10,10),
    //                                                                                                          agl::point2_d(10,0),
    //                                                                                                          agl::point2_d(0,0)});
    //     auto new_polygon = agl::algorithm::rotate(polygon, 90_deg, agl::point2_d(0,0));

    //     QVERIFY(new_polygon.points()[0] == agl::point2_d(10,0));
    //     QVERIFY(new_polygon.points()[1] == agl::point2_d(10,-10));
    //     QVERIFY(new_polygon.points()[2] == agl::point2_d(0,-10));
    //     QVERIFY(new_polygon.points()[3] == agl::point2_d(0,0));
    // }
}

void TestAlgorithm::test_midplane()
{
    {
        agl::point2_d point1{10,10};
        agl::point2_d point2{5,5};
        auto value = agl::algorithm::midplane(point1, point2);
        QVERIFY(agl::algorithm::compare(value.x(), 7.5));
        QVERIFY(agl::algorithm::compare(value.y(), 7.5));
    }
    {
        agl::arc2_d arc{{1.,1.}, 5., 0_deg, 90_deg};
        auto value = agl::algorithm::midplane(arc);
        QVERIFY(value == agl::point2_d(4.535534, 4.535534));
    }
    {
        agl::arc2_d arc{{1.,1.}, 5., 90_deg, 0_deg};
        auto value = agl::algorithm::midplane(arc);
        QVERIFY(value == agl::point2_d(4.535534, -2.535534));
    }
}

void TestAlgorithm::test_intersection()
{
    {
        auto line1 = agl::straight_line2_d(agl::point2_d{0.,0.},
                                                      agl::point2_d{0.,10.});
        auto line2 = agl::straight_line2_d(agl::point2_d{0.,2.},
                                                      agl::point2_d{5.,2.});
        auto value = agl::algorithm::intersection<agl::point2_d>(line1, line2);
        auto point = agl::point2_d{0.,2.};
        QVERIFY(value.has_value() && (value.value() == point));
    }

    {
        auto line1 = agl::straight_line2_d(agl::point2_d{0.,2.},
                                                      agl::point2_d{10.,2.});
        auto line2 = agl::straight_line2_d(agl::point2_d{0.,5.},
                                                      agl::point2_d{10.,5.});
        auto value = agl::algorithm::intersection<agl::point2_d>(line1, line2);
        QVERIFY(!value.has_value());
    }

    {
        auto half_line1 = agl::half_line2_d(agl::point2_d{3.,2.}, 50_deg);
        auto half_line2 = agl::half_line2_d(agl::point2_d{3.,2.}, 50_deg);
        auto value = agl::algorithm::intersection<agl::point2_d>(half_line1, half_line2);
        QVERIFY(!value.has_value());
    }

    {
        auto half_line1 = agl::half_line2_d(agl::point2_d{0.,2.}, 90_deg);
        auto half_line2 = agl::half_line2_d(agl::point2_d{2.,0.}, 0_deg);
        auto value = agl::algorithm::intersection<agl::point2_d>(half_line1, half_line2);
        auto point = agl::point2_d{2.,2.};
        QVERIFY(value.has_value() && (value.value() == point));
    }

    {
        auto line_section1 = agl::line_section2_d(agl::point2_d{1.,2.},
                                                     agl::point2_d{5.,2.});
        auto line_section2 = agl::line_section2_d(agl::point2_d{2.,3.},
                                                     agl::point2_d{2.,10.});
        auto value = agl::algorithm::intersection<agl::point2_d>(line_section1, line_section2);
        QVERIFY(!value.has_value());
    }

    {
        auto line_section1 = agl::line_section2_d(agl::point2_d{1.,2.},
                                                     agl::point2_d{5.,2.});
        auto line_section2 = agl::line_section2_d(agl::point2_d{2.,0.},
                                                     agl::point2_d{2.,10.});
        auto value = agl::algorithm::intersection<agl::point2_d>(line_section1, line_section2);
        auto point = agl::point2_d{2.,2.};
        QVERIFY(value.has_value() && (value.value() == point));
    }

    {//line_to_circle
        {
            agl::circle2_d circle{{0.,5.}, 5.};
            auto line = agl::straight_line2_d(agl::point2_d{0.,5.},
                                                         agl::point2_d{5.,5.});
            auto value = agl::algorithm::intersection<agl::point2_d>(circle, line);
            QVERIFY(value.first.has_value() && value.second.has_value()
                    && (value.first.value() == agl::point2_d(-5,5))
                    && (value.second.value() == agl::point2_d(5,5)));
        }

        {
            agl::circle2_d circle{{0.,5.}, 5.};
            auto line = agl::straight_line2_d(agl::point2_d{0.,10.},
                                                         agl::point2_d{5.,10.});
            auto value = agl::algorithm::intersection<agl::point2_d>(circle, line);
            QVERIFY(value.first.has_value() && !value.second.has_value()
                    && (value.first == agl::point2_d(0,10)));
        }

        {
            agl::circle2_d circle{{0.,5.}, 5.};
            auto line = agl::straight_line2_d(agl::point2_d{0.,15.},
                                                         agl::point2_d{5.,15.});
            auto value = agl::algorithm::intersection<agl::point2_d>(circle, line);
            QVERIFY(!value.first.has_value() && !value.second.has_value());
        }
    }

    {//section_to_circle
        {
            agl::circle2_d circle{{0.,5.}, 5.};
            auto line = agl::line_section2_d(agl::point2_d{1.,5.},
                                                agl::point2_d{4.,5.});
            auto value = agl::algorithm::intersection<agl::point2_d>(circle, line);
            QVERIFY(!value.first.has_value() && !value.second.has_value());
        }
        {
            agl::circle2_d circle{{0.,5.}, 5.};
            auto line = agl::line_section2_d(agl::point2_d{0.,5.},
                                                agl::point2_d{5.,5.});
            auto value = agl::algorithm::intersection<agl::point2_d>(circle, line);
            QVERIFY(value.first.has_value() && !value.second.has_value()
                    && (value.first == agl::point2_d(5,5)));
        }
        {
            agl::circle2_d circle{{0.,5.}, 5.};
            auto line = agl::line_section2_d(agl::point2_d{-5.,5.},
                                                agl::point2_d{5.,5.});
            auto value = agl::algorithm::intersection<agl::point2_d>(circle, line);
            QVERIFY(value.first.has_value() && value.second.has_value()
                    && (value.first == agl::point2_d(-5,5))
                    && (value.second == agl::point2_d(5,5)));
        }
    }

    {//circle_to_circle
        {
            agl::circle2_d circle1{{0.,5.}, 5.};
            agl::circle2_d circle2{{5.,5.}, 5.};
            auto value = agl::algorithm::intersection<agl::point2_d>(circle1, circle2);
            QVERIFY(value.first.has_value() && value.second.has_value()
                    && (value.first == agl::point2_d(2.5,4.566987))
                    && (value.second == agl::point2_d(2.5,5.433013)));
        }
        {
            agl::circle2_d circle1{{0.,5.}, 5.};
            agl::circle2_d circle2{{10.,5.}, 5.};
            auto value = agl::algorithm::intersection<agl::point2_d>(circle1, circle2);
            QVERIFY(value.first.has_value() && !value.second.has_value()
                    && (value.first == agl::point2_d(5, 5)));
        }

        {
            agl::circle2_d circle1{{0.,5.}, 5.};
            agl::circle2_d circle2{{15.,5.}, 5.};
            auto value = agl::algorithm::intersection<agl::point2_d>(circle1, circle2);
            QVERIFY(!value.first.has_value() && !value.second.has_value());
        }

        {
            agl::circle2_d circle1{{0.,5.}, 5.};
            agl::circle2_d circle2{{0.,5.}, 5.};
            auto value = agl::algorithm::intersection<agl::point2_d>(circle1, circle2);
            QVERIFY(!value.first.has_value() && !value.second.has_value());
        }
    }

    {//polygon_to_line
        {
            auto polygon = agl::polygon({agl::point2_d(0,0),
                                                                                                                 agl::point2_d(0,10),
                                                                                                                 agl::point2_d(10,10),
                                                                                                                 agl::point2_d(10,0)});
            auto line = agl::line_section2_d(agl::point2_d{-5,0},
                                                agl::point2_d{11,11});
            auto temp = agl::algorithm::intersection<agl::point2_d>(polygon, line);
            QVERIFY(temp.size() == 2);
            QVERIFY(temp[0] == agl::point2_d(0, 3.4375));
            QVERIFY(temp[1] == agl::point2_d(9.545455, 10));
        }
        {
            auto polygon = agl::polygon({agl::point2_d(0,0),
                                                                                                                 agl::point2_d(0,10),
                                                                                                                 agl::point2_d(10,10),
                                                                                                                 agl::point2_d(10,0)});
            auto line = agl::line_section2_d(agl::point2_d{0,0},
                                                agl::point2_d{10,10});
            auto temp = agl::algorithm::intersection<agl::point2_d>(polygon, line);
            QVERIFY(temp.size() == 2);
            QVERIFY(temp[0] == agl::point2_d(0, 0));
            QVERIFY(temp[1] == agl::point2_d(10, 10));
        }
        {
            auto polygon = agl::polygon({agl::point2_d(0,0),
                                                                                                                 agl::point2_d(0,10),
                                                                                                                 agl::point2_d(10,10),
                                                                                                                 agl::point2_d(10,0)});
            auto line = agl::line_section2_d(agl::point2_d{0,15},
                                                agl::point2_d{50,100});
            auto temp = agl::algorithm::intersection<agl::point2_d>(polygon, line);
            QVERIFY(temp.empty());
        }
    }

    {//point_to_polygon
        {
            // auto polygon1 = ConvexPolygon({point2d(0,0), point2d(0,10), point2d(10,10), point2d(10,0)});
            // auto polygon2 = ConvexPolygon({point2d(0,0), point2d(0,10), point2d(5,15), point2d(10,10), point2d(10,0)});
            // QVERIFY(polygon_algo::polygon_intersect_polygon(polygon1, polygon2));
        }
        {
            // auto polygon1 = ConvexPolygon({point2d(0,10), point2d(0,20), point2d(10,20), point2d(10,20)});
            // auto polygon2 = ConvexPolygon({point2d(0,0), point2d(0,10), point2d(5,15), point2d(10,10), point2d(10,0)});
            // QVERIFY(polygon_algo::polygon_intersect_polygon(polygon1, polygon2));
        }
        {
            // auto polygon1 = ConvexPolygon({point2d(0,14), point2d(0,30), point2d(10,30), point2d(10,14)});
            // auto polygon2 = ConvexPolygon({point2d(0,0), point2d(0,10), point2d(5,15), point2d(10,10), point2d(10,0)});
            // QVERIFY(polygon_algo::polygon_intersect_polygon(polygon1, polygon2));
        }
        {
            // auto polygon1 = ConvexPolygon({point2d(0,0), point2d(0,5), point2d(5,5), point2d(5,0)});
            // auto polygon2 = ConvexPolygon({point2d(10,0), point2d(10,10), point2d(20,20), point2d(20,10)});
            // QVERIFY(!polygon_algo::polygon_intersect_polygon(polygon1, polygon2));
        }
    }
}

void TestAlgorithm::test_contain()
{
    {
        auto line = agl::straight_line2_d(agl::point2_d{0.,0.},
                                                     agl::point2_d{0.,10.});
        QVERIFY(agl::algorithm::contain(line, agl::point2_d{0.,0.}));
        QVERIFY(agl::algorithm::contain(line, agl::point2_d{0.,10.}));
        QVERIFY(agl::algorithm::contain(line, agl::point2_d{0.,5.}));
        QVERIFY(agl::algorithm::contain(line, agl::point2_d{0.,-5.}));
    }
    {
        auto line = agl::half_line2_d(agl::point2_d{0.,0.}, 45_deg);
        QVERIFY(agl::algorithm::contain(line, agl::point2_d{0.,0.}));
        QVERIFY(agl::algorithm::contain(line, agl::point2_d{10.,10.}));
        QVERIFY(!agl::algorithm::contain(line, agl::point2_d{0.,5.}));
        QVERIFY(!agl::algorithm::contain(line, agl::point2_d{-1.,-1.}));
    }
    {
        auto line = agl::line_section2_d(agl::point2_d{0.,0.},
                                            agl::point2_d{10.,10.});
        QVERIFY(agl::algorithm::contain(line, agl::point2_d{0.,0.}));
        QVERIFY(agl::algorithm::contain(line, agl::point2_d{10.,10.}));
        QVERIFY(!agl::algorithm::contain(line, agl::point2_d{0.,5.}));
        QVERIFY(!agl::algorithm::contain(line, agl::point2_d{-1.,-1.}));
        QVERIFY(!agl::algorithm::contain(line, agl::point2_d{11.,11.}));
    }

        // {//point_appertain_polygon
        //     auto polygon = ConvexPolygon({point2d(0,0), point2d(0,10), point2d(5,15), point2d(10,10), point2d(10,0)});
        //     QVERIFY(polygon_algo::point_appertain_polygon(polygon, point2d(1,1)));
        //     QVERIFY(!polygon_algo::point_appertain_polygon(polygon, point2d(-1,-1)));
        //     QVERIFY(polygon_algo::point_appertain_polygon(polygon, point2d(0,5)));
        //     QVERIFY(!polygon_algo::point_appertain_polygon(polygon, point2d(15,15)));
        //     QVERIFY(polygon_algo::point_appertain_polygon(polygon, point2d(5,15)));
        // }

        // {//polygon_appertain_section
        //     {
        //         auto polygon = ConvexPolygon({point2d(0,0), point2d(0,10), point2d(10,10), point2d(10,0)});
        //         auto line = LineSection(point2d(0,0), point2d(1,1));
        //         QVERIFY(polygon_algo::polygon_appertain_section(polygon, view_line(line)));
        //     }
        //     {
        //         auto polygon = ConvexPolygon({point2d(0,0), point2d(0,10), point2d(10,10), point2d(10,0)});
        //         auto line = LineSection(point2d(-1,-1), point2d(1,1));
        //         QVERIFY(!polygon_algo::polygon_appertain_section(polygon, view_line(line)));
        //     }
        //     {
        //         auto polygon = ConvexPolygon({point2d(0,0), point2d(0,10), point2d(10,10), point2d(10,0)});
        //         auto line = LineSection(point2d(-2,-2), point2d(-1,-1));
        //         QVERIFY(!polygon_algo::polygon_appertain_section(polygon, view_line(line)));
        //     }
        // }

        // {//polygon_appertain_polygon
        //     {
        //         auto polygon1 = ConvexPolygon({point2d(0,0), point2d(0,10), point2d(10,10), point2d(10,0)});
        //         auto polygon2 = ConvexPolygon({point2d(1,1), point2d(1,9), point2d(9,9), point2d(9,1)});
        //         QVERIFY(polygon_algo::polygon_appertain_polygon(polygon1, polygon2));
        //     }

        //     {
        //         auto polygon1 = ConvexPolygon({point2d(0,0), point2d(0,10), point2d(10,10), point2d(10,0)});
        //         auto polygon2 = ConvexPolygon({point2d(0,0), point2d(0,11), point2d(11,11), point2d(11,0)});
        //         QVERIFY(!polygon_algo::polygon_appertain_polygon(polygon1, polygon2));
        //     }

        //     {
        //         auto polygon1 = ConvexPolygon({point2d(0,0), point2d(0,10), point2d(10,10), point2d(10,0)});
        //         auto polygon2 = ConvexPolygon({point2d(0,0), point2d(0,9), point2d(9,9), point2d(9,0)});
        //         QVERIFY(!polygon_algo::polygon_appertain_polygon(polygon1, polygon2));
        //     }
        // }
}

void TestAlgorithm::test_parallel()
{
    {
        auto line = agl::straight_line2_d(agl::point2_d{0.,0.},
                                                     agl::point2_d{0.,10.});
        {
            auto temp = agl::algorithm::parallel<agl::straight_line2_d>(line, 10);
            QVERIFY(temp == agl::straight_line2_d(-1, 0, -10));
        }
        {
            auto temp = agl::algorithm::parallel<agl::straight_line2_d>(line, -10);
            QVERIFY(temp == agl::straight_line2_d(1, 0, -10));
        }
    }
    {
        auto line = agl::half_line2_d(agl::point2_d{0.,0.}, 0_deg);
        {
            auto temp = agl::algorithm::parallel<agl::straight_line2_d>(line, 10);
            QVERIFY(temp == agl::straight_line2_d(-1, 0, -10));
        }
        {
            auto temp = agl::algorithm::parallel<agl::straight_line2_d>(line, -10);
            QVERIFY(temp == agl::straight_line2_d(1, 0, -10));
        }
    }
    {
        auto line = agl::line_section2_d(agl::point2_d{0.,0.},
                                            agl::point2_d{0.,10.});
        {
            auto temp = agl::algorithm::parallel<agl::straight_line2_d>(line, 10);
            QVERIFY(temp == agl::straight_line2_d(-1, 0, -10));
        }
        {
            auto temp = agl::algorithm::parallel<agl::straight_line2_d>(line, -10);
            QVERIFY(temp == agl::straight_line2_d(1, 0, -10));
        }
    }
}

void TestAlgorithm::test_perpendicular()
{
    {
        auto line = agl::straight_line2_d(agl::point2_d{1.,2.},
                                                     agl::point2_d{5.,2.});
        auto temp = agl::algorithm::perpendicular<agl::straight_line2_d>(line, agl::point2_d{0.,0.});
        auto point =  agl::algorithm::intersection<agl::point2_d>(line, temp);
        QVERIFY(point == agl::point2_d(0.,2.));
    }
    {
        auto line = agl::straight_line2_d(agl::point2_d{1.,2.},
                                                     agl::point2_d{5.,2.});
        auto temp = agl::algorithm::perpendicular<agl::straight_line2_d>(line, agl::point2_d{10.,10.});
        auto point =  agl::algorithm::intersection<agl::point2_d>(line, temp);
        QVERIFY(point == agl::point2_d(10.,2.));
    }

    {
        auto line = agl::half_line2_d(agl::point2_d{1.,2.}, 45_deg);
        auto temp = agl::algorithm::perpendicular<agl::straight_line2_d>(line, agl::point2_d{10.,10.});
        auto point =  agl::algorithm::intersection<agl::point2_d>(line, temp);
        QVERIFY(point.has_value() && (point == agl::point2_d(9.5,10.5)));
    }
    {
        auto line = agl::half_line2_d(agl::point2_d{1.,2.}, 45_deg);
        auto temp = agl::algorithm::perpendicular<agl::straight_line2_d>(line, agl::point2_d{-100.,-100.});
        auto point =  agl::algorithm::intersection<agl::point2_d>(line, temp);
        QVERIFY(!point.has_value());
    }

    {
        auto line = agl::line_section2_d(agl::point2_d{1.,2.},
                                            agl::point2_d{5.,2.});
        auto temp = agl::algorithm::perpendicular<agl::straight_line2_d>(line, agl::point2_d{0.,0.});
        auto point =  agl::algorithm::intersection<agl::point2_d>(line, temp);
        QVERIFY(!point.has_value());
    }
    {
        auto line = agl::line_section2_d(agl::point2_d{1.,2.},
                                            agl::point2_d{50.,20.});
        auto temp = agl::algorithm::perpendicular<agl::straight_line2_d>(line, agl::point2_d{10.,10.});
        auto point =  agl::algorithm::intersection<agl::point2_d>(line, temp);
        QVERIFY(point.has_value() && (point == agl::point2_d(11.519266,5.864220)));
    }
}

void TestAlgorithm::test_point_on_curve()
{
    {
        auto half_line = agl::half_line2_d(agl::point2_d{1.,2.}, 45_deg);
        auto point = agl::algorithm::point_on_curve<agl::point2_d>(half_line, 10.);
        QVERIFY(point == agl::point2_d(8.071068,9.071068));
    }

    {
        auto half_line = agl::half_line2_d(agl::point2_d{1.,2.}, 45_deg);
        auto point = agl::algorithm::point_on_curve<agl::point2_d>(half_line, 2.);
        QVERIFY(point == agl::point2_d(2.414214,3.414214));
    }
    {
        auto line_section = agl::line_section2_d(agl::point2_d{1.,2.},
                                                    agl::point2_d{5.,2.});
        auto point = agl::algorithm::point_on_curve<agl::point2_d>(line_section, 10.);
        QVERIFY(!point.has_value());
    }

    {
        auto line_section = agl::line_section2_d(agl::point2_d{1.,2.},
                                                    agl::point2_d{5.,2.});
        auto point = agl::algorithm::point_on_curve<agl::point2_d>(line_section, 2.);
        QVERIFY(point.has_value() && (point.value() == agl::point2_d(3.,2.)));
    }
    {
        agl::arc2_d arc{{1.,1.}, 5., 0_deg, 90_deg};
        auto value = agl::algorithm::point_on_curve<agl::point2_d>(arc, 10.);
        QVERIFY(!value.has_value());
    }
    {
        agl::arc2_d arc{{1.,1.}, 5., 0_deg, 90_deg};
        auto value = agl::algorithm::point_on_curve<agl::point2_d>(arc, 5.);
        QVERIFY(value.has_value() && (value.value() == agl::point2_d(5.207355, 3.701512)));
    }
}

void TestAlgorithm::test_located_inside()
{
    {
        {
            agl::circle2_d circle{{1.,1.}, 10.};
            QVERIFY(agl::algorithm::contain(circle, agl::point2_d{0., 0.}));
        }
        {
            agl::circle2_d circle{{1.,1.}, 10.};
            QVERIFY(!agl::algorithm::contain(circle, agl::point2_d{100., 100.}));
        }
    }
}

void TestAlgorithm::test_create_polygon()
{
    {
        auto polygon = agl::algorithm::create_polygon<agl::figure::polygon<agl::point2_d, agl::tag::polygon::rectangle>,
                                                      agl::algorithm::strategy::create_rectangle_point_sides>(agl::point2_d{0., 0.}, 5., 2.);
        auto points = polygon.points();
        QVERIFY(points[0] == agl::point2_d(0,0));
        QVERIFY(points[1] == agl::point2_d(5,0));
        QVERIFY(points[2] == agl::point2_d(5,2));
        QVERIFY(points[3] == agl::point2_d(0,2));
    }
    {
        auto polygon = agl::algorithm::create_polygon<agl::figure::polygon<agl::point2_d, agl::tag::polygon::rectangle>,
                                                      agl::algorithm::strategy::create_rectangle_center_sides>(agl::point2_d{0., 0.}, 5., 2.);
        auto points = polygon.points();
        QVERIFY(points[0] == agl::point2_d(-2.5, -1));
        QVERIFY(points[1] == agl::point2_d(2.5, -1));
        QVERIFY(points[2] == agl::point2_d(2.5, 1));
        QVERIFY(points[3] == agl::point2_d(-2.5, 1));
    }
    {
        auto polygon = agl::algorithm::create_polygon<agl::regular,
                                                      agl::algorithm::strategy::create_square_point_sides>(agl::point2_d{0., 0.}, 5.);
        auto points = polygon.points();
        QVERIFY(points[0] == agl::point2_d(0,0));
        QVERIFY(points[1] == agl::point2_d(5,0));
        QVERIFY(points[2] == agl::point2_d(5,5));
        QVERIFY(points[3] == agl::point2_d(0,5));
    }
    {
        auto polygon = agl::algorithm::create_polygon<agl::regular,
                                                      agl::algorithm::strategy::create_square_center_sides>(agl::point2_d{0., 0.}, 5.);
        auto points = polygon.points();
        QVERIFY(points[0] == agl::point2_d(-2.5, -2.5));
        QVERIFY(points[1] == agl::point2_d(2.5, -2.5));
        QVERIFY(points[2] == agl::point2_d(2.5, 2.5));
        QVERIFY(points[3] == agl::point2_d(-2.5, 2.5));
    }
//     //------------------------------------------
    {
        auto polygon = agl::algorithm::create_polygon<agl::figure::polygon<agl::point2_d, agl::tag::polygon::triangle>,
                                                      agl::algorithm::strategy::create_triangle_point_sides>(agl::point2_d{0., 0.}, 3., 4., 6.);
        auto points = polygon.points();
        QVERIFY(points[0] == agl::point2_d(0, 0));
        QVERIFY(points[1] == agl::point2_d(3, 0));
        QVERIFY(points[2] == agl::point2_d(4.833333, -3.555122));
    }
    {
        auto polygon = agl::algorithm::create_polygon<agl::figure::polygon<agl::point2_d, agl::tag::polygon::triangle>,
                                                      agl::algorithm::strategy::create_triangle_point_sides_angle>(agl::point2_d{0., 0.}, 3., 4., 45_deg);
        auto points = polygon.points();
        QVERIFY(points[0] == agl::point2_d(0, 0));
        QVERIFY(points[1] == agl::point2_d(3, 0));
        QVERIFY(points[2] == agl::point2_d(2.121320, 2.121320));
    }
    {
        auto polygon = agl::algorithm::create_polygon<agl::figure::polygon<agl::point2_d, agl::tag::polygon::triangle>,
                                                      agl::algorithm::strategy::create_triangle_point_sides_angles>(agl::point2_d{0., 0.}, 5., 30_deg, 80_deg);
        auto points = polygon.points();
        QVERIFY(points[0] == agl::point2_d(0, 0));
        QVERIFY(points[1] == agl::point2_d(5, 0));
        QVERIFY(points[2] == agl::point2_d(-3.868146, 5.120026));
    }
    {
        auto polygon = agl::algorithm::create_polygon<agl::figure::polygon<agl::point2_d, agl::tag::polygon::triangle>,
                                                      agl::algorithm::strategy::create_triangle_rectangular_sides>(agl::point2_d{0., 0.}, 5., 7.);
        auto points = polygon.points();
        QVERIFY(points[0] == agl::point2_d(0, 0));
        QVERIFY(points[1] == agl::point2_d(5, 0));
        QVERIFY(points[2] == agl::point2_d(0, 7));
    }
//     // std::cout << polygon << std::endl;
    {
        auto polygon = agl::algorithm::create_polygon<agl::figure::polygon<agl::point2_d, agl::tag::polygon::triangle>,
                                                      agl::algorithm::strategy::create_triangle_rectangular_sides_angles>(agl::point2_d{0., 0.}, 5., 80_deg);
        auto points = polygon.points();
        QVERIFY(points[0] == agl::point2_d(0, 0));
        QVERIFY(points[1] == agl::point2_d(5, 0));
        QVERIFY(points[2] == agl::point2_d(0, 28.356409));
    }
    {
        auto polygon = agl::algorithm::create_polygon<agl::figure::polygon<agl::point2_d, agl::tag::polygon::triangle>,
                                                      agl::algorithm::strategy::create_triangle_isosceles_sides>(agl::point2_d{0., 0.}, 5., 3.);
        auto points = polygon.points();
        QVERIFY(points[0] == agl::point2_d(0, 0));
        QVERIFY(points[1] == agl::point2_d(5, 0));
        QVERIFY(points[2] == agl::point2_d(0.9, -2.861818));
    }
    {
        auto polygon = agl::algorithm::create_polygon<agl::figure::polygon<agl::point2_d, agl::tag::polygon::triangle>,
                                                      agl::algorithm::strategy::create_triangle_isosceles_sides_angles>(agl::point2_d{0., 0.}, 5., 80_deg);
        auto points = polygon.points();
        QVERIFY(points[0] == agl::point2_d(0, 0));
        QVERIFY(points[1] == agl::point2_d(5, 0));
        QVERIFY(points[2] == agl::point2_d(0.868241, 4.924039));
    }
    {
        auto polygon = agl::algorithm::create_polygon<agl::figure::polygon<agl::point2_d, agl::tag::polygon::triangle>,
                                                      agl::algorithm::strategy::create_triangle_regular>(agl::point2_d{0., 0.}, 5.);
        auto points = polygon.points();
        QVERIFY(points[0] == agl::point2_d(0, 0));
        QVERIFY(points[1] == agl::point2_d(5, 0));
        QVERIFY(points[2] == agl::point2_d(0.669873, -2.5));
    }
    {
        auto polygon = agl::algorithm::create_polygon<agl::regular,
                                                      agl::algorithm::strategy::create_triangle_regular>(agl::point2_d{0., 0.}, 5., 3);
        auto points = polygon.points();
        QVERIFY(points[0] == agl::point2_d(0, 0));
        QVERIFY(points[1] == agl::point2_d(5, 0));
        QVERIFY(points[2] == agl::point2_d(0.669873, -2.5));
    }
    {
        {
            auto polygon = agl::algorithm::create_polygon<agl::regular,
                                                          agl::algorithm::strategy::create_polygon_regular>(agl::point2_d{0., 0.}, 5., 3);
            auto points = polygon.points();
            QVERIFY(points[0] == agl::point2_d(0, 2.886751));
            QVERIFY(points[1] == agl::point2_d(2.5, -1.443376));
            QVERIFY(points[2] == agl::point2_d(-2.5, -1.443376));
        }
        {
            auto polygon = agl::algorithm::create_polygon<agl::regular,
                                                          agl::algorithm::strategy::create_polygon_regular>(agl::point2_d{0., 0.}, 5., 4);
            auto points = polygon.points();
            QVERIFY(points[0] == agl::point2_d(0, 3.535534));
            QVERIFY(points[1] == agl::point2_d(3.535534, 0));
            QVERIFY(points[2] == agl::point2_d(0, -3.535534));
            QVERIFY(points[3] == agl::point2_d(-3.535534, 0));
        }
        {
            auto polygon = agl::algorithm::create_polygon<agl::regular,
                                                          agl::algorithm::strategy::create_polygon_regular>(agl::point2_d{0., 0.}, 5., 5);
            auto points = polygon.points();
            QVERIFY(points[0] == agl::point2_d(0, 4.253254));
            QVERIFY(points[1] == agl::point2_d(4.045085, 1.314328));
            QVERIFY(points[2] == agl::point2_d(2.5, -3.440955));
            QVERIFY(points[3] == agl::point2_d(-2.5, -3.440955));
            QVERIFY(points[4] == agl::point2_d(-4.045085, 1.314328));
        }
    }
}

void TestAlgorithm::test_tangent_circle()
{
    {//scaling_tangent_out
        {
            agl::circle2_d circle1{{0.,5.}, 5.};
            agl::circle2_d circle2{{5.,5.}, 5.};
            auto [line1, line2] = agl::algorithm::tangent_circle<agl::line_section2_d>(circle1, circle2, agl::algorithm::type_tangent::external{});
            QVERIFY(line1.has_value() && (line1->start() == agl::point2_d(0, 10)) && (line1->stop() == agl::point2_d(5, 10)));
            QVERIFY(line2.has_value() && (line2->start() == agl::point2_d(0, 0)) && (line2->stop() == agl::point2_d(5, 0)));
        }

        {
            agl::circle2_d circle1{{0.,5.}, 5.};
            agl::circle2_d circle2{{0.,5.}, 5.};
            auto [line1, line2] = agl::algorithm::tangent_circle<agl::line_section2_d>(circle1, circle2, agl::algorithm::type_tangent::external{});
            QVERIFY(!line1.has_value());
            QVERIFY(!line2.has_value());
        }

        {
            agl::circle2_d circle1{{0.,5.}, 5.};
            agl::circle2_d circle2{{10.,5.}, 50.};
            auto [line1, line2] = agl::algorithm::tangent_circle<agl::line_section2_d>(circle1, circle2, agl::algorithm::type_tangent::external{});
            QVERIFY(!line1.has_value());
            QVERIFY(!line2.has_value());
        }

        {
            agl::circle2_d circle1{{0.,5.}, 5.};
            agl::circle2_d circle2{{10.,5.}, 8.};
            auto [line1, line2] = agl::algorithm::tangent_circle<agl::line_section2_d>(circle1, circle2, agl::algorithm::type_tangent::external{});
            QVERIFY(line1.has_value() && (line1->start() == agl::point2_d(-1.5, 0.230304)) && (line1->stop() == agl::point2_d(7.6, -2.631514)));
            QVERIFY(line2.has_value() && (line2->start() == agl::point2_d(-1.5, 9.769696)) && (line2->stop() == agl::point2_d(7.6, 12.631514)));
        }
    }

    {//scaling_tangent_inboard
        {
            agl::circle2_d circle1{{0.,5.}, 5.};
            agl::circle2_d circle2{{5.,5.}, 5.};
            auto [line1, line2] = agl::algorithm::tangent_circle<agl::line_section2_d>(circle1, circle2, agl::algorithm::type_tangent::internal{});
            QVERIFY(!line1.has_value());
            QVERIFY(!line2.has_value());
        }
        {
            agl::circle2_d circle1{{0.,5.}, 5.};
            agl::circle2_d circle2{{0.,5.}, 5.};
            auto [line1, line2] = agl::algorithm::tangent_circle<agl::line_section2_d>(circle1, circle2, agl::algorithm::type_tangent::internal{});
            QVERIFY(!line1.has_value());
            QVERIFY(!line2.has_value());
        }
        {
            agl::circle2_d circle1{{0.,5.}, 5.};
            agl::circle2_d circle2{{10.,5.}, 50.};
            auto [line1, line2] = agl::algorithm::tangent_circle<agl::line_section2_d>(circle1, circle2, agl::algorithm::type_tangent::internal{});
            QVERIFY(!line1.has_value());
            QVERIFY(!line2.has_value());
        }
        {
            agl::circle2_d circle1{{0.,5.}, 5.};
            agl::circle2_d circle2{{10.,5.}, 8.};
            auto [line1, line2] = agl::algorithm::tangent_circle<agl::line_section2_d>(circle1, circle2, agl::algorithm::type_tangent::internal{});
            QVERIFY(!line1.has_value());
            QVERIFY(!line2.has_value());
        }
        {
            agl::circle2_d circle1{{0.,5.}, 5.};
            agl::circle2_d circle2{{20.,5.}, 5.};
            auto [line1, line2] = agl::algorithm::tangent_circle<agl::line_section2_d>(circle1, circle2, agl::algorithm::type_tangent::internal{});
            QVERIFY(line1.has_value() && (line1->start() == agl::point2_d(2.5, 9.330127)) && (line1->stop() == agl::point2_d(17.5, 0.669873)));
            QVERIFY(line2.has_value() && (line2->start() == agl::point2_d(2.5,  0.669873)) && (line2->stop() == agl::point2_d(17.5,  9.330127)));
        }

        {
            agl::circle2_d circle1{{0.,5.}, 5.};
            agl::circle2_d circle2{{100.,5.}, 50.};
            auto [line1, line2] = agl::algorithm::tangent_circle<agl::line_section2_d>(circle1, circle2, agl::algorithm::type_tangent::internal{});
            QVERIFY(line1.has_value() && (line1->start() == agl::point2_d(2.75, 9.175823)) && (line1->stop() == agl::point2_d(72.5, -36.758233)));
            QVERIFY(line2.has_value() && (line2->start() == agl::point2_d(2.75, 0.824177)) && (line2->stop() == agl::point2_d(72.5,  46.758233)));
        }
    }

    {
        {
            agl::circle2_d circle{{0.,0.}, 5.};
            auto point = agl::point2_d(10., 0.);
            auto [line1, line2] = agl::algorithm::tangent_circle<agl::line_section2_d>(circle, point, agl::algorithm::type_tangent::external{});
            QVERIFY(line1.has_value() && (line1->start() == agl::point2_d(2.5, -4.330127)) && (line1->stop() == agl::point2_d(10, 0)));
            QVERIFY(line2.has_value() && (line2->start() == agl::point2_d(2.5, 4.330127)) && (line2->stop() == agl::point2_d(10, 0)));
        }

        {
            agl::circle2_d circle{{0.,0.}, 5.};
            auto point = agl::point2_d(1., 0.);
            auto [line1, line2] = agl::algorithm::tangent_circle<agl::line_section2_d>(circle, point, agl::algorithm::type_tangent::external{});
            QVERIFY(!line1.has_value());
            QVERIFY(!line2.has_value());
        }

        {
            agl::circle2_d circle{{5.,5.}, 5.};
            auto point = agl::point2_d(30., 45.);
            auto [line1, line2] = agl::algorithm::tangent_circle<agl::line_section2_d>(circle, point, agl::algorithm::type_tangent::external{});
            QVERIFY(line1.has_value() && (line1->start() == agl::point2_d(9.497003, 2.814373)) && (line1->stop() == agl::point2_d(30, 45)));
            QVERIFY(line2.has_value() && (line2->start() == agl::point2_d(1.064795, 8.084503)) && (line2->stop() == agl::point2_d(30, 45)));
        }
    }
}

void TestAlgorithm::test_create_circle()
{
    {//center_circle_in_line
        {
            auto point = agl::point2_d(0, 5);
            auto [circle1, circle2] = agl::algorithm::create_circle<agl::circle2_d,
                                                                    agl::algorithm::strategy::create_circle_angle_point>(0_deg, point, 10.);
            QVERIFY((circle1->center() == agl::point2_d(-10, 5)) && (circle2->center() == agl::point2_d(10, 5)));
        }
        // {
        //     auto point = agl::point2_d(0, 0);
        //     auto [circle1, circle2] = agl::algorithm::create_circle<agl::circle2_d,
        //                                                             agl::algorithm::strategy::create_circle_angle_point>(0_deg, point, 10.);
        //     QVERIFY((circle1->center() == agl::point2_d(-10, 0)) && (circle2->center() == agl::point2_d(10, 0)));
        // }
        // {
        //     auto point = agl::point2_d(5, 5);
        //     auto [circle1, circle2] = agl::algorithm::create_circle<agl::circle2_d,
        //                                                             agl::algorithm::strategy::create_circle_angle_point>(45_deg, point, 10.);
        //     QVERIFY((circle1->center() == agl::point2_d(-2.071068, 12.071068)) && (circle2->center() == agl::point2_d(12.071068, -2.071068)));
        // }
    }
}

void TestAlgorithm::test_get_lines()
{
    {//get_lines
        auto polygon = agl::polygon({agl::point2_d(0,10),
                                                                                                             agl::point2_d(10,10),
                                                                                                             agl::point2_d(10,0),
                                                                                                             agl::point2_d(0,0)});
        auto lines = agl::algorithm::get_lines<agl::line_section2_d>(polygon);
        std::vector<agl::line_section2_d> temp{
                                      {agl::point2_d(0,10),agl::point2_d(10,10)},
                                      {agl::point2_d(10,10), agl::point2_d(10,0)},
                                      {agl::point2_d(10,0), agl::point2_d(0,0)},
                                      {agl::point2_d(0,0), agl::point2_d(0,10)}};
        QVERIFY(lines.size() == polygon.points().size());
        for(size_t i = 0; i < lines.size(); ++i){
            QVERIFY(lines[i] == temp[i]);
        }
    }
}

void TestAlgorithm::point_coupling()
{
    {//point_coupling
        {
            auto line_section = agl::line_section2_d(agl::point2_d{0,10},
                                                        agl::point2_d{10,10});
            auto point = agl::algorithm::point_coupling(line_section, agl::point2_d{-1,1}, true);
            QVERIFY(!point.has_value());
        }
        {
            auto line_section = agl::line_section2_d(agl::point2_d{0,10},
                                                        agl::point2_d{10,10});
            auto point = agl::algorithm::point_coupling(line_section, agl::point2_d{-1,1}, false);
            QVERIFY(point == agl::point2_d(0.,10.));
        }
        {
            auto polygon = agl::polygon({agl::point2_d(0,10),
                                                                                                                 agl::point2_d(10,10),
                                                                                                                 agl::point2_d(10,0),
                                                                                                                 agl::point2_d(0,0)});
            {
                auto point = agl::algorithm::point_coupling(polygon, agl::point2_d(-1,1), true);
                QVERIFY(point == agl::point2_d(0.,1.));
            }
            {
                auto point = agl::algorithm::point_coupling(polygon, agl::point2_d(-1,1), false);
                QVERIFY(point == agl::point2_d(0.,1.));
            }
        }
        {
            auto polygon = agl::polygon({agl::point2_d(0,10),
                                                                                                                 agl::point2_d(10,10),
                                                                                                                 agl::point2_d(10,0),
                                                                                                                 agl::point2_d(0,0)});
            {
                auto point = agl::algorithm::point_coupling(polygon, agl::point2_d(-1,-1), true);
                QVERIFY(!point.has_value());
            }
            {
                auto point = agl::algorithm::point_coupling(polygon, agl::point2_d(-1,-1), false);
                QVERIFY(point == agl::point2_d(0.,0.));
            }
        }
        {
            auto polygon = agl::polygon({agl::point2_d(0,10),
                                                                                                                 agl::point2_d(10,10),
                                                                                                                 agl::point2_d(10,0),
                                                                                                                 agl::point2_d(0,0)});
            {
                auto point = agl::algorithm::point_coupling(polygon, agl::point2_d(5,50), true);
                QVERIFY(point == agl::point2_d(5.,10.));
            }
            {
                auto point = agl::algorithm::point_coupling(polygon, agl::point2_d(5,50), false);
                QVERIFY(point == agl::point2_d(5.,10.));
            }
        }
        {
            auto polygon = agl::polygon({agl::point2_d(0,10),
                                                                                                                 agl::point2_d(10,10),
                                                                                                                 agl::point2_d(10,0),
                                                                                                                 agl::point2_d(0,0)});
            {
                auto point = agl::algorithm::point_coupling(polygon, agl::point2_d(4,3), true);
                QVERIFY(point == agl::point2_d(4.,0.));
            }
            {
                auto point = agl::algorithm::point_coupling(polygon, agl::point2_d(4,3), false);
                QVERIFY(point == agl::point2_d(4.,0.));
            }
        }
    }
}
