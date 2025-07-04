#ifndef WEIGHT_H
#define WEIGHT_H

#include "../system/system_unit.h"

namespace agl::unit {

using _weight = enum_unit<0,1,0,0>;

using gram = measure_unit<_weight, 0.001>;
using kilogram = measure_unit<_weight, 1.>;
using tonne = measure_unit<_weight, 1000.>;

using weight_prefix = std::tuple<gram, kilogram, tonne>;

template<class WeightPrefix, c_type_value Type, c_basic_value BasicValue>
    requires(c_unit_prefix<WeightPrefix, _weight> && find_type<WeightPrefix>(weight_prefix()))
struct Convert<WeightPrefix, Type, _weight, BasicValue>{
    constexpr static Type convert(Type value) {
        if constexpr(std::is_same_v<BasicValue, basic>){
            return value * WeightPrefix::unit_value;
        }
        else{
            return value / WeightPrefix::unit_value;
        }
    }
};

using weight = unit::Value<unit::_weight, double>;

}

OPERATOR_QM(agl::unit::weight, g, agl::unit::gram)
OPERATOR_QM(agl::unit::weight, kg, agl::unit::kilogram)
OPERATOR_QM(agl::unit::weight, t, agl::unit::tonne)

constexpr agl::unit::weight operator +(const agl::unit::weight &value1, const agl::unit::weight &value2){
    return agl::unit::weight(value1.value() + value2.value()) ;
}

constexpr agl::unit::weight operator *(const double &value1, const agl::unit::weight &value2){
    return agl::unit::weight(value1 * value2.value()) ;
}

constexpr agl::unit::weight operator *(const agl::unit::weight &value1, const double &value2){
    return value2 * value1;
}


#endif // WEIGHT_H
