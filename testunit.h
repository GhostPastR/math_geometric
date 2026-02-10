#ifndef TESTUNIT_H
#define TESTUNIT_H

#include <QObject>

class TestUnit : public QObject
{
    Q_OBJECT
public:
    explicit TestUnit(QObject *parent = nullptr);

private slots:
    void test();
};

#endif // TESTUNIT_H
