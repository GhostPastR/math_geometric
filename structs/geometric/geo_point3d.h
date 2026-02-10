#ifndef AGL_STRUCT_POINT_GEO_POINT3D_H
#define AGL_STRUCT_POINT_GEO_POINT3D_H

#include "algorithm/math_algorithm.h"
#include "structs/geometric/geo_point2d.h"
#include <format>

namespace agl::point::geo {

template<agl::c_value_point Angle, agl::c_value_point TypeAltitude>
class point_geo3d : public point_geo2d<Angle>{
public:
    constexpr point_geo3d() : point_geo2d<Angle>(){}
    constexpr point_geo3d(const Angle &latitude, const Angle &longitude, const TypeAltitude &altitude)
        : point_geo2d<Angle>(latitude, longitude){
        set_altitude(altitude);
    }

    constexpr auto altitude() const{
        return altitude_;
    }
    constexpr void set_altitude(auto altitude){
        altitude_ = altitude;
    }

    constexpr friend bool operator==(const point_geo3d &point1, const point_geo3d &point2){
        return point1.compare(point2);
    }

protected:
    Angle latitude_;
    Angle longitude_;
    TypeAltitude altitude_;

    constexpr bool compare(const point_geo3d &point) const{
        return point_geo2d<Angle>::compare(point) && algorithm::compare(altitude_, point.altitude_);
    }
};

}

template<typename Angle, typename TypeAltitude>
constexpr std::ostream& operator<<(std::ostream& os, const agl::point::geo::point_geo3d<Angle, TypeAltitude> &point){
    os << std::format("latitude={} longitude={} altitude={}",
                      agl::traits::value<Angle>::get(point.latitude()),
                      agl::traits::value<Angle>::get(point.longitude()),
                      agl::traits::value<TypeAltitude>::get(point.altitude()));
    return os;
}


#endif // AGL_STRUCT_POINT_GEO_POINT3D_H
