#ifndef AGL_STRUCT_POINT_DECART_POINT2D_H
#define AGL_STRUCT_POINT_DECART_POINT2D_H

#include <format>
#include "system/tag.h"
#include "model_point.h"

namespace agl::point::decart {

template<typename Type>
class point2 : public model_point<Type, agl::system_coordinat::cartesian, 2>{
public:
    constexpr point2() : model_point<Type, agl::system_coordinat::cartesian, 2>(){}
    constexpr point2(Type x, Type y) : model_point<Type, agl::system_coordinat::cartesian, 2>({x,y}){}

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

    friend constexpr bool operator==(const point2<Type> &p1, const point2<Type> &p2){
        return p1.compare(p2);
    }
};

}



template<typename Type>
struct std::formatter<agl::point::decart::point2<Type>> {
    std::formatter<std::string> _formatter;
    constexpr auto parse(std::format_parse_context& parse_context) {
        return _formatter.parse(parse_context);
    }

    auto format(const agl::point::decart::point2<Type>& point, std::format_context& format_context) const {
        return _formatter.format(std::format("Point(x={} y={})", point.x(), point.y()), format_context);
    }
};


template<typename Type>
constexpr std::ostream& operator<<(std::ostream& os, const agl::point::decart::point2<Type> &point){
    os << std::format("{}", point);
    return os;
}

#endif // AGL_STRUCT_POINT_DECART_POINT2D_H
