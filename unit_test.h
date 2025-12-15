#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <QObject>

class Unit_Test : public QObject
{
    Q_OBJECT
public:
    explicit Unit_Test(QObject *parent = nullptr);

private slots:
    void test_polygon_algorithm();

    void test_approximation();
    void test_matrix();
    void test_vector();
};

#endif // UNIT_TEST_H
