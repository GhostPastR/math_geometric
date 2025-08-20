#ifndef AGL_UNIT_DISTANCE_H
#define AGL_UNIT_DISTANCE_H

#include "system/tag.h"
#include "unit/unit.h"

namespace agl::unit {

using _distance = enum_unit<1,0,0,0>;

using millimeter = measure_unit<_distance, 0.001>;
using centimeter = measure_unit<_distance, 0.01>;
using decimeter = measure_unit<_distance, 0.1>;
using meter = measure_unit<_distance, 1.>;
using kilometer = measure_unit<_distance, 1000.>;
using inches = measure_unit<_distance, 0.0254>;             //Дюймы -> метры
using foot = measure_unit<_distance, 0.3048>;               //Футы -> метры
using foot_usa = measure_unit<_distance, 0.3048006>;        //Футы(США) -> метры
using mile = measure_unit<_distance, 1609.344>;             //Миля(междунаровдная) -> метры
using mile_overland = measure_unit<_distance, 1609.3>;      //Миля(сухопутная) -> метры
using mile_usa = measure_unit<_distance, 1609.347>;         //Миля(США) -> метры
using mile_nautical = measure_unit<_distance, 1852.>;       //Миля(международная, морская) -> метры
using mile_britain_n = measure_unit<_distance, 1853.184>;   //Миля(морская, Великобритания) -> метры
using yard = measure_unit<_distance, 0.9144>;               //Ярды -> метры


using distance_prefix = std::tuple<
    millimeter,
    centimeter,
    decimeter,
    meter,
    kilometer,
    inches,
    foot,
    foot_usa,
    mile,
    mile_overland,
    mile_usa,
    mile_nautical,
    mile_britain_n,
    yard>;

template<class DistancePrefix, c_type_value Type, c_basic_value BasicValue>
    requires(c_unit_prefix<DistancePrefix, _distance> && find_type<DistancePrefix>(distance_prefix()))
struct Convert<DistancePrefix, Type, _distance, BasicValue>{
    constexpr static Type convert(Type value) {
        if constexpr(std::is_same_v<BasicValue, basic>){
            return value * DistancePrefix::unit_value;
        }
        else{
            return value / DistancePrefix::unit_value;
        }
    }
};

using distance = unit::Value<unit::_distance, double>;

}

OPERATOR_QM(agl::unit::distance, mm, agl::unit::millimeter)
OPERATOR_QM(agl::unit::distance, cm, agl::unit::centimeter)
OPERATOR_QM(agl::unit::distance, dm, agl::unit::decimeter)
OPERATOR_QM(agl::unit::distance, m, agl::unit::meter)
OPERATOR_QM(agl::unit::distance, km, agl::unit::kilometer)
OPERATOR_QM(agl::unit::distance, in, agl::unit::inches)
OPERATOR_QM(agl::unit::distance, ft, agl::unit::foot)
OPERATOR_QM(agl::unit::distance, ft_usa, agl::unit::foot_usa)
OPERATOR_QM(agl::unit::distance, mile, agl::unit::mile)
OPERATOR_QM(agl::unit::distance, mile_ov, agl::unit::mile_overland)
OPERATOR_QM(agl::unit::distance, mile_usa, agl::unit::mile_usa)
OPERATOR_QM(agl::unit::distance, mile_n, agl::unit::mile_nautical)
OPERATOR_QM(agl::unit::distance, mile_bn, agl::unit::mile_britain_n)
OPERATOR_QM(agl::unit::distance, yd, agl::unit::yard)

constexpr agl::unit::distance operator +(const agl::unit::distance &value1, const agl::unit::distance &value2){
    return agl::unit::distance(value1.value() + value2.value()) ;
}

constexpr agl::unit::distance operator *(const double &value1, const agl::unit::distance &value2){
    return agl::unit::distance(value1 * value2.value()) ;
}

constexpr agl::unit::distance operator *(const agl::unit::distance &value1, const double &value2){
    return value2 * value1;
}



template<> struct std::formatter<agl::unit::distance> {
    std::string attributes;

    constexpr auto parse(std::format_parse_context& parse_context) {
        auto it = std::ranges::find(parse_context, '}');
        attributes = std::string(parse_context.begin(), it);
        return it;
    }

    auto format(const agl::unit::distance& value, std::format_context& format_context) const {
        auto out = format_context.out();
        CASE_VALUE("mm", mm, agl::unit::millimeter)
        CASE_VALUE("cm", cm, agl::unit::centimeter)
        CASE_VALUE("dm", dm, agl::unit::decimeter)
        CASE_VALUE("m", m, agl::unit::meter)
        CASE_VALUE("km", km, agl::unit::kilometer)
        CASE_VALUE("in", in, agl::unit::inches)
        CASE_VALUE("ft", ft, agl::unit::foot)
        CASE_VALUE("ft_usa", ft_usa, agl::unit::foot_usa)
        CASE_VALUE("mile", mile, agl::unit::mile)
        CASE_VALUE("mile_ov", mile_ov, agl::unit::mile_overland)
        CASE_VALUE("mile_usa", mile_usa, agl::unit::mile_usa)
        CASE_VALUE("mile_n", mile_n, agl::unit::mile_nautical)
        CASE_VALUE("mile_bn", mile_bn, agl::unit::mile_britain_n)
        CASE_VALUE("yd", yd, agl::unit::yard)

        out = std::format_to(out, "{}_m", value.value());
        return out;
    }
};



namespace agl::system::tag{

template<> struct value<agl::unit::distance>{
    inline constexpr static auto get(const agl::unit::distance &temp){
        return temp.value();
    }
};

}


/* Для добавления новой единицы измерения:
 * using <name> = measure_unit<_length, <value>>; value - на сколько нужно умножить чтобы получились метры
 * В list_prefix новый тип
 * Добавляем оператор OPERATOR(unit::distance, <префикс>, <name>)
 * */


#endif // AGL_UNIT_DISTANCE_H
