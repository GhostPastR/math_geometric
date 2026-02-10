#ifndef AGL_ALGORITHM_CONVERT_IMPLEMENTATION_GEO_H
#define AGL_ALGORITHM_CONVERT_IMPLEMENTATION_GEO_H

#include "algorithm/math_algorithm.h"
#include "algorithm/traits.h"

//https://geoproj.ru/
//https://racurs.ru/downloads/documentation/gost_r_32453-2017.pdf

namespace agl::algorithm::dispatch::geo {

template<typename Point, typename Turning, typename Range, typename NewPoint, typename CoordinateSystem, std::size_t Dimension>
struct create_point{
    inline constexpr static auto get(const Point &point, const Turning &turning, const Range &range){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<typename Point, typename Turning, typename Range, typename NewPoint>
struct create_point<Point, Turning, Range, NewPoint, sc_default, 2>{
    inline constexpr static auto get(const Point &point, const Turning &turning, const Range &range){
        using Type = traits::type_coordinate<Point>::type;
        const auto latitude = traits::access_point<Point, 0>::get(point);
        const auto longitude = traits::access_point<Point, 1>::get(point);

        if(algorithm::compare(range, Range{}) && algorithm::compare(range, Turning{})){
            return NewPoint{latitude, longitude};
        }

        const auto _e2 = eccentricity2_1<Type>();
        const auto _sinLat = std::sin(latitude);
        const auto _os = sqrt(1.0 - _e2 * _sinLat * _sinLat);
        const auto _sqrtE2 = sqrt(1.0 - _e2);
        const auto _sinU1 = _sinLat * _sqrtE2 / _os;
        const auto _cosU1 = std::cos(latitude) / _os;
        const auto _cosOmn = std::cos(turning);
        const auto _sinOmn = std::sin(turning);

        const auto _a0 = std::asin(_cosU1 * _sinOmn);
        auto _sin2q1 = 0.0;
        auto _cos2q1 = 1.0;
        if(!algorithm::compare(_sinU1, 0.0)){
            double _ctgQ1 = _cosU1 * _cosOmn / _sinU1;
            _sin2q1 = 2.0 * _ctgQ1 / (_ctgQ1 * _ctgQ1 + 1.0);
            _cos2q1 = (_ctgQ1 * _ctgQ1 - 1.0) / (_ctgQ1 * _ctgQ1 + 1.0);
        }

        const auto _cos2a0 = std::cos(_a0) * std::cos(_a0);
        const auto _k2 = eccentricity2_2<Type>() * _cos2a0;

        const auto _k2_2 = _k2 * _k2;
        const auto _kA = 1.0 + _k2 / 4.0 - 3.0 * _k2_2 / 64.0;
        const auto _kBA = (_k2 / 4.0 - _k2_2 / 16.0) / _kA;
        const auto _kC = _k2_2 / 128.0;

        auto _q = range / (_kA * axis::semiminor_axis<Type>);
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
        auto new_longitude = longitude + _dY - std::sin(_a0) * ((0.5 + _e2 / 8.0 - (_e2 / 16.0) * _cos2a0) * _e2 * _q + _e2 * _e2 * _cos2a0 / 16.0 * std::sin(_q) * _cos2q1_q);

        if(new_longitude > algorithm::pi<decltype(new_longitude)>){
            while(new_longitude > algorithm::pi<decltype(new_longitude)>){
                new_longitude -=2 * algorithm::pi<decltype(new_longitude)>;
            }
        }
        else{
            while(new_longitude < -algorithm::pi<decltype(new_longitude)>){
                new_longitude += 2 * algorithm::pi<decltype(new_longitude)>;
            }
        }
        return NewPoint(new_latitude, new_longitude);
    }
};

}

#endif // AGL_ALGORITHM_CONVERT_IMPLEMENTATION_GEO_H
