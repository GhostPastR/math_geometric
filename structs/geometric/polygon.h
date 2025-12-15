#ifndef AGL_STRUCT_POLYGON_H
#define AGL_STRUCT_POLYGON_H

#include <format>
#include <ranges>
#include "algorithm/is_correct_polygon/interface.h"

namespace agl::figure {

template<typename Point, typename Tag>
class polygon{
public:
    constexpr polygon() = default;
    constexpr polygon(const std::vector<Point> &points, bool correctness_check = false) : points_(points){
        if(correctness_check && !agl::algorithm::is_correct_polygon(*this)){
            throw std::logic_error("Couldn't create convex polygon!");
        }
    }
    constexpr polygon(std::vector<Point> &&points, bool correctness_check = false){
        std::swap(points_, points);
        if(correctness_check && !agl::algorithm::is_correct_polygon(*this)){
            throw std::logic_error("Couldn't create convex polygon!");
        }
    }

    constexpr std::vector<Point> points() const{
        return points_;
    }

private:
    std::vector<Point> points_;
};

}



template<typename Point, typename Tag>
struct std::formatter<agl::figure::polygon<Point, Tag>> {
    std::formatter<std::string> _formatter;
    constexpr auto parse(std::format_parse_context& parse_context) {
        return _formatter.parse(parse_context);
    }

    auto format(const agl::figure::polygon<Point, Tag>& polygon, std::format_context& format_context) const {
        const auto points = polygon.points();
        std::string temp;
        auto str = points | std::ranges::views::transform([](auto i){return std::format("{} ", i);}) | std::ranges::views::join;
        std::ranges::copy(str, std::back_inserter(temp));
        std::string tag = "undefined";
        if constexpr(std::is_same_v<Tag, agl::tag::polygon::non_convex>){
            tag = "non_convex";
        }
        else if constexpr(std::is_same_v<Tag, agl::tag::polygon::convex>){
            tag = "convex";
        }
        else if constexpr(std::is_same_v<Tag, agl::tag::polygon::self_intersecting>){
            tag = "self_intersecting";
        }
        else if constexpr(std::is_same_v<Tag, agl::tag::polygon::regular>){
            tag = "regular";
        }
        else if constexpr(std::is_same_v<Tag, agl::tag::polygon::triangle>){
            tag = "triangle";
        }
        else if constexpr(std::is_same_v<Tag, agl::tag::polygon::rectangular_triangle>){
            tag = "rectangular_triangle";
        }
        else if constexpr(std::is_same_v<Tag, agl::tag::polygon::rectangle>){
            tag = "rectangle";
        }

        return _formatter.format(std::format("Polygon(tag=\"{}\", size={}, points=[{}])",
                                             tag, points.size(), temp), format_context);
    }
};

template<typename Point, typename Tag>
constexpr std::ostream& operator<<(std::ostream& os, const agl::figure::polygon<Point, Tag> &polygon){
    os << std::format("{}", polygon);
    return os;
}


#endif // POLYGON_H
