#ifndef POLYGON_IMPL_H
#define POLYGON_IMPL_H

#include <vector>
#include "../system/system_concept.h"
#include "../algorithm/polygon_algorithm.h"


// template<std::floating_point Type, c_point2d Point>
// struct polygon_abstract {
//     polygon_abstract() = default;
//     polygon_abstract(const std::initializer_list<Point> &list){
//         points_.insert(points_.end(), list.begin(), list.end());
//     }

//     std::vector<Point> get_points() const{
//         return points_;
//     }

//     friend constexpr bool operator==(const polygon_abstract& polugon1, const polygon_abstract& polugon2){
//         if(polugon1.points_.size() != polugon2.points_.size()){
//             return false;
//         }
//         auto it1 = std::begin(polugon1.points_);
//         auto it2 = std::begin(polugon2.points_);
//         for(auto end = std::end(polugon1.points_); it1 != end; ++it1, ++it2){
//             if(!(*it1 == *it2)){
//                 return false;
//             }
//         }
//         return true;
//     }

// protected:
//     std::vector<Point> points_;
// };

namespace agl {

template<c_point2d Point>
struct convex_polygone_impl{
    using type_point = Point;

    convex_polygone_impl() = default;
    convex_polygone_impl(const std::initializer_list<Point> &list){
        std::vector<Point> points;
        points.insert(points.end(), list.begin(), list.end());
        if(!polygon_algo::is_convex_polygone(points)){
            throw std::logic_error("Couldn't create convex polygone!");
        }
        std::swap(points_, points);
    }

    std::vector<Point> get_points() const{
        return points_;
    }

protected:
    std::vector<Point> points_;
};

template<std::floating_point Type, c_point2d Point>
struct rectangle_impl final{
    using type_point = Point;

    rectangle_impl() = default;
    rectangle_impl(const std::initializer_list<Point> &list){
        std::vector<Point> points;
        points.insert(points.end(), list.begin(), list.end());
        if(!polygon_algo::is_rectangle(points)){
            throw std::logic_error("Couldn't create convex rectangle!");
        }
        top_left_ = points.front();
        width_ = point_algo::distance(points[0], points[1]);
        height_ = point_algo::distance(points[1], points[2]);
    }

    rectangle_impl(const Point &top_left, Type width, Type height)
        : top_left_(top_left), width_(width), height_(height){}

    std::vector<Point> get_points() const{
        return polygon_algo::create_rectangle(top_left_, width_, height_);
    }

    Point get_top_left() const{
        return top_left_;
    }

    Type width() const{
        return width_;
    }

    Type height() const{
        return height_;
    }

private:
    Point top_left_;
    Type width_{};
    Type height_{};
};

template<std::floating_point Type, c_point2d Point>
struct square_impl final{
    using type_point = Point;

    square_impl() = default;
    square_impl(const std::initializer_list<Point> &list){
        std::vector<Point> points;
        points.insert(points.end(), list.begin(), list.end());
        if(!polygon_algo::is_square(points)){
            throw std::logic_error("Couldn't create convex square!");
        }
        top_left_ = points.front();
        lenght_ = point_algo::distance(points[0], points[1]);
    }

    square_impl(const Point &top_left, Type lenght)
        : top_left_(top_left), lenght_(lenght){}

    std::vector<Point> get_points() const{
        return polygon_algo::create_square(top_left_, lenght_);
    }

    Point get_top_left() const{
        return top_left_;
    }

    Type lenght() const{
        return lenght_;
    }

private:
    Point top_left_;
    Type lenght_{};
};

template<std::floating_point Type, c_point2d Point>
struct triangle_impl final{
    using type_point = Point;

    triangle_impl() = default;
    triangle_impl(const std::initializer_list<Point> &list){
        std::vector<Point> points;
        points.insert(points.end(), list.begin(), list.end());
        if(!polygon_algo::is_triangle(points)){
            throw std::logic_error("Couldn't create convex triangle!");
        }
        top_left_ = points[0];
        a_ = point_algo::distance(points[0], points[1]);
        b_ = point_algo::distance(points[1], points[2]);
        c_ = point_algo::distance(points[0], points[2]);
    }

    std::vector<Point> get_points() const{
        return polygon_algo::create_triangle(top_left_, a_, b_, c_);
    }

    Point get_top_left() const{
        return top_left_;
    }

    Type get_a() const{
        return a_;
    }

    Type get_b() const{
        return b_;
    }

    Type get_c() const{
        return c_;
    }

private:
    Point top_left_;
    Type a_{};
    Type b_{};
    Type c_{};
};

template<std::floating_point Type, c_point2d Point>
struct regular_polygon_impl final{
    using type_point = Point;

    regular_polygon_impl() = default;
    regular_polygon_impl(const std::initializer_list<Point> &list){
        std::vector<Point> points;
        points.insert(points.end(), list.begin(), list.end());
        if(!polygon_algo::is_regular_polygon(points)){
            throw std::logic_error("Couldn't create convex triangle!");
        }
        center_ = polygon_algo::get_centre(points);
        lenght_ = point_algo::distance(points[0], points[1]);
        count_ = points.size();
    }
    regular_polygon_impl(const std::vector<Point> &points){
        if(!polygon_algo::is_regular_polygon(points)){
            throw std::logic_error("Couldn't create convex triangle!");
        }
        center_ = polygon_algo::get_centre(points);
        lenght_ = point_algo::distance(points[0], points[1]);
        count_ = points.size();
    }

    regular_polygon_impl(const Point &center, Type lenght, size_t count)
        : center_(center), lenght_(lenght), count_(count){}

    template<std::floating_point TypeAngle = Type>
    std::vector<Point> get_points(TypeAngle angle = {}) const{
        return polygon_algo::create_regular_polygon(center_, lenght_, count_, angle);
    }

    Point get_center() const{
        return center_;
    }

    Type get_lenght() const{
        return lenght_;
    }

    Type get_count() const{
        return count_;
    }

private:
    Point center_;
    Type lenght_{};
    size_t count_{};
};

}

#endif // POLYGON_IMPL_H
