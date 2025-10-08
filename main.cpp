#include <QCoreApplication>
#include "QtTest/qtestcase.h"

#include "testunit.h"
#include "testgeometricstruct.h"
#include "testalgorithm.h"

#include "unit_test.h"

#include "unit_test_sa.h"


// #include "system/system_concept.h"
// #include "structs/geometric_object.h"
// #include "iostream"

// template<agl::c_point_2d T>
// void foo(T t){
//     std::cout << "2" << std::endl;
// }

int main(int argc, char *argv[])
{
    // agl::point::decart::point2d<double> p{0,0};
    // using tt = agl::traits::tag<agl::point::decart::point2d<double>>::type_tag;

    // foo(p);





    QCoreApplication a(argc, argv);
    // QTest::qExec(new TestUnit, argc, argv);
    // QTest::qExec(new TestGeometricStruct, argc, argv);
    QTest::qExec(new TestAlgorithm, argc, argv);

    // QTest::qExec(new Unit_Test, argc, argv);
    // QTest::qExec(new Unit_Test_SA, argc, argv);
    return a.exec();
}
