#include "unit_test.h"
#include <QtTest/QTest>
#include "algorithm/approximation_algorithm.h"
#include "algorithm/circle_algorithm.h"
#include "algorithm/geo_algorithm.h"
#include "algorithm/point_algorithm.h"
#include "algorithm/line_algorithm.h"
#include "algorithm/polygon_algorithm.h"

#include "unit/distance.h"


#include "qtestcase.h"
#include "structs/matrix.h"
#include "structs/vector.h"
#include "unit/speed.h"
#include "unit/temperature.h"
#include "unit/time.h"
#include "unit/weight.h"
#include "user_type.h"

using namespace agl;

Unit_Test::Unit_Test(QObject *parent) : QObject{parent}{}

void Unit_Test::test_angle()
{
    {
        Angle angle;
        QVERIFY(algorithm::compare(angle.radian(), 0.));
        QVERIFY(algorithm::compare(angle.degrees(), 0.));
        angle = 180._deg;
        QVERIFY(algorithm::compare(angle.radian(), algorithm::pi<decltype(angle.radian())>));
        QVERIFY(algorithm::compare(angle.degrees(), 180.));
    }
    {
        QVERIFY(4_rad == 4_rad);
        QVERIFY(5_deg == 5_deg);

        QVERIFY(50._rad == 50._rad);
        QVERIFY(50._deg == 50._deg);

        QVERIFY(20._deg < 50._deg);
        QVERIFY(23._rad < 45._rad);

        QVERIFY(12._deg > 2._deg);
        QVERIFY(56._rad > 45._rad);

        QVERIFY(20._deg <= 50._deg);
        QVERIFY(23._rad <= 45._rad);
        QVERIFY(23._rad <= 23._rad);

        QVERIFY(12._deg >= 2._deg);
        QVERIFY(56._rad >= 45._rad);
        QVERIFY(1._rad >= 1._rad);

        QVERIFY(-50._deg == -50._deg);
        QVERIFY(-50._rad == -50._rad);
        QVERIFY((50._deg + 70._deg) == 120._deg);

        {
            Angle angle1 = 40._deg;
            Angle angle2 = 65._deg;
            QVERIFY((angle1 + 70._deg) == 110._deg);
            QVERIFY((angle1 + angle2) == 105._deg);
        }

        {
            Angle angle1 = 76._deg;
            Angle angle2 = 25._deg;
            QVERIFY((angle1 - 70._deg) == 6._deg);
            QVERIFY((angle1 - angle2) == 51._deg);
            QVERIFY((angle1 - 100._deg) == -24._deg);
            QVERIFY((angle2 - angle1) == -51._deg);
        }

        {
            Angle angle = 35._deg;
            QVERIFY((angle * 2) == 70._deg);
            QVERIFY((2 * angle) == 70._deg);
            angle = 90._deg;
            QVERIFY((angle / 3) == 30._deg);
            QVERIFY((90_deg / 3) == 30._deg);
        }

        {
            Angle angle = 20._deg;
            angle += 20._deg;
            QVERIFY(angle == 40._deg);
            angle -= 50._deg;
            QVERIFY(angle == -10._deg);
        }
    }

    {
        {
            Angle angle = 45._deg;
            QVERIFY(Angle().asin(angle.sin()) == 45._deg);
            QVERIFY(Angle().acos(angle.cos()) == 45._deg);
            QVERIFY(Angle().atan(angle.tan()) == 45._deg);
            QVERIFY(Angle().actan(angle.ctan()) == 45._deg);
        }

        {
            Angle angle = 0._deg;
            QVERIFY(angle.asin(angle.sin()) == 0._deg);
            QVERIFY(angle.acos(angle.cos()) == 0._deg);
            QVERIFY(angle.atan(angle.tan()) == 0._deg);
            QVERIFY(angle.actan(angle.ctan()) == 0._deg);
        }
    }
}

