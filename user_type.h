#ifndef USER_TYPE_H
#define USER_TYPE_H

#include "structs/point/decart_point2d.h"
#include "structs/polygon_impl.h"
#include "structs/struct_geo_imp.h"

#include "unit/distance.h"


namespace agl{

// using Lenght = double;
// using Angle = angle_impl<double>;
// using point2d = point2<double>;
// using point3d = point3<double>;

// using polar2d = polar2<double>;

// using line2d = straight_line_impl<double>;
// using half_Line2d = half_line_impl<double>;
// using line_section2d = line_section_impl<double>;

// using Circle = circle_impl<double, point2d>;
// using Arc = arc_impl<double, point2d, Angle>;


// using ConvexPolygon = convex_polygone_impl<point2d>;
// using Rectangle = rectangle_impl<double, point2d>;
// using Square = square_impl<double, point2d>;
// using Triangle = triangle_impl<double, point2d>;
// using RegularPolygon = regular_polygon_impl<double, point2d>;

// using PointGeo = point_geo2<double>;
// using PointGeo3d = point_geo3<double>;

// using HalfLineGeo = half_line_geo_impl<double, PointGeo, Angle>;
// using LineSectionGeo = line_section_geo_impl<PointGeo>;

// using CircleGeo = circle_geo_impl<double, PointGeo>;
// using ArcGeo  = arc_geo_impl<double, PointGeo, Angle>;

}

namespace agl::traits {

template<> struct tag<point::decart::point2d<unit::distance>>{
    using type_tag = tag_point;
};

template<> struct coordinate_system<point::decart::point2d<unit::distance>>{
    using system = cartesian;
};

template<> struct dimension<point::decart::point2d<unit::distance>>{
    inline static constexpr std::size_t value(){
        return 2;
    }
};

namespace traits_point {

template<> struct type_property<point::decart::point2d<unit::distance>>{
    using type = unit::distance::type_value;
};

template<> struct access_point<point::decart::point2d<unit::distance>, 0>{
    inline constexpr static auto get(const point::decart::point2d<unit::distance> &point){
        return agl::system::tag::value<unit::distance>::get(point.x());
    }
};

template<> struct access_point<point::decart::point2d<unit::distance>, 1>{
    inline constexpr static auto get(const point::decart::point2d<unit::distance> &point){
        return agl::system::tag::value<unit::distance>::get(point.y());
    }
};

}

}

#endif // USER_TYPE_H
