#ifndef SPEED_H
#define SPEED_H

#include "../system/system_unit.h"
#include "distance.h"
#include "time.h"

namespace agl::unit {

using _speed = enum_unit<1,0,-1,0>;

using meter_secund = measure_unit<_speed, meter::unit_value / second::unit_value>;
using meter_minute = measure_unit<_speed, meter::unit_value / minute::unit_value>;
using meter_hour = measure_unit<_speed, meter::unit_value / hour::unit_value>;
using kilometer_secund = measure_unit<_speed, kilometer::unit_value / second::unit_value>;
using kilometer_minute = measure_unit<_speed, kilometer::unit_value / minute::unit_value>;
using kilometer_hour = measure_unit<_speed, kilometer::unit_value / hour::unit_value>;
using foot_secund = measure_unit<_speed, foot::unit_value / second::unit_value>;
using foot_minute = measure_unit<_speed, foot::unit_value / minute::unit_value>;
using foot_hour = measure_unit<_speed, foot::unit_value / hour::unit_value>;
using mile_secund = measure_unit<_speed, mile::unit_value / second::unit_value>;
using mile_minute = measure_unit<_speed, mile::unit_value / minute::unit_value>;
using mile_hour = measure_unit<_speed, mile::unit_value / hour::unit_value>;
using knots = measure_unit<_speed, 0.514444444444>;

using speed_prefix = std::tuple<
    meter_secund,
    meter_minute,
    meter_hour,
    kilometer_secund,
    kilometer_minute,
    kilometer_hour,
    foot_secund,
    foot_minute,
    foot_hour,
    mile_secund,
    mile_minute,
    mile_hour,
    knots
    >;

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
OPERATOR_QM(agl::unit::speed, m_m, agl::unit::meter_minute)
OPERATOR_QM(agl::unit::speed, m_h, agl::unit::meter_hour)
OPERATOR_QM(agl::unit::speed, km_s, agl::unit::kilometer_secund)
OPERATOR_QM(agl::unit::speed, km_m, agl::unit::kilometer_minute)
OPERATOR_QM(agl::unit::speed, km_h, agl::unit::kilometer_hour)
OPERATOR_QM(agl::unit::speed, ft_s, agl::unit::foot_secund)
OPERATOR_QM(agl::unit::speed, ft_m, agl::unit::foot_minute)
OPERATOR_QM(agl::unit::speed, ft_h, agl::unit::foot_hour)
OPERATOR_QM(agl::unit::speed, mile_s, agl::unit::mile_secund)
OPERATOR_QM(agl::unit::speed, mile_m, agl::unit::mile_minute)
OPERATOR_QM(agl::unit::speed, mile_h, agl::unit::mile_hour)
OPERATOR_QM(agl::unit::speed, kn, agl::unit::knots)

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
