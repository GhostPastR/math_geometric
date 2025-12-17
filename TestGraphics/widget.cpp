#include "widget.h"
#include "./ui_widget.h"
#include <QPainter>
#include <QDebug>
#include <algorithm>
#include <ranges>

#include "../../math_geometric/special_algorithms/navigation_route/algorithm_route.h"
// #include "../../math_geometric/algorithm/approximation_algorithm.h"
#include "../../math_geometric/user_type.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    point1 = QPoint(ui->spinBox->value(), ui->spinBox_2->value());
    point2 = QPoint(ui->spinBox_3->value(), ui->spinBox_4->value());
    point3 = QPoint(ui->spinBox_5->value(), ui->spinBox_6->value());
}

Widget::~Widget()
{
    delete ui;
}
// const Arc &arc, Type interval, Type &prior_remains
void Widget::paintEvent(QPaintEvent *event)
{
    // QPainter painter(this);

    // {
    //     QPen pointPen(Qt::black, 4);
    //     painter.setPen(pointPen);
    // }

    // // auto figures = sa::itinerary_stage(agl::point2d(point1.x(), point1.y()),
    // //                                    agl::point2d(point2.x(), point2.y()),
    // //                                    agl::point2d(point3.x(), point3.y()), 100);
    // // auto figures = sa::through_stage(agl::point2d(point1.x(), point1.y()),
    // //                                    agl::point2d(point2.x(), point2.y()),
    // //                                    agl::point2d(point3.x(), point3.y()), 100);
    // auto figures = sa::combine_stage(agl::point2d(point1.x(), point1.y()),
    //                                  agl::point2d(point2.x(), point2.y()),
    //                                  agl::point2d(point3.x(), point3.y()),
    //                                  50, 80, agl::algorithm::pi<double>, 30);
    // std::vector<agl::point2d> points;
    // // std::cout << "======================================" << std::endl;
    // for(auto &&i : figures){
    //     std::ranges::copy(i.draw_point(), std::back_inserter(points));
    // }

    // QPolygon polygon;
    // // double len = 0;
    // // auto point = agl::approximation_algo::splitting_evenly(arc, 50., len, agl::algorithm::direct::LEFT);
    // // auto point = agl::approximation_algo::splitting_evenly(arc, 50., len);
    // for(auto i : points){
    //     polygon.push_back(QPoint(i.x(), i.y()));
    // }



    // // painter.drawPolyline(polygon);
    // painter.drawPoints(polygon);

    // {
    //     QPen pointPen(Qt::red, 4);
    //     painter.setPen(pointPen);
    // }
    // QPolygon red;
    // red.push_back(point1);
    // red.push_back(point2);
    // red.push_back(point3);
    // painter.drawPoints(red);
}

void Widget::on_pushButton_clicked()
{

}


void Widget::on_spinBox_valueChanged(int arg1)
{
    point1.setX(arg1);
    update();
}


void Widget::on_spinBox_2_valueChanged(int arg1)
{
    point1.setY(arg1);
    update();
}


void Widget::on_spinBox_3_valueChanged(int arg1)
{
    point2.setX(arg1);
    update();
}


void Widget::on_spinBox_4_valueChanged(int arg1)
{
    point2.setY(arg1);
    update();
}

void Widget::on_spinBox_5_valueChanged(int arg1)
{
    point3.setX(arg1);
    update();
}


void Widget::on_spinBox_6_valueChanged(int arg1)
{
    point3.setY(arg1);
    update();
}

