#ifndef LINE_SECTION_H
#define LINE_SECTION_H

namespace agl::line::decart {

template<typename Point>
struct line_section_impl final{
    constexpr line_section_impl(const Point &start, const Point &stop)
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

    friend constexpr bool operator==(const line_section_impl &line1, const line_section_impl &line2){
        return (line1.start_ == line2.start_) && (line1.stop_ == line2.stop_);
    }
private:
    Point start_;
    Point stop_;
};

}

#endif // LINE_SECTION_H
