#include "unit_test.h"
#include <QtTest/QTest>

#include <algorithm/algorithm.h>
#include <structs/geometric_object.h>

#include "algorithm/approximation_algorithm.h"
#include "algorithm/geo_algorithm.h"



#include "structs/matrix.h"
#include "structs/vector.h"

#include <unit/unit_object.h>

#include "user_type.h"

using namespace agl;

Unit_Test::Unit_Test(QObject *parent) : QObject{parent}{}


void Unit_Test::test_point_algorithm()
{
    // {
    //     auto value = convert_polar(point2d{10,10}, point2d{5,5});
    //     QVERIFY(algorithm::compare(value.psi(), 5 * std::sqrt(2)));
    //     QVERIFY(value.fi() == 225_deg);
    // }
}

void Unit_Test::test_polygon_algorithm()
{
//     {//scale_regular_polygon
//         {
//             auto polygon = RegularPolygon(point2d(0,0), 5, 4);
//             auto temp = polygon_algo::scale_regular_polygon(polygon, 1.);

//             auto points = temp.get_points();
//             QVERIFY(points[0] == point2d(0, 4.949747));
//             QVERIFY(points[1] == point2d(4.949747, 0));
//             QVERIFY(points[2] == point2d(0, -4.949747));
//             QVERIFY(points[3] == point2d(-4.949747, 0));
//         }
//         {
//             auto polygon = RegularPolygon(point2d(0,0), 5, 5);
//             auto temp = polygon_algo::scale_regular_polygon(polygon, 2.);
//             auto points = temp.get_points();
//             QVERIFY(points[0] == point2d(0, 7.227238));
//             QVERIFY(points[1] == point2d(6.873512, 2.233340));
//             QVERIFY(points[2] == point2d(4.248064, -5.846959));
//             QVERIFY(points[3] == point2d(-4.248064, -5.846959));
//             QVERIFY(points[4] == point2d(-6.873512, 2.233339));
//         }
//     }

//     {//rotation
//         {

//             auto polygon1 = RegularPolygon(point2d(0,0), 10 * sqrt(2), 4);
//             auto temp = polygon_algo::rotation(polygon1, algorithm::pi_on_2<double>);
//             auto polygon2 = polygon_algo::create_regular_polygon(point2d(0,0), 10 * sqrt(2), 4, algorithm::pi_on_2<double>);
//             auto points = temp.get_points(algorithm::pi_on_2<double>);

//             QVERIFY(points[0] == polygon2[0]);
//             QVERIFY(points[1] == polygon2[1]);
//             QVERIFY(points[2] == polygon2[2]);
//             QVERIFY(points[3] == polygon2[3]);
//         }

//         // {
//         //     auto polygon1 = RegularPolygon({point2d(0,0), point2d(0,10), point2d(10,10), point2d(10,0)});
//         //     auto temp = polygon_algo::rotation(polygon1, algorithm::pi_on_2<double>);
//         //     auto points = temp.get_points(algorithm::pi_on_2<double>);


//         //     for(auto i : points){
//         //         std::cout << std::format("{} {}", i.x(), i.y()) << std::endl;
//         //     }
//         //     QVERIFY(points[0] == point2d(0,10));
//         //     QVERIFY(points[1] == point2d(10,10));
//         //     QVERIFY(points[2] == point2d(10,0));
//         //     QVERIFY(points[3] == point2d(0,0));
//         // }

//     }
}