void Unit_Test::test_unit()
{
    {//distance
        {
            unit::distance d(1000);
            QVERIFY(algorithm::compare(d.value<unit::millimeter>(), 1000000));
            QVERIFY(algorithm::compare(d.value<unit::centimeter>(), 100000));
            QVERIFY(algorithm::compare(d.value<unit::decimeter>(), 10000));
            QVERIFY(algorithm::compare(d.value<unit::meter>(), 1000));
            QVERIFY(algorithm::compare(d.value<unit::kilometer>(), 1));
            QVERIFY(algorithm::compare(d.value<unit::inches>(), 39370.078740));
            QVERIFY(algorithm::compare(d.value<unit::foot>(), 3280.839895));
            QVERIFY(algorithm::compare(d.value<unit::foot_usa>(), 3280.833437));
            QVERIFY(algorithm::compare(d.value<unit::mile>(), 0.621371));
            QVERIFY(algorithm::compare(d.value<unit::mile_overland>(), 0.621388));
            QVERIFY(algorithm::compare(d.value<unit::mile_usa>(), 0.62137));
            QVERIFY(algorithm::compare(d.value<unit::mile_nautical>(), 0.539957));
            QVERIFY(algorithm::compare(d.value<unit::mile_britain_n>(), 0.539612));
            QVERIFY(algorithm::compare(d.value<unit::yard>(), 1093.613298));
        }
        {
            unit::distance d;
            d.set_value<unit::millimeter>(100);
            QVERIFY(algorithm::compare(d.value<unit::meter>(), 0.1));
            d.set_value<unit::centimeter>(100);
            QVERIFY(algorithm::compare(d.value<unit::meter>(), 1));
            d.set_value<unit::decimeter>(100);
            QVERIFY(algorithm::compare(d.value<unit::meter>(), 10));
            d.set_value<unit::meter>(100);
            QVERIFY(algorithm::compare(d.value<unit::meter>(), 100));
            d.set_value<unit::kilometer>(100);
            QVERIFY(algorithm::compare(d.value<unit::meter>(), 100000));
            d.set_value<unit::inches>(100);
            QVERIFY(algorithm::compare(d.value<unit::meter>(), 2.54));
            d.set_value<unit::foot>(100);
            QVERIFY(algorithm::compare(d.value<unit::meter>(), 30.48));
            d.set_value<unit::foot_usa>(100);
            QVERIFY(algorithm::compare(d.value<unit::meter>(), 30.48006));
            d.set_value<unit::mile>(100);
            QVERIFY(algorithm::compare(d.value<unit::meter>(), 160934.4));
            d.set_value<unit::mile_overland>(100);
            QVERIFY(algorithm::compare(d.value<unit::meter>(), 160930));
            d.set_value<unit::mile_usa>(100);
            QVERIFY(algorithm::compare(d.value<unit::meter>(), 160934.7));
            d.set_value<unit::mile_nautical>(100);
            QVERIFY(algorithm::compare(d.value<unit::meter>(), 185200));
            d.set_value<unit::mile_britain_n>(100);
            QVERIFY(algorithm::compare(d.value<unit::meter>(), 185318.4));
            d.set_value<unit::yard>(100);
            QVERIFY(algorithm::compare(d.value<unit::meter>(), 91.44));
        }
        {
            QVERIFY(algorithm::compare((100_mm).value<unit::meter>(), 0.1));
            QVERIFY(algorithm::compare((100_cm).value<unit::meter>(), 1));
            QVERIFY(algorithm::compare((100_dm).value<unit::meter>(), 10));
            QVERIFY(algorithm::compare((100_m).value<unit::meter>(), 100));
            QVERIFY(algorithm::compare((100_km).value<unit::meter>(), 100000));
            QVERIFY(algorithm::compare((100_in).value<unit::meter>(), 2.54));
            QVERIFY(algorithm::compare((100_ft).value<unit::meter>(), 30.48));
            QVERIFY(algorithm::compare((100_ft_usa).value<unit::meter>(), 30.48006));
            QVERIFY(algorithm::compare((100_mile).value<unit::meter>(), 160934.4));
            QVERIFY(algorithm::compare((100_mile_ov).value<unit::meter>(), 160930));
            QVERIFY(algorithm::compare((100_mile_usa).value<unit::meter>(), 160934.7));
            QVERIFY(algorithm::compare((100_mile_n).value<unit::meter>(), 185200));
            QVERIFY(algorithm::compare((100_mile_bn).value<unit::meter>(), 185318.4));
            QVERIFY(algorithm::compare((100_yd).value<unit::meter>(), 91.44));
        }
    }

    {//time
        {
            unit::time t(1000);
            QVERIFY(algorithm::compare(t.value<unit::second>(), 1000));
            QVERIFY(algorithm::compare(t.value<unit::minute>(), 16.666667));
            QVERIFY(algorithm::compare(t.value<unit::hour>(), 0.277778));
            QVERIFY(algorithm::compare(t.value<unit::day>(), 0.011574));
        }
        {
            unit::time t;
            t.set_value<unit::second>(100);
            QVERIFY(algorithm::compare(t.value<unit::second>(), 100));
            t.set_value<unit::minute>(100);
            QVERIFY(algorithm::compare(t.value<unit::second>(), 6000));
            t.set_value<unit::hour>(100);
            QVERIFY(algorithm::compare(t.value<unit::second>(), 360000));
            t.set_value<unit::day>(100);
            QVERIFY(algorithm::compare(t.value<unit::second>(), 8640000));
        }
        {
            QVERIFY(algorithm::compare((100_sec).value<unit::second>(), 100));
            QVERIFY(algorithm::compare((100_min).value<unit::second>(), 6000));
            QVERIFY(algorithm::compare((100_hour).value<unit::second>(), 360000));
            QVERIFY(algorithm::compare((100_day).value<unit::second>(), 8640000));
        }
    }

    {//temperature
        {
            unit::temperature t(1000);
            QVERIFY(algorithm::compare(t.value<unit::kelvin>(), 1273.15));
            QVERIFY(algorithm::compare(t.value<unit::celsius>(), 1000));
            QVERIFY(algorithm::compare(t.value<unit::fahrenheit>(), 1832));
            QVERIFY(algorithm::compare(t.value<unit::rankin>(), 2291.67));
        }
        {
            unit::temperature t;
            t.set_value<unit::kelvin>(100);
            QVERIFY(algorithm::compare(t.value<unit::celsius>(), -173.15));
            t.set_value<unit::celsius>(100);
            QVERIFY(algorithm::compare(t.value<unit::celsius>(), 100));
            t.set_value<unit::fahrenheit>(100);
            QVERIFY(algorithm::compare(t.value<unit::celsius>(), 37.777778));
            t.set_value<unit::rankin>(100);
            QVERIFY(algorithm::compare(t.value<unit::celsius>(), -217.594445));
        }
        {
            QVERIFY(algorithm::compare((100_K).value<unit::celsius>(), -173.15));
            QVERIFY(algorithm::compare((100_C).value<unit::celsius>(), 100));
            QVERIFY(algorithm::compare((100_F).value<unit::celsius>(), 37.777778));
            QVERIFY(algorithm::compare((100_Ra).value<unit::celsius>(), -217.594445));
        }
    }

    {//weight
        {
            unit::weight w(1000);
            QVERIFY(algorithm::compare(w.value<unit::gram>(), 1000000));
            QVERIFY(algorithm::compare(w.value<unit::kilogram>(), 1000));
            QVERIFY(algorithm::compare(w.value<unit::tonne>(), 1));
            QVERIFY(algorithm::compare(w.value<unit::hundredweight>(), 10));
            QVERIFY(algorithm::compare(w.value<unit::ounce_troy>(), 32150.743261));
            QVERIFY(algorithm::compare(w.value<unit::ounce>(), 35273.965838));
            QVERIFY(algorithm::compare(w.value<unit::pennyweight>(), 643014.865218));
            QVERIFY(algorithm::compare(w.value<unit::pounds>(), 2204.622476));
            QVERIFY(algorithm::compare(w.value<unit::pounds_troy>(), 2679.229036));
        }

        {
            unit::weight w;
            w.set_value<unit::gram>(100);
            QVERIFY(algorithm::compare(w.value<unit::kilogram>(), 0.1));
            w.set_value<unit::kilogram>(100);
            QVERIFY(algorithm::compare(w.value<unit::kilogram>(), 100));
            w.set_value<unit::tonne>(100);
            QVERIFY(algorithm::compare(w.value<unit::kilogram>(), 100000));
            w.set_value<unit::hundredweight>(100);
            QVERIFY(algorithm::compare(w.value<unit::kilogram>(), 10000));
            w.set_value<unit::ounce_troy>(100);
            QVERIFY(algorithm::compare(w.value<unit::kilogram>(), 3.110348));
            w.set_value<unit::ounce>(100);
            QVERIFY(algorithm::compare(w.value<unit::kilogram>(), 2.834952));
            w.set_value<unit::pennyweight>(100);
            QVERIFY(algorithm::compare(w.value<unit::kilogram>(), 0.1555174));
            w.set_value<unit::pounds>(100);
            QVERIFY(algorithm::compare(w.value<unit::kilogram>(), 45.35924));
            w.set_value<unit::pounds_troy>(100);
            QVERIFY(algorithm::compare(w.value<unit::kilogram>(), 37.32417));
        }

        {
            QVERIFY(algorithm::compare((100_g).value<unit::kilogram>(), 0.1));
            QVERIFY(algorithm::compare((100_kg).value<unit::kilogram>(), 100));
            QVERIFY(algorithm::compare((100_t).value<unit::kilogram>(), 100000));
            QVERIFY(algorithm::compare((100_cwt).value<unit::kilogram>(), 10000));
            QVERIFY(algorithm::compare((100_oz_t).value<unit::kilogram>(), 3.110348));
            QVERIFY(algorithm::compare((100_oz).value<unit::kilogram>(), 2.834952));
            QVERIFY(algorithm::compare((100_dwt).value<unit::kilogram>(), 0.1555174));
            QVERIFY(algorithm::compare((100_lb).value<unit::kilogram>(), 45.35924));
            QVERIFY(algorithm::compare((100_lb_t).value<unit::kilogram>(), 37.32417));
        }
    }

    {//speed
        {
            unit::speed s(1000);
            QVERIFY(algorithm::compare(s.value<unit::meter_secund>(), 1000));
            QVERIFY(algorithm::compare(s.value<unit::meter_minute>(), 60000));
            QVERIFY(algorithm::compare(s.value<unit::meter_hour>(), 3600000));
            QVERIFY(algorithm::compare(s.value<unit::kilometer_secund>(), 1));
            QVERIFY(algorithm::compare(s.value<unit::kilometer_minute>(), 60));
            QVERIFY(algorithm::compare(s.value<unit::kilometer_hour>(), 3600));
            QVERIFY(algorithm::compare(s.value<unit::foot_secund>(), 3280.839895));
            QVERIFY(algorithm::compare(s.value<unit::foot_minute>(), 196850.393701));
            QVERIFY(algorithm::compare(s.value<unit::foot_hour>(), 11811023.622047));
            QVERIFY(algorithm::compare(s.value<unit::mile_secund>(), 0.621371));
            QVERIFY(algorithm::compare(s.value<unit::mile_minute>(), 37.282272));
            QVERIFY(algorithm::compare(s.value<unit::mile_hour>(), 2236.936292));
            QVERIFY(algorithm::compare(s.value<unit::knots>(), 1943.844492));
        }

        {
            unit::speed s;
            s.set_value<unit::meter_secund>(100);
            QVERIFY(algorithm::compare(s.value<unit::meter_secund>(), 100));
            s.set_value<unit::meter_minute>(100);
            QVERIFY(algorithm::compare(s.value<unit::meter_secund>(), 1.666667));
            s.set_value<unit::meter_hour>(100);
            QVERIFY(algorithm::compare(s.value<unit::meter_secund>(), 0.027778));
            s.set_value<unit::kilometer_secund>(100);
            QVERIFY(algorithm::compare(s.value<unit::meter_secund>(), 100000));
            s.set_value<unit::kilometer_minute>(100);
            QVERIFY(algorithm::compare(s.value<unit::meter_secund>(), 1666.666667));
            s.set_value<unit::kilometer_hour>(100);
            QVERIFY(algorithm::compare(s.value<unit::meter_secund>(), 27.777778));
            s.set_value<unit::foot_secund>(100);
            QVERIFY(algorithm::compare(s.value<unit::meter_secund>(), 30.48));
            s.set_value<unit::foot_minute>(100);
            QVERIFY(algorithm::compare(s.value<unit::meter_secund>(), 0.508));
            s.set_value<unit::foot_hour>(100);
            QVERIFY(algorithm::compare(s.value<unit::meter_secund>(), 0.008467));
            s.set_value<unit::mile_secund>(100);
            QVERIFY(algorithm::compare(s.value<unit::meter_secund>(), 160934.4));
            s.set_value<unit::mile_minute>(100);
            QVERIFY(algorithm::compare(s.value<unit::meter_secund>(), 2682.24));
            s.set_value<unit::mile_hour>(100);
            QVERIFY(algorithm::compare(s.value<unit::meter_secund>(), 44.704));
            s.set_value<unit::knots>(100);
            QVERIFY(algorithm::compare(s.value<unit::meter_secund>(), 51.444444));
        }

        {
            QVERIFY(algorithm::compare((100_m_s).value<unit::meter_secund>(), 100));
            QVERIFY(algorithm::compare((100_m_m).value<unit::meter_secund>(), 1.666667));
            QVERIFY(algorithm::compare((100_m_h).value<unit::meter_secund>(), 0.027778));
            QVERIFY(algorithm::compare((100_km_s).value<unit::meter_secund>(), 100000));
            QVERIFY(algorithm::compare((100_km_m).value<unit::meter_secund>(), 1666.666667));
            QVERIFY(algorithm::compare((100_km_h).value<unit::meter_secund>(), 27.777778));
            QVERIFY(algorithm::compare((100_ft_s).value<unit::meter_secund>(), 30.48));
            QVERIFY(algorithm::compare((100_ft_m).value<unit::meter_secund>(), 0.508));
            QVERIFY(algorithm::compare((100_ft_h).value<unit::meter_secund>(), 0.008467));
            QVERIFY(algorithm::compare((100_mile_s).value<unit::meter_secund>(), 160934.4));
            QVERIFY(algorithm::compare((100_mile_m).value<unit::meter_secund>(), 2682.24));
            QVERIFY(algorithm::compare((100_mile_h).value<unit::meter_secund>(), 44.704));
            QVERIFY(algorithm::compare((100_kn).value<unit::meter_secund>(), 51.444444));
        }
    }
}

void Unit_Test::test_point()
{
    {
        Point point1;
        QVERIFY(algorithm::compare(point1.x(), 0.));
        QVERIFY(algorithm::compare(point1.y(), 0.));

        point1.set_x(100.);
        point1.set_y(100.);
        QVERIFY(algorithm::compare(point1.x(), 100.));
        QVERIFY(algorithm::compare(point1.y(), 100.));

        Point point2;
        point2.set_x(100.);
        point2.set_y(100.);
        QVERIFY(point1 == point2);
    }

    {
        Point3d point1;
        QVERIFY(algorithm::compare(point1.x(), 0.));
        QVERIFY(algorithm::compare(point1.y(), 0.));
        QVERIFY(algorithm::compare(point1.h(), 0.));

        point1.set_x(100.);
        point1.set_y(123.);
        point1.set_h(34.);
        QVERIFY(algorithm::compare(point1.x(), 100.));
        QVERIFY(algorithm::compare(point1.y(), 123.));
        QVERIFY(algorithm::compare(point1.h(), 34.));

        Point3d point2;
        point2.set_x(100.);
        point2.set_y(123.);
        point2.set_h(34.);
        QVERIFY(point1 == point2);
    }

    {
        Point4d point1;
        QVERIFY(algorithm::compare(point1.x(), 0.));
        QVERIFY(algorithm::compare(point1.y(), 0.));
        QVERIFY(algorithm::compare(point1.h(), 0.));
        QVERIFY(algorithm::compare(point1.time(), 0.));

        point1.set_x(100.);
        point1.set_y(123.);
        point1.set_h(34.);
        point1.set_time(74.);
        QVERIFY(algorithm::compare(point1.x(), 100.));
        QVERIFY(algorithm::compare(point1.y(), 123.));
        QVERIFY(algorithm::compare(point1.h(), 34.));
        QVERIFY(algorithm::compare(point1.time(), 74.));

        Point4d point2;
        point2.set_x(100.);
        point2.set_y(123.);
        point2.set_h(34.);
        point2.set_time(74.);
        QVERIFY(point1 == point2);
    }

    {
        {
            PointGeo point;
            QVERIFY(point.latitude_angle() == 0_deg);
            QVERIFY(point.longitude_angle() == 0_deg);

            point.set_latitude(56.7_deg);
            point.set_longitude(12.12_deg);
            QVERIFY(point.latitude_angle() == 56.7_deg);
            QVERIFY(point.longitude_angle() == 12.12_deg);

            PointGeo point1{10_deg, 10_deg};
            PointGeo point2{10_deg, 10_deg};
            QVERIFY(point1 == point2);
        }

        {
            PointGeo3d point;
            QVERIFY(point.latitude() == 0_deg);
            QVERIFY(point.longitude() == 0_deg);
            QVERIFY(algorithm::compare(point.altitude(), 0.));

            point.set_latitude(56.7_deg);
            point.set_longitude(12.12_deg);
            point.set_altitude(1232);
            QVERIFY(point.latitude() == 56.7_deg);
            QVERIFY(point.longitude() == 12.12_deg);
            QVERIFY(algorithm::compare(point.altitude(), 1232.));

            PointGeo3d point1{10_deg, 10_deg, 123.0};
            PointGeo3d point2{10_deg, 10_deg, 123.};
            QVERIFY(point1 == point2);
        }

        {
            PointGeo4d point;
            QVERIFY(point.latitude() == 0_deg);
            QVERIFY(point.longitude() == 0_deg);
            QVERIFY(algorithm::compare(point.altitude(), 0.));
            QVERIFY(algorithm::compare(point.time(), 0.));

            point.set_latitude(56.7_deg);
            point.set_longitude(12.12_deg);
            point.set_altitude(1232);
            point.set_time(3533);
            QVERIFY(point.latitude() == 56.7_deg);
            QVERIFY(point.longitude() == 12.12_deg);
            QVERIFY(algorithm::compare(point.altitude(), 1232.));
            QVERIFY(algorithm::compare(point.time(), 3533.));

            PointGeo4d point1{10_deg, 10_deg, 123, 56};
            PointGeo4d point2{10_deg, 10_deg, 123, 56};
            QVERIFY(point1 == point2);
        }

        {
            Polar2d point;
            QVERIFY(algorithm::compare(point.psi(), 0.));
            QVERIFY(point.angle_fi() == 0_deg);

            point.set_psi(123);
            point.set_fi(3_deg);
            QVERIFY(algorithm::compare(point.psi(), 123.));
            QVERIFY(point.angle_fi() == 3_deg);
        }

        {
            Polar3d point;
            QVERIFY(algorithm::compare(point.psi(), 0.));
            QVERIFY(point.fi() == 0_deg);
            QVERIFY(point.z() == 0.);

            point.set_psi(123);
            point.set_fi(3_deg);
            point.set_z(21);
            QVERIFY(algorithm::compare(point.psi(), 123.));
            QVERIFY(point.fi() == 3_deg);
            QVERIFY(point.z() == 21.);
        }
    }
}

