#ifndef AGL_ALGORITHM_CONVERT_IMPLEMENTATION_GEO_H
#define AGL_ALGORITHM_CONVERT_IMPLEMENTATION_GEO_H

#include "algorithm/math_algorithm.h"
#include "system/system_concept.h"
#include "system/traits.h"

//https://geoproj.ru/
//https://racurs.ru/downloads/documentation/gost_r_32453-2017.pdf

namespace agl::algorithm::dispatch::primitive {

template<c_value X1,
         c_value Y1,
         c_value X2,
         c_value Y2,
         c_value Range,
         c_value Omnibearing>
constexpr auto cartesian_to_polar(const X1 &x1, const Y1 &y1, const X2 &x2, const Y2 &y2)
    -> std::pair<Range, Omnibearing>{
    return {std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2)), std::atan2(y2 - y1, x2 - x1)};
}

template<c_value Range,
         c_value Omnibearing,
         c_value X1,
         c_value Y1,
         c_value X2,
         c_value Y2>
constexpr auto polar_to_cartesian(const Range &range, const Omnibearing &omnibearing, const X1 &x, const Y1 &y)
    -> std::pair<X2, X2>{
    return {x + range * std::sin(omnibearing), y + range * std::cos(omnibearing)};
}


template<c_value Lat1,
         c_value Long1,
         c_value Lat2,
         c_value Long2,
         c_value Range,
         c_value Omnibearing,
         typename SystemGeographical>
constexpr auto geo_to_polar(const Lat1 &a_latitude, const Long1 &a_longitude,
                            const Lat2 &b_latitude, const Long2 &b_longitude)
    -> std::pair<Range, Omnibearing>{
    if(compare(a_latitude, b_latitude) && compare(a_longitude, b_longitude)){
        return {a_latitude, a_longitude};
    }
    const auto _e2 = axis::eccentricity2_1<Range>();
    auto _sinLat = std::sin(a_latitude);
    auto _os = sqrt( 1.0 - _e2 * _sinLat * _sinLat );
    const auto _sinU1 = _sinLat * sqrt( 1.0 - _e2 ) / _os;
    const auto _cosU1 = std::cos(a_latitude) / _os;
    _sinLat = std::sin(b_latitude);
    _os = sqrt( 1.0 - _e2 * _sinLat * _sinLat );
    const auto _sinU2 = _sinLat * sqrt( 1.0 - _e2 ) / _os;
    const auto _cosU2 =  std::cos(b_latitude) / _os;

    const auto _dL = (b_longitude - a_longitude);
    auto _omnibearing = std::atan2(_cosU2 * std::sin( _dL ),
                                   algorithm::determine(_cosU1, _sinU1, _cosU2 * std::cos(_dL), _sinU2) );
    auto _g = acos(algorithm::determine(_sinU1, -_cosU1, _cosU2 * std::cos(_dL), _sinU2));
    const auto _sinA0 = _cosU1 * std::sin(_omnibearing);
    auto _a0 = std::cos(std::asin(_sinA0));
    _a0 *= _a0;
    const auto _dY = _dL + _sinA0 * ( 0.5 + _e2 / 8.0 - ( _e2 / 16.0 ) * _a0 ) * _e2 * _g;

    _omnibearing = std::atan2(_cosU2 * std::sin(_dY),
                              algorithm::determine(_cosU1, _sinU1, _cosU2 * std::cos(_dY), _sinU2));
    _g = std::acos(algorithm::determine(_sinU1, -_cosU1, _cosU2 * std::cos(_dY), _sinU2));
    _a0 = std::cos(std::asin(std::sin(_omnibearing) * _cosU1));
    _a0 *= _a0;
    if( _omnibearing < 0 ){
        _omnibearing += 2 * algorithm::pi<decltype(_omnibearing)>;
    }
    const auto _g1 = std::atan2(_sinU1 , (_cosU1 * std::cos(_omnibearing)));
    const auto _k2 = axis::eccentricity2_2<Range>() * _a0;
    const auto _k2_2 = _k2 * _k2;

    const auto _range = ( 1.0 + _k2 / 4.0 - 3.0 * _k2_2 / 64.0 ) * axis::semiminor_axis<Range> * _g -
                        ( _k2 / 4.0 - _k2_2 / 16.0 ) * axis::semiminor_axis<Range>
                            * std::sin(_g) * cos( 2 * _g1 + _g ) -
                        ( _k2_2 / 128.0 ) * axis::semiminor_axis<Range>
                            * std::sin(2 * _g) * cos( 4 * _g1 + 2 * _g );

    return {_range, _omnibearing};
}

template<c_value Range,
         c_value Omnibearing,
         c_value Lat1,
         c_value Long1,
         c_value Lat2,
         c_value Long2,
         typename SystemGeographical>