void Unit_Test::test_geo_algorithm()
{
//     {//common_survey_comp
//         auto value = geo_algo::common_survey_comp(100'000., (0_deg).radian(), PointGeo(0_deg, 0_deg));
//         QVERIFY(value.latitude() == 0.898316_deg);
//         QVERIFY(value.longitude() == 0._deg);

//         value = geo_algo::common_survey_comp(11'000'000., (0_deg).radian(), PointGeo(0_deg, 0_deg));
//         QVERIFY(value.latitude() == 81.004577_deg);
//         QVERIFY((value.longitude() == 180._deg) || (value.longitude() == -180._deg));

//         value = geo_algo::common_survey_comp(1'000'000., (45_deg).radian(), PointGeo(0_deg, 0_deg));
//         QVERIFY(value.latitude() == 6.338979_deg);
//         QVERIFY(value.longitude() == 6.421122_deg);

//         value = geo_algo::common_survey_comp(10'000'000., (67_deg).radian(), PointGeo(0_deg, 0_deg));
//         QVERIFY(value.latitude() == 22.930826_deg);
//         QVERIFY(value.longitude() == 90.399161_deg);

//         value = geo_algo::common_survey_comp(5'000'000., (30_deg).radian(), PointGeo(10_deg, 20_deg));
//         QVERIFY(value.latitude() == 46.492402_deg);
//         QVERIFY(value.longitude() == 51.053114_deg);
//     }

//     {//geographic_inverse
//         {
//             auto value = geo_algo::geographic_inverse(PointGeo(0_deg, 0_deg), PointGeo(1_deg, 0_deg));
//             polar2d polar(std::get<0>(value), std::get<1>(value));
//             QVERIFY(algorithm::compare(polar.psi(), 111319.435509));
//             QVERIFY(polar.fi() == 0._deg);
//         }

//         {
//             auto value = geo_algo::geographic_inverse(PointGeo(10_deg, 10_deg), PointGeo(20_deg, 20_deg));
//             polar2d polar(std::get<0>(value), std::get<1>(value));
//             QVERIFY(algorithm::compare(polar.psi(), 1541490.960101));
//             QVERIFY(polar.fi() == 42.635007_deg);
//         }

//         {
//             auto value = geo_algo::geographic_inverse(PointGeo(10_deg, 170_deg), PointGeo(20_deg, -170_deg));
//             polar2d polar(std::get<0>(value), std::get<1>(value));
//             QVERIFY(algorithm::compare(polar.psi(), 2405529.167408));
//             QVERIFY(polar.fi() == 60.130829_deg);
//         }

//         {
//             auto value = geo_algo::geographic_inverse(PointGeo(0_deg, 0_deg), PointGeo(20_deg, -180_deg));
//             polar2d polar(std::get<0>(value), std::get<1>(value));
//             QVERIFY(algorithm::compare(polar.psi(), 17777834.212800));
//             QVERIFY(polar.fi() == 360_deg);
//         }
//     }

//     {//convert(point2d -> PointGeo)
//         auto point = geo_algo::convert<point2d>(PointGeo(1_deg, 0_deg), PointGeo(0_deg, 0_deg));
//         QVERIFY(point == point2d(0., 111319.435510));
//     }
//     {//convert(PointGeo -> point2d)
//         auto point = geo_algo::convert(point2d(100000, 100000), PointGeo(0_deg, 0_deg));
//         QVERIFY(point == PointGeo(0.0156779, 0.0157855));
//     }
//     {//convert(Polar -> PointGeo)
//         auto point = geo_algo::convert(polar2d(500000., 90_deg), PointGeo(0_deg, 0_deg));
//         QVERIFY(point == PointGeo(0., 0.0789211));
//     }
//     {//convert(PointGeo -> Polar)
//         auto point = geo_algo::convert<polar2d>(PointGeo(1_deg, 2_deg), PointGeo(0_deg, 0_deg));
//         QVERIFY(algorithm::compare(point.psi(), 247573.405637));
//         QVERIFY(point.fi() == 1.104330);
//     }
//     {//convert(half_line -> half_line_geo)
//         auto line = geo_algo::convert<HalfLine>(HalfLineGeo(PointGeo(5_deg, 2_deg), (45_deg).radian()), PointGeo(0_deg, 0_deg));
//         QVERIFY(line == HalfLine(point2d(220583.762639, 556704.705610), 0.785398));
//     }
//     {//convert(half_line_geo -> half_line)
//         auto line = geo_algo::convert<HalfLineGeo>(HalfLine(point2d(200000, 500000), (45_deg).radian()), PointGeo(0_deg, 0_deg));
//         QVERIFY(line == HalfLineGeo(PointGeo(0.078380, 0.031633), 0.785398));
//     }
//     {//convert(line_section_geo -> line_section)
//         auto line = geo_algo::convert<LineSection>(LineSectionGeo(PointGeo(5_deg, 2_deg), PointGeo(7_deg, 10_deg)), PointGeo(0_deg, 0_deg));
//         QVERIFY(line == LineSection(point2d(220583.762639, 556704.705610), point2d(1100200.237985, 783151.054589)));
//     }
//     {//convert(line_section -> line_section_geo)
//         auto line = geo_algo::convert<LineSectionGeo>(LineSection(point2d(1, 0), point2d(100000, 550000)), PointGeo(0_deg, 0_deg));
//         QVERIFY(line == LineSectionGeo(PointGeo(0, 0), PointGeo(0.086229, 0.015823)));
//     }

//     {//convert(arc -> arc_geo)
//         auto arc = geo_algo::convert<ArcGeo, Arc>(Arc(point2d(10000.,10000.), 1000., 5_deg, 34_deg), PointGeo(0_deg, 0_deg));
//         QVERIFY(arc.center() == PointGeo(0.00156786, 0.00157842));
//         QVERIFY(arc.radius() == 1000.);
//         QVERIFY(arc.start_angle() == 5_deg);
//         QVERIFY(arc.stop_angle() == 34_deg);
//     }

//     {//convert(arc_geo -> arc)
//         auto arc = geo_algo::convert<Arc>(ArcGeo(PointGeo(0.00156786, 0.00157842), 1000., 5_deg, 34_deg), PointGeo(0_deg, 0_deg));
//         QVERIFY(arc.center() == point2d(9999.847348,10000.028406));
//         QVERIFY(arc.radius() == 1000.);
//         QVERIFY(arc.start_angle() == 5_deg);
//         QVERIFY(arc.stop_angle() == 34_deg);
//     }

//     {
//         auto arc = geo_algo::convert<CircleGeo>(Circle(point2d(10000.,10000.), 1000.), PointGeo(0_deg, 0_deg));
//     }

//     {
//         auto points = std::vector{point2d(0,0), point2d(0,10), point2d(10,10), point2d(10,0)};
//         auto geo_points = geo_algo::convert<PointGeo>(points, PointGeo(0_deg, 0_deg));
//     }

//     {
//         auto points = std::vector{LineSection{point2d(0,0), point2d(0,10)}, LineSection{point2d(10,10), point2d(10,0)}};
//         auto geo_points = geo_algo::convert<LineSectionGeo>(points, PointGeo(0_deg, 0_deg));
//     }
}

