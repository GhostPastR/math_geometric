#ifndef AGL_STRUCT_POINT_POLAR_POINT2D_H
#define AGL_STRUCT_POINT_POLAR_POINT2D_H

#include <format>
#include "algorithm/math_algorithm.h"

namespace agl::point::polar {

template<typename TypePsi, typename TypeFi>
class polar2d{
public:
    constexpr polar2d(){}
    constexpr polar2d(TypePsi psi, const TypeFi &fi){
        set_psi(psi);
        set_fi(fi);
    }

    constexpr auto psi() const{
        return psi_;
    }
    constexpr void set_psi(TypePsi psi){
        psi_ = psi;
    }

    constexpr auto fi() const{
        return fi_;
    }
    constexpr void set_fi(const TypeFi &fi){
        fi_ = fi;
    }

    constexpr friend bool operator==(const polar2d &point1, const polar2d &point2){
        return point1.compare(point2);
    }

protected:
    TypePsi psi_{};
    TypeFi fi_;

    constexpr bool compare(const polar2d &point) const{
        return algorithm::compare(psi_, point.psi_) && algorithm::compare(fi_, point.fi_);
    }
};

}



template<typename TypePsi, typename TypeFi>
struct std::formatter<agl::point::polar::polar2d<TypePsi, TypeFi>> {
    std::formatter<std::string> _formatter;
    constexpr auto parse(std::format_parse_context& parse_context) {
        return _formatter.parse(parse_context);
    }

    auto format(const agl::point::polar::polar2d<TypePsi, TypeFi>& point, std::format_context& format_context) const {
        return _formatter.format(std::format("PointPolar(psi={} fi={})", point.psi(), point.fi()), format_context);
    }
};


template<typename TypePsi, typename TypeFi>
constexpr std::ostream& operator<<(std::ostream& os, const agl::point::polar::polar2d<TypePsi, TypeFi> &point){
    os << std::format("psi={} fi={}", point);
    return os;
}

#endif // AGL_STRUCT_POINT_POLAR_POINT2D_H
