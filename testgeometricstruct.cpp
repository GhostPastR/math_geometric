#include "testgeometricstruct.h"
#include <QtTest/QTest>
#include <structs/geometric_object.h>
#include <unit/unit_object.h>
#include "algorithm/math_algorithm.h"

TestGeometricStruct::TestGeometricStruct(QObject *parent)
    : QObject{parent}
{}

void TestGeometricStruct::test_point()
{
    {
        agl::point::decart::point2d<double> point1;
        QVERIFY(agl::algorithm::compare(point1.x(), 0.));
        QVERIFY(agl::algorithm::compare(point1.y(), 0.));

        point1.set_x(100.);
        point1.set_y(100.);
        QVERIFY(agl::algorithm::compare(point1.x(), 100.));
        QVERIFY(agl::algorithm::compare(point1.y(), 100.));

        agl::point::decart::point2d<double> point2;
        point2.set_x(100.);
        point2.set_y(100.);
        QVERIFY(point1 == point2);
    }


    {
        agl::point::decart::point2d<double> point1;
        QVERIFY(agl::algorithm::compare(point1.x(), 0.));
        QVERIFY(agl::algorithm::compare(point1.y(), 0.));

        point1.set_x(100.);
        point1.set_y(100.);
        QVERIFY(agl::algorithm::compare(point1.x(), 100.));
        QVERIFY(agl::algorithm::compare(point1.y(), 100.));

        agl::point::decart::point2d<double> point2;
        point2.set_x(100.);
        point2.set_y(100.);
        QVERIFY(point1 == point2);
    }

    {
        agl::point::decart::point3d<double> point1;
        QVERIFY(agl::algorithm::compare(point1.x(), 0.));
        QVERIFY(agl::algorithm::compare(point1.y(), 0.));
        QVERIFY(agl::algorithm::compare(point1.z(), 0.));

        point1.set_x(100.);
        point1.set_y(123.);
        point1.set_z(34.);
        QVERIFY(agl::algorithm::compare(point1.x(), 100.));
        QVERIFY(agl::algorithm::compare(point1.y(), 123.));
        QVERIFY(agl::algorithm::compare(point1.z(), 34.));

        agl::point::decart::point3d<double> point2;
        point2.set_x(100.);
        point2.set_y(123.);
        point2.set_z(34.);
        QVERIFY(point1 == point2);
    }

    {
        // PointGeo point;
        // QVERIFY(point.latitude() == 0_deg);
        // QVERIFY(point.longitude() == 0_deg);

        // point.set_latitude(56.7_deg);
        // point.set_longitude(12.12_deg);
        // QVERIFY(point.latitude() == 56.7_deg);
        // QVERIFY(point.longitude() == 12.12_deg);

        // PointGeo point1{10_deg, 10_deg};
        // PointGeo point2{10_deg, 10_deg};
        // QVERIFY(point1 == point2);
    }

    {
        // PointGeo3d point;
        // QVERIFY(point.latitude() == 0_deg);
        // QVERIFY(point.longitude() == 0_deg);
        // QVERIFY(algorithm::compare(point.altitude(), 0.));

        // point.set_latitude(56.7_deg);
        // point.set_longitude(12.12_deg);
        // point.set_altitude(1232);
        // QVERIFY(point.latitude() == 56.7_deg);
        // QVERIFY(point.longitude() == 12.12_deg);
        // QVERIFY(algorithm::compare(point.altitude(), 1232.));

        // PointGeo3d point1{10_deg, 10_deg, 123.0};
        // PointGeo3d point2{10_deg, 10_deg, 123.};
        // QVERIFY(point1 == point2);
    }

    // {
    //     PointGeo4d point;
    //     QVERIFY(point.latitude() == 0_deg);
    //     QVERIFY(point.longitude() == 0_deg);
    //     QVERIFY(algorithm::compare(point.altitude(), 0.));
    //     QVERIFY(algorithm::compare(point.time(), 0.));

    //     point.set_latitude(56.7_deg);
    //     point.set_longitude(12.12_deg);
    //     point.set_altitude(1232);
    //     point.set_time(3533);
    //     QVERIFY(point.latitude() == 56.7_deg);
    //     QVERIFY(point.longitude() == 12.12_deg);
    //     QVERIFY(algorithm::compare(point.altitude(), 1232.));
    //     QVERIFY(algorithm::compare(point.time(), 3533.));

    //     PointGeo4d point1{10_deg, 10_deg, 123, 56};
    //     PointGeo4d point2{10_deg, 10_deg, 123, 56};
    //     QVERIFY(point1 == point2);
    // }

    {
        agl::point::polar::polar2d<double, agl::unit::angle> point;
        QVERIFY(agl::algorithm::compare(point.psi(), 0.));
        QVERIFY(point.fi() == 0_deg);

        point.set_psi(123);
        point.set_fi(3_deg);
        QVERIFY(agl::algorithm::compare(point.psi(), 123.));
        QVERIFY(point.fi() == 3_deg);
    }

    {
        agl::point::polar::polar3d<double, agl::unit::angle, double> point;
        QVERIFY(agl::algorithm::compare(point.psi(), 0.));
        QVERIFY(point.fi() == 0_deg);
        QVERIFY(agl::algorithm::compare(point.z(), 0.));

        point.set_psi(123);
        point.set_fi(3_deg);
        point.set_z(21);
        QVERIFY(agl::algorithm::compare(point.psi(), 123.));
        QVERIFY(point.fi() == 3_deg);
        QVERIFY(agl::algorithm::compare(point.z(), 21.));
    }


    {
        agl::point::decart::point2d<agl::unit::distance> point1;
        QVERIFY(agl::algorithm::compare(point1.x(), 0_m));
        QVERIFY(agl::algorithm::compare(point1.y(), 0_m));

        point1.set_x(100_m);
        point1.set_y(100_m);
        QVERIFY(agl::algorithm::compare(point1.x(), 100_m));
        QVERIFY(agl::algorithm::compare(point1.y(), 100_m));

        agl::point::decart::point2d<agl::unit::distance> point2;
        point2.set_x(100_m);
        point2.set_y(100_m);
        QVERIFY(point1 == point2);
    }
}

