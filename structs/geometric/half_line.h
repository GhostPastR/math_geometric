#ifndef AGL_STRUCT_HALF_LINE_H
#define AGL_STRUCT_HALF_LINE_H

#include <format>

namespace agl::line {

template<typename Point, typename Angle>
struct half_line final {
    constexpr half_line() = default;
    constexpr half_line(const Point &start, const Angle &angle) : start_(start), direction_(angle){}

    auto start() const{
        return start_;
    }
    void set_start(const Point &start) const{
        start_ = start;
    }

    auto direction() const{
        return direction_;
    }
    void set_direction(const Angle &angle) const{
        direction_ = angle;
    }

    friend constexpr bool operator==(const half_line &line1, const half_line &line2){
        return (line1.start_ == line2.start_) && (line1.direction_ == line2.direction_);
    }

private:
    Point start_;
    Angle direction_;
};

}



template<typename Point, typename Angle>
struct std::formatter<agl::line::half_line<Point, Angle>> {
    std::formatter<std::string> _formatter;
    constexpr auto parse(std::format_parse_context& parse_context) {
        return _formatter.parse(parse_context);
    }

    auto format(const agl::line::half_line<Point, Angle>& half_line, std::format_context& format_context) const {
        return _formatter.format(std::format("half_line(start={} direction={})", half_line.start(), half_line.direction()), format_context);
    }
};

template<typename Point, typename Angle>
constexpr std::ostream& operator<<(std::ostream& os, const agl::line::half_line<Point, Angle> &half_line){
    os << std::format("{}", half_line);
    return os;
}

#endif // AGL_STRUCT_HALF_LINE_H
