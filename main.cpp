#include <QCoreApplication>
#include "QtTest/qtestcase.h"
#include "unit_test.h"
#include "unit_test_sa.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTest::qExec(new Unit_Test, argc, argv);
    QTest::qExec(new Unit_Test_SA, argc, argv);
    return a.exec();
}
