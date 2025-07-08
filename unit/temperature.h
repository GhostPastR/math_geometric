#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "../system/system_unit.h"

namespace agl::unit {

using _temperature = enum_unit<0,0,0,1>;

using kelvin = measure_unit_2<_temperature, 1., 273.15, 1.>;
using celsius = measure_unit_2<_temperature, 1., 0., 1.>;
using fahrenheit = measure_unit_2<_temperature, 1.8, 32., 1.>;
using rankin = measure_unit_2<_temperature, 1., 273.15, 1.8>;

using temperature_prefix = std::tuple<kelvin, celsius, fahrenheit, rankin>;

template<class TemperaturePrefix, c_type_value Type, c_basic_value BasicValue>
    requires(c_unit_prefix<TemperaturePrefix, _temperature> && find_type<TemperaturePrefix>(temperature_prefix()))
struct Convert<TemperaturePrefix, Type, _temperature, BasicValue>{
    constexpr static Type convert(Type value) {
        if constexpr(std::is_same_v<BasicValue, basic>){
            return (value / TemperaturePrefix::unit_value_3 - TemperaturePrefix::unit_value_2)
                   / TemperaturePrefix::unit_value_1;
        }
        else{
            return (value * TemperaturePrefix::unit_value_1 + TemperaturePrefix::unit_value_2)
                   * TemperaturePrefix::unit_value_3;
        }
    }
};

using temperature = unit::Value<unit::_temperature, double>;

}

OPERATOR_QM(agl::unit::temperature, K, agl::unit::kelvin)
OPERATOR_QM(agl::unit::temperature, C, agl::unit::celsius)
OPERATOR_QM(agl::unit::temperature, F, agl::unit::fahrenheit)
OPERATOR_QM(agl::unit::temperature, Ra, agl::unit::rankin)

constexpr agl::unit::temperature operator +(const agl::unit::temperature &value1, const agl::unit::temperature &value2){
    return agl::unit::temperature(value1.value() + value2.value()) ;
}

constexpr agl::unit::temperature operator *(const double &value1, const agl::unit::temperature &value2){
    return agl::unit::temperature(value1 * value2.value()) ;
}

constexpr agl::unit::temperature operator *(const agl::unit::temperature &value1, const double &value2){
    return value2 * value1;
}


#endif // TEMPERATURE_H
