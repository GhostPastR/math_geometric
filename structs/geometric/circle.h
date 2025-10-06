#ifndef AGL_STRUCT_CIRCLE_DECART_CIRCLE_H
#define AGL_STRUCT_CIRCLE_DECART_CIRCLE_H

#include <format>
#include "algorithm/math_algorithm.h"

namespace agl::circle {

template<typename PointCenter, typename TypeRadius>
struct circle{
    constexpr circle() = default;
    constexpr circle(const PointCenter &center, const TypeRadius &radius)
        : center_(center), radius_(radius){}

    constexpr auto center() const{
        return center_;
    }
    constexpr void set_center(const PointCenter &center){
        center_ = center;
    }

    constexpr auto radius() const{
        return radius_;
    }
    constexpr void radius_center(const TypeRadius &radius){
        radius_ = radius;
    }

    friend constexpr bool operator==(const circle &arc1, const circle &arc2){
        return (arc1.center_ == arc2.center_) && algorithm::compare(arc1.radius_, arc2.radius_);
    }

private:
    PointCenter center_;
    TypeRadius radius_{};
};

}



template<typename PointCenter, typename TypeRadius>
struct std::formatter<agl::circle::circle<PointCenter, TypeRadius>> {
    std::formatter<std::string> _formatter;
    constexpr auto parse(std::format_parse_context& parse_context) {
        return _formatter.parse(parse_context);
    }

    auto format(const agl::circle::circle<PointCenter, TypeRadius>& circle, std::format_context& format_context) const {
        return _formatter.format(std::format("Circle(center={} radius={})", circle.center(), circle.radius()), format_context);
    }
};

template<typename PointCenter, typename TypeRadius>
constexpr std::ostream& operator<<(std::ostream& os, const agl::circle::circle<PointCenter, TypeRadius> &circle){
    os << std::format("Circle(center={} radius={})", circle.center(), circle.radius());
    return os;
}

#endif // AGL_STRUCT_CIRCLE_DECART_CIRCLE_H
