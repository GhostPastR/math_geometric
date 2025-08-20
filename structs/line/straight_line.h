#ifndef STRAIGHT_LINE_H
#define STRAIGHT_LINE_H

namespace agl::line::decart {

template<typename Type>
struct straight_line_impl final {
    constexpr straight_line_impl(const Type &a, const Type &b, const Type &c) : a_(a), b_(b), c_(c){}
    // constexpr straight_line_impl(const point2<Type> &point1, const point2<Type> &point2){
    //     auto [a,b,c] = line_algo::equation_line_quick(point1.x(), point1.y(), point2.x(), point2.y());
    //     a_ = a;
    //     b_ = b;
    //     c_ = c;
    // }

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

    // friend constexpr bool operator==(const straight_line_impl &line1, const straight_line_impl &line2){
    //     return line_algo::compare(line1.a_, line1.b_, line1.c_, line2.a_, line2.b_, line2.c_);
    // }
private:
    //!Коэффициенты уравнения Ax + By + C = 0
    Type a_{};
    Type b_{};
    Type c_{};
};

}

#endif // STRAIGHT_LINE_H
