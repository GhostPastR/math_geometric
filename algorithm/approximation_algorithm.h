#ifndef APPROXIMATION_ALGORITHM_H
#define APPROXIMATION_ALGORITHM_H

// namespace approximation_algo{

// // LineSection
// // Arc
// //


// /**
//      * @brief approximation - Метод разбивает отрезок на отдельны точки.
//      * @param line - Отрезок.
//      * @param equidistant - Параметр задает способ разбиения(true - равномерное
//      * разбиение объекта на точки с перерасчетам интервала между точками,
//      * false - без перерасчета интервала между точками).
//      * @return Список точек.
//      */
// QList<NPoint> approximation( const NLineSection &line,
//                             bool equidistant ) {
//     QList<NPoint> _listPoint;
//     nreal _length = line.length();
//     nreal _interval = this->interval_;
//     if( equidistant )
//         _interval = this->equidistantIterval( _length );
//     nreal _len;
//     NAngle _angle = line.angle();
//     if( !_interval.compare( nreal() ) )
//         this->calcPointLineSection( line, _listPoint, _len, _length, _interval );
//     _listPoint.append( line.stop() );
//     return _listPoint;
// }
// /**
//      * @brief approximation - Метод разбивает дугу на отдельны точки.
//      * @param arc - Дуга.
//      * @param equidistant - Параметр задает способ разбиения(true - равномерное
//      * разбиение объекта на точки с перерасчетам интервала между точками,
//      * false - без перерасчета интервала между точками).
//      * @return Список точек.
//      */
// QList<NPoint> approximation( const NArc &arc, bool equidistant ){
//     QList<NPoint> _listPoint;
//     nreal _length = arc.lengthArc();
//     nreal _interval = this->interval_;
//     if( equidistant )
//         _interval = this->equidistantIterval( _length );
//     nreal _lenStage = _length / arc.radius();
//     NAngle _delStart;
//     NAngle _delAngle( _interval / arc.radius() );
//     NAngle _angleStart = arc.angleStart();
//     if( !_interval.compare( nreal() ) )
//         this->calcPointArc( arc, _listPoint, _delStart, _lenStage,
//                            _delAngle, _angleStart );
//     _listPoint.append( NPoint::newPoint( arc.angleStop(), arc.radius(),
//                                        arc.center() ) );

//     return _listPoint;
// }


// /**
//      * @brief equidistantIterval - Метод перерасчитывает интервал между точками.
//      * @param length - длина участка.
//      * @return Новый интервал между точками.
//      */
// nreal equidistantIterval( const nreal &length ){
//     nreal _c = ( length / this->interval_ ).entier();
//     if( _c.compare( nreal() ) )
//         return nreal();
//     return length / _c;
// }

// /**
//      * @brief calcPointLineSection - Метод заполняет контейнер новыми точками
//      * для отрезка.
//      * @param lineSection - Отрезок.
//      * @param listPoint - Контейнер где будут храниться точки.
//      * @param lenIterator - Изменяющийся интервал от начало отрезка и
//      * увеличивающийся с каждой точки на велечину interval.
//      * @param lenStage - Длинна линии.
//      * @param interval - Интервал между точками.
//      */
// void calcPointLineSection( const NLineSection &lineSection,
//                           QList<NPoint> &listPoint, nreal &lenIterator,
//                           const nreal &lenStage,
//                           const nreal &interval ){
//     while( lenIterator < lenStage )
//     {
//         listPoint.append( std::move( NPoint::newPoint( lineSection.angle(),
//                                                     lenIterator, lineSection.start() ) ) );
//         lenIterator += interval;
//     }
// }

// /**
//      * @brief calcPointArc - Метод заполняет контейнер новыми точками для дуги.
//      * @param arc - Дуга.
//      * @param listPoint - Контейнер где будут храниться точки.
//      * @param lenIterator - Изменяющийся интервал от начало отрезка и
//      * увеличивающийся с каждой точки на велечину interval.
//      * @param lenStage - Длинна дуги.
//      * @param interval - Интервал между точками.
//      * @param angleStart - Направления на начало дуги от центра.
//      */
// void calcPointArc( const NArc &arc, QList<NPoint> &listPoint,
//                   NAngle &lenIterator, const nreal &lenStage,
//                   const NAngle &interval,
//                   const NAngle &angleStart ){
//     auto _while = [&]( const nreal &sign )
//     {
//         while( lenIterator < lenStage )
//         {
//             listPoint.append( std::move( NPoint::newPoint(
//                 angleStart + lenIterator * sign,
//                 arc.radius(), arc.center() ) ) );
//             lenIterator += interval;
//         }
//     };
//     if( arc.direct() == NDirect::EN_D_LEFT )
//         _while( nreal( -1.0 ) );
//     else
//         _while( nreal( 1.0 ) );
// }










// }




