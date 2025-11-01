#ifndef AGL_STRUCT_POINT_DECART_POINT3D_H
#define AGL_STRUCT_POINT_DECART_POINT3D_H

#include <format>
#include "system/traits.h"
#include "structs/geometric/decart_point2d.h"


namespace agl::point::decart {

template<typename Type>
class point3d : public model_point<Type, agl::system_coordinat::cartesian, 3>{
public:
    constexpr point3d() : model_point<Type, agl::system_coordinat::cartesian, 3>(){}
    constexpr point3d(Type x, Type y, Type z) : model_point<Type, agl::system_coordinat::cartesian, 3>({x,y,z}){}
    constexpr auto x() const{
        return this->template value<0>();
    }
    constexpr void set_x(Type x){
        this->template set_value<0>(x);
    }
    constexpr auto y() const{
        return this->template value<1>();
    }
    constexpr void set_y(Type y){
        this->template set_value<1>(y);
    }
    constexpr auto z() const{
        return this->template value<2>();
    }
    constexpr void set_z(Type z){
        this->template set_value<2>(z);
    }

    constexpr friend bool operator==(const point3d &point1, const point3d &point2){
        return point1.compare(point2);
    }
};

}


template<typename Type>
constexpr std::ostream& operator<<(std::ostream& os, const agl::point::decart::point3d<Type> &point){
    os << std::format("x={} y={} z={}",
                      agl::traits::value<Type>::get(point.x()),
                      agl::traits::value<Type>::get(point.y()),
                      agl::traits::value<Type>::get(point.z()));
    return os;
}



#endif // AGL_STRUCT_POINT_DECART_POINT3D_H