void Unit_Test::test_point_algorithm()
{
    {
        Point point1{0,0};
        Point point2{5,5};
        auto angle = Angle(point_algo::angle(point1, point2));
        QVERIFY(angle == 45_deg);
    }

    {
        Point point1{5,5};
        Point point2{10,10};
        auto value = point_algo::distance(point1, point2);
        QVERIFY(algorithm::compare(value, 5 * std::sqrt(2)));
    }

    {//new_point
        {
            Point point1{10,10};
            auto value = point_algo::new_point(point1, (90._deg).radian(), 10.);
            QVERIFY(algorithm::compare(value.x(), 20.));
            QVERIFY(algorithm::compare(value.y(), 10.));
        }
        {
            Point point1{10,10};
            auto value = point_algo::new_point(point1, (0._deg).radian(), 10.);
            QVERIFY(algorithm::compare(value.x(), 10.));
            QVERIFY(algorithm::compare(value.y(), 20.));
        }
        {
            Point point1{10,10};
            auto value = point_algo::new_point(point1, (180._deg).radian(), 10.);
            QVERIFY(algorithm::compare(value.x(), 10.));
            QVERIFY(algorithm::compare(value.y(), 0.));
        }
        {
            Point point1{10,10};
            auto value = point_algo::new_point(point1, (270._deg).radian(), 10.);
            QVERIFY(algorithm::compare(value.x(), 0.));
            QVERIFY(algorithm::compare(value.y(), 10.));
        }
    }

    {
        Point point1{10,10};
        auto value = point_algo::rotate(point1, (90._deg).radian(), Point{5,5});
        QVERIFY(algorithm::compare(value.x(), 10.));
        QVERIFY(algorithm::compare(value.y(), 0.));
    }

    {
        auto value = point_algo::midplane(Point{10,10}, Point{5,5});
        QVERIFY(algorithm::compare(value.x(), 7.5));
        QVERIFY(algorithm::compare(value.y(), 7.5));
    }

    {
        auto value = point_algo::convert_polar<Polar2d>(Point{10,10}, Point{5,5});
        QVERIFY(algorithm::compare(value.psi(), 5 * std::sqrt(2)));
        QVERIFY(value.angle_fi() == 225_deg);
    }
}

void Unit_Test::test_line()
{
    {
        {
            auto line = Line({1.,0.}, {5.,3.});
            QVERIFY(line.a() == -3);
            QVERIFY(line.b() == 4);
            QVERIFY(line.c() == 3);
        }

        {
            auto line1 = Line({0.,0.}, {0.,10.});
            auto line2 = Line({0.,2.}, {5.,2.});
            QVERIFY(line1 != line2);
        }

        {
            auto line1 = Line({0.,2.}, {5.,2.});
            auto line2 = Line({0.,2.}, {5.,2.});
            QVERIFY(line1 == line2);
        }

        {
            Line line1 = {1,1,1};
            Line line2 = {2,2,2};
            QVERIFY(line1 == line2);
        }
    }

    {
        {
            auto half_line = HalfLine({3.,2.}, 50_deg);
            auto [a,b,c] = line_algo::equation_line_quick(half_line.start(), half_line.direction());
            QVERIFY(algorithm::compare(a, -0.642788));
            QVERIFY(algorithm::compare(b, 0.7660444));
            QVERIFY(algorithm::compare(c, 0.3962739));
        }

        {
            auto half_line1 = HalfLine({3.,2.}, 50_deg);
            auto half_line2 = HalfLine({3.,2.}, 50_deg);
            QVERIFY(half_line1 == half_line2);
        }

        {
            auto half_line1 = HalfLine({3.,2.}, 50_deg);
            auto half_line2 = HalfLine({3.,20.}, 50_deg);
            QVERIFY(half_line1 != half_line2);
        }
    }

    {
        {
            auto line_section = LineSection({0.,2.}, {1.,2.});
            auto [a,b,c] = line_algo::equation_line_quick(line_section.start(), line_section.stop());
            QVERIFY(algorithm::compare(a, 0.));
            QVERIFY(algorithm::compare(b, 1.));
            QVERIFY(algorithm::compare(c, -2.));
        }

        {
            auto line_section1 = LineSection({0.,2.}, {1.,2.});
            auto line_section2 = LineSection({0.,2.}, {1.,2.});
            QVERIFY(line_section1 == line_section2);
        }

        {
            auto line_section1 = LineSection({0.,2.}, {1.,2.});
            auto line_section2 = LineSection({1.,2.}, {2.,2.});
            QVERIFY(line_section1 != line_section2);
        }
    }
}

void Unit_Test::test_line_algorithm()
{
    {//equation_line_quick, distance_to_line
        auto line = Line({0.,0.}, {0.,10.});
        auto dist = line_algo::distance_to_line(view_line(line), Point{5,5});
        QVERIFY(algorithm::compare(dist, -5.));

        line = Line({0.,0.}, {0.,10.});
        dist = line_algo::distance_to_line(view_line(line), Point{-5,-5});
        QVERIFY(algorithm::compare(dist, 5.));
    }

    {//value_function
        {
            auto line = Line({0.,0.}, {5.,5.});
            auto value = line_algo::value_function(view_line(line), Point{5,5});
            QVERIFY(algorithm::compare(value, 0.));
        }

        {
            auto line = Line({1.,0.}, {5.,3.});
            auto value = line_algo::value_function(view_line(line), Point{5,5});
            QVERIFY(!algorithm::compare(value, 0.));
        }
    }

    {//intersection_line(3)
        {
            auto line1 = Line({0.,0.}, {0.,10.});
            auto line2 = Line({0.,2.}, {5.,2.});

            auto value = line_algo::intersection_line(view_line(line1), view_line(line2));
            auto point = Point(0,2);
            QVERIFY(value.has_value() && (value.value() == point));
        }

        {
            auto line1 = Line({0.,2.}, {10.,2.});
            auto line2 = Line({0.,5.}, {10.,5.});

            auto value = line_algo::intersection_line(view_line(line1), view_line(line2));
            QVERIFY(!value.has_value());
        }

        {
            auto half_line1 = HalfLine({3.,2.}, 50_deg);
            auto half_line2 = HalfLine({3.,2.}, 50_deg);

            auto value = line_algo::intersection_line(view_line(half_line1), view_line(half_line2));
            QVERIFY(!value.has_value());
        }

        {
            auto half_line1 = HalfLine({0,2}, 90_deg);
            auto half_line2 = HalfLine({2.,0}, 0_deg);

            auto value = line_algo::intersection_line(view_line(half_line1), view_line(half_line2));
            auto point = Point(2, 2);
            QVERIFY(value == point);
        }

        {
            auto line1 = LineSection({1,2}, {5, 2});
            auto line2 = LineSection({2.,0}, {2.,10});
            QVERIFY(line_algo::intersection_line(view_line(line1), view_line(line2)).has_value());
        }
    }

    {//check_point_on_line(3)
        {
            auto line = Line({0.,0.}, {0.,10.});
            QVERIFY(line_algo::check_point_on_line(view_line(line), Point{0.,0.}));
            QVERIFY(line_algo::check_point_on_line(view_line(line), Point{0.,10.}));
            QVERIFY(line_algo::check_point_on_line(view_line(line), Point{0.,5.}));
            QVERIFY(line_algo::check_point_on_line(view_line(line), Point{0.,-5.}));
        }
        {
            auto line = HalfLine({0.,0.}, 45_deg);
            QVERIFY(line_algo::check_point_on_line(view_line(line), Point{0.,0.}));
            QVERIFY(line_algo::check_point_on_line(view_line(line), Point{10.,10.}));
            QVERIFY(!line_algo::check_point_on_line(view_line(line), Point{0.,5.}));
            QVERIFY(!line_algo::check_point_on_line(view_line(line), Point{-1.,-1.}));
        }
        {
            auto line = LineSection({0.,0.}, {10.,10.});
            QVERIFY(line_algo::check_point_on_line(view_line(line), Point{0.,0.}));
            QVERIFY(line_algo::check_point_on_line(view_line(line), Point{10.,10.}));
            QVERIFY(!line_algo::check_point_on_line(view_line(line), Point{0.,5.}));
            QVERIFY(!line_algo::check_point_on_line(view_line(line), Point{-1.,-1.}));
            QVERIFY(!line_algo::check_point_on_line(view_line(line), Point{11.,11.}));
        }
        {
            auto line = LineSection({0,0}, {0,10});
            QVERIFY(line_algo::check_point_on_line(view_line(line), Point{0,1}));
        }
    }

    {//parallel_line
        {
            auto line = Line({0.,0.}, {0.,10.});
            {
                auto pl = line_algo::parallel_line(view_line(line), 10.);
                QVERIFY(Line(pl.view_begin.value, pl.view_end.value) == Line(-10, 0, 100));
            }
            {
                auto pl = line_algo::parallel_line(view_line(line), -10.);
                QVERIFY(Line(pl.view_begin.value, pl.view_end.value) == Line(-10, 0, -100));
            }
        }
    }

    {//point_perpendicular
        {
            auto line = Line({1.,2.}, {5.,2.});
            auto point = line_algo::point_perpendicular(view_line(line), Point{0.,0.});
            QVERIFY(point == Point(0.,2.));
        }

        {
            auto line = Line({1.,2.}, {5.,2.});
            auto point = line_algo::point_perpendicular(view_line(line), Point{10.,10.});
            QVERIFY(point == Point(10.,2.));
        }
    }

    {//point_on_line
        {
            auto line = LineSection({1.,2.}, {5.,2.});
            auto point = line_algo::point_on_line(view_line(line), 10.);
            QVERIFY(!point.has_value());
        }

        {
            auto line = LineSection({1.,2.}, {5.,2.});
            auto point = line_algo::point_on_line(view_line(line), 2.);
            QVERIFY(point.has_value() && (point.value() == Point(3.,2.)));
        }
    }
}

