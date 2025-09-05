#include <QCoreApplication>
#include "QtTest/qtestcase.h"

#include "testunit.h"
#include "testgeometricstruct.h"
#include "testalgorithm.h"

#include "unit_test.h"

#include "unit_test_sa.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // QTest::qExec(new TestUnit, argc, argv);
    // QTest::qExec(new TestGeometricStruct, argc, argv);
    QTest::qExec(new TestAlgorithm, argc, argv);

    // QTest::qExec(new Unit_Test, argc, argv);
    // QTest::qExec(new Unit_Test_SA, argc, argv);
    return a.exec();
}
