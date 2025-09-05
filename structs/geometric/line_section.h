#ifndef AGL_STRUCT_LINE_SECTION_H
#define AGL_STRUCT_LINE_SECTION_H

#include <format>
#include "system/traits.h"

namespace agl::line {

template<typename Point>
struct line_section final{
    constexpr line_section(const Point &start, const Point &stop)
        : start_(start), stop_(stop){}

    auto start() const{
        return start_;
    }
    void set_start(const Point &start) const{
        start_ = start;
    }

    auto stop() const{
        return stop_;
    }
    void set_stop(const Point &stop) const{
        stop_ = stop;
    }

    friend constexpr bool operator==(const line_section &line1, const line_section &line2){
        return (line1.start_ == line2.start_) && (line1.stop_ == line2.stop_);
    }
private:
    Point start_;
    Point stop_;
};

}



namespace agl::traits {

template<typename Point>
struct tag<agl::line::line_section<Point>>{
    using type_tag = agl::tag::tag_line_section;
};

template<typename Point>
struct group<agl::line::line_section<Point>>{
    using type_group = agl::group::group_line;
};

template<typename Point>
struct coordinate_system<agl::line::line_section<Point>>{
    using system = coordinate_system<Point>::system;;
};

template<typename Point>
struct dimension<agl::line::line_section<Point>>{
    inline static constexpr std::size_t value(){
        return 2;
    }
};

namespace traits_line_section {

template<typename Point>
struct type_property<agl::line::line_section<Point>>{
    using type_point = Point;
};

template<typename Point>
struct access_start<agl::line::line_section<Point>>{
    inline constexpr static auto get(const agl::line::line_section<Point> &object){
        return object.start();
    }
};

template<typename Point>
struct access_stop<agl::line::line_section<Point>>{
    inline constexpr static auto get(const agl::line::line_section<Point> &object){
        return object.stop();
    }
};

}

}




template<typename Point>
struct std::formatter<agl::line::line_section<Point>> {
    std::formatter<std::string> _formatter;
    constexpr auto parse(std::format_parse_context& parse_context) {
        return _formatter.parse(parse_context);
    }

    auto format(const agl::line::line_section<Point>& line_section, std::format_context& format_context) const {
        return _formatter.format(std::format("line_section(start={} stop={})", line_section.start(), line_section.stop()), format_context);
    }
};

template<typename Point, typename Angle>
constexpr std::ostream& operator<<(std::ostream& os, const agl::line::line_section<Point> &line_section){
    os << std::format("{}", line_section);
    return os;
}

#endif // AGL_STRUCT_LINE_SECTION_H
