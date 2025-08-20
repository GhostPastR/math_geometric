#ifndef TRAITS_H
#define TRAITS_H

#include <concepts>
#include <cstddef>

namespace agl{

struct undefined final{};

struct cartesian final{};
struct polar final{};
struct spherical final{};
struct geographical final{};

struct tag_point final{};
struct tag_circle final{};
struct tag_arc final{};
struct tag_line final{};

struct sc_default final{};
struct wgs_84 final{};
struct pz_90_02 final{};

namespace traits {

template<typename Object>
struct tag{
    using type_tag = undefined;
};

template<typename Object>
struct coordinate_system{
    using system = undefined;
};

template<typename Object>
struct dimension{
    inline static constexpr std::size_t value(){
        return 0;
    }
};

template<typename Object>
struct geo_coordinate_system{
    using system = sc_default;
};

namespace traits_point {

template<typename Object>
struct type_property{
    using type_point = undefined;
};

template<typename Object, std::size_t NumberPoint>
struct access_point{
    inline constexpr static auto get(const Object &object){
        static_assert(false, "Access is not implemented for this object.");
    }
};

}

namespace traits_arc {

template<typename Object>
struct type_property{
    using type_center = undefined;
    using type_radius = undefined;
    using type_angle = undefined;
};

template<typename Object>
struct access_center{
    inline constexpr static auto get(const Object &object){
        static_assert(false, "Access is not implemented for this object.");
    }
};

template<typename Object>
struct access_radius{
    inline constexpr static auto get(const Object &object){
        static_assert(false, "Access is not implemented for this object.");
    }
};

template<typename Object, std::size_t NumberAngle>
struct access_angle{
    inline constexpr static auto get(const Object &object){
        static_assert(false, "Access is not implemented for this object.");
    }
};

}



}



namespace axis{

template <std::floating_point Type> inline constexpr Type semiminor_axis;
template<> inline constexpr double semiminor_axis<long double> = 6356751.362;
template<> inline constexpr double semiminor_axis<double> = 6356751.362;
template<> inline constexpr float semiminor_axis<float> = 6356751.362;

template <std::floating_point Type> inline constexpr Type semimajor_axis;
template<> inline constexpr double semimajor_axis<long double> = 6378136.;
template<> inline constexpr double semimajor_axis<double> = 6378136.;
template<> inline constexpr float semimajor_axis<float> = 6378136.;

template<std::floating_point Type>
constexpr Type eccentricity2_1(){
    return (semiminor_axis<Type> * semiminor_axis<Type> - semimajor_axis<Type> * semimajor_axis<Type>)
    / (semiminor_axis<Type> * semiminor_axis<Type>);
}

template<std::floating_point Type>
constexpr Type eccentricity2_2(){
    return (semimajor_axis<Type> * semimajor_axis<Type> - semiminor_axis<Type> * semiminor_axis<Type>)
    / (semiminor_axis<Type> * semiminor_axis<Type>);
}

}





}

#endif // TRAITS_H