void Unit_Test::test_circle()
{
    {
        auto arc = Arc({1.,1.}, 5., 0_deg, 90_deg);
        QVERIFY((arc.center() == Point(1.,1.))&& algorithm::compare(arc.radius(), 5.)
                && (arc.start_angle() == 0_deg) && (arc.stop_angle() == 90_deg));
    }
    {
        auto circle = Circle({1.,1.}, 5.);
        QVERIFY((circle.center() == Point(1.,1.)) && algorithm::compare(circle.radius(), 5.));
    }
}

void Unit_Test::test_circle_algorithm()
{
    {//length_arc
        {
            auto arc = Arc({1.,1.}, 5., 0_deg, 90_deg);
            QVERIFY(algorithm::compare(circle_algo::length_arc(arc), 7.853982));
        }
        {
            auto arc = Arc({1.,1.}, 5., 90_deg, 0_deg);
            QVERIFY(algorithm::compare(circle_algo::length_arc(arc), 23.561945));
        }
    }
    {//point_on_arc
        {
            auto arc = Arc({1.,1.}, 5., 0_deg, 90_deg);
            auto value = circle_algo::point_on_arc(arc, 10.);
            QVERIFY(!value.has_value());
        }
        {
            auto arc = Arc({1.,1.}, 5., 0_deg, 90_deg);
            auto value = circle_algo::point_on_arc(arc, 5.);
            QVERIFY(value.has_value() && (value.value() == Point(5.207355, 3.701512)));
        }
    }
    {//midplane
        {
            auto arc = Arc({1.,1.}, 5., 0_deg, 90_deg);
            auto value = circle_algo::midplane(arc);
            QVERIFY(value == Point(4.535534, 4.535534));
        }
        {
            auto arc = Arc({1.,1.}, 5., 90_deg, 0_deg);
            auto value = circle_algo::midplane(arc);
            QVERIFY(value == Point(4.535534, -2.535534));
        }
    }

    {//point_appertain_circle
        {
            auto circle = Circle({1.,1.}, 10.);
            QVERIFY(circle_algo::point_appertain_circle(circle, Point{0., 0.}));
        }
        {
            auto circle = Circle({1.,1.}, 10.);
            QVERIFY(!circle_algo::point_appertain_circle(circle, Point{100., 100.}));
        }
    }

    {//line_to_circle
        {
            auto circle = Circle({0.,5.}, 5.);
            auto line = Line({0.,5.}, {5.,5.});
            auto value = circle_algo::line_to_circle(circle, view_line(line));
            QVERIFY(value.first.has_value() && value.second.has_value() &&
                    (value.first == Point(-5,5)) && (value.second == Point(5,5)));
        }

        {
            auto circle = Circle({0.,5.}, 5.);
            auto line = Line({0.,10.}, {5.,10.});
            auto value = circle_algo::line_to_circle(circle, view_line(line));
            QVERIFY(value.first.has_value() && !value.second.has_value() &&
                    (value.first == Point(0,10)));
        }

        {
            auto circle = Circle({0.,5.}, 5.);
            auto line = Line({0.,15.}, {5.,15.});
            auto value = circle_algo::line_to_circle(circle, view_line(line));
            QVERIFY(!value.first.has_value() && !value.second.has_value());
        }
    }

    {//section_to_circle
        {
            auto circle = Circle({0.,5.}, 5.);
            auto line = LineSection({1.,5.}, {4.,5.});
            auto value = circle_algo::line_to_circle(circle, view_line(line));
            QVERIFY(!value.first.has_value() && !value.second.has_value());
        }
        {
            auto circle = Circle({0.,5.}, 5.);
            auto line = LineSection({0.,5.}, {5.,5.});
            auto value = circle_algo::line_to_circle(circle, view_line(line));
            QVERIFY(value.first.has_value() && !value.second.has_value()
                    && (value.first == Point(5,5)));
        }
        {
            auto circle = Circle({0.,5.}, 5.);
            auto line = LineSection({-5.,5.}, {5.,5.});
            auto value = circle_algo::line_to_circle(circle, view_line(line));
            QVERIFY(value.first.has_value() && value.second.has_value()
                    && (value.first == Point(-5,5)) && (value.second == Point(5,5)));
        }
    }

    {//circle_to_circle
        {
            auto circle1 = Circle({0.,5.}, 5.);
            auto circle2 = Circle({5.,5.}, 5.);
            auto value = circle_algo::circle_to_circle(circle1, circle2);
            QVERIFY(value.first.has_value() && value.second.has_value()
                    && (value.first == Point(2.5,4.566987)) && (value.second == Point(2.5,5.433013)));
        }
        {
            auto circle1 = Circle({0.,5.}, 5.);
            auto circle2 = Circle({10.,5.}, 5.);
            auto value = circle_algo::circle_to_circle(circle1, circle2);
            QVERIFY(value.first.has_value() && !value.second.has_value()
                    && (value.first == Point(5, 5)));
        }

        {
            auto circle1 = Circle({0.,5.}, 5.);
            auto circle2 = Circle({15.,5.}, 5.);
            auto value = circle_algo::circle_to_circle(circle1, circle2);
            QVERIFY(!value.first.has_value() && !value.second.has_value());
        }

        {
            auto circle1 = Circle({0.,5.}, 5.);
            auto circle2 = Circle({0.,5.}, 5.);
            auto value = circle_algo::circle_to_circle(circle1, circle2);
            QVERIFY(!value.first.has_value() && !value.second.has_value());
        }
    }

    {//scaling_tangent_out
        {
            auto circle1 = Circle({0.,5.}, 5.);
            auto circle2 = Circle({5.,5.}, 5.);
            {
                auto line = circle_algo::scaling_tangent_out(circle1, circle2, algorithm::direct::RIGHT);
                QVERIFY(line.has_value() && (line->view_begin.value == Point(0, 10)) && (line->view_end.value == Point(5, 10)));
            }
            {
                auto line = circle_algo::scaling_tangent_out(circle1, circle2, algorithm::direct::LEFT);
                QVERIFY(line.has_value() && (line->view_begin.value == Point(0, 0)) && (line->view_end.value == Point(5, 0)));
            }
        }

        {
            auto circle1 = Circle({0.,5.}, 5.);
            auto circle2 = Circle({0.,5.}, 5.);
            {
                auto line = circle_algo::scaling_tangent_out(circle1, circle2, algorithm::direct::RIGHT);
                QVERIFY(!line.has_value());
            }
            {
                auto line = circle_algo::scaling_tangent_out(circle1, circle2, algorithm::direct::LEFT);
                QVERIFY(!line.has_value());
            }
        }

        {
            auto circle1 = Circle({0.,5.}, 5.);
            auto circle2 = Circle({10.,5.}, 50.);
            {
                auto line = circle_algo::scaling_tangent_out(circle1, circle2, algorithm::direct::RIGHT);
                QVERIFY(!line.has_value());
            }
            {
                auto line = circle_algo::scaling_tangent_out(circle1, circle2, algorithm::direct::LEFT);
                QVERIFY(!line.has_value());
            }
        }

        {
            auto circle1 = Circle({0.,5.}, 5.);
            auto circle2 = Circle({10.,5.}, 8.);
            {
                auto line = circle_algo::scaling_tangent_out(circle1, circle2, algorithm::direct::RIGHT);
                QVERIFY(line.has_value() && (line->view_begin.value == Point(-1.5, 0.230304)) && (line->view_end.value == Point(7.6, -2.631514)));
            }
            {
                auto line = circle_algo::scaling_tangent_out(circle1, circle2, algorithm::direct::LEFT);
                QVERIFY(line.has_value() && (line->view_begin.value == Point(-1.5, 9.769696)) && (line->view_end.value == Point(7.6, 12.631514)));
            }
        }
    }

    {//scaling_tangent_inboard
        {
            auto circle1 = Circle({0.,5.}, 5.);
            auto circle2 = Circle({5.,5.}, 5.);
            {
                auto line = circle_algo::scaling_tangent_inboard(circle1, circle2, algorithm::direct::RIGHT);
                QVERIFY(!line.has_value());
            }
            {
                auto line = circle_algo::scaling_tangent_inboard(circle1, circle2, algorithm::direct::LEFT);
                QVERIFY(!line.has_value());
            }
        }
        {
            auto circle1 = Circle({0.,5.}, 5.);
            auto circle2 = Circle({0.,5.}, 5.);
            {
                auto line = circle_algo::scaling_tangent_inboard(circle1, circle2, algorithm::direct::RIGHT);
                QVERIFY(!line.has_value());
            }
            {
                auto line = circle_algo::scaling_tangent_inboard(circle1, circle2, algorithm::direct::LEFT);
                QVERIFY(!line.has_value());
            }
        }
        {
            auto circle1 = Circle({0.,5.}, 5.);
            auto circle2 = Circle({10.,5.}, 50.);
            {
                auto line = circle_algo::scaling_tangent_inboard(circle1, circle2, algorithm::direct::RIGHT);
                QVERIFY(!line.has_value());
            }
            {
                auto line = circle_algo::scaling_tangent_inboard(circle1, circle2, algorithm::direct::LEFT);
                QVERIFY(!line.has_value());
            }
        }
        {
            auto circle1 = Circle({0.,5.}, 5.);
            auto circle2 = Circle({10.,5.}, 8.);
            {
                auto line = circle_algo::scaling_tangent_inboard(circle1, circle2, algorithm::direct::RIGHT);
                QVERIFY(!line.has_value());
            }
            {
                auto line = circle_algo::scaling_tangent_inboard(circle1, circle2, algorithm::direct::LEFT);
                QVERIFY(!line.has_value());
            }
        }
        {
            auto circle1 = Circle({0.,5.}, 5.);
            auto circle2 = Circle({20.,5.}, 5.);
            {
                auto line = circle_algo::scaling_tangent_inboard(circle1, circle2, algorithm::direct::RIGHT);
                QVERIFY(line.has_value() && (line->view_begin.value == Point(2.5, 9.330127)) && (line->view_end.value == Point(17.5, 0.669873)));

            }
            {
                auto line = circle_algo::scaling_tangent_inboard(circle1, circle2, algorithm::direct::LEFT);
                QVERIFY(line.has_value() && (line->view_begin.value == Point(2.5,  0.669873)) && (line->view_end.value == Point(17.5,  9.330127)));
            }
        }

        {
            auto circle1 = Circle({0.,5.}, 5.);
            auto circle2 = Circle({100.,5.}, 50.);
            {
                auto line = circle_algo::scaling_tangent_inboard(circle1, circle2, algorithm::direct::RIGHT);
                QVERIFY(line.has_value() && (line->view_begin.value == Point(2.75, 9.175823)) && (line->view_end.value == Point(72.5, -36.758233)));
            }
            {
                auto line = circle_algo::scaling_tangent_inboard(circle1, circle2, algorithm::direct::LEFT);
                QVERIFY(line.has_value() && (line->view_begin.value == Point(2.75, 0.824177)) && (line->view_end.value == Point(72.5,  46.758233)));
            }
        }
    }

    {
        {
            auto circle = Circle({0.,0.}, 5.);
            auto point = Point(10., 0.);
            auto line = circle_algo::tangent(circle, point);
            QVERIFY(line.has_value());
            auto line1 = line.value().first;
            QVERIFY((line1.view_begin.value == Point(2.5, -4.330127)) && (line1.view_end.value == Point(10, 0)));
            auto line2 = line.value().second;
            QVERIFY((line2.view_begin.value == Point(2.5, 4.330127)) && (line2.view_end.value == Point(10, 0)));
        }

        {
            auto circle = Circle({0.,0.}, 5.);
            auto point = Point(1., 0.);
            auto line = circle_algo::tangent(circle, point);
            QVERIFY(!line.has_value());
        }

        {
            auto circle = Circle({5.,5.}, 5.);
            auto point = Point(30., 45.);
            auto line = circle_algo::tangent(circle, point);

            QVERIFY(line.has_value());
            auto line1 = line.value().first;
            QVERIFY((line1.view_begin.value == Point(9.497003, 2.814373)) && (line1.view_end.value == Point(30, 45)));
            auto line2 = line.value().second;
            QVERIFY((line2.view_begin.value == Point(1.064795, 8.084503)) && (line2.view_end.value == Point(30, 45)));
        }
    }

    {//center_circle_in_line
        {
            auto line = LineSection({0,0}, {0, 5});
            auto point = Point(0,5);
            auto temp = circle_algo::center_circle_in_line(view_line(line), point, 10.);
            QVERIFY((temp.first == Point(-10, 5)) && (temp.second == Point(10, 5)));
        }
        {
            auto line = LineSection({0,0}, {0, 5});
            auto point = Point(0,0);
            auto temp = circle_algo::center_circle_in_line(view_line(line), point, 10.);
            QVERIFY((temp.first == Point(-10, 0)) && (temp.second == Point(10, 0)));
        }
        {
            auto line = LineSection({0,0}, {5, 5});
            auto point = Point(5,5);
            auto temp = circle_algo::center_circle_in_line(view_line(line), point, 10.);
            QVERIFY((temp.first == Point(-2.071068, 12.071068)) && (temp.second == Point(12.071068, -2.071068)));
        }
    }
}

