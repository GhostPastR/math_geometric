#ifndef AGL_STRUCT_STRAIGHT_LINE_H
#define AGL_STRUCT_STRAIGHT_LINE_H

#include <format>
#include "algorithm/math_algorithm.h"
#include "algorithm/equation_of_line/interface.h"

namespace agl::line {

template<typename Type, typename CoordinateSystem = system_coordinat::cartesian>
struct straight_line final {
    constexpr straight_line(const Type &a, const Type &b, const Type &c){
        auto array = agl::algorithm::normalized(std::array<Type,3>{a,b,c});
        a_ = array[0];
        b_ = array[1];
        c_ = array[2];
    }

    template<typename Point>
    constexpr straight_line(const Point &point1, const Point &point2){
        auto array = agl::algorithm::equation_of_line(point1, point2);
        a_ = array[0];
        b_ = array[1];
        c_ = array[2];
    }

    auto a() const{
        return a_;
    }
    void set_a(const Type &a) const{
        a_ = a;
    }

    auto b() const{
        return b_;
    }
    void set_b(const Type &b) const{
        b_ = b;
    }

    auto c() const{
        return c_;
    }
    void set_c(const Type &c) const{
        c_ = c;
    }

    friend constexpr bool operator==(const straight_line &line1, const straight_line &line2){
        return algorithm::compare(line1.a_, line2.a_)
               && algorithm::compare(line1.b_, line2.b_)
               && algorithm::compare(line1.c_, line2.c_);
    }
private:
    //!Коэффициенты уравнения Ax + By + C = 0
    Type a_{};
    Type b_{};
    Type c_{};
};

}



template<typename Type>
struct std::formatter<agl::line::straight_line<Type>> {
    std::formatter<std::string> _formatter;
    constexpr auto parse(std::format_parse_context& parse_context) {
        return _formatter.parse(parse_context);
    }

    auto format(const agl::line::straight_line<Type>& straight_line, std::format_context& format_context) const {
        return _formatter.format(std::format("straight_line({}, {}, {})", straight_line.a(), straight_line.b(), straight_line.c()), format_context);
    }
};

template<typename Type>
constexpr std::ostream& operator<<(std::ostream& os, const agl::line::straight_line<Type> &straight_line){
    os << std::format("{}", straight_line);
    return os;
}

#endif // AGL_STRUCT_STRAIGHT_LINE_H
