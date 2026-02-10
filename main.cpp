#include <QCoreApplication>
#include "QtTest/qtestcase.h"

#include "testunit.h"
#include "testgeometricstruct.h"
#include "testalgorithm.h"

#include "unit_test.h"

#include "unit_test_sa.h"

#include "iostream"



#include "system/traits.h"
#include "structs/geometric_object.h"
#include "user_type.h"
#include "system/system_concept.h"


// template<typename Object>
// struct access_types{
//     template<typename ...T>
//     using point = std::tuple<T...>;
// };

// template<>
// struct access_types<agl::point_geo2_a>{
//     using point = std::tuple<double,double>;
// };


// template<typename Object>
// concept c_point_2d = requires(Object object){
//     requires agl::c_not_undefined<typename access_types<Object>::point>;
//     requires std::get<0>(access_types<Object>::point);
//     requires std::get<1>(access_types<Object>::point);
// };




template <typename T>
class Temp;

template <typename Point>
void foo(const Point &point){
    auto[x1, y1] = agl::traits::access_propery<Point>::get(point);
    std::cout << x1 << std::endl;
    std::cout << y1 << std::endl;
}



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // agl::point2_d p1(1.,10.);
    // agl::point2_d p2(2.,20.);

    // agl::point::decart::point2<agl::point2_d> p(std::move(p1), std::move(p2));
    // std::cout << "----------------" <<std::endl;
    // foo(p);

    // agl::point::decart::point2<agl::point2_d> p(agl::point2_d(1.,10.), agl::point2_d(2.,20.));
    // std::cout << "----------------" <<std::endl;
    // foo(p);


    QTest::qExec(new TestUnit, argc, argv);
    QTest::qExec(new TestGeometricStruct, argc, argv);
    QTest::qExec(new TestAlgorithm, argc, argv);
    QTest::qExec(new Unit_Test, argc, argv);
    QTest::qExec(new Unit_Test_SA, argc, argv);
    return a.exec();
    return 0;
}
