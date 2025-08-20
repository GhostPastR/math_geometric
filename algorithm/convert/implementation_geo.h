#ifndef AGL_ALGORITHM_CONVERT_IMPLEMENTATION_GEO_H
#define AGL_ALGORITHM_CONVERT_IMPLEMENTATION_GEO_H

#include "algorithm/math_algorithm.h"
#include "algorithm/traits.h"

//https://geoproj.ru/
//https://racurs.ru/downloads/documentation/gost_r_32453-2017.pdf

namespace agl::algorithm::dispatch::geo {

template<typename Point, typename PointOut, typename CoordinateSystemPoint, typename CoordinateSystemPointOut, std::size_t Dimension>
struct convert{
    inline constexpr static auto get(const Point &){
        static_assert(false, "No 'convert' calculations have been implemented for these objects.");
    }
};

template<typename Point, typename PointOut>
struct convert<Point, PointOut, sc_default, polar, 2>{
    inline constexpr static auto get(const Point &a, const Point &b = {}){
        using Type = traits::traits_point::type_property<Point>::type;
        const auto a_latitude = traits::traits_point::access_point<Point, 0>::get(a);
        const auto a_longitude = traits::traits_point::access_point<Point, 1>::get(a);
        const auto b_latitude = traits::traits_point::access_point<Point, 0>::get(b);
        const auto b_longitude = traits::traits_point::access_point<Point, 1>::get(b);

        if(a == b){
            return PointOut{};
        }
        const auto _e2 = axis::eccentricity2_1<Type>();
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
        const auto _k2 = axis::eccentricity2_2<Type>() * _a0;
        const auto _k2_2 = _k2 * _k2;

        const auto _range = ( 1.0 + _k2 / 4.0 - 3.0 * _k2_2 / 64.0 ) * axis::semiminor_axis<Type> * _g -
                      ( _k2 / 4.0 - _k2_2 / 16.0 ) * axis::semiminor_axis<Type>
                          * std::sin(_g) * cos( 2 * _g1 + _g ) -
                      ( _k2_2 / 128.0 ) * axis::semiminor_axis<Type>
                          * std::sin(2 * _g) * cos( 4 * _g1 + 2 * _g );

        return PointOut{_range, _omnibearing};
    }
};

template<typename Point, typename PointOut>
struct convert<Point, PointOut, polar, sc_default, 2>{
    inline constexpr static auto get(const Point &object){
        static_assert(false, "Error release.");
    }
};


template<typename Point, typename PointOut>
struct convert<Point, PointOut, wgs_84, polar, 2>{
    inline constexpr static auto get(const Point &){
        static_assert(false, "Error release.");
    }
};

template<typename Point, typename PointOut>
struct convert<Point, PointOut, polar, wgs_84, 2>{
    inline constexpr static auto get(const Point &){
        static_assert(false, "Error release.");
    }
};

template<typename Point, typename PointOut>
struct convert<Point, PointOut, pz_90_02, polar, 2>{
    inline constexpr static auto get(const Point &){
        static_assert(false, "Error release.");
    }
};

template<typename Point, typename PointOut>
struct convert<Point, PointOut, polar, pz_90_02, 2>{
    inline constexpr static auto get(const Point &){
        static_assert(false, "Error release.");
    }
};

}

#endif // AGL_ALGORITHM_CONVERT_IMPLEMENTATION_GEO_H