void Unit_Test::test_polygon()
{
    {//ConvexPolygon
        {
            auto polygon = ConvexPolygon({Point(0,0), Point(5,5), Point(5,0)});
            auto points = polygon.get_points();
            QVERIFY(points[0] == Point(0,0));
            QVERIFY(points[1] == Point(5,5));
            QVERIFY(points[2] == Point(5,0));
        }
        {
            try{
                auto polygon = ConvexPolygon({Point(0,1), Point(25,5), Point(-5,0), Point(4,3)});
                QVERIFY(false);
            }
            catch (const std::logic_error &e){
                QVERIFY(true);
            }
        }
        {
            auto polygon = ConvexPolygon({Point(0,10), Point(10,10), Point(10,0), Point(0,0)});
            auto points = polygon.get_points();
            QVERIFY(points[0] == Point(0,10));
            QVERIFY(points[1] == Point(10,10));
            QVERIFY(points[2] == Point(10,0));
            QVERIFY(points[3] == Point(0,0));
        }
    }
    {//create_rectangle
        {
            auto polygon = Rectangle(Point(0,0), 10, 5);
            auto points = polygon.get_points();
            QVERIFY(points[0] == Point(0,0));
            QVERIFY(points[1] == Point(10,0));
            QVERIFY(points[2] == Point(10,-5));
            QVERIFY(points[3] == Point(0,-5));
        }
    }

    {//create_square
        {
            auto polygon = Square(Point(0,0), 10);
            auto points = polygon.get_points();
            QVERIFY(points[0] == Point(0,0));
            QVERIFY(points[1] == Point(10,0));
            QVERIFY(points[2] == Point(10,-10));
            QVERIFY(points[3] == Point(0,-10));
        }
    }

    {//create_triangle
        {
            auto polygon = Triangle({Point(0,0), Point(10,0), Point(10,10)});
            auto points = polygon.get_points();
            QVERIFY(points[0] == Point(0,0));
            QVERIFY(points[1] == Point(10,0));
            QVERIFY(points[2] == Point(10,-10));
        }

        {
            try{
                Triangle({Point(0,0), Point(10,0), Point(20,0)});
                QVERIFY(false);
            }
            catch (const std::logic_error &e){
                QVERIFY(true);
            }
        }
    }

    {//create_regular_polygon
        {
            auto polygon = RegularPolygon(Point(0,0), 10, 3);
            auto points = polygon.get_points();
            QVERIFY(points[0] == Point(0, 5.773503));
            QVERIFY(points[1] == Point(5, -2.886751));
            QVERIFY(points[2] == Point(-5,-2.886751));
        }
        {
            auto polygon = RegularPolygon(Point(0,0), 10, 4);
            auto points = polygon.get_points();
            QVERIFY(points[0] == Point(0, 7.071068));
            QVERIFY(points[1] == Point(7.071068, 0));
            QVERIFY(points[2] == Point(0, -7.071068));
            QVERIFY(points[3] == Point(-7.071068, 0));
        }
        {
            auto polygon = RegularPolygon(Point(0,0), 5, 5);
            auto points = polygon.get_points();
            QVERIFY(points[0] == Point(0, 4.253254));
            QVERIFY(points[1] == Point(4.045085, 1.314328));
            QVERIFY(points[2] == Point(2.5, -3.440955));
            QVERIFY(points[3] == Point(-2.5, -3.440955));
            QVERIFY(points[4] == Point(-4.045085, 1.314328));
        }
    }
}

