#ifndef DISTANCE_H
#define DISTANCE_H

#include "../system/system_unit.h"

namespace unit {

using _length = enum_unit<1,0,0,0>;

using millimeter = measure_unit<_length, 0.001>;
using centimeter = measure_unit<_length, 0.01>;
using decimeter = measure_unit<_length, 0.1>;
using meter = measure_unit<_length, 1.>;
using kilometer = measure_unit<_length, 1000.>;

using length_prefix = std::tuple<millimeter, centimeter, decimeter, meter, kilometer>;

template<class LengthPrefix, c_type_value Type, c_basic_value BasicValue>
    requires(c_unit_prefix<LengthPrefix, _length> && find_type<LengthPrefix>(length_prefix()))
struct Convert<LengthPrefix, Type, _length, BasicValue>{
    constexpr static Type convert(Type value) {
        if constexpr(std::is_same_v<BasicValue, basic>){
            return value * LengthPrefix::unit_value;
        }
        else{
            return value / LengthPrefix::unit_value;
        }
    }
};

using length = unit::Value<unit::_length, double>;

}

OPERATOR_QM(unit::length, mm, unit::millimeter)
OPERATOR_QM(unit::length, cm, unit::centimeter)
OPERATOR_QM(unit::length, dm, unit::decimeter)
OPERATOR_QM(unit::length, m, unit::meter)
OPERATOR_QM(unit::length, km, unit::kilometer)

constexpr unit::length operator +(const unit::length &value1, const unit::length &value2){
    return unit::length(value1.value() + value2.value()) ;
}

constexpr unit::length operator *(const double &value1, const unit::length &value2){
    return unit::length(value1 * value2.value()) ;
}

constexpr unit::length operator *(const unit::length &value1, const double &value2){
    return value2 * value1;
}


/* Для добавления новой единицы измерения:
 * using <name> = measure_unit<_length, <value>>; value - на сколько нужно умножить чтобы получились метры
 * В list_prefix новый тип
 * Добавляем оператор OPERATOR(unit::length, <префикс>, <name>)
 * */


#endif // DISTANCE_H
