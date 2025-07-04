#ifndef USER_TYPE_H
#define USER_TYPE_H

#include "structs/circle_impl.h"
#include "structs/line_impl.h"
#include "structs/point_impl.h"
#include "unit/angle.h"
#include "structs/polygon_impl.h"
#include "structs/struct_geo_imp.h"

namespace agl{

using Lenght = double;
using Angle = angle_impl<double>;
using Point = point2d_impl<double>;
using Point3d = point3d_impl<double>;
using Point4d = point4d_abstract<double, double, double, double>;

using Polar2d = polar2d_impl<double, Angle>;
using Polar3d = Polar3d_Impl<double, Angle, double>;

using Line = straight_line_impl<double, Point>;
using HalfLine = half_line_impl<double, Point, Angle>;
using LineSection = line_section_impl<Point>;

using Circle = circle_impl<double, Point>;
using Arc = arc_impl<double, Point, Angle>;


using ConvexPolygon = convex_polygone_impl<Point>;
using Rectangle = rectangle_impl<double, Point>;
using Square = square_impl<double, Point>;
using Triangle = triangle_impl<double, Point>;
using RegularPolygon = regular_polygon_impl<double, Point>;

using PointGeo = point_geo2d_impl<double, Angle>;
using PointGeo3d = point_geo3d_abstract<Angle, Angle, double>;
using PointGeo4d = PointGeo4d_Impl<Angle, Angle, double, double>;

using HalfLineGeo = half_line_geo_impl<double, PointGeo, Angle>;
using LineSectionGeo = line_section_geo_impl<PointGeo>;

using CircleGeo = circle_geo_impl<double, PointGeo>;
using ArcGeo  = arc_geo_impl<double, PointGeo, Angle>;

}

#endif // USER_TYPE_H