// /**
//      * @brief approximation - Метод разбивает список фигур на отдельны точки.
//      * @param lFigure - Список фигур.
//      * @param equidistant - Параметр задает способ разбиения(true - равномерное
//      * разбиение объекта на точки с перерасчетам интервала между точками,
//      * false - без перерасчета интервала между точками).
//      * @return Список точек.
//      */
// QList<NPoint> approximation( const QList<NFigure> &lFigure,
//                             bool equidistant )
// {
//     if( lFigure.isEmpty() )
//         return QList<NPoint>();
//     QList<NPoint> _listPoint;
//     nreal _length = NFigure::lehghtFigure( lFigure );
//     nreal _interval = this->interval_;
//     if( equidistant )
//         _interval = this->equidistantIterval( _length );
//     if( !_interval.compare( nreal() ) )
//         return _listPoint;
//     nreal _ds;
//     for( auto i : lFigure )
//     {
//         if( i.figureArc() )
//         {
//             nreal _lenStage = i.arc().lengthArc();
//             nreal _len;
//             if( _ds > nreal() )
//                 _len = _interval - _ds;
//             if( _len > _lenStage )
//             {
//                 _ds = _lenStage + _lenStage;
//                 continue;
//             }
//             _lenStage = _lenStage / i.arc().radius();
//             NAngle _delStart( _len / i.arc().radius() );
//             NAngle _delAngle( _interval / i.arc().radius() );
//             NAngle _angleStart = i.arc().angleStart();
//             this->calcPointArc( i.arc(), _listPoint, _delStart, _lenStage,
//                                _delAngle, _angleStart );
//             _ds = i.arc().lengthArc() - ( _delStart - _delAngle ).r()
//                                             * i.arc().radius();
//         }
//         else if( i.figureLineSection() )
//         {
//             nreal _lenStage = i.lineSection().length();
//             nreal _len;
//             if( _ds > nreal() )
//                 _len = _interval - _ds;
//             if( _len > _lenStage )
//             {
//                 _ds = _lenStage + _lenStage;
//                 continue;
//             }
//             this->calcPointLineSection( i.lineSection(), _listPoint, _len,
//                                        _lenStage, _interval );
//             _ds = _lenStage - ( _len - _interval );
//         }
//     }
//     return _listPoint;
// }






//QList<double> NApproximation::approxData( const double &dStart, const double &dStop, const double &lenght, const double &interval )
//{
//    QList<double> _list;
//    double _dlen = 0;
//    if( lenght > 0 )
//    {
//        _dlen = ( dStop - dStart ) / lenght;
//    }
//    else
//    {
//        _dlen = 1.0;
//    }
//    double _len = 0.0;
//    while( _len < lenght )
//    {
//        _list.append( dStart + _dlen * _len );
//        _len += interval;
//    }
//    _list.append( dStop );
//    return _list;
//}

//QList<double> NApproximation::approxData( const double &dStart, const double &dStop, const double &lenght, const double &interval, double &del )
//{
//    QList<double> _list;
//    double _dlen = 0;
//    if( lenght > 0 )
//    {
//        _dlen = ( dStop - dStart ) / lenght;
//    }
//    else
//    {
//        _dlen = 1.0;
//    }
//    double _len = interval - del;
//    while( _len < lenght )
//    {
//        _list.append( dStart + _dlen * _len );
//        _len += interval;
//    }
//    return _list;
//}

//QList<NPoint> NApproximation::approxIntervalLine( const NLineSection &line, double &del )
//{
//    QList<NPoint> _list;
//    double _lenStage = line.length();
//    double _len = 0;
//    if( del > 0 )
//    {
//        _len = this->interval_ - del;
//    }
//    if( _len > _lenStage )
//    {
//        del = _lenStage + _lenStage;
//        return QList<NPoint>();
//    }
//    double _angle = line.angle();
//    while( _len < _lenStage )
//    {
//        _list.append( NPoint::getCoordinate( _angle, _len, line.start() ) );
//        _len += this->interval_;
//    }
//    del = _lenStage - ( _len - this->interval_ );
//    return _list;
//}

//QList<NPoint> NApproximation::approxIntervalArc( const NArc &arc, double &del )
//{
//    QList<NPoint> _list;
//    double _lenStage = arc.lengthArc();
//    double _len = 0;
//    if( del > 0 )
//    {
//        _len = this->interval_ - del;
//    }
//    if( _len > _lenStage )
//    {
//        del = _lenStage + _lenStage;
//        return QList<NPoint>();
//    }
//    _lenStage = _lenStage / arc.radius();
//    double _delStart = _len / arc.radius();
//    double _delAngle = this->interval_ / arc.radius();
//    double _angleStart = arc.angleStart();

//    if( arc.direct() == NArc::LEFT )
//    {
//        while( _delStart < _lenStage )
//        {
//            _list.append( NPoint::getCoordinate( _angleStart - _delStart, arc.radius(), arc.center() ) );
//            _delStart += _delAngle;
//        }
//    }
//    else
//    {
//        while( _delStart < _lenStage )
//        {
//            _list.append( NPoint::getCoordinate( _angleStart + _delStart, arc.radius(), arc.center() ) );
//            _delStart += _delAngle;
//        }
//    }
//    del = arc.lengthArc() - ( _delStart - _delAngle ) * arc.radius();
//    return _list;
//}














#endif // APPROXIMATION_ALGORITHM_H
