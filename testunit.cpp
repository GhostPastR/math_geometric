#include "testunit.h"
#include <QtTest/QTest>
#include "algorithm/math_algorithm.h"
#include <unit/unit_object.h>


TestUnit::TestUnit(QObject *parent)
    : QObject{parent}
{}

void TestUnit::test()
{
    using namespace agl;
    {//angle
        {
            unit::angle d(algorithm::pi<double>);
            QVERIFY(algorithm::compare(d.value<unit::radian>(), algorithm::pi<double>));
            QVERIFY(algorithm::compare(d.value<unit::degrees>(), 180));
        }
        {
            unit::angle d;
            d.set_value<unit::radian>(algorithm::pi_on_2<double>);
            QVERIFY(algorithm::compare(d.value<unit::radian>(), algorithm::pi_on_2<double>));
            d.set_value<unit::degrees>(45);
            QVERIFY(algorithm::compare(d.value<unit::radian>(), algorithm::pi_on_4<double>));
        }
        {
            QVERIFY(algorithm::compare((1_rad).value<unit::radian>(), 1));
            QVERIFY(algorithm::compare((100_deg).value<unit::radian>(), 1.745329));
        }
    }
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
