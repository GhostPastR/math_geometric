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

    // using tpoint = std::tuple<agl::undefined>;

    // using t1 = decltype(agl::traits::point::access_point<agl::point_geo2_a, 0>::get(point));
    // using t2 = std::remove_cvref_t<decltype(std::get<0>(std::declval<access_types<agl::point_geo2_a>::point>()))>;

    // using t2 = std::tuple_element<0, access_types<agl::point_geo2_a>::point>::type;

    // Temp<t1> q1;
    // Temp<t2> q2;

    // auto t = std::is_same_v<decltype(agl::traits::point::access_point<agl::point_geo2_a, 0>::get(point)),
    //                         std::tuple_element<0, access_types<agl::point_geo2_a>::point>::type>;
    // std::cout << t << std::endl;


    QTest::qExec(new TestUnit, argc, argv);
    QTest::qExec(new TestGeometricStruct, argc, argv);
    QTest::qExec(new TestAlgorithm, argc, argv);
    QTest::qExec(new Unit_Test, argc, argv);
    QTest::qExec(new Unit_Test_SA, argc, argv);
    return a.exec();
    return 0;
}
