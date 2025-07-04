#ifndef TIME_H
#define TIME_H

#include "../system/system_unit.h"

namespace agl::unit {

using _time = enum_unit<0,0,1,0>;

using second = measure_unit<_time, 1.>;
using minute = measure_unit<_time, 60.>;
using hour = measure_unit<_time, 3600.>;
using day = measure_unit<_time, 86400.>;

using time_prefix = std::tuple<second, minute, hour, day>;

template<class TimePrefix, c_type_value Type, c_basic_value BasicValue>
    requires(c_unit_prefix<TimePrefix, _time> && find_type<TimePrefix>(time_prefix()))
struct Convert<TimePrefix, Type, _time, BasicValue>{
    constexpr static Type convert(Type value) {
        if constexpr(std::is_same_v<BasicValue, basic>){
            return value * TimePrefix::unit_value;
        }
        else{
            return value / TimePrefix::unit_value;
        }
    }
};

using time = unit::Value<unit::_time, double>;

}

OPERATOR_QM(agl::unit::time, second, agl::unit::second)
OPERATOR_QM(agl::unit::time, minute, agl::unit::minute)
OPERATOR_QM(agl::unit::time, hour, agl::unit::hour)
OPERATOR_QM(agl::unit::time, day, agl::unit::day)

constexpr agl::unit::time operator +(const agl::unit::time &value1, const agl::unit::time &value2){
    return agl::unit::time(value1.value() + value2.value()) ;
}

constexpr agl::unit::time operator *(const double &value1, const agl::unit::time &value2){
    return agl::unit::time(value1 * value2.value()) ;
}

constexpr agl::unit::time operator *(const agl::unit::time &value1, const double &value2){
    return value2 * value1;
}

#endif // TIME_H
