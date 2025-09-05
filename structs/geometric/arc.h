#ifndef AGL_STRUCT_CIRCLE_DECART_ARC_H
#define AGL_STRUCT_CIRCLE_DECART_ARC_H

#include <format>
#include "system/traits.h"
#include "algorithm/math_algorithm.h"

namespace agl::circle {

template<typename PointCenter, typename TypeRadius, typename Angle>
struct arc final {
    constexpr arc(const PointCenter &center, const TypeRadius &radius, const Angle &start, const Angle &stop)
        : center_(center), radius_(radius), start_(start), stop_(stop){}

    constexpr auto center() const{
        return center_;
    }
    constexpr auto radius() const{
        return radius_;
    }
    constexpr auto start() const{
        return start_;
    }
    constexpr auto stop() const{
        return stop_;
    }

    friend constexpr bool operator==(const arc &arc1, const arc &arc2){
        return (arc1.center_ == arc2.center_) && algorithm::compare(arc1.radius_, arc2.radius_)
               && algorithm::compare(arc1.start_, arc2.start_) && algorithm::compare(arc1.stop_, arc2.stop_);
    }

private:
    PointCenter center_;
    TypeRadius radius_{};

    Angle start_{};
    Angle stop_{};
};

}



namespace agl::traits {

template<typename PointCenter, typename TypeRadius, typename Angle>
struct tag<circle::arc<PointCenter, TypeRadius, Angle>>{
    using type_tag = agl::tag::tag_arc;
};

template<typename PointCenter, typename TypeRadius, typename Angle>
struct group<circle::arc<PointCenter, TypeRadius, Angle>>{
    using type_group = agl::group::group_elements_circle;
};


template<typename PointCenter, typename TypeRadius, typename Angle>
struct coordinate_system<circle::arc<PointCenter, TypeRadius, Angle>>{
    using system = coordinate_system<PointCenter>::system;
};

template<typename PointCenter, typename TypeRadius, typename Angle>
struct dimension<circle::arc<PointCenter, TypeRadius, Angle>>{
    inline static constexpr std::size_t value(){
        return 2;
    }
};

namespace traits_arc {

template<typename PointCenter, typename TypeRadius, typename Angle>
struct type_property<circle::arc<PointCenter, TypeRadius, Angle>>{
    using type_center = PointCenter;
    using type_radius = TypeRadius;
    using type_angle = Angle;
};

template<typename PointCenter, typename TypeRadius, typename Angle>
struct access_center<circle::arc<PointCenter, TypeRadius, Angle>>{
    inline constexpr static auto get(const circle::arc<PointCenter, TypeRadius, Angle> &arc){
        return arc.center();
    }
};


template<typename PointCenter, typename TypeRadius, typename Angle>
struct access_radius<circle::arc<PointCenter, TypeRadius, Angle>>{
    inline constexpr static auto get(const circle::arc<PointCenter, TypeRadius, Angle> &arc){
        return agl::traits::value<TypeRadius>::get(arc.radius());
    }
};

template<typename PointCenter, typename TypeRadius, typename Angle>
struct access_angle<circle::arc<PointCenter, TypeRadius, Angle>, 0>{
    inline constexpr static auto get(const circle::arc<PointCenter, TypeRadius, Angle> &arc){
        return agl::traits::value<Angle>::get(arc.start());
    }
};

template<typename PointCenter, typename TypeRadius, typename Angle>
struct access_angle<circle::arc<PointCenter, TypeRadius, Angle>, 1>{
    inline constexpr static auto get(const circle::arc<PointCenter, TypeRadius, Angle> &arc){
        return agl::traits::value<Angle>::get(arc.stop());
    }
};

}

}



template<typename PointCenter, typename TypeRadius, typename Angle>
struct std::formatter<agl::circle::arc<PointCenter, TypeRadius, Angle>> {
    std::formatter<std::string> _formatter;
    constexpr auto parse(std::format_parse_context& parse_context) {
        return _formatter.parse(parse_context);
    }

    auto format(const agl::circle::arc<PointCenter, TypeRadius, Angle>& arc, std::format_context& format_context) const {
        return _formatter.format(std::format("Arc(center={} radius={} start={} stop={})", arc.center(), arc.radius(), arc.start(), arc.stop()), format_context);
    }
};

template<typename PointCenter, typename TypeRadius, typename Angle>
constexpr std::ostream& operator<<(std::ostream& os, const agl::circle::arc<PointCenter, TypeRadius, Angle> &arc){
    os << std::format("{}", arc);
    return os;
}

#endif // AGL_STRUCT_CIRCLE_DECART_ARC_H