void Unit_Test::test_polygon_algorithm()
{
    {//get_lines
        auto polygon = ConvexPolygon({Point(0,10), Point(10,10), Point(10,0), Point(0,0)});
        auto lines = polygon_algo::get_lines(polygon);
        std::vector<LineSection> temp{{Point(0,10), Point(10,10)}, {Point(10,10), Point(10,0)},
                                      {Point(10,0), Point(0,0)}, {Point(0,0), Point(0,10)}};
        QVERIFY(lines.size() == polygon.get_points().size());
        for(size_t i = 0; i < lines.size(); ++i){
            QVERIFY(LineSection(lines[i].view_begin.value, lines[i].view_end.value) == temp[i]);
        }
    }
    {//point_appertain_polygon
        auto polygon = ConvexPolygon({Point(0,0), Point(0,10), Point(5,15), Point(10,10), Point(10,0)});
        QVERIFY(polygon_algo::point_appertain_polygon(polygon, Point(1,1)));
        QVERIFY(!polygon_algo::point_appertain_polygon(polygon, Point(-1,-1)));
        QVERIFY(polygon_algo::point_appertain_polygon(polygon, Point(0,5)));
        QVERIFY(!polygon_algo::point_appertain_polygon(polygon, Point(15,15)));
        QVERIFY(polygon_algo::point_appertain_polygon(polygon, Point(5,15)));
    }
    {//point_appertain_polygon
        {
            auto polygon1 = ConvexPolygon({Point(0,0), Point(0,10), Point(10,10), Point(10,0)});
            auto polygon2 = ConvexPolygon({Point(0,0), Point(0,10), Point(5,15), Point(10,10), Point(10,0)});
            QVERIFY(polygon_algo::polygon_intersect_polygon(polygon1, polygon2));
        }
        {
            auto polygon1 = ConvexPolygon({Point(0,10), Point(0,20), Point(10,20), Point(10,20)});
            auto polygon2 = ConvexPolygon({Point(0,0), Point(0,10), Point(5,15), Point(10,10), Point(10,0)});
            QVERIFY(polygon_algo::polygon_intersect_polygon(polygon1, polygon2));
        }
        {
            auto polygon1 = ConvexPolygon({Point(0,14), Point(0,30), Point(10,30), Point(10,14)});
            auto polygon2 = ConvexPolygon({Point(0,0), Point(0,10), Point(5,15), Point(10,10), Point(10,0)});
            QVERIFY(polygon_algo::polygon_intersect_polygon(polygon1, polygon2));
        }
        {
            auto polygon1 = ConvexPolygon({Point(0,0), Point(0,5), Point(5,5), Point(5,0)});
            auto polygon2 = ConvexPolygon({Point(10,0), Point(10,10), Point(20,20), Point(20,10)});
            QVERIFY(!polygon_algo::polygon_intersect_polygon(polygon1, polygon2));
        }
    }

    {//polygon_appertain_section
        {
            auto polygon = ConvexPolygon({Point(0,0), Point(0,10), Point(10,10), Point(10,0)});
            auto line = LineSection(Point(0,0), Point(1,1));
            QVERIFY(polygon_algo::polygon_appertain_section(polygon, view_line(line)));
        }
        {
            auto polygon = ConvexPolygon({Point(0,0), Point(0,10), Point(10,10), Point(10,0)});
            auto line = LineSection(Point(-1,-1), Point(1,1));
            QVERIFY(!polygon_algo::polygon_appertain_section(polygon, view_line(line)));
        }
        {
            auto polygon = ConvexPolygon({Point(0,0), Point(0,10), Point(10,10), Point(10,0)});
            auto line = LineSection(Point(-2,-2), Point(-1,-1));
            QVERIFY(!polygon_algo::polygon_appertain_section(polygon, view_line(line)));
        }
    }

    {//point_coupling
        {
            auto polygon1 = ConvexPolygon({Point(0.,0.), Point(0.,10.), Point(10.,10.), Point(10.,0.)});
            auto point = polygon_algo::point_coupling(polygon1, Point(-1.,1.));
            QVERIFY(point == Point(0,1));
        }
        {
            auto polygon1 = ConvexPolygon({Point(0,0), Point(0,10), Point(10,10), Point(10,0)});
            auto point = polygon_algo::point_coupling(polygon1, Point(-1,-1));
            QVERIFY(point == Point(0,0));
        }
        {
            auto polygon1 = ConvexPolygon({Point(0,0), Point(0,10), Point(10,10), Point(10,0)});
            auto point = polygon_algo::point_coupling(polygon1, Point(5,50));
            QVERIFY(point == Point(5,10));
        }
        {
            auto polygon1 = ConvexPolygon({Point(0,0), Point(0,10), Point(10,10), Point(10,0)});
            auto point = polygon_algo::point_coupling(polygon1, Point(4,3));
            QVERIFY(point == Point(4,0));
        }
    }

    {//point_coupling
        {
            auto polygon1 = polygon_algo::create_convex_polygone({Point(0,0), Point(0,10), Point(10,10), Point(10,0)});
            auto point = polygon_algo::get_centre(polygon1);
            QVERIFY(point == Point(5,5));
        }
        {
            auto polygon1 = polygon_algo::create_convex_polygone({Point(0,0), Point(0,10), Point(10,10)});
            auto point = polygon_algo::get_centre(polygon1);
            QVERIFY(point == Point(3.333333,6.666667));
        }
        {
            auto polygon = polygon_algo::create_regular_polygon(Point(0,0), 5., 7.);
            auto point = polygon_algo::get_centre(polygon);
            QVERIFY(point == Point(0,0));
        }
    }

    {//scale_regular_polygon
        {
            auto polygon = RegularPolygon(Point(0,0), 5, 4);
            auto temp = polygon_algo::scale_regular_polygon(polygon, 1.);

            auto points = temp.get_points();
            QVERIFY(points[0] == Point(0, 4.949747));
            QVERIFY(points[1] == Point(4.949747, 0));
            QVERIFY(points[2] == Point(0, -4.949747));
            QVERIFY(points[3] == Point(-4.949747, 0));
        }
        {
            auto polygon = RegularPolygon(Point(0,0), 5, 5);
            auto temp = polygon_algo::scale_regular_polygon(polygon, 2.);
            auto points = temp.get_points();
            QVERIFY(points[0] == Point(0, 7.227238));
            QVERIFY(points[1] == Point(6.873512, 2.233340));
            QVERIFY(points[2] == Point(4.248064, -5.846959));
            QVERIFY(points[3] == Point(-4.248064, -5.846959));
            QVERIFY(points[4] == Point(-6.873512, 2.233339));
        }
    }

    {//polygon_apertain_line
        {
            auto polygon = ConvexPolygon({Point(0,0), Point(0,10), Point(10,10), Point(10,0)});
            auto line = Line(Point(-5,0), Point(11,11));
            auto temp = polygon_algo::polygon_apertain_line(polygon, view_line(line));
            QVERIFY(temp[0] == Point(0, 3.4375));
            QVERIFY(temp[1] == Point(9.545455, 10));
        }
        {
            auto polygon = ConvexPolygon({Point(0,0), Point(0,10), Point(10,10), Point(10,0)});
            auto line = Line(Point(0,15), Point(50,100));
            auto temp = polygon_algo::polygon_apertain_line(polygon, view_line(line));
            QVERIFY(temp.empty());
        }
    }

    {//polygon_appertain_polygon
        {
            auto polygon1 = ConvexPolygon({Point(0,0), Point(0,10), Point(10,10), Point(10,0)});
            auto polygon2 = ConvexPolygon({Point(1,1), Point(1,9), Point(9,9), Point(9,1)});
            QVERIFY(polygon_algo::polygon_appertain_polygon(polygon1, polygon2));
        }

        {
            auto polygon1 = ConvexPolygon({Point(0,0), Point(0,10), Point(10,10), Point(10,0)});
            auto polygon2 = ConvexPolygon({Point(0,0), Point(0,11), Point(11,11), Point(11,0)});
            QVERIFY(!polygon_algo::polygon_appertain_polygon(polygon1, polygon2));
        }

        {
            auto polygon1 = ConvexPolygon({Point(0,0), Point(0,10), Point(10,10), Point(10,0)});
            auto polygon2 = ConvexPolygon({Point(0,0), Point(0,9), Point(9,9), Point(9,0)});
            QVERIFY(!polygon_algo::polygon_appertain_polygon(polygon1, polygon2));
        }
    }

    {//rotation
        {

            auto polygon1 = RegularPolygon(Point(0,0), 10 * sqrt(2), 4);
            auto temp = polygon_algo::rotation(polygon1, algorithm::pi_on_2<double>);
            auto polygon2 = polygon_algo::create_regular_polygon(Point(0,0), 10 * sqrt(2), 4, algorithm::pi_on_2<double>);
            auto points = temp.get_points(algorithm::pi_on_2<double>);

            QVERIFY(points[0] == polygon2[0]);
            QVERIFY(points[1] == polygon2[1]);
            QVERIFY(points[2] == polygon2[2]);
            QVERIFY(points[3] == polygon2[3]);
        }

        // {
        //     auto polygon1 = RegularPolygon({Point(0,0), Point(0,10), Point(10,10), Point(10,0)});
        //     auto temp = polygon_algo::rotation(polygon1, algorithm::pi_on_2<double>);
        //     auto points = temp.get_points(algorithm::pi_on_2<double>);


        //     for(auto i : points){
        //         std::cout << std::format("{} {}", i.x(), i.y()) << std::endl;
        //     }
        //     QVERIFY(points[0] == Point(0,10));
        //     QVERIFY(points[1] == Point(10,10));
        //     QVERIFY(points[2] == Point(10,0));
        //     QVERIFY(points[3] == Point(0,0));
        // }

    }
}

