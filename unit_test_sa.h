#ifndef UNIT_TEST_SA_H
#define UNIT_TEST_SA_H

#include <QObject>

class Unit_Test_SA : public QObject
{
    Q_OBJECT
public:
    explicit Unit_Test_SA(QObject *parent = nullptr);

private slots:
    void test_figure_route();
};

#endif // UNIT_TEST_SA_H
