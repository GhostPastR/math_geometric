#ifndef AGL_ALGORITHM_CONVERT_IMPLEMENTATION_H
#define AGL_ALGORITHM_CONVERT_IMPLEMENTATION_H

#include "implementation_convert.h"

namespace agl::algorithm::dispatch {

template<typename Object,
         typename ObjectOut>
struct convert{
    inline constexpr static auto get(const Object &){
        static_assert(false, "No 'convert' calculations have been implemented for these objects.");
    }
};

template<c_point_2d Point,
         c_point_2d PointOut>
    requires c_cartesian_all<Point> && c_polar<PointOut>
struct convert<Point,
               PointOut>{
    inline constexpr static auto get(const Point &point){
        using X = agl::traits::point::element_point_v<Point, 0>;
        using Y = agl::traits::point::element_point_v<Point, 1>;
        using Range = agl::traits::point::element_point_v<PointOut, 0>;
        using Omnibearing = agl::traits::point::element_point_v<PointOut, 1>;
        const auto x = traits::point::access_point<Point, 0>::get(point);
        const auto y = traits::point::access_point<Point, 1>::get(point);
        auto [r, omn] = primitive::cartesian_to_polar<X,
                                                      Y,
                                                      X,
                                                      Y,
                                                      Range,
                                                      Omnibearing>(X{}, Y{}, x, y);
        return traits::make<PointOut>::apply(r, omn);
    }
};

template<c_point_2d Point,
         c_point_2d PointOut>
    requires c_polar_all<Point> && c_cartesian_all<PointOut>
struct convert<Point,
               PointOut>{
    inline constexpr static auto get(const Point &point){
        using X = agl::traits::point::element_point_v<Point, 0>;
        using Y = agl::traits::point::element_point_v<Point, 1>;
        using Range = agl::traits::point::element_point_v<PointOut, 0>;
        using Omnibearing = agl::traits::point::element_point_v<PointOut, 1>;
        const auto range = traits::point::access_point<Point, 0>::get(point);
        const auto omnibearing = traits::point::access_point<Point, 1>::get(point);
        auto [x, y] = primitive::polar_to_cartesian<Range,
                                                    Omnibearing,
                                                    X,
                                                    Y,
                                                    X,
                                                    Y>(range, omnibearing, X{}, Y{});
        return traits::make<PointOut>::apply(x, y);
    }
};

template<c_point_2d Point,
         c_point_2d PointOut>
    requires c_geographical_all<Point> && c_polar<PointOut>
struct convert<Point,
               PointOut>{
    inline constexpr static auto get(const Point &point){
        using system = traits::geo_coordinate_system<Point>::system;
        using Lat = agl::traits::point::element_point_v<Point, 0>;
        using Long = agl::traits::point::element_point_v<Point, 1>;
        using Range = agl::traits::point::element_point_v<PointOut, 0>;
        using Omnibearing = agl::traits::point::element_point_v<PointOut, 1>;
        const auto latitude = traits::point::access_point<Point, 0>::get(point);
        const auto longitude = traits::point::access_point<Point, 1>::get(point);
        auto [r, omn] = primitive::geo_to_polar<Lat,
                                                Long,
                                                Lat,
                                                Long,
                                                Range,
                                                Omnibearing,
                                                system>(Lat{}, Long{}, latitude, longitude);
        return traits::make<PointOut>::apply(r, omn);
    }
};

template<c_point_2d Point,
         c_point_2d PointOut>
    requires c_polar<Point> && c_geographical_all<PointOut>
struct convert<Point,
               PointOut>{
    inline constexpr static auto get(const Point &point){
        using system = traits::geo_coordinate_system<PointOut>::system;
        using Range = agl::traits::point::element_point_v<Point, 0>;
        using Omnibearing = agl::traits::point::element_point_v<Point, 1>;
        using Lat = agl::traits::point::element_point_v<PointOut, 0>;
        using Long = agl::traits::point::element_point_v<PointOut, 1>;

        const auto range = traits::point::access_point<Point, 0>::get(point);
        const auto omnibearing = traits::point::access_point<Point, 1>::get(point);
        auto [lat, lon] = primitive::polar_to_geo<Range,
                                                  Omnibearing,
                                                  Lat,
                                                  Long,
                                                  Lat,
                                                  Long,
                                                  system>(range, omnibearing, Lat{}, Long{});
        return traits::make<PointOut>::apply(lat, lon);
    }
};

template<c_point_2d Point,
         c_point_2d PointOut>
    requires c_geographical_all<Point> && c_cartesian<PointOut>
struct convert<Point,
               PointOut>{
    inline constexpr static auto get(const Point &point){
        using system = traits::geo_coordinate_system<Point>::system;
        using Lat = agl::traits::point::element_point_v<Point, 0>;
        using Long = agl::traits::point::element_point_v<Point, 1>;
        using X = agl::traits::point::element_point_v<PointOut, 0>;
        using Y = agl::traits::point::element_point_v<PointOut, 1>;
        using Range = X;
        using Omnibearing = Lat;
        const auto latitude = traits::point::access_point<Point, 0>::get(point);
        const auto longitude = traits::point::access_point<Point, 1>::get(point);
        auto [r, omn] = primitive::geo_to_polar<Lat,
                                                Long,
                                                Lat,
                                                Long,
                                                Range,
                                                Omnibearing,
                                                system>(Lat{}, Long{}, latitude, longitude);
        auto [x, y] = primitive::polar_to_cartesian<Range,
                                                    Omnibearing,
                                                    X,
                                                    Y,
                                                    X,
                                                    Y>(r, omn, X{}, Y{});
        return traits::make<PointOut>::apply(x, y);
    }
};

template<c_point_2d Point,
         c_point_2d PointOut>
    requires c_cartesian<Point> && c_geographical_all<PointOut>
struct convert<Point,
               PointOut>{
    inline constexpr static auto get(const Point &point){
        using system = traits::geo_coordinate_system<PointOut>::system;
        using X = agl::traits::point::element_point_v<Point, 0>;
        using Y = agl::traits::point::element_point_v<Point, 1>;
        using Lat = agl::traits::point::element_point_v<PointOut, 0>;
        using Long = agl::traits::point::element_point_v<PointOut, 1>;
        using Range = X;
        using Omnibearing = Lat;
        const auto x = traits::point::access_point<Point, 0>::get(point);
        const auto y = traits::point::access_point<Point, 1>::get(point);
        auto [r, omn] = primitive::cartesian_to_polar<X,
                                                      Y,
                                                      X,
                                                      Y,
                                                      Range,
                                                      Omnibearing>(X{}, Y{}, x, y);
        auto [lat, lon] = primitive::polar_to_geo<Range,
                                                  Omnibearing,
                                                  Lat,
                                                  Long,
                                                  Lat,
                                                  Long,
                                                  system>(r, omn, Lat{}, Long{});
        return traits::make<PointOut>::apply(lat, lon);
    }
};


// template<c_geometric Object,
//          c_geometric ObjectOut>
//     requires (c_geographical<Object> && c_cartesian<ObjectOut>) || (c_geographical<ObjectOut> && c_cartesian<Object>)
// struct convert<Object,
//                ObjectOut>{
//     inline constexpr static auto get(const Object &object){
//         auto predicat = []<typename Point, typename PointOut>(Point point){
//             return convert<Point, PointOut>::get(point);
//         };
//         return object::convert<Object, ObjectOut, decltype(predicat)>::get(object, predicat);
//     }
// };



template<c_circle Circle,
         c_create_circle CircleOut>
    requires (c_geographical<Circle> && c_cartesian<CircleOut>) || (c_geographical<CircleOut> && c_cartesian<Circle>)
struct convert<Circle,
               CircleOut>{
    inline constexpr static auto get(const Circle &circle){
        auto predicat = []<typename Point, typename PointOut>(Point point){
            return convert<Point, PointOut>::get(point);
        };
        return object::convert<Circle, CircleOut, decltype(predicat)>::get(circle, predicat);
    }
};

template<c_arc Arc,
         c_create_arc ArcOut>
    requires (c_geographical<Arc> && c_cartesian<ArcOut>) || (c_geographical<ArcOut> && c_cartesian<Arc>)
struct convert<Arc,
               ArcOut>{
    inline constexpr static auto get(const Arc &arc){
        auto predicat = []<typename Point, typename PointOut>(Point point){
            return convert<Point, PointOut>::get(point);
        };
        return object::convert<Arc, ArcOut, decltype(predicat)>::get(arc, predicat);
    }
};

template<c_half_line_2d Line,
         c_create_half_line_2d LineOut>
    requires (c_geographical<Line> && c_cartesian<LineOut>) || (c_geographical<LineOut> && c_cartesian<Line>)
struct convert<Line,
               LineOut>{
    inline constexpr static auto get(const Line &line){
        auto predicat = []<typename Point, typename PointOut>(Point point){
            return convert<Point, PointOut>::get(point);
        };
        return object::convert<Line, LineOut, decltype(predicat)>::get(line, predicat);
    }
};

template<c_line_section Line,
         c_create_line_section LineOut>
    requires (c_geographical<Line> && c_cartesian<LineOut>) || (c_geographical<LineOut> && c_cartesian<Line>)
struct convert<Line,
               LineOut>{
    inline constexpr static auto get(const Line &line){
        auto predicat = []<typename Point, typename PointOut>(Point point){
            return convert<Point, PointOut>::get(point);
        };
        return object::convert<Line, LineOut, decltype(predicat)>::get(line, predicat);
    }
};

template<c_polygon Polygon,
         c_create_polygon PolygonOut>
    requires (c_geographical<Polygon> && c_cartesian<PolygonOut>) || (c_geographical<PolygonOut> && c_cartesian<Polygon>)
struct convert<Polygon,
               PolygonOut>{
    inline constexpr static auto get(const Polygon &polygon){
        auto predicat = []<typename Point, typename PointOut>(Point point){
            return convert<Point, PointOut>::get(point);
        };
        return object::convert<Polygon, PolygonOut, decltype(predicat)>::get(polygon, predicat);
    }
};



}

#endif // AGL_ALGORITHM_CONVERT_IMPLEMENTATION_H
