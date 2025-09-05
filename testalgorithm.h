#ifndef TESTALGORITHM_H
#define TESTALGORITHM_H

#include <QObject>

class TestAlgorithm : public QObject
{
    Q_OBJECT
public:
    explicit TestAlgorithm(QObject *parent = nullptr);

private slots:
    void test_distance();
    void test_direction();
    void test_create_point();
    void test_rotate();
    void test_midplane();
    void test_intersection();
    void test_contain();
    void test_parallel();
    void test_perpendicular();
    void test_point_on_curve();
    void test_located_inside();
    void test_create_polygon();


    // void test_();
};

#endif // TESTALGORITHM_H