constexpr auto polar_to_geo(const Range &range, const Omnibearing &omnibearing,
                            const Lat1 &latitude, const Long1 &longitude)
    -> std::pair<Lat2, Long2>{
    if(algorithm::compare(range, Range{}) && (omnibearing == Omnibearing{})){
        return {range, omnibearing};
    }

    const auto _e2 = axis::eccentricity2_1<Range>();
    const auto _sinLat = std::sin(latitude);
    const auto _os = sqrt(1.0 - _e2 * _sinLat * _sinLat);
    const auto _sqrtE2 = sqrt(1.0 - _e2);
    const auto _sinU1 = _sinLat * _sqrtE2 / _os;
    const auto _cosU1 = std::cos(latitude) / _os;
    const auto _cosOmn = std::cos(omnibearing);
    const auto _sinOmn = std::sin(omnibearing);

    const auto _a0 = asin(_cosU1 * _sinOmn);
    auto _sin2q1 = 0.0;
    auto _cos2q1 = 1.0;
    if(!algorithm::compare(_sinU1, 0.0)){
        double _ctgQ1 = _cosU1 * _cosOmn / _sinU1;
        _sin2q1 = 2.0 * _ctgQ1 / (_ctgQ1 * _ctgQ1 + 1.0);
        _cos2q1 = (_ctgQ1 * _ctgQ1 - 1.0) / (_ctgQ1 * _ctgQ1 + 1.0);
    }

    const auto _cos2a0 = std::cos(_a0) * std::cos(_a0);
    const auto _k2 = axis::eccentricity2_2<Range>() * _cos2a0;

    const auto _k2_2 = _k2 * _k2;
    const auto _kA = 1.0 + _k2 / 4.0 - 3.0 * _k2_2 / 64.0;
    const auto _kBA = (_k2 / 4.0 - _k2_2 / 16.0) / _kA;
    const auto _kC = _k2_2 / 128.0;

    auto _q = range / (_kA * axis::semiminor_axis<Range>);
    const auto _qD = _q;
    auto _cos2q1_q = algorithm::determine(_cos2q1, _sin2q1, std::sin(_q), std::cos(_q));
    _q = _qD + _kBA * std::sin(_q) * _cos2q1_q;
    _cos2q1_q = algorithm::determine(_cos2q1, _sin2q1, std::sin(_q), std::cos(_q));
    const auto _cos4q1_2q = 2 * _cos2q1_q * _cos2q1_q - 1;
    _q = _qD + _kBA * std::sin(_q) * _cos2q1_q + (_kC / _kA) * std::sin(2 * _q) * _cos4q1_2q;
    _cos2q1_q = algorithm::determine(_cos2q1, _sin2q1, std::sin(_q), std::cos(_q));

    const auto _cosQ = std::cos(_q);
    const auto _sinQ = std::sin(_q) * _cosOmn;

    const auto _cosU2 = algorithm::determine(_cosU1, _sinU1, _sinQ, _cosQ);
    const auto _dY = std::atan2(std::sin(_q) * _sinOmn , _cosU2);
    const auto _sinU2 = algorithm::determine(_sinU1, -_cosU1, _sinQ, _cosQ);

    const auto new_latitude = std::atan(_sinU2 * std::cos(_dY) / (_sqrtE2 * _cosU2));
    auto new_longitude = longitude + _dY - std::sin(_a0) * ((0.5 + _e2 / 8.0 - (_e2 / 16.0) * _cos2a0)
                                                                * _e2 * _q + _e2 * _e2 * _cos2a0 / 16.0 * std::sin(_q) * _cos2q1_q);

    if(new_longitude > algorithm::pi<Range>){
        while(new_longitude > algorithm::pi<Range>){
            new_longitude -=2 * algorithm::pi<Range>;
        }
    }
    else{
        while(new_longitude < -algorithm::pi<Range>){
            new_longitude += 2 * algorithm::pi<Range>;
        }
    }

    return {new_latitude, new_longitude};
}


// template<typename Point, typename PointOut>
// struct convert<Point, PointOut, agl::system_coordinat::geo::wgs_84, agl::system_coordinat::polar, 2>{
//     inline constexpr static auto get(const Point &){
//         static_assert(false, "Error release.");
//     }
// };

// template<typename Point, typename PointOut>
// struct convert<Point, PointOut, agl::system_coordinat::polar, agl::system_coordinat::geo::wgs_84, 2>{
//     inline constexpr static auto get(const Point &){
//         static_assert(false, "Error release.");
//     }
// };

// template<typename Point, typename PointOut>
// struct convert<Point, PointOut, agl::system_coordinat::geo::pz_90_02, agl::system_coordinat::polar, 2>{
//     inline constexpr static auto get(const Point &){
//         static_assert(false, "Error release.");
//     }
// };

// template<typename Point, typename PointOut>
// struct convert<Point, PointOut, agl::system_coordinat::polar, agl::system_coordinat::geo::pz_90_02, 2>{
//     inline constexpr static auto get(const Point &){
//         static_assert(false, "Error release.");
//     }
// };

}

#endif // AGL_ALGORITHM_CONVERT_IMPLEMENTATION_GEO_H
