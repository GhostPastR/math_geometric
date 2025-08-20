#ifndef AGL_STRUCT_CIRCLE_DECART_CIRCLE_H
#define AGL_STRUCT_CIRCLE_DECART_CIRCLE_H

#include <format>
#include "system/tag.h"
#include "algorithm/traits.h"
#include "algorithm/math_algorithm.h"

namespace agl::circle::decart {

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



namespace agl::traits {

// template<typename PointCenter, typename TypeRadius>
// struct type_coordinate<circle::decart::circle<PointCenter, TypeRadius>>{
//     using type = type_coordinate<PointCenter>::type;
//     using type_radius = TypeRadius;
// };

// template<typename PointCenter, typename TypeRadius>
// struct tag<circle::decart::circle<PointCenter, TypeRadius>>{
//     using type_tag = tag_circle;
// };

// template<typename PointCenter, typename TypeRadius>
// struct coordinate_system<circle::decart::circle<PointCenter, TypeRadius>>{
//     using system = cartesian;
// };

// template<typename PointCenter, typename TypeRadius>
// struct dimension<circle::decart::circle<PointCenter, TypeRadius>>{
//     inline static constexpr std::size_t value(){
//         return 2;
//     }
// };

// template<typename PointCenter, typename TypeRadius>
// struct access_point<circle::decart::circle<PointCenter, TypeRadius>, 0>{
//     inline constexpr static auto get(const circle::decart::circle<PointCenter, TypeRadius> &arc){
//         return agl::system::tag::value<PointCenter>::get(arc.center());
//     }
// };

// template<typename PointCenter, typename TypeRadius>
// struct access_point<circle::decart::circle<PointCenter, TypeRadius>, 1>{
//     inline constexpr static auto get(const circle::decart::circle<PointCenter, TypeRadius> &arc){
//         return agl::system::tag::value<TypeRadius>::get(arc.radius());
//     }
// };

}



template<typename PointCenter, typename TypeRadius>
struct std::formatter<agl::circle::decart::circle<PointCenter, TypeRadius>> {
    std::formatter<std::string> _formatter;
    constexpr auto parse(std::format_parse_context& parse_context) {
        return _formatter.parse(parse_context);
    }

    auto format(const agl::circle::decart::circle<PointCenter, TypeRadius>& circle, std::format_context& format_context) const {
        return _formatter.format(std::format("Circle(center={} radius={})", circle.center(), circle.radius()), format_context);
    }
};



template<typename PointCenter, typename TypeRadius>
constexpr std::ostream& operator<<(std::ostream& os, const agl::circle::decart::circle<PointCenter, TypeRadius> &circle){
    os << std::format("Circle(center={} radius={})", circle.center(), circle.radius());
    return os;
}

#endif // AGL_STRUCT_CIRCLE_DECART_CIRCLE_H