void Unit_Test::test_convert()
{

}

void Unit_Test::test_approximation()
{
//     {
//         auto points = approximation_algo::splitting_evenly(point2d(0,0), point2d(4,3), 5);
//         // for(auto i : points){
//         //     std::cout << std::format("{} {}", i.x(), i.y()) << std::endl;
//         // }
//         // 0.8 0.6
//         // 1.6 1.2
//         // 2.4000000000000004 1.7999999999999998
//         // 3.2 2.4
//         // 4 3
//     }

//     {
//         auto line = LineSection(point2d(1,1), point2d(5,4));
//         auto points = approximation_algo::splitting_evenly(view_line(line), 5);
//         // for(auto i : points){
//         //     std::cout << std::format("{} {}", i.x(), i.y()) << std::endl;
//         // }
//         // 1.8 1.6
//         // 2.6 2.2
//         // 3.4000000000000004 2.8
//         // 4.2 3.4
//         // 5 4
//     }

//     {
//         auto arc = Arc(point2d(0,0), 10, 0, 90_deg);
//         auto points = approximation_algo::splitting_evenly(arc, 5);
//         // for(auto i : points){
//         //     std::cout << std::format("{} {}", i.x(), i.y()) << std::endl;
//         // }
//         // 1.8 1.6
//         // 2.6 2.2
//         // 3.4000000000000004 2.8
//         // 4.2 3.4
//         // 5 4
//     }

//     {
//         auto arc = Circle(point2d(0,0), 10);
//         auto points = approximation_algo::splitting_evenly(arc, 4);
//         // for(auto i : points){
//         //     std::cout << std::format("{} {}", i.x(), i.y()) << std::endl;
//         // }
//         // 1.8 1.6
//         // 2.6 2.2
//         // 3.4000000000000004 2.8
//         // 4.2 3.4
//         // 5 4
//     }



//     {
//         double prior = 0;
//         auto points = approximation_algo::splitting_evenly(point2d(0,0), point2d(40,30), 5., prior);
//         // for(auto i : points){
//         //     std::cout << std::format("{} {}", i.x(), i.y()) << std::endl;
//         // }
//         // 0 0
//         // 4 3
//         // 8 6
//         // 12 9
//         // 16 12
//         // 20 15
//         // 24 18
//         // 28 21
//         // 32 24
//         // 36 27
//     }

//     {
//         double prior = 0;
//         auto line = LineSection(point2d(1,1), point2d(41,31));
//         auto points = approximation_algo::splitting_evenly(view_line(line), 5., prior);
//         // for(auto i : points){
//         //     std::cout << std::format("{} {}", i.x(), i.y()) << std::endl;
//         // }
//         // 0 0
//         // 4.1 3.1
//         // 8.2 6.2
//         // 12.299999999999999 9.3
//         // 16.4 12.4
//         // 20.5 15.5
//         // 24.599999999999998 18.6
//         // 28.699999999999996 21.7
//         // 32.8 24.8
//         // 36.9 27.900000000000002
//     }

//     {
//         double prior = 0;
//         auto arc = Arc(point2d(0,0), 50, 0, 90_deg);
//         auto points = approximation_algo::splitting_evenly(arc, 5., prior);
//         // for(auto i : points){
//         //     std::cout << std::format("{} {}", i.x(), i.y()) << std::endl;
//         // }
//         // 0 50
//         // 5.226423163382673 49.72609476841367
//         // 10.395584540887965 48.907380036690284
//         // 15.450849718747369 47.552825814757675
//         // 20.336832153790006 45.67727288213004
//         // 24.999999999999996 43.30127018922194
//         // 29.389262614623657 40.45084971874737
//         // 33.45653031794291 37.157241273869715
//         // 37.15724127386971 33.456530317942914
//         // 40.45084971874737 29.389262614623657
//         // 43.30127018922193 25.000000000000007
//         // 45.67727288213004 20.33683215379002
//         // 47.552825814757675 15.450849718747373
//         // 48.90738003669028 10.395584540887972
//         // 49.72609476841367 5.226423163382684
//     }
}

void Unit_Test::test_matrix()
{
    using namespace agl;

    {
        {
            agl::matrix<int, 3, 3> m1;
            agl::matrix<int, 3, 3> m2;
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
    using namespace agl;
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
