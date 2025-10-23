#ifndef USER_TYPE_H
#define USER_TYPE_H

#include <unit/unit_object.h>
#include <structs/geometric_object.h>

namespace agl{

using point2_d = agl::point::decart::point2d<double>;
using point3_d = agl::point::decart::point3d<double>;

using polar2_d = agl::point::polar::polar2d<double, agl::unit::angle>;
using polar3_d = agl::point::polar::polar3d<double, agl::unit::angle, double>;

using straight_line2_d = agl::line::straight_line<double>;
using half_line2_d = agl::line::half_line<point2_d, agl::unit::angle>;
using line_section2_d = agl::line::line_section<point2_d>;

using circle2_d = agl::circle::circle<agl::point2_d, double>;
using arc2_d = agl::circle::arc<agl::point2_d, double, agl::unit::angle>;

using non_convex_polygon = agl::figure::polygon<agl::point2_d, agl::tag::polygon::non_convex>;
using polygon = agl::figure::polygon<agl::point2_d, agl::tag::polygon::convex>;
using polygon_intersecting = agl::figure::polygon<agl::point2_d, agl::tag::polygon::self_intersecting>;
using regular = agl::figure::polygon<agl::point2_d, agl::tag::polygon::regular>;
using triangle = agl::figure::polygon<agl::point2_d, agl::tag::polygon::triangle>;
using triangle_regular = agl::figure::polygon<agl::point2_d, agl::tag::polygon::rectangular_triangle>;
using rectangle = agl::figure::polygon<agl::point2_d, agl::tag::polygon::rectangle>;


// using Lenght = double;
// using Angle = angle_impl<double>;

// using PointGeo = point_geo2<double>;
// using PointGeo3d = point_geo3<double>;

// using HalfLineGeo = half_line_geo_impl<double, PointGeo, Angle>;
// using LineSectionGeo = line_section_geo_impl<PointGeo>;

// using CircleGeo = circle_geo_impl<double, PointGeo>;
// using ArcGeo  = arc_geo_impl<double, PointGeo, Angle>;

}

// namespace agl::traits {

// template<> struct tag<point::decart::point2d<unit::distance>>{
//     using type_tag = agl::tag::point::point;
// };

// template<> struct coordinate_system<point::decart::point2d<unit::distance>>{
//     using system = system_coordinat::cartesian;
// };

// template<> struct dimension<point::decart::point2d<unit::distance>>{
//     inline static constexpr std::size_t value(){
//         return 2;
//     }
// };

// namespace traits_point {

// template<> struct type_property<point::decart::point2d<unit::distance>>{
//     using type_point = unit::distance::type_value;
// };

// template<> struct access_point<point::decart::point2d<unit::distance>, 0>{
//     inline constexpr static auto get(const point::decart::point2d<unit::distance> &point){
//         return agl::traits::value<unit::distance>::get(point.x());
//     }
// };

// template<> struct access_point<point::decart::point2d<unit::distance>, 1>{
//     inline constexpr static auto get(const point::decart::point2d<unit::distance> &point){
//         return agl::traits::value<unit::distance>::get(point.y());
//     }
// };

// }

// }

#endif // USER_TYPE_H
