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




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // auto lamda = []<typename T, typename R>(T a){
    //     func<T, R>(a);
    // };

    // lamda.template operator()<double, double>(1);

    // agl::point_geo2_a point(1_deg, 2_deg);
    // agl::polar2_d p_point(10., 2_deg);
    // func(point);
    // func(p_point);


    QTest::qExec(new TestUnit, argc, argv);
    QTest::qExec(new TestGeometricStruct, argc, argv);
    QTest::qExec(new TestAlgorithm, argc, argv);
    QTest::qExec(new Unit_Test, argc, argv);
    QTest::qExec(new Unit_Test_SA, argc, argv);
    return a.exec();
    return 0;
}
