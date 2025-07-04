#ifndef GEO_ALGORITHM_H
#define GEO_ALGORITHM_H

#include "../system/system_concept.h"
#include "../algorithm/point_algorithm.h"
#include "math_algorithm.h"
#include <algorithm>
#include <vector>

namespace agl::geo_algo {

namespace {

template <std::floating_point Type> inline constexpr Type semiminor_axis;
template<> inline constexpr double semiminor_axis<double> = 6356751.362;
template<> inline constexpr float semiminor_axis<float> = 6356751.362;

template <std::floating_point Type> inline constexpr Type semimajor_axis;
template<> inline constexpr double semimajor_axis<double> = 6378136.;
template<> inline constexpr float semimajor_axis<float> = 6378136;

template<std::floating_point Type>
constexpr Type eccentricity2_1(){
    return (semiminor_axis<Type> * semiminor_axis<Type> - semimajor_axis<Type> * semimajor_axis<Type>)
    / (semiminor_axis<Type> * semiminor_axis<Type>);
}

template<std::floating_point Type>
constexpr Type eccentricity2_2(){
    return (semimajor_axis<Type> * semimajor_axis<Type> - semiminor_axis<Type> * semiminor_axis<Type>)
    / (semiminor_axis<Type> * semiminor_axis<Type>);
}

}

template<std::floating_point Type, std::floating_point TypeAngle, c_point2d_geo PointGeo,
         c_function_angle<Type> ClassFunc = algorithm::function_angle<Type>>
constexpr PointGeo common_survey_comp(Type range, TypeAngle omnibearing, const PointGeo &reference_point){
    if(algorithm::compare(range, 0.) && (omnibearing == TypeAngle())){
        return reference_point;
    }

    const auto _e2 = eccentricity2_1<Type>();
    const auto _sinLat = ClassFunc::sin(reference_point.latitude());
    const auto _os = sqrt(1.0 - _e2 * _sinLat * _sinLat);
    const auto _sqrtE2 = sqrt(1.0 - _e2);
    const auto _sinU1 = _sinLat * _sqrtE2 / _os;
    const auto _cosU1 = ClassFunc::cos(reference_point.latitude()) / _os;
    const auto _cosOmn = ClassFunc::cos(omnibearing);
    const auto _sinOmn = ClassFunc::sin(omnibearing);

    const auto _a0 = asin(_cosU1 * _sinOmn);
    auto _sin2q1 = 0.0;
    auto _cos2q1 = 1.0;
    if(!algorithm::compare(_sinU1, 0.0)){
        double _ctgQ1 = _cosU1 * _cosOmn / _sinU1;
        _sin2q1 = 2.0 * _ctgQ1 / (_ctgQ1 * _ctgQ1 + 1.0);
        _cos2q1 = (_ctgQ1 * _ctgQ1 - 1.0) / (_ctgQ1 * _ctgQ1 + 1.0);
    }

    const auto _cos2a0 = ClassFunc::cos(_a0) * ClassFunc::cos(_a0);
    const auto _k2 = eccentricity2_2<Type>() * _cos2a0;

    const auto _k2_2 = _k2 * _k2;
    const auto _kA = 1.0 + _k2 / 4.0 - 3.0 * _k2_2 / 64.0;
    const auto _kBA = (_k2 / 4.0 - _k2_2 / 16.0) / _kA;
    const auto _kC = _k2_2 / 128.0;

    auto _q = range / (_kA * semiminor_axis<Type>);
    const auto _qD = _q;
    auto _cos2q1_q = _cos2q1 * ClassFunc::cos(_q) - _sin2q1 * ClassFunc::sin(_q);
    _q = _qD + _kBA * ClassFunc::sin(_q) * _cos2q1_q;
    _cos2q1_q = _cos2q1 * ClassFunc::cos(_q) - _sin2q1 * ClassFunc::sin(_q);
    const auto _cos4q1_2q = 2 * _cos2q1_q * _cos2q1_q - 1;
    _q = _qD + _kBA * ClassFunc::sin(_q) * _cos2q1_q + (_kC / _kA) * ClassFunc::sin(2 * _q) * _cos4q1_2q;
    _cos2q1_q = _cos2q1 * ClassFunc::cos(_q) - _sin2q1 * ClassFunc::sin(_q);

    const auto _cosQ = ClassFunc::cos(_q);
    const auto _sinQ = ClassFunc::sin(_q) * _cosOmn;

    const auto _cosU2 = _cosU1 * _cosQ - _sinU1 * _sinQ;
    const auto _dY = ClassFunc::atan2(ClassFunc::sin(_q) * _sinOmn , _cosU2);
    const auto _sinU2 = _sinU1 * _cosQ + _cosU1 * _sinQ;

    const auto latitude = ClassFunc::atan(_sinU2 * ClassFunc::cos(_dY) / (_sqrtE2 * _cosU2));
    auto longitude = reference_point.longitude() + _dY - ClassFunc::sin(_a0) * ((0.5 + _e2 / 8.0 - (_e2 / 16.0) * _cos2a0)
                                                                                    * _e2 * _q + _e2 * _e2 * _cos2a0 / 16.0 * ClassFunc::sin(_q) * _cos2q1_q);

    if(longitude > algorithm::pi<decltype(longitude)>){
        while(longitude > algorithm::pi<decltype(longitude)>){
            longitude -=2 * algorithm::pi<decltype(longitude)>;
        }
    }
    else{
        while(longitude < -algorithm::pi<decltype(longitude)>){
            longitude += 2 * algorithm::pi<decltype(longitude)>;
        }
    }
    using Angle = PointGeo::type_coordinate;
    return PointGeo(Angle(latitude), Angle(longitude));
}

template<c_point2d_geo PointGeo,
         c_function_angle<typename PointGeo::type_coordinate> ClassFunc = algorithm::function_angle<typename PointGeo::type_coordinate>>
constexpr auto geographic_inverse(const PointGeo &start, const PointGeo &stop)
    -> std::tuple<typename PointGeo::type_coordinate, typename PointGeo::type_coordinate>{
    using TypeAngle = PointGeo::type_coordinate;
    if(start == stop){
        return {};
    }
    const auto _e2 = eccentricity2_1<TypeAngle>();
    auto _sinLat = ClassFunc::sin(start.latitude());
    auto _os = sqrt( 1.0 - _e2 * _sinLat * _sinLat );
    const auto _sinU1 = _sinLat * sqrt( 1.0 - _e2 ) / _os;
    const auto _cosU1 = ClassFunc::cos(start.latitude()) / _os;
    _sinLat = ClassFunc::sin(stop.latitude());
    _os = sqrt( 1.0 - _e2 * _sinLat * _sinLat );
    const auto _sinU2 = _sinLat * sqrt( 1.0 - _e2 ) / _os;
    const auto _cosU2 =  ClassFunc::cos(stop.latitude()) / _os;

    const auto _dL = (stop.longitude() - start.longitude());

    auto _p = _cosU2 * ClassFunc::sin( _dL );
    auto _q = _cosU1 * _sinU2 - _sinU1 * _cosU2 * ClassFunc::cos(_dL);
    auto _n = _sinU1 * _sinU2 + _cosU1 * _cosU2 * ClassFunc::cos(_dL);
    auto _omnibearing = ClassFunc::atan2( _p , _q );
    auto _g = acos( _n );
    const auto _sinA0 = _cosU1 * ClassFunc::sin(_omnibearing);
    auto _a0 = ClassFunc::cos(ClassFunc::asin(_sinA0));
    _a0 *= _a0;
    const auto _dY = _dL + _sinA0 * ( 0.5 + _e2 / 8.0 - ( _e2 / 16.0 ) * _a0 ) * _e2 * _g;

    _p = _cosU2 * ClassFunc::sin(_dY);
    _q = _cosU1 * _sinU2 - _sinU1 * _cosU2 * ClassFunc::cos(_dY);
    _n = _sinU1 * _sinU2 + _cosU1 * _cosU2 * ClassFunc::cos(_dY);
    _omnibearing = ClassFunc::atan2(_p , _q);
    _g = ClassFunc::acos(_n);
    _a0 = ClassFunc::cos(ClassFunc::asin(ClassFunc::sin(_omnibearing) * _cosU1));
    _a0 *= _a0;
    if( _omnibearing < 0 ){
        _omnibearing += 2 * algorithm::pi<decltype(_omnibearing)>;
    }
    const auto _g1 = ClassFunc::atan2(_sinU1 , (_cosU1 * ClassFunc::cos(_omnibearing)));
    const auto _e2h = eccentricity2_2<TypeAngle>();
    const auto _k2 = _e2h * _a0;
    const auto _k2_2 = _k2 * _k2;

    const auto _range = ( 1.0 + _k2 / 4.0 - 3.0 * _k2_2 / 64.0 ) * semiminor_axis<TypeAngle> * _g -
                  ( _k2 / 4.0 - _k2_2 / 16.0 ) * semiminor_axis<TypeAngle>
                      * ClassFunc::sin(_g) * cos( 2 * _g1 + _g ) -
                  ( _k2_2 / 128.0 ) * semiminor_axis<TypeAngle>
                      * ClassFunc::sin(2 * _g) * cos( 4 * _g1 + 2 * _g );

    return {_range, _omnibearing};
}



template<c_point2d_geo PointGeo, c_point2d_decard Point>
constexpr PointGeo convert(const Point &point, const PointGeo &reference_poin){
    return common_survey_comp(point_algo::distance(Point(), point), point_algo::angle(Point(), point), reference_poin);
}

template<c_point2d_decard Point, c_point2d_geo PointGeo>
constexpr Point convert(const PointGeo &point, const PointGeo &reference_poin){
    auto temp = geographic_inverse(reference_poin, point);
    return point_algo::new_point(Point(), std::get<1>(temp), std::get<0>(temp));
}

template<c_point2d_polar Polar, c_point2d_geo PointGeo>
constexpr PointGeo convert(const Polar &point, const PointGeo &reference_poin){
    return common_survey_comp(point.psi(), point.fi(), reference_poin);
}

template<c_point2d_polar Polar, c_point2d_geo PointGeo>
constexpr Polar convert(const PointGeo &point, const PointGeo &reference_poin){
    auto temp = geographic_inverse(reference_poin, point);
    return Polar{std::get<0>(temp), std::get<1>(temp)};
}

template<c_half_line LineOut, c_half_line LineIn, c_point2d_geo PointGeo>
constexpr LineOut convert(const LineIn &half_line, const PointGeo &reference_poin){
    using TypeIn = decltype(half_line.start());
    using TypeOut = decltype(std::declval<LineOut>().start());
    return LineOut(convert<TypeOut, TypeIn>(half_line.start(), reference_poin), half_line.direction());
}

template<c_line_section LineOut, c_line_section LineIn, c_point2d_geo PointGeo>
constexpr LineOut convert(const LineIn &line_section, const PointGeo &reference_poin){
    using TypeIn = decltype(line_section.start());
    using TypeOut = decltype(std::declval<LineOut>().start());
    return LineOut(convert<TypeOut, TypeIn>(line_section.start(), reference_poin),
                   convert<TypeOut, TypeIn>(line_section.stop(), reference_poin));
}

template<c_arc ArcOut, c_arc ArcIn, c_point2d_geo PointGeo>
constexpr ArcOut convert(const ArcIn &arc, const PointGeo &reference_poin){
    using TypeIn = decltype(arc.center());
    using TypeOut = decltype(std::declval<ArcOut>().center());
    return ArcOut(convert<TypeOut, TypeIn>(arc.center(), reference_poin), arc.radius(), arc.start(), arc.stop());
}

template<c_circle CircleOut, c_circle CircleIn, c_point2d_geo PointGeo>
constexpr CircleOut convert(const CircleIn &circle, const PointGeo &reference_poin){
    using TypeIn = decltype(circle.center());
    using TypeOut = decltype(std::declval<CircleOut>().center());
    return CircleOut(convert<TypeOut, TypeIn>(circle.center(), reference_poin), circle.radius());
}

template<c_point2d PointOut, c_point2d PointIn, c_point2d_geo PointGeo>
constexpr std::vector<PointOut> convert(const std::vector<PointIn> &points, const PointGeo &reference_poin){
    std::vector<PointOut> temp;
    temp.reserve(points.size());
    std::transform(std::begin(points), std::end(points), std::back_inserter(temp),[&reference_poin](const auto &item){
        return convert<PointOut>(item, reference_poin);
    });
    return temp;
}

template<c_line_section LineOut, c_line_section LineIn, c_point2d_geo PointGeo>
constexpr std::vector<LineOut> convert(const std::vector<LineIn> &points, const PointGeo &reference_poin){
    std::vector<LineOut> temp;
    temp.reserve(points.size());
    std::transform(std::begin(points), std::end(points), std::back_inserter(temp),[&reference_poin](const auto &item){
        return convert<LineOut>(item, reference_poin);
    });
    return temp;
}

}

#endif // GEO_ALGORITHM_H