void TestGeometricStruct::test_line()
{
    {
        {
            auto line = agl::line::straight_line<double>(1,2,3);
            QVERIFY(agl::algorithm::compare(line.a(), -0.447214));
            QVERIFY(agl::algorithm::compare(line.b(),  -0.894427));
            QVERIFY(agl::algorithm::compare(line.c(),  -1.341641));
        }
        {
            auto line = agl::line::straight_line<double>(agl::point::decart::point2d<double>{1.,0.},
                                                         agl::point::decart::point2d<double>{5.,3.});
            QVERIFY(agl::algorithm::compare(line.a(), 0.6));
            QVERIFY(agl::algorithm::compare(line.b(), -0.8));
            QVERIFY(agl::algorithm::compare(line.c(), -0.6));
        }

        {
            auto line1 = agl::line::straight_line<double>(agl::point::decart::point2d<double>{0.,0.},
                                                          agl::point::decart::point2d<double>{0.,10.});
            auto line2 = agl::line::straight_line<double>(agl::point::decart::point2d<double>{0.,2.},
                                                          agl::point::decart::point2d<double>{5.,2.});
            QVERIFY(line1 != line2);
        }

        {
            auto line1 = agl::line::straight_line<double>(agl::point::decart::point2d<double>{0.,2.},
                                                          agl::point::decart::point2d<double>{5.,2.});
            auto line2 = agl::line::straight_line<double>(agl::point::decart::point2d<double>{0.,2.},
                                                          agl::point::decart::point2d<double>{5.,2.});
            QVERIFY(line1 == line2);
        }

        {
            auto line1 = agl::line::straight_line<double>(1,1,1);
            auto line2 = agl::line::straight_line<double>(2,2,2);
            QVERIFY(line1 == line2);
        }
    }

    {
        {
            auto half_line = agl::line::half_line(agl::point::decart::point2d<double>{0.,2.}, 50_deg);
            auto [a,b,c] = agl::algorithm::equation_of_line(half_line);
            QVERIFY(agl::algorithm::compare(a, -0.642788));
            QVERIFY(agl::algorithm::compare(b, 0.7660444));
            QVERIFY(agl::algorithm::compare(c, -1.532089));
        }

        {
            auto half_line1 = agl::line::half_line(agl::point::decart::point2d<double>{3.,2.}, 50_deg);
            auto half_line2 = agl::line::half_line(agl::point::decart::point2d<double>{3.,2.}, 50_deg);
            QVERIFY(half_line1 == half_line2);
        }

        {
            auto half_line1 = agl::line::half_line(agl::point::decart::point2d<double>{3.,2.}, 50_deg);
            auto half_line2 = agl::line::half_line(agl::point::decart::point2d<double>{3.,20.}, 50_deg);
            QVERIFY(half_line1 != half_line2);
        }
    }

    {
        {
            auto line_section = agl::line::line_section(agl::point::decart::point2d<double>{0.,2.},
                                                        agl::point::decart::point2d<double>{1.,2.});
            auto [a,b,c] = agl::algorithm::equation_of_line(line_section);
            QVERIFY(agl::algorithm::compare(a, 0.));
            QVERIFY(agl::algorithm::compare(b, 1.));
            QVERIFY(agl::algorithm::compare(c, -2.));
        }

        {
            auto line_section1 = agl::line::line_section(agl::point::decart::point2d<double>{0.,2.},
                                                         agl::point::decart::point2d<double>{1.,2.});
            auto line_section2 = agl::line::line_section(agl::point::decart::point2d<double>{0.,2.},
                                                         agl::point::decart::point2d<double>{1.,2.});
            QVERIFY(line_section1 == line_section2);
        }

        {
            auto line_section1 = agl::line::line_section(agl::point::decart::point2d<double>{0.,2.},
                                                         agl::point::decart::point2d<double>{1.,2.});
            auto line_section2 = agl::line::line_section(agl::point::decart::point2d<double>{1.,2.},
                                                         agl::point::decart::point2d<double>{2.,2.});
            QVERIFY(line_section1 != line_section2);
        }
    }
}

