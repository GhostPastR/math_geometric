#ifndef AGL_STRUCT_POINT_GEO_POINT2D_H
#define AGL_STRUCT_POINT_GEO_POINT2D_H

#include <format>
#include "algorithm/math_algorithm.h"
#include "system/system_concept.h"


namespace agl::point::geo {

template<agl::c_value_point Angle>
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



template<agl::c_value_point Angle>
struct std::formatter<agl::point::geo::point_geo2d<Angle>> {
    std::formatter<std::string> _formatter;

    constexpr auto parse(std::format_parse_context& parse_context) {
        return _formatter.parse(parse_context);
    }

    auto format(const agl::point::geo::point_geo2d<Angle>& point, std::format_context& format_context) const {
        return _formatter.format(std::format("PointGeo(latitude={}, longitude={})",
                                             point.latitude(), point.longitude()), format_context);
    }
};

template<agl::c_value_point Angle>
constexpr std::ostream& operator<<(std::ostream& os, const agl::point::geo::point_geo2d<Angle> &point){
    os << std::format("{}", point);
    return os;
}

#endif // AGL_STRUCT_POINT_GEO_POINT2D_H
