#ifndef AGL_STRUCT_POLYGON_H
#define AGL_STRUCT_POLYGON_H

#include <array>
#include <format>
#include <ranges>
#include "algorithm/is_correct_polygon/interface.h"
#include "system/traits.h"


namespace agl::figure {

template<typename Point, std::size_t N, typename Tag = agl::tag::tag_polygon>
class polygon{
public:
    using type_polygon = Tag;

    polygon() = default;
    polygon(const std::array<Point,N> &points, bool correctness_check = false) : points_(points){
        if(correctness_check){
            if(!agl::algorithm::is_correct_polygon(*this)){
                throw std::logic_error("Couldn't create convex polygon!");
            }
        }
    }
    polygon(std::array<Point,N> &&points, bool correctness_check = false){
        std::swap(points_, points);
        if(correctness_check){
            if(!agl::algorithm::is_correct_polygon(*this)){
                throw std::logic_error("Couldn't create convex polygon!");
            }
        }
    }

    std::array<Point,N> points() const{
        return points_;
    }

private:
    std::array<Point,N> points_;
};

}

namespace agl::traits{

template<typename Point, std::size_t N, typename Tag>
struct tag<agl::figure::polygon<Point, N, Tag>>{
    using type_tag = Tag;
};

template<typename Point, std::size_t N, typename Tag>
struct group<agl::figure::polygon<Point, N, Tag>>{
    using type_group = agl::group::group_polygon;
};

template<typename Point, std::size_t N, typename Tag>
struct coordinate_system<agl::figure::polygon<Point, N, Tag>>{
    using system = agl::traits::coordinate_system<Point>::system;
};

template<typename Point, std::size_t N, typename Tag>
struct dimension<agl::figure::polygon<Point, N, Tag>>{
    inline static constexpr std::size_t value(){
        return 2;
    }
};

namespace traits_polygon {

template<typename Point, std::size_t N, typename Tag>
struct type_property<agl::figure::polygon<Point, N, Tag>>{
    using type_point = Point;
    static constexpr std::size_t size = N;
};

template<typename Point, std::size_t N, typename Tag>
struct access_points<agl::figure::polygon<Point, N, Tag>>{
    inline constexpr static auto get(const agl::figure::polygon<Point, N, Tag> &object){
        return object.points();
    }
};

template<typename Point, std::size_t N, typename Tag>
struct access_create<agl::figure::polygon<Point, N, Tag>>{
    inline constexpr static auto get(std::array<Point, N> &&points){
        return agl::figure::polygon<Point, N, Tag>(std::forward<std::array<Point, N>>(points));
    }
};

}

}



template<typename Point, std::size_t N, typename Tag>
struct std::formatter<agl::figure::polygon<Point, N, Tag>> {
    std::formatter<std::string> _formatter;
    constexpr auto parse(std::format_parse_context& parse_context) {
        return _formatter.parse(parse_context);
    }

    auto format(const agl::figure::polygon<Point, N, Tag>& polygon, std::format_context& format_context) const {
        const auto points = polygon.points();
        std::string temp;
        auto str = points | std::ranges::views::transform([](auto i){return std::format("{} ", i);}) | std::ranges::views::join;
        std::ranges::copy(str, std::back_inserter(temp));
        if constexpr(std::is_same_v<Tag, agl::tag::tag_polygon>){
            return _formatter.format(std::format("Polygon(type=polygon, size={}, points=[{}])",
                                                 N, temp), format_context);
        }
        else if constexpr(std::is_same_v<Tag, agl::tag::tag_convex_polygone>){
            return _formatter.format(std::format("Polygon(type=convex_polygone, size={}, points=[{}])",
                                                 N, temp), format_context);
        }
        else if constexpr(std::is_same_v<Tag, agl::tag::tag_rectangle>){
            return _formatter.format(std::format("Polygon(type=rectangle, size={}, points=[{}])",
                                                 N, temp), format_context);
        }
        else if constexpr(std::is_same_v<Tag, agl::tag::tag_triangle>){
            return _formatter.format(std::format("Polygon(type=triangle, size={}, points=[{}])",
                                                 N, temp), format_context);
        }
        else if constexpr(std::is_same_v<Tag, agl::tag::tag_regular_polygon>){
            return _formatter.format(std::format("Polygon(type=regular_polygon, size={}, points=[{}])",
                                                 N, temp), format_context);
        }
        else{
            static_assert(false, "Unknown polygon type");
        }
    }
};

template<typename Point, std::size_t N, typename Tag>
constexpr std::ostream& operator<<(std::ostream& os, const agl::figure::polygon<Point, N, Tag> &polygon){
    os << std::format("{}", polygon);
    return os;
}


#endif // POLYGON_H
