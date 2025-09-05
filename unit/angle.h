#ifndef AGL_UNIT_ANGLE_H
#define AGL_UNIT_ANGLE_H

#include "unit/unit.h"
#include "algorithm/tag_algoritm.h"

namespace agl::unit {

using _angle = enum_unit<0,0,0,0>;

using radian = measure_unit<_angle, 1.>;
using degrees = measure_unit<_angle, 0.01745329251994329577>;

using angle_prefix = std::tuple<
    radian,
    degrees
    >;

template<class AnglePrefix, c_type_value Type, c_basic_value BasicValue>
    requires(c_unit_prefix<AnglePrefix, _angle> && find_type<AnglePrefix>(angle_prefix()))
struct Convert<AnglePrefix, Type, _angle, BasicValue>{
    constexpr static Type convert(Type value) {
        if constexpr(std::is_same_v<BasicValue, basic>){
            return value * AnglePrefix::unit_value;
        }
        else{
            return value / AnglePrefix::unit_value;
        }
    }
};

using angle = unit::Value<unit::_angle, double>;

}

OPERATOR_QM(agl::unit::angle, rad, agl::unit::radian)
OPERATOR_QM(agl::unit::angle, deg, agl::unit::degrees)

constexpr agl::unit::angle operator +(const agl::unit::angle &value1, const agl::unit::angle &value2){
    return agl::unit::angle(value1.value() + value2.value()) ;
}

constexpr agl::unit::angle operator *(const double &value1, const agl::unit::angle &value2){
    return agl::unit::angle(value1 * value2.value()) ;
}

constexpr agl::unit::angle operator *(const agl::unit::angle &value1, const double &value2){
    return value2 * value1;
}



template<> struct std::formatter<agl::unit::angle> {
    std::string attributes;

    constexpr auto parse(std::format_parse_context& parse_context) {
        auto it = std::ranges::find(parse_context, '}');
        attributes = std::string(parse_context.begin(), it);
        return it;
    }

    auto format(const agl::unit::angle& value, std::format_context& format_context) const {
        auto out = format_context.out();
        if (attributes.empty()) {
            out = std::format_to(out, "{}_rad", value.value());
            return out;
        }
        for (auto n = 0u; n <= attributes.size(); ++n) {
            switch (attributes[n]) {
            case 'r':
                out = std::format_to(out, "{}_rad", value.value<agl::unit::radian>());
                break;
            case 'd':
                out = std::format_to(out, "{}_deg", value.value<agl::unit::degrees>());
                break;
            default:
                out = std::format_to(out, "{}", attributes[n]);
            }
        }
        return out;
    }
};




namespace agl::traits{

template<>
struct type<agl::unit::angle>{
    using type_value = double;
};

template<> struct value<agl::unit::angle>{
    inline constexpr static auto get(const agl::unit::angle &temp){
        return temp.value();
    }
};

}

template<> struct agl::algorithm::direction_object<agl::unit::angle>{
    using type_direction_object = direction_angle;
};

#endif // AGL_UNIT_ANGLE_H
