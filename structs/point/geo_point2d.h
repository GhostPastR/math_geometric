#ifndef AGL_STRUCT_POINT_GEO_POINT2D_H
#define AGL_STRUCT_POINT_GEO_POINT2D_H

#include <format>
#include "system/tag.h"
#include "algorithm/math_algorithm.h"


namespace agl::point::geo {

template<typename Angle>
class point_geo2d{
public:
    constexpr point_geo2d(){}
    constexpr point_geo2d(const Angle &latitude, const Angle &longitude){
        set_latitude(latitude);
        set_longitude(longitude);
    }

    constexpr auto latitude() const{
        return latitude_;
    }
    constexpr void set_latitude(const Angle &latitude){
        latitude_ = latitude;
    }
    constexpr auto longitude() const{
        return longitude_;
    }
    constexpr void set_longitude(const Angle &longitude){
        longitude_ = longitude;
    }

    constexpr friend bool operator==(const point_geo2d &point1, const point_geo2d &point2){
        return point1.compare(point2);
    }

protected:
    Angle latitude_;
    Angle longitude_;

    constexpr bool compare(const point_geo2d &point) const{
        return algorithm::compare(latitude_, point.latitude_) && algorithm::compare(longitude_, point.longitude_);
    }
};

}


template<typename Angle>
constexpr std::ostream& operator<<(std::ostream& os, const agl::point::geo::point_geo2d<Angle> &point){
    os << std::format("latitude={} longitude={}",
                      agl::system::tag::value<Angle>::get(point.latitude()),
                      agl::system::tag::value<Angle>::get(point.longitude()));
    return os;
}

#endif // AGL_STRUCT_POINT_GEO_POINT2D_H
