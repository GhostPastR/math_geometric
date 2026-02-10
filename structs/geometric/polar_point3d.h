#ifndef AGL_STRUCT_POINT_POLAR_POINT3D_H
#define AGL_STRUCT_POINT_POLAR_POINT3D_H

#include "algorithm/math_algorithm.h"
#include "structs/geometric/polar_point2d.h"
#include <format>
#include "system/traits.h"

namespace agl::point::polar {

template<typename TypePsi, typename TypeFi, typename TypeZ>
class polar3d : public polar2d<TypePsi, TypeFi>{
public:
    constexpr polar3d() : polar2d<TypePsi, TypeFi>(){}
    constexpr polar3d(const TypePsi &psi, const TypeFi &fi, const TypeZ &z) : polar2d<TypePsi, TypeFi>(psi, fi, z){
        set_z(psi);
    }

    constexpr auto z() const{
        return z_;
    }
    constexpr void set_z(const TypeZ &z){
        z_ = z;
    }

    constexpr friend bool operator==(const polar3d &point1, const polar3d &point2){
        return point1.compare(point2);
    }

protected:
    TypePsi psi_{};
    TypeFi fi_;
    TypeZ z_{};

    constexpr bool compare(const polar3d &point) const{
        return polar2d<TypePsi, TypeFi>::compare(point) && algorithm::compare(z_, point.z_);
    }
};

}

template<typename TypePsi, typename TypeFi, typename TypeZ>
constexpr std::ostream& operator<<(std::ostream& os, const agl::point::polar::polar3d<TypePsi, TypeFi, TypeZ> &point){
    os << std::format("psi={} fi={} z={}",
                      agl::traits::value<TypePsi>::get(point.psi()),
                      agl::traits::value<TypePsi>::get(point.fi()),
                      agl::traits::value<TypePsi>::get(point.z()));
    return os;
}



#endif // AGL_STRUCT_POINT_POLAR_POINT3D_H
