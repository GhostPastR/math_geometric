// #ifndef STRUCT_GEO_IMP_H
// #define STRUCT_GEO_IMP_H

// #include "../system/system_concept.h"
// #include "../system/system_function.h"
// #include "../algorithm/math_algorithm.h"
// #include "../unit/angle.h"

// namespace agl {

// template<std::floating_point Type, c_point2d_geo PointGeo, c_angle Angle>
// struct half_line_geo_impl final {
//     using type_point = PointGeo;
//     constexpr half_line_geo_impl(const PointGeo &start, Type direction)
//         : start_(start), direction_(direction){}
//     constexpr half_line_geo_impl(const PointGeo &start, const Angle &angle)
//         : start_(start), direction_(angle.radian()){}

//     auto start() const{
//         return start_;
//     }
//     auto direction() const{
//         return direction_;
//     }
//     auto direction_angle() const{
//         return Angle(direction_);
//     }

//     friend constexpr bool operator==(const half_line_geo_impl &line1, const half_line_geo_impl &line2){
//         return (line1.start_ == line2.start_) && algorithm::compare(line1.direction_, line2.direction_);
//     }

// private:
//     PointGeo start_;
//     Type direction_;
// };

// template<c_point2d_geo PointGeo>
// struct line_section_geo_impl final{
//     using type_point = PointGeo;

//     constexpr line_section_geo_impl(const PointGeo &start, const PointGeo &stop)
//         : start_(start), stop_(stop){}

//     auto start() const{
//         return start_;
//     }
//     auto stop() const{
//         return stop_;
//     }

//     friend constexpr bool operator==(const line_section_geo_impl &line1, const line_section_geo_impl &line2){
//         return (line1.start_ == line2.start_) && (line1.stop_ == line2.stop_);
//     }
// private:
//     PointGeo start_;
//     PointGeo stop_;
// };



// template<std::floating_point Type, c_point2d_geo PointGeo>
// struct circle_geo_impl final {
//     using figure = std::true_type;

//     constexpr circle_geo_impl(const PointGeo &center, Type radius)
//         : center_(center), radius_(radius){}

//     PointGeo center() const{
//         return center_;
//     }
//     Type radius() const{
//         return radius_;
//     }

// private:
//     PointGeo center_;
//     Type radius_{};
// };

// template<std::floating_point Type, c_point2d_geo PointGeo, c_angle Angle>
// struct arc_geo_impl final {
//     using figure = std::false_type;

//     constexpr arc_geo_impl(const PointGeo &center, Type radius, Type start, Type stop)
//         : center_(center), radius_(radius), start_(start), stop_(stop){}
//     constexpr arc_geo_impl(const PointGeo &center, Type radius, const Angle &start, const Angle &stop)
//         : center_(center), radius_(radius), start_(start.radian()), stop_(stop.radian()){}

//     PointGeo center() const{
//         return center_;
//     }
//     Type radius() const{
//         return radius_;
//     }
//     Type start() const{
//         return start_;
//     }
//     Angle start_angle() const{
//         return Angle(start_);
//     }
//     Type stop() const{
//         return stop_;
//     }
//     Angle stop_angle() const{
//         return Angle(stop_);
//     }

// private:
//     PointGeo center_;
//     Type radius_{};

//     Type start_{};
//     Type stop_{};
// };

// }

// #endif // STRUCT_GEO_IMP_H