void Unit_Test::test_geo_algorithm()
{
    {//common_survey_comp
        auto value = geo_algo::common_survey_comp(100'000., (0_deg).radian(), PointGeo(0_deg, 0_deg));
        QVERIFY(value.latitude_angle() == 0.898316_deg);
        QVERIFY(value.longitude_angle() == 0._deg);

        value = geo_algo::common_survey_comp(11'000'000., (0_deg).radian(), PointGeo(0_deg, 0_deg));
        QVERIFY(value.latitude_angle() == 81.004577_deg);
        QVERIFY((value.longitude_angle() == 180._deg) || (value.longitude_angle() == -180._deg));

        value = geo_algo::common_survey_comp(1'000'000., (45_deg).radian(), PointGeo(0_deg, 0_deg));
        QVERIFY(value.latitude_angle() == 6.338979_deg);
        QVERIFY(value.longitude_angle() == 6.421122_deg);

        value = geo_algo::common_survey_comp(10'000'000., (67_deg).radian(), PointGeo(0_deg, 0_deg));
        QVERIFY(value.latitude_angle() == 22.930826_deg);
        QVERIFY(value.longitude_angle() == 90.399161_deg);

        value = geo_algo::common_survey_comp(5'000'000., (30_deg).radian(), PointGeo(10_deg, 20_deg));
        QVERIFY(value.latitude_angle() == 46.492402_deg);
        QVERIFY(value.longitude_angle() == 51.053114_deg);
    }

    {//geographic_inverse
        {
            auto value = geo_algo::geographic_inverse(PointGeo(0_deg, 0_deg), PointGeo(1_deg, 0_deg));
            Polar2d polar(std::get<0>(value), std::get<1>(value));
            QVERIFY(algorithm::compare(polar.psi(), 111319.435509));
            QVERIFY(polar.angle_fi() == 0._deg);
        }

        {
            auto value = geo_algo::geographic_inverse(PointGeo(10_deg, 10_deg), PointGeo(20_deg, 20_deg));
            Polar2d polar(std::get<0>(value), std::get<1>(value));
            QVERIFY(algorithm::compare(polar.psi(), 1541490.960101));
            QVERIFY(polar.angle_fi() == 42.635007_deg);
        }

        {
            auto value = geo_algo::geographic_inverse(PointGeo(10_deg, 170_deg), PointGeo(20_deg, -170_deg));
            Polar2d polar(std::get<0>(value), std::get<1>(value));
            QVERIFY(algorithm::compare(polar.psi(), 2405529.167408));
            QVERIFY(polar.angle_fi() == 60.130829_deg);
        }

        {
            auto value = geo_algo::geographic_inverse(PointGeo(0_deg, 0_deg), PointGeo(20_deg, -180_deg));
            Polar2d polar(std::get<0>(value), std::get<1>(value));
            QVERIFY(algorithm::compare(polar.psi(), 17777834.212800));
            QVERIFY(polar.angle_fi() == 360_deg);
        }
    }

    {//convert(Point -> PointGeo)
        auto point = geo_algo::convert<Point>(PointGeo(1_deg, 0_deg), PointGeo(0_deg, 0_deg));
        QVERIFY(point == Point(0., 111319.435510));
    }
    {//convert(PointGeo -> Point)
        auto point = geo_algo::convert(Point(100000, 100000), PointGeo(0_deg, 0_deg));
        QVERIFY(point == PointGeo(0.0156779, 0.0157855));
    }
    {//convert(Polar -> PointGeo)
        auto point = geo_algo::convert(Polar2d(500000., (90_deg).radian()), PointGeo(0_deg, 0_deg));
        QVERIFY(point == PointGeo(0., 0.0789211));
    }
    {//convert(PointGeo -> Polar)
        auto point = geo_algo::convert<Polar2d>(PointGeo(1_deg, 2_deg), PointGeo(0_deg, 0_deg));
        QVERIFY(algorithm::compare(point.psi(), 247573.405637));
        QVERIFY(algorithm::compare(point.fi(),1.104330));
    }
    {//convert(half_line -> half_line_geo)
        auto line = geo_algo::convert<HalfLine>(HalfLineGeo(PointGeo(5_deg, 2_deg), (45_deg).radian()), PointGeo(0_deg, 0_deg));
        QVERIFY(line == HalfLine(Point(220583.762639, 556704.705610), 0.785398));
    }
    {//convert(half_line_geo -> half_line)
        auto line = geo_algo::convert<HalfLineGeo>(HalfLine(Point(200000, 500000), (45_deg).radian()), PointGeo(0_deg, 0_deg));
        QVERIFY(line == HalfLineGeo(PointGeo(0.078380, 0.031633), 0.785398));
    }
    {//convert(line_section_geo -> line_section)
        auto line = geo_algo::convert<LineSection>(LineSectionGeo(PointGeo(5_deg, 2_deg), PointGeo(7_deg, 10_deg)), PointGeo(0_deg, 0_deg));
        QVERIFY(line == LineSection(Point(220583.762639, 556704.705610), Point(1100200.237985, 783151.054589)));
    }
    {//convert(line_section -> line_section_geo)
        auto line = geo_algo::convert<LineSectionGeo>(LineSection(Point(1, 0), Point(100000, 550000)), PointGeo(0_deg, 0_deg));
        QVERIFY(line == LineSectionGeo(PointGeo(0, 0), PointGeo(0.086229, 0.015823)));
    }

    {//convert(arc -> arc_geo)
        auto arc = geo_algo::convert<ArcGeo, Arc>(Arc(Point(10000.,10000.), 1000., 5_deg, 34_deg), PointGeo(0_deg, 0_deg));
        QVERIFY(arc.center() == PointGeo(0.00156786, 0.00157842));
        QVERIFY(arc.radius() == 1000.);
        QVERIFY(arc.start_angle() == 5_deg);
        QVERIFY(arc.stop_angle() == 34_deg);
    }

    {//convert(arc_geo -> arc)
        auto arc = geo_algo::convert<Arc>(ArcGeo(PointGeo(0.00156786, 0.00157842), 1000., 5_deg, 34_deg), PointGeo(0_deg, 0_deg));
        QVERIFY(arc.center() == Point(9999.847348,10000.028406));
        QVERIFY(arc.radius() == 1000.);
        QVERIFY(arc.start_angle() == 5_deg);
        QVERIFY(arc.stop_angle() == 34_deg);
    }

    {
        auto arc = geo_algo::convert<CircleGeo>(Circle(Point(10000.,10000.), 1000.), PointGeo(0_deg, 0_deg));
    }

    {
        auto points = std::vector{Point(0,0), Point(0,10), Point(10,10), Point(10,0)};
        auto geo_points = geo_algo::convert<PointGeo>(points, PointGeo(0_deg, 0_deg));
    }

    {
        auto points = std::vector{LineSection{Point(0,0), Point(0,10)}, LineSection{Point(10,10), Point(10,0)}};
        auto geo_points = geo_algo::convert<LineSectionGeo>(points, PointGeo(0_deg, 0_deg));
    }
}

void Unit_Test::test_approximation()
{
    {
        auto points = approximation_algo::splitting_evenly(Point(0,0), Point(4,3), 5);
        // for(auto i : points){
        //     std::cout << std::format("{} {}", i.x(), i.y()) << std::endl;
        // }
        // 0.8 0.6
        // 1.6 1.2
        // 2.4000000000000004 1.7999999999999998
        // 3.2 2.4
        // 4 3
    }

    {
        auto line = LineSection(Point(1,1), Point(5,4));
        auto points = approximation_algo::splitting_evenly(view_line(line), 5);
        // for(auto i : points){
        //     std::cout << std::format("{} {}", i.x(), i.y()) << std::endl;
        // }
        // 1.8 1.6
        // 2.6 2.2
        // 3.4000000000000004 2.8
        // 4.2 3.4
        // 5 4
    }

    {
        auto arc = Arc(Point(0,0), 10, 0, 90_deg);
        auto points = approximation_algo::splitting_evenly(arc, 5);
        // for(auto i : points){
        //     std::cout << std::format("{} {}", i.x(), i.y()) << std::endl;
        // }
        // 1.8 1.6
        // 2.6 2.2
        // 3.4000000000000004 2.8
        // 4.2 3.4
        // 5 4
    }

    {
        auto arc = Circle(Point(0,0), 10);
        auto points = approximation_algo::splitting_evenly(arc, 4);
        // for(auto i : points){
        //     std::cout << std::format("{} {}", i.x(), i.y()) << std::endl;
        // }
        // 1.8 1.6
        // 2.6 2.2
        // 3.4000000000000004 2.8
        // 4.2 3.4
        // 5 4
    }



    {
        double prior = 0;
        auto points = approximation_algo::splitting_evenly(Point(0,0), Point(40,30), 5., prior);
        // for(auto i : points){
        //     std::cout << std::format("{} {}", i.x(), i.y()) << std::endl;
        // }
        // 0 0
        // 4 3
        // 8 6
        // 12 9
        // 16 12
        // 20 15
        // 24 18
        // 28 21
        // 32 24
        // 36 27
    }

    {
        double prior = 0;
        auto line = LineSection(Point(1,1), Point(41,31));
        auto points = approximation_algo::splitting_evenly(view_line(line), 5., prior);
        // for(auto i : points){
        //     std::cout << std::format("{} {}", i.x(), i.y()) << std::endl;
        // }
        // 0 0
        // 4.1 3.1
        // 8.2 6.2
        // 12.299999999999999 9.3
        // 16.4 12.4
        // 20.5 15.5
        // 24.599999999999998 18.6
        // 28.699999999999996 21.7
        // 32.8 24.8
        // 36.9 27.900000000000002
    }

    {
        double prior = 0;
        auto arc = Arc(Point(0,0), 50, 0, 90_deg);
        auto points = approximation_algo::splitting_evenly(arc, 5., prior);
        // for(auto i : points){
        //     std::cout << std::format("{} {}", i.x(), i.y()) << std::endl;
        // }
        // 0 50
        // 5.226423163382673 49.72609476841367
        // 10.395584540887965 48.907380036690284
        // 15.450849718747369 47.552825814757675
        // 20.336832153790006 45.67727288213004
        // 24.999999999999996 43.30127018922194
        // 29.389262614623657 40.45084971874737
        // 33.45653031794291 37.157241273869715
        // 37.15724127386971 33.456530317942914
        // 40.45084971874737 29.389262614623657
        // 43.30127018922193 25.000000000000007
        // 45.67727288213004 20.33683215379002
        // 47.552825814757675 15.450849718747373
        // 48.90738003669028 10.395584540887972
        // 49.72609476841367 5.226423163382684
    }
}

void Unit_Test::test_matrix()
{
    {
        {
            matrix<int, 3, 3> m1;
            matrix<int, 3, 3> m2;
            QVERIFY(m1 == m2);
        }

        {
            matrix<int, 3, 3> m1({1,2,3,4,5,6});
            matrix<int, 3, 3> m2({1,2,3,4,5,6,0,0,0});
            QVERIFY(m1 == m2);
        }

        {
            matrix<int, 3, 3> m({1,2,3,4,5,6,7,8,9});
            std::array<int, 3> row = m.row(0);
            std::array<int, 3> ar({1,2,3});
            QVERIFY(std::ranges::equal(row, ar));
        }

        {
            matrix<int, 3, 3> m({1,2,3,4,5,6,7,8,9});
            std::array<int, 3> row = m.column(1);
            std::array<int, 3> ar({2,5,8});
            QVERIFY(std::ranges::equal(row, ar));
        }

        {
            matrix<int, 3, 3> m1({1,2,3,4,5,6,7,8,9});
            m1.swap_row(0,1);
            matrix<int, 3, 3> m2({4,5,6,1,2,3,7,8,9});
            QVERIFY(m1 == m2);
        }
        {
            matrix<int, 3, 3> m1({
                                  1,2,3,
                                  4,5,6,
                                  7,8,9});
            m1.swap_column(0,1);
            matrix<int, 3, 3> m2({2,1,3,
                                  5,4,6,
                                  8,7,9});
            QVERIFY(m1 == m2);
        }
        {
            matrix<int, 3, 3> m1({
                                  1,2,3,
                                  4,5,6,
                                  7,8,9});
            m1.copy_row(1,2);
            matrix<int, 3, 3> m2({
                                  1,2,3,
                                  7,8,9,
                                  7,8,9});
            QVERIFY(m1 == m2);
        }
        {
            matrix<int, 3, 3> m1({
                                  1,2,3,
                                  4,5,6,
                                  7,8,9});
            m1.copy_row(1,{9,9,9});
            matrix<int, 3, 3> m2({
                                  1,2,3,
                                  9,9,9,
                                  7,8,9});
            QVERIFY(m1 == m2);
        }
        {
            matrix<int, 3, 3> m1({
                                  1,2,3,
                                  4,5,6,
                                  7,8,9});
            m1.copy_column(1,2);
            matrix<int, 3, 3> m2({
                                  1,3,3,
                                  4,6,6,
                                  7,9,9});
            QVERIFY(m1 == m2);
        }
        {
            matrix<int, 3, 3> m1({
                                  1,2,3,
                                  4,5,6,
                                  7,8,9});
            m1.copy_column(1,{9,9,9});
            matrix<int, 3, 3> m2({
                                  1,9,3,
                                  4,9,6,
                                  7,9,9});
            QVERIFY(m1 == m2);
        }
        {
            matrix<int, 3, 3> m({1,2,3,4,5,6,7,8,9});
            QVERIFY(m.value(1,1) == 5);
        }
        {
            matrix<int, 3, 3> m({1,2,3,4,5,6,7,8,9});
            QVERIFY(m.value(2,0) == 7);
        }
    }

    {//operator
        {
            matrix<double, 4, 3> m1{1,2,3,
                                    4,5,6,
                                    7,8,9,
                                    10,11,12};

            matrix<double, 4, 3> m2{10,20,30,
                                    40,50,60,
                                    70,80,90,
                                    100,110,120};
            matrix<double, 4, 3> m3{11,22,33,
                                    44,55,66,
                                    77,88,99,
                                    110,121,132};
            QVERIFY((m1 + m2) == m3);
        }
        {
            matrix<double, 4, 3> m1{1,2,3,
                                    4,5,6,
                                    7,8,9,
                                    10,11,12};

            matrix<double, 4, 3> m2{10,20,30,
                                    40,50,60,
                                    70,80,90,
                                    100,110,120};
            matrix<double, 4, 3> m3{9,18,27,
                                    36,45,54,
                                    63,72,81,
                                    90,99,108};
            QVERIFY((m2 - m1) == m3);
        }
        {
            matrix<double, 4, 3> m1{1,2,3,
                                    4,5,6,
                                    7,8,9,
                                    10,11,12};

            matrix<double, 4, 3> m2{10,20,30,
                                    40,50,60,
                                    70,80,90,
                                    100,110,120};
            QVERIFY((10 * m1) == m2);
            QVERIFY((m1 * 10) == m2);
        }

        {
            {
                matrix<double, 3, 3> m1({1,2,3,
                                         4,5,6,
                                         7,8,9});

                matrix<double, 3, 4> m2{1,2,3,4,
                                        5,6,7,8,
                                        9,10,11,12};
                matrix<double, 3, 4> m3{38,	44,	50,	56,
                                        83, 98, 113, 128,
                                        128, 152, 176, 200};
                QVERIFY((m1 * m2) == m3);
            }
            {
                matrix<double, 2, 3> m1({1,2,3,
                                         4,5,6});

                matrix<double, 3, 2> m2{1,2,
                                        4,5,
                                        7,8};
                matrix<double, 2, 2> m3{30,	36,
                                        66, 81};
                QVERIFY((m1 * m2) == m3);
            }
            {
                matrix<double, 6, 1> m1({1,3,5,7,9,11});
                matrix<double, 1, 6> m2{1,2,3,4,5,6};
                matrix<double, 6, 6> m3{1,2,3,4,5,6,
                                        3,	6,	9,	12,	15,	18,
                                        5,	10,	15,	20,	25,	30,
                                        7,	14,	21,	28,	35,	42,
                                        9,	18,	27,	36,	45,	54,
                                        11,	22,	33,	44,	55,	66};
                QVERIFY((m1 * m2) == m3);
            }
        }
    }

    {//determinant
        {
            matrix<double, 2, 2> m{1,2,
                                   3,4};
            QVERIFY(algorithm::compare(m.determinant(), -2));
        }
        {
            matrix<double, 3, 3> m{1,2,3,
                                   4,5,6,
                                   7,8,9};
            // std::cout << "---------------" << std::endl;
            // std::cout << m.determinant() << std::endl;
            QVERIFY(algorithm::compare(m.determinant(), 0));
        }
        {
            matrix<double, 3, 3> m{1,2,3,
                                4,5,6,
                                7,5,1};
            QVERIFY(algorithm::compare(m.determinant(), 6));
        }
        {
            matrix<double, 4, 4> m{1,2,3,4,
                                5,6,7,8,
                                1,4,5,3,
                                13,56,5,16};
            QVERIFY(algorithm::compare(m.determinant(), 1624));
        }

        {
            matrix<double, 7, 7> m{
                1,2,3,2,3,4,5,
                4,5,6,3,2,2,4,
                7,5,1,5,5,0,0,
                4,2,3,4,5,4,0,
                5,3,4,5,4,4,3,
                7,6,5,6,5,6,4,
                1,1,9,0,7,9,0
            };
            QVERIFY(algorithm::compare(m.determinant(), -6660));
        }
    }
    {//transposed
        {
            matrix<double, 2, 2> m1{
                1,2,
                3,4
            };
            matrix<double, 2, 2> m2{
                1,3,
                2,4
            };
            QVERIFY(m1.transposed() == m2);
        }
        {
            matrix<double, 3, 3> m1{
                1,2,3,
                4,5,6,
                7,8,9
            };
            matrix<double, 3, 3> m2{
                1,4,7,
                2,5,8,
                3,6,9
            };
            QVERIFY(m1.transposed() == m2);
        }
        {
            matrix<double, 4, 5> m1{
                1,2,3,4,5,
                5,6,7,8,6,
                1,4,5,3,7,
                13,56,5,16,8
            };
            matrix<double, 5, 4> m2{
                1,5,1,13,
                2,6,4,56,
                3,7,5,5,
                4,8,3,16,
                5,6,7,8
            };
            QVERIFY(m1.transposed() == m2);
        }

        {
            matrix<double, 2, 7> m1{
                1,2,3,2,3,4,5,
                4,5,6,3,2,2,4,
            };
            matrix<double, 7, 2> m2{
                1,4,
                2,5,
                3,6,
                2,3,
                3,2,
                4,2,
                5,4,
            };
            QVERIFY(m1.transposed() == m2);
        }
    }

    {//identity_matrix
        {
            matrix<double, 2, 2> m1{
                1,0,
                0,1
            };
            auto m = matrix_algo::identity_matrix<matrix,double,2>();
            QVERIFY(m1 == m);
        }
        {
            matrix<double, 3, 3> m2{
                1,0,0,
                0,1,0,
                0,0,1
            };
            auto m = matrix_algo::identity_matrix<matrix,double,3>();
            QVERIFY(m2 == m);
        }
    }

    {//identity_matrix
        {
            matrix<double, 3, 3> m{
                1,2,3,
                4,5,6,
                7,8,9
            };
            {
                auto minor = matrix_algo::minor(m, 0, 0);
                matrix<double, 2, 2> m2{
                    5,6,
                    8,9,
                };
                QVERIFY(minor == m2);
            }
            {
                auto minor = matrix_algo::minor(m, 0, 1);
                matrix<double, 2, 2> m2{
                    4,6,
                    7,9,
                };
                QVERIFY(minor == m2);
            }
            {
                auto minor = matrix_algo::minor(m, 0, 2);
                matrix<double, 2, 2> m2{
                    4,5,
                    7,8,
                };
                QVERIFY(minor == m2);
            }
            {
                auto minor = matrix_algo::minor(m, 1, 0);
                matrix<double, 2, 2> m2{
                    2,3,
                    8,9,
                };
                QVERIFY(minor == m2);
            }
            {
                auto minor = matrix_algo::minor(m, 1, 1);
                matrix<double, 2, 2> m2{
                    1,3,
                    7,9,
                };
                QVERIFY(minor == m2);
            }
            {
                auto minor = matrix_algo::minor(m, 1, 2);
                matrix<double, 2, 2> m2{
                    1,2,
                    7,8,
                };
                QVERIFY(minor == m2);
            }
            {
                auto minor = matrix_algo::minor(m, 2, 0);
                matrix<double, 2, 2> m2{
                    2,3,
                    5,6,
                };
                QVERIFY(minor == m2);
            }
            {
                auto minor = matrix_algo::minor(m, 2, 1);
                matrix<double, 2, 2> m2{
                    1,3,
                    4,6,
                };
                QVERIFY(minor == m2);
            }
            {
                auto minor = matrix_algo::minor(m, 2, 2);
                matrix<double, 2, 2> m2{
                    1,2,
                    4,5,
                };
                QVERIFY(minor == m2);
            }
        }
    }

    {//matrix_algebraic_additions
        {
            matrix<double, 3, 3> m1{
                1,2,3,
                4,5,6,
                7,8,9
            };

            auto adj = matrix_algo::matrix_algebraic_additions(m1);
            matrix<double, 3, 3> m2{
                -3,6,-3,
                6,-12,6,
                -3,6,-3
            };

            QVERIFY(adj == m2);
        }
    }

    {//inverse_matrix
        {
            matrix<double, 3, 3> m{
                1,2,3,
                4,5,6,
                7,8,9
            };
            auto inv = matrix_algo::inverse_matrix(m);
            QVERIFY(!inv.has_value());
        }
        {
            matrix<double, 3, 3> m{
                1,1,1,
                2,3,4,
                4,4,5
            };
            auto inv = matrix_algo::inverse_matrix(m);
            auto iden = matrix_algo::identity_matrix<matrix,double,3>();
            QVERIFY(inv.value() * m == iden);
        }
    }

    {//rang
        {
            matrix<double, 3, 3> m{
                1,2,3,
                4,5,6,
                7,8,9
            };
            QVERIFY(matrix_algo::rang(m) == 2);
        }
        {
            matrix<double, 3, 3> m{
                2,2,2,
                4,4,4,
                5,5,6
            };
            QVERIFY(matrix_algo::rang(m) == 2);
        }
        {
            matrix<double, 4, 3> m{
                2,2,2,
                4,4,4,
                5,5,5,
                6,6,6,
            };
            QVERIFY(matrix_algo::rang(m) == 1);
        }
        {
            matrix<double, 4, 3> m{
                2,2,3,
                4,4,7,
                5,5,11,
                6,6,13,
            };
            QVERIFY(matrix_algo::rang(m) == 2);
        }
        {
            matrix<double, 3, 3> m{
                3,2,3,
                7,4,5,
                11,5,7
            };
            QVERIFY(matrix_algo::rang(m) == 3);
        }
    }
}

void Unit_Test::test_vector()
{
    {//vector_product
        {
            vector<double, 3> v1{1,2,3};
            vector<double, 3> v2{3,7,5};
            vector<double, 3> temp{-11,4,1};
            QVERIFY(matrix_algo::vector_product(v1, v2) == temp);
        }
        {
            vector<double, 3> v1{1,2,3};
            vector<double, 3> v2{3,7,5};
            vector<double, 3> temp{11,-4,-1};
            QVERIFY(matrix_algo::vector_product(v2, v1) == temp);
        }
    }
    {//module
        {
            vector<double, 2> v1{3,4};
            QVERIFY(algorithm::compare(matrix_algo::module(v1), 5));
        }
        {
            vector<double, 4> v1{1,2,3,4};
            QVERIFY(algorithm::compare(matrix_algo::module(v1), 5.477226));
        }
    }
    {//scalar_product
        {
            vector<double, 3> v1{1,2,3};
            vector<double, 3> v2{3,7,5};
            QVERIFY(algorithm::compare(matrix_algo::scalar_product(v1, v2), 32));
        }
        {
            vector<double, 5> v1{1,2,3,4,5};
            vector<double, 5> v2{3,5,7,11,13};
            QVERIFY(algorithm::compare(matrix_algo::scalar_product(v1, v2), 143));
        }
    }
    {//vector_projection
        {
            vector<double, 3> v1{1,2,3};
            vector<double, 3> v2{3,7,5};
            QVERIFY(algorithm::compare(matrix_algo::vector_projection(v1, v2), 3.512456));
        }
        {
            vector<double, 3> v1{1,2,3};
            vector<double, 3> v2{1,0,0};
            QVERIFY(algorithm::compare(matrix_algo::vector_projection(v1, v2), 1));
        }
    }
    {//normal
        {
            vector<double, 3> v1{1,2,3};
            vector<double, 3> v2{0.267261, 0.534522, 0.801784};
            QVERIFY(matrix_algo::normal(v1) == v2);
        }
        {
            vector<double, 3> v1{1,0,0};
            vector<double, 3> v2{1,0,0};
            QVERIFY(matrix_algo::normal(v1) == v2);
        }
    }
    {//mul
        {
            matrix<double, 3, 3> m({1,2,3,4,5,6,7,8,9});
            vector<double, 3> v{3,5,7};
            vector<double, 3> temp{34,79,124};
            QVERIFY(matrix_algo::mul(m, v) == temp);
        }
        {
            auto t = matrix_algo::mul<double, 3>({1,2,3,4,5,6,7,8,9}, {3,5,7});
            QVERIFY(std::ranges::equal(t, std::array<double,3>{34,79,124}, [](const auto &i, const auto &j){
                return algorithm::compare(i, j);
            }));
        }
    }

    {//is_co_directional
        // {
        //     vector<double, 3> v1{1,2,3};
        //     vector<double, 3> v2{3,7,5};
        //     QVERIFY(!matrix_algo::is_co_directional(v1, v2));
        // }
        // {
        //     vector<double, 3> v1{0,0,0};
        //     vector<double, 3> v2{3,7,5};
        //     QVERIFY(!matrix_algo::is_co_directional(v1, v2));
        // }
        // {
        //     vector<double, 3> v1{0,1,1};
        //     vector<double, 3> v2{0,2,2};
        //     QVERIFY(matrix_algo::is_co_directional(v1, v2));
        // }
        // {
        //     vector<double, 3> v1{1,2,3};
        //     vector<double, 3> v2{-1,-2,-3};
        //     QVERIFY(!matrix_algo::is_co_directional(v1, v2));
        // }
    }
}
