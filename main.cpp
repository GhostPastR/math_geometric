#include <QCoreApplication>
#include <iostream>
#include "QtTest/qtestcase.h"
#include "unit_test.h"
#include "unit_test_sa.h"


#include "structs/point/decart_point2d.h"
#include "algorithm/distance/test_distance.h"

int main(int argc, char *argv[])
{
    agl::point::decart::point2d<double> p1{0,0};
    // agl::point::decart::point2d<double> p2{5,5};
    // auto d = agl::algorithm::distance(p1, p2);
    // std::cout << d << std::endl;

    auto dd = agl::algorithm::distance(p1, 11);
    std::cout << dd << std::endl;


    // QCoreApplication a(argc, argv);
    // QTest::qExec(new Unit_Test, argc, argv);
    // QTest::qExec(new Unit_Test_SA, argc, argv);
    // return a.exec();
}
