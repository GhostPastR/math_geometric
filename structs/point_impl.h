#ifndef POINT_IMPL_H
#define POINT_IMPL_H

#include "../system/system_concept.h"
#include "../system/system_function.h"
#include "../algorithm/math_algorithm.h"

namespace agl {

namespace {

constexpr bool compare_point(const auto &property1, const auto &property2){
    return conjunction_tuple(property1, property2, [](const auto &v1, const auto &v2){
        if constexpr(std::is_floating_point_v<std::remove_cvref_t<decltype(v1)>>
                      && std::is_floating_point_v<std::remove_cvref_t<decltype(v2)>>){
            return algorithm::compare(v1, v2);
        }
        else{
            return v1 == v2;
        }
    });
}

}

template<typename ...Args>
struct point2d_abstract : public Carcass<Args...>{
    constexpr point2d_abstract() : Carcass<Args...>(){}
    constexpr point2d_abstract(auto x, auto y) : Carcass<Args...>(){
        set_x(x);
        set_y(y);
    }

    constexpr auto x() const{
        return std::get<0>(this->property_);
    }
    constexpr void set_x(auto x){
        std::get<0>(this->property_) = x;
    }

    constexpr auto y() const{
        return std::get<1>(this->property_);
    }
    constexpr void set_y(auto y){
        std::get<1>(this->property_) = y;
    }

    constexpr bool is_valid() const{
        return algorithm::is_valid(x()) && algorithm::is_valid(y());
    }

    constexpr friend bool operator==(const point2d_abstract &point1, const point2d_abstract &point2){
        return compare_point(point1.property_, point2.property_);
    }
};



template<typename ...Args>
class point3d_abstract : public point2d_abstract<Args...>{
public:
    constexpr point3d_abstract(){}
    constexpr point3d_abstract(auto x, auto y, auto h) : point2d_abstract<Args...>(x,y){
        set_h(h);
    }

    constexpr auto h() const{
        return std::get<2>(this->property_);
    }
    constexpr void set_h(auto h){
        std::get<2>(this->property_) = h;
    }

    constexpr bool is_valid() const{
        return point2d_abstract<Args...>::is_valid() && algorithm::is_valid(h());
    }

    constexpr friend bool operator==(const point3d_abstract &point1, const point3d_abstract &point2){
        return compare_point(point1.property_, point2.property_);
    }
};



template<typename ...Args>
class point4d_abstract : public point3d_abstract<Args...>{
public:
    constexpr point4d_abstract(){}
    constexpr point4d_abstract(auto x, auto y, auto h, auto time) : point3d_abstract<Args...>(x,y,h){
        set_time(time);
    }

    constexpr auto time() const{
        return std::get<3>(this->property_);
    }
    constexpr void set_time(auto time){
        std::get<3>(this->property_) = time;
    }

    constexpr bool is_valid() const{
        return point3d_abstract<Args...>::is_valid() && algorithm::is_valid(time());
    }

    constexpr friend bool operator==(const point4d_abstract &point1, const point4d_abstract &point2){
        return compare_point(point1.property_, point2.property_);
    }
};

template<typename ...Args>
struct polar2d_abstract : public Carcass<Args...>{
    constexpr polar2d_abstract() : Carcass<Args...>(){}
    constexpr polar2d_abstract(auto psi, auto fi) : Carcass<Args...>(){
        set_psi(psi);
        set_fi(fi);
    }

    constexpr auto psi() const{
        return std::get<0>(this->property_);
    }
    constexpr void set_psi(auto psi){
        std::get<0>(this->property_) = psi;
    }

    constexpr auto fi() const{
        return std::get<1>(this->property_);
    }
    constexpr void set_fi(auto fi){
        std::get<1>(this->property_) = fi;
    }

    constexpr friend bool operator==(const polar2d_abstract &point1, const polar2d_abstract &point2){
        return compare_point(point1.property_, point2.property_);
    }
};



template<typename ...Args>
struct Polar3d_Impl : public polar2d_abstract<Args...>{
    constexpr Polar3d_Impl() : polar2d_abstract<Args...>(){}
    constexpr Polar3d_Impl(auto psi, auto fi, auto z) : polar2d_abstract<Args...>(psi, fi){
        set_z(z);
    }

    constexpr auto z() const{
        return std::get<2>(this->property_);
    }
    constexpr void set_z(auto z){
        std::get<2>(this->property_) = z;
    }

    constexpr friend bool operator==(const Polar3d_Impl &point1, const Polar3d_Impl &point2){
        return compare_point(point1.property_, point2.property_);
    }
};

template<std::floating_point Type>
struct point2d_impl final : point2d_abstract<Type, Type>{
    using type_coordinate = Type;

    constexpr point2d_impl() : point2d_abstract<Type, Type>(){}
    constexpr point2d_impl(auto x, auto y) : point2d_abstract<Type, Type>(x,y){}
};

template<std::floating_point Type>
struct point3d_impl final : point3d_abstract<Type, Type, Type>{
    using type_coordinate = Type;

    constexpr point3d_impl() : point3d_abstract<Type, Type, Type>(){}
    constexpr point3d_impl(auto x, auto y, auto z) : point3d_abstract<Type, Type, Type>(x,y,z){}
};

template<std::floating_point Type, c_angle Angle>
struct polar2d_impl final : polar2d_abstract<Type, Type>{
    using type_coordinate = Type;

    constexpr polar2d_impl() : polar2d_abstract<Type, Type>(){}
    constexpr polar2d_impl(auto psi, auto fi) : polar2d_abstract<Type, Type>(psi, fi){}

    Angle angle_fi() const {
        return Angle(polar2d_abstract<Type, Type>::fi());
    }

    void set_fi(const Angle &angle) {
        polar2d_abstract<Type, Type>::set_fi(angle.radian());
    }
};

}

#endif // POINT_IMPL_H
