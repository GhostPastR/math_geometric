#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <QObject>

class Unit_Test : public QObject
{
    Q_OBJECT
public:
    explicit Unit_Test(QObject *parent = nullptr);

private slots:
    void test_angle();
    void test_unit();

    void test_point();
    void test_point_algorithm();

    void test_line();
    void test_line_algorithm();

    void test_circle();
    void test_circle_algorithm();

    void test_polygon();
    void test_polygon_algorithm();

    void test_geo_algorithm();

    void test_approximation();

    void test_matrix();
};

#endif // UNIT_TEST_H
