#ifndef STRUCT_GEO_IMP_H
#define STRUCT_GEO_IMP_H

#include "../system/system_concept.h"
#include "../system/system_function.h"
#include "../algorithm/math_algorithm.h"

template<typename ...Args>
class point_geo2d_abstract : public Carcass<Args...>{
public:
    constexpr point_geo2d_abstract() : Carcass<Args...>(){}
    constexpr point_geo2d_abstract(auto latitude, auto longitude) : Carcass<Args...>(){
        set_latitude(latitude);
        set_longitude(longitude);
    }

    constexpr auto latitude() const{
        return std::get<0>(this->property_);
    }
    constexpr void set_latitude(auto latitude){
        std::get<0>(this->property_) = latitude;
    }
    constexpr auto longitude() const{
        return std::get<1>(this->property_);
    }
    constexpr void set_longitude(auto longitude){
        std::get<1>(this->property_) = longitude;
    }

    constexpr bool is_valid() const{
        return algorithm::is_valid(latitude()) && algorithm::is_valid(longitude());
    }

    constexpr friend bool operator==(const point_geo2d_abstract &point1, const point_geo2d_abstract &point2){
        return compare_point(point1.property_, point2.property_);
    }
};



template<typename ...Args>
class point_geo3d_abstract : public point_geo2d_abstract<Args...>{
public:
    constexpr point_geo3d_abstract() : point_geo2d_abstract<Args...>(){}
    constexpr point_geo3d_abstract(auto latitude, auto longitude, auto altitude) : point_geo2d_abstract<Args...>(latitude, longitude){
        set_altitude(altitude);
    }

    constexpr auto altitude() const{
        return std::get<2>(Carcass<Args...>::property_);
    }
    constexpr void set_altitude(auto altitude){
        std::get<2>(Carcass<Args...>::property_) = altitude;
    }

    constexpr bool is_valid() const{
        return point_geo2d_abstract<Args...>::is_valid() && algorithm::is_valid(altitude());
    }

    constexpr friend bool operator==(const point_geo3d_abstract &point1, const point_geo3d_abstract &point2){
        return compare_point(point1.property_, point2.property_);
    }
};



template<typename ...Args>
class PointGeo4d_Impl : public point_geo3d_abstract<Args...>{
public:
    constexpr PointGeo4d_Impl() : point_geo3d_abstract<Args...>(){}
    constexpr PointGeo4d_Impl(auto latitude, auto longitude, auto altitude, auto time)
        : point_geo3d_abstract<Args...>(latitude, longitude, altitude){
        set_time(time);
    }

    constexpr auto time() const{
        return std::get<3>(Carcass<Args...>::property_);
    }
    constexpr void set_time(auto time){
        std::get<3>(Carcass<Args...>::property_) = time;
    }

    constexpr bool is_valid() const{
        return point_geo3d_abstract<Args...>::is_valid() && algorithm::is_valid(time());
    }

    constexpr friend bool operator==(const PointGeo4d_Impl &point1, const PointGeo4d_Impl &point2){
        return compare_point(point1.property_, point2.property_);
    }
};

template<std::floating_point Type, c_angle Angle>
struct point_geo2d_impl final : point_geo2d_abstract<Type, Type>{
    using type_coordinate = Type;

    constexpr point_geo2d_impl() : point_geo2d_abstract<Type, Type>(){}
    constexpr point_geo2d_impl(Type latitude, Type longitude)
        : point_geo2d_abstract<Type, Type>(latitude, longitude){}
    constexpr point_geo2d_impl(const Angle &latitude, const Angle &longitude)
        : point_geo2d_abstract<Type, Type>(latitude.radian(), longitude.radian()){}

    constexpr Angle latitude_angle() const{
        return point_geo2d_abstract<Type, Type>::latitude();
    }
    constexpr void set_latitude(const Angle &latitude){
        point_geo2d_abstract<Type, Type>::set_latitude(latitude.radian());
    }
    constexpr Angle longitude_angle() const{
        return point_geo2d_abstract<Type, Type>::longitude();
    }
    constexpr void set_longitude(const Angle &longitude){
        point_geo2d_abstract<Type, Type>::set_longitude(longitude.radian());
    }
};

template<std::floating_point Type, c_point2d_geo PointGeo, c_angle Angle>
struct half_line_geo_impl final {
    constexpr half_line_geo_impl(const PointGeo &start, Type direction)
        : start_(start), direction_(direction){}
    constexpr half_line_geo_impl(const PointGeo &start, const Angle &angle)
        : start_(start), direction_(angle.radian()){}

    auto start() const{
        return start_;
    }
    auto direction() const{
        return direction_;
    }
    auto direction_angle() const{
        return Angle(direction_);
    }

    friend constexpr bool operator==(const half_line_geo_impl &line1, const half_line_geo_impl &line2){
        return (line1.start_ == line2.start_) && algorithm::compare(line1.direction_, line2.direction_);
    }

private:
    PointGeo start_;
    Type direction_;
};

template<c_point2d_geo PointGeo>
struct line_section_geo_impl final{
    constexpr line_section_geo_impl(const PointGeo &start, const PointGeo &stop)
        : start_(start), stop_(stop){}

    auto start() const{
        return start_;
    }
    auto stop() const{
        return stop_;
    }

    friend constexpr bool operator==(const line_section_geo_impl &line1, const line_section_geo_impl &line2){
        return (line1.start_ == line2.start_) && (line1.stop_ == line2.stop_);
    }
private:
    PointGeo start_;
    PointGeo stop_;
};



template<std::floating_point Type, c_point2d_geo PointGeo>
struct circle_geo_impl final {
    constexpr circle_geo_impl(const PointGeo &center, Type radius)
        : center_(center), radius_(radius){}

    PointGeo center() const{
        return center_;
    }
    Type radius() const{
        return radius_;
    }

private:
    PointGeo center_;
    Type radius_{};
};

template<std::floating_point Type, c_point2d_decard PointGeo, c_angle Angle>
struct arc_geo_impl final {
    constexpr arc_geo_impl(const PointGeo &center, Type radius, Type start, Type stop)
        : center_(center), radius_(radius), start_(start), stop_(stop){}
    constexpr arc_geo_impl(const PointGeo &center, Type radius, const Angle &start, const Angle &stop)
        : center_(center), radius_(radius), start_(start.radian()), stop_(stop.radian()){}

    PointGeo center() const{
        return center_;
    }
    Type radius() const{
        return radius_;
    }
    Type start() const{
        return start_;
    }
    Angle start_angle() const{
        return Angle(start_);
    }
    Type stop() const{
        return stop_;
    }
    Angle stop_angle() const{
        return Angle(stop_);
    }

private:
    PointGeo center_;
    Type radius_{};

    Type start_{};
    Type stop_{};
};


#endif // STRUCT_GEO_IMP_H
