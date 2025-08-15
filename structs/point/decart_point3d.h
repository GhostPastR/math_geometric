#ifndef AGL_STRUCT_POINT_DECART_POINT3D_H
#define AGL_STRUCT_POINT_DECART_POINT3D_H

#include <format>
#include "structs/point/decart_point2d.h"


namespace agl::point::decart {

template<typename Type>
class point3d : public point2d<Type>{
public:
    constexpr point3d() : point2d<Type>(){}
    constexpr point3d(auto x, auto y, auto z) : point2d<Type>(x,y){
        set_z(z);
    }
    constexpr auto z() const{
        return z_;
    }
    constexpr void set_z(auto z){
        z_ = z;
    }

    constexpr bool is_valid() const{
        return point2d<Type>::is_valid() && algorithm::is_valid(z_);
    }

    constexpr friend bool operator==(const point3d &point1, const point3d &point2){
        return point1.compare(point2);
    }

protected:
    Type z_{};

    constexpr bool compare(const point3d &point) const{
        return point2d<Type>::compare(point) && algorithm::compare(z_, point.z_);
    }
};

}


template<typename Type>
constexpr std::ostream& operator<<(std::ostream& os, const agl::point::decart::point3d<Type> &point){
    os << std::format("x={} y={} z={}",
                      agl::system::tag::value<Type>::get(point.x()),
                      agl::system::tag::value<Type>::get(point.y()),
                      agl::system::tag::value<Type>::get(point.z()));
    return os;
}



#endif // AGL_STRUCT_POINT_DECART_POINT3D_H