void TestGeometricStruct::test_circle()
{
    {
        agl::circle::arc<agl::point::decart::point2d<double>, double, agl::unit::angle> arc{{1.,1.}, 5., 0_deg, 90_deg};
        QVERIFY((arc.center() == agl::point::decart::point2d<double>(1.,1.))
                && agl::algorithm::compare(arc.radius(), 5.) && (arc.start() == 0_deg) && (arc.stop() == 90_deg));
    }
    {
        agl::circle::circle<agl::point::decart::point2d<double>, double> circle{{1.,1.}, 5.};
        QVERIFY((circle.center() == agl::point::decart::point2d<double>(1.,1.)) && agl::algorithm::compare(circle.radius(), 5.));
    }
}

void TestGeometricStruct::test_polygon()
{
    {
        {
            try{
                auto polygon = agl::figure::polygon<agl::point::decart::point2d<double>,
                                                    agl::tag::polygon::convex>(
                    {agl::point::decart::point2d<double>(0,0),
                     agl::point::decart::point2d<double>(5,5),
                     agl::point::decart::point2d<double>(5,0)}, true);
                auto points = polygon.points();
                QVERIFY(points[0] == agl::point::decart::point2d<double>(0,0));
                QVERIFY(points[1] == agl::point::decart::point2d<double>(5,5));
                QVERIFY(points[2] == agl::point::decart::point2d<double>(5,0));
            }
            catch (const std::logic_error &e){
                QVERIFY(false);
            }
        }
        {
            try{
                auto polygon = agl::figure::polygon<agl::point::decart::point2d<double>,
                                                    agl::tag::polygon::convex>(
                    {agl::point::decart::point2d<double>(0,1),
                     agl::point::decart::point2d<double>(25,5),
                     agl::point::decart::point2d<double>(-5,0),
                     agl::point::decart::point2d<double>(4,3)}, true);
                QVERIFY(false);
            }
            catch (const std::logic_error &e){
                QVERIFY(true);
            }
        }
        {
            try{
                auto polygon = agl::figure::polygon<agl::point::decart::point2d<double>,
                                                    agl::tag::polygon::regular>(
                    {agl::point::decart::point2d<double>(0,10),
                     agl::point::decart::point2d<double>(10,10),
                     agl::point::decart::point2d<double>(10,0),
                     agl::point::decart::point2d<double>(0,0)}, true);
                auto points = polygon.points();
                QVERIFY(points[0] == agl::point::decart::point2d<double>(0,10));
                QVERIFY(points[1] == agl::point::decart::point2d<double>(10,10));
                QVERIFY(points[2] == agl::point::decart::point2d<double>(10,0));
                QVERIFY(points[3] == agl::point::decart::point2d<double>(0,0));
            }
            catch (const std::logic_error &e){
                QVERIFY(false);
            }
        }
    }
    {
        {
            try{
                auto polygon = agl::figure::polygon<agl::point::decart::point2d<double>,
                                                    agl::tag::polygon::rectangle>(
                    {agl::point::decart::point2d<double>(0,0),
                     agl::point::decart::point2d<double>(10,0),
                     agl::point::decart::point2d<double>(10,-5),
                     agl::point::decart::point2d<double>(0,-5)}, true);
                auto points = polygon.points();
                QVERIFY(points[0] == agl::point::decart::point2d<double>(0,0));
                QVERIFY(points[1] == agl::point::decart::point2d<double>(10,0));
                QVERIFY(points[2] == agl::point::decart::point2d<double>(10,-5));
                QVERIFY(points[3] == agl::point::decart::point2d<double>(0,-5));
            }
            catch (const std::logic_error &e){
                QVERIFY(false);
            }
        }
    }

    {
        {
            try{
                auto polygon = agl::figure::polygon<agl::point::decart::point2d<double>,
                                                    agl::tag::polygon::rectangular_triangle>(
                    {agl::point::decart::point2d<double>(0,0),
                     agl::point::decart::point2d<double>(10,0),
                     agl::point::decart::point2d<double>(10,10)}, true);
                auto points = polygon.points();
                QVERIFY(points[0] == agl::point::decart::point2d<double>(0,0));
                QVERIFY(points[1] == agl::point::decart::point2d<double>(10,0));
                QVERIFY(points[2] == agl::point::decart::point2d<double>(10,10));
            }
            catch (const std::logic_error &e){
                QVERIFY(false);
            }
        }

        {
            try{
                auto polygon = agl::figure::polygon<agl::point::decart::point2d<double>,
                                                    agl::tag::polygon::triangle>(
                    {agl::point::decart::point2d<double>(0,0),
                     agl::point::decart::point2d<double>(10,0),
                     agl::point::decart::point2d<double>(20,0)}, true);
                QVERIFY(false);
            }
            catch (const std::logic_error &e){
                QVERIFY(true);
            }
        }
    }

    {//create_regular_polygon
        {
            try{
                auto polygon = agl::figure::polygon<agl::point::decart::point2d<double>,
                                                    agl::tag::polygon::regular>(
                    {agl::point::decart::point2d<double>(0, 5.773503),
                     agl::point::decart::point2d<double>(5, -2.886751),
                     agl::point::decart::point2d<double>(-5,-2.886751)}, true);
                auto points = polygon.points();
                QVERIFY(points[0] == agl::point::decart::point2d<double>(0, 5.773503));
                QVERIFY(points[1] == agl::point::decart::point2d<double>(5, -2.886751));
                QVERIFY(points[2] == agl::point::decart::point2d<double>(-5,-2.886751));
            }
            catch (const std::logic_error &e){
                QVERIFY(false);
            }
        }
        {
            try{
                auto polygon = agl::figure::polygon<agl::point::decart::point2d<double>,
                                                    agl::tag::polygon::regular>(
                    {agl::point::decart::point2d<double>(0, 7.071068),
                     agl::point::decart::point2d<double>(7.071068, 0),
                     agl::point::decart::point2d<double>(0, -7.071068),
                     agl::point::decart::point2d<double>(-7.071068, 0)}, true);
                auto points = polygon.points();
                QVERIFY(points[0] == agl::point::decart::point2d<double>(0, 7.071068));
                QVERIFY(points[1] == agl::point::decart::point2d<double>(7.071068, 0));
                QVERIFY(points[2] == agl::point::decart::point2d<double>(0, -7.071068));
                QVERIFY(points[3] == agl::point::decart::point2d<double>(-7.071068, 0));
            }
            catch (const std::logic_error &e){
                QVERIFY(false);
            }
        }
        {
            try{
                auto polygon = agl::figure::polygon<agl::point::decart::point2d<double>,
                                                    agl::tag::polygon::regular>(
                    {agl::point::decart::point2d<double>(0, 4.253254),
                     agl::point::decart::point2d<double>(4.045085, 1.314328),
                     agl::point::decart::point2d<double>(2.5, -3.440955),
                     agl::point::decart::point2d<double>(-2.5, -3.440955),
                     agl::point::decart::point2d<double>(-4.045085, 1.314328)}, true);
                auto points = polygon.points();
                QVERIFY(points[0] == agl::point::decart::point2d<double>(0, 4.253254));
                QVERIFY(points[1] == agl::point::decart::point2d<double>(4.045085, 1.314328));
                QVERIFY(points[2] == agl::point::decart::point2d<double>(2.5, -3.440955));
                QVERIFY(points[3] == agl::point::decart::point2d<double>(-2.5, -3.440955));
                QVERIFY(points[4] == agl::point::decart::point2d<double>(-4.045085, 1.314328));
            }
            catch (const std::logic_error &e){
                QVERIFY(false);
            }
        }
    }
}
