#ifndef SPEED_H
#define SPEED_H

#include "../system/system_unit.h"

namespace agl::unit {

using _speed = enum_unit<1,0,-1,0>;

using meter_secund = measure_unit<_speed, 1.>;
using kilometer_hour = measure_unit<_speed, 1.0/3.6>;

using speed_prefix = std::tuple<meter_secund, kilometer_hour>;

template<class SpeedPrefix, c_type_value Type, c_basic_value BasicValue>
    requires(c_unit_prefix<SpeedPrefix, _speed> && find_type<SpeedPrefix>(speed_prefix()))
struct Convert<SpeedPrefix, Type, _speed, BasicValue>{
    constexpr static Type convert(Type value) {
        if constexpr(std::is_same_v<BasicValue, basic>){
            return value * SpeedPrefix::unit_value;
        }
        else{
            return value / SpeedPrefix::unit_value;
        }
    }
};

using speed = unit::Value<unit::_speed, double>;

}

OPERATOR_QM(agl::unit::speed, m_s, agl::unit::meter_secund)
OPERATOR_QM(agl::unit::speed, km_h, agl::unit::kilometer_hour)

constexpr agl::unit::speed operator +(const agl::unit::speed &value1, const agl::unit::speed &value2){
    return agl::unit::speed(value1.value() + value2.value()) ;
}

constexpr agl::unit::speed operator *(const double &value1, const agl::unit::speed &value2){
    return agl::unit::speed(value1 * value2.value()) ;
}

constexpr agl::unit::speed operator *(const agl::unit::speed &value1, const double &value2){
    return value2 * value1;
}

#endif // SPEED_H
