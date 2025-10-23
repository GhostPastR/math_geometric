#ifndef AGL_ALGORITHM_POINT_COUPLING_IMPLEMENTATION_LINE_H
#define AGL_ALGORITHM_POINT_COUPLING_IMPLEMENTATION_LINE_H

#include <ranges>
#include "system/assert.h"
#include "system/tag.h"
#include "system/traits.h"
#include "system/traits_standart.h"
#include "algorithm/perpendicular/interface.h"
#include "algorithm/intersection/interface.h"
#include "algorithm/distance/interface.h"

namespace agl::algorithm::dispatch::group_line {

namespace agl::algorithm::dispatch::group_line::dispatch {

template<typename Line,
         typename Point,
         typename CoordinateSystem,
         std::size_t Dimension>
struct point_coupling{
    inline constexpr static auto get(const Line &line, const Point &point, bool is_perpendicular){
        static_assert(false, "No '' calculations have been implemented for these objects.");
    }
};

template<c_line_section Line,
         c_point_2d Point>
struct point_coupling<Line,
                      Point,
                      system_coordinat::cartesian,
                      2>{
    inline constexpr static auto get(const Line &line, const Point &point, bool is_perpendicular) -> std::optional<Point>{
        using str_line = ::agl::traits::line_section::access_straight_line<Line>::type;
        auto p_line = ::agl::algorithm::perpendicular<str_line>(line, point);
        if(const auto int_point = ::agl::algorithm::intersection<Point>(line, p_line); int_point.has_value()){
            return int_point;
        }
        const auto &start = ::agl::traits::line_section::access_start<Line>::get(line);
        const auto &stop = ::agl::traits::line_section::access_stop<Line>::get(line);
        if(is_perpendicular){
            return std::nullopt;
        }
        auto d1 = ::agl::algorithm::distance(point, start);
        auto d2 = ::agl::algorithm::distance(point, stop);
        if(d1 < d2){
            return start;
        }
        return stop;
    }
};

}


template<typename Line,
         typename Point,
         typename CoordinateSystem,
         std::size_t Dimension>
inline constexpr auto point_coupling(const Line &line, const Point &point, bool is_perpendicular){
    return agl::algorithm::dispatch::group_line::dispatch::point_coupling<Line,
                                                                          Point,
                                                                          CoordinateSystem,
                                                                          Dimension>::get(line, point, is_perpendicular);
}

}










#endif // AGL_ALGORITHM_POINT_COUPLING_IMPLEMENTATION_LINE_H
