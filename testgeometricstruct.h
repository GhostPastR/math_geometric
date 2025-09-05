#ifndef TESTGEOMETRICSTRUCT_H
#define TESTGEOMETRICSTRUCT_H

#include <QObject>

class TestGeometricStruct : public QObject
{
    Q_OBJECT
public:
    explicit TestGeometricStruct(QObject *parent = nullptr);

private slots:
    void test_point();
    void test_line();
    void test_circle();
    void test_polygon();
};

#endif // TESTGEOMETRICSTRUCT_H
