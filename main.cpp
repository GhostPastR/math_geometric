#include <QCoreApplication>
#include "QtTest/qtestcase.h"

#include "testunit.h"
#include "testgeometricstruct.h"
#include "testalgorithm.h"

#include "unit_test.h"

#include "unit_test_sa.h"



// #include "system/traits.h"
// #include "structs/geometric_object.h"
// #include "iostream"

// template<agl::c_point_2d T>
// void foo(T t){
//     std::cout << "1" << std::endl;
// }

// template<agl::c_line_section T>
// void foo(T t){
//     std::cout << "2" << std::endl;
// }

// template<typename T>
// class Temp;

int main(int argc, char *argv[])
{
    // agl::point::decart::point2d<double> p{0,0};
    // auto line_section = agl::line::line_section(agl::point::decart::point2d<double>{1.,2.},
    //                                             agl::point::decart::point2d<double>{5.,2.});

    // foo(p);
    // foo(line_section);


    QCoreApplication a(argc, argv);
    // QTest::qExec(new TestUnit, argc, argv);
    // QTest::qExec(new TestGeometricStruct, argc, argv);
    QTest::qExec(new TestAlgorithm, argc, argv);

    // QTest::qExec(new Unit_Test, argc, argv);
    // QTest::qExec(new Unit_Test_SA, argc, argv);
    return a.exec();
}
