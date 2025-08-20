#ifndef AGL_STRUCT_POINT_DECART_POINT2D_H
#define AGL_STRUCT_POINT_DECART_POINT2D_H

#include <format>
#include "system/tag.h"
#include "algorithm/math_algorithm.h"
#include "algorithm/traits.h"

namespace agl::point::decart {

template<typename Type>
class point2d{
public:
    constexpr point2d(){}
    constexpr point2d(auto x, auto y){
        set_x(x);
        set_y(y);
    }

    constexpr auto x() const{
        return x_;
    }
    constexpr void set_x(auto x){
        x_ = x;
    }

    constexpr auto y() const{
        return y_;
    }
    constexpr void set_y(auto y){
        y_ = y;
    }

    constexpr bool is_valid() const{
        return algorithm::is_valid(x_) && algorithm::is_valid(y_);
    }

    constexpr friend bool operator==(const point2d &point1, const point2d &point2){
        return point1.compare(point2);
    }

protected:
    Type x_{};
    Type y_{};

    constexpr bool compare(const point2d &point) const{
        return algorithm::compare(x_, point.x_) && algorithm::compare(y_, point.y_);
    }
};

}



namespace agl::traits {

template<typename Type>
struct tag<point::decart::point2d<Type>>{
    using type_tag = tag_point;
};

template<typename Type>
struct coordinate_system<point::decart::point2d<Type>>{
    using system = cartesian;
};

template<typename Type>
struct dimension<point::decart::point2d<Type>>{
    inline static constexpr std::size_t value(){
        return 2;
    }
};

namespace traits_point {

template<typename Type>
struct type_property<point::decart::point2d<Type>>{
    using type = Type;
};

template<typename Type>
struct access_point<point::decart::point2d<Type>, 0>{
    inline constexpr static auto get(const point::decart::point2d<Type> &point){
        return agl::system::tag::value<Type>::get(point.x());
    }
};

template<typename Type>
struct access_point<point::decart::point2d<Type>, 1>{
    inline constexpr static auto get(const point::decart::point2d<Type> &point){
        return agl::system::tag::value<Type>::get(point.y());
    }
};

}

}



template<typename Type>
struct std::formatter<agl::point::decart::point2d<Type>> {
    std::formatter<std::string> _formatter;
    constexpr auto parse(std::format_parse_context& parse_context) {
        return _formatter.parse(parse_context);
    }

    auto format(const agl::point::decart::point2d<Type>& point, std::format_context& format_context) const {
        return _formatter.format(std::format("Point(x={} y={})", point.x(), point.y()), format_context);
    }
};


template<typename Type>
constexpr std::ostream& operator<<(std::ostream& os, const agl::point::decart::point2d<Type> &point){
    os << std::format("{}", point);
    return os;
}

#endif // AGL_STRUCT_POINT_DECART_POINT2D_H
