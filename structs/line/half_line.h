#ifndef HALF_LINE_H
#define HALF_LINE_H

namespace agl::line::decart {

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

#endif // HALF_LINE_H
