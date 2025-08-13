#ifndef POINT_IMPL_H
#define POINT_IMPL_H

#include "../../algorithm/math_algorithm.h"
// #include "../algorithm/point_algorithm.h"
// #include "../unit/angle.h"
#include <format>
#include "algorithm/traits.h"

namespace agl::point::decart {

template<std::floating_point Type>
class point2d{
public:
    constexpr point2d(){}
    constexpr point2d(auto x, auto y){
        set_x(x);
        set_y(y);
    }

    constexpr auto x() const{
        return x_;
    }
    constexpr void set_x(auto x){
        x_ = x;
    }

    constexpr auto y() const{
        return y_;
    }
    constexpr void set_y(auto y){
        y_ = y;
    }

    constexpr bool is_valid() const{
        return algorithm::is_valid(x_) && algorithm::is_valid(y_);
    }

    constexpr friend bool operator==(const point2d &point1, const point2d &point2){
        return point1.compare(point2);
    }

protected:
    Type x_{};
    Type y_{};

    constexpr bool compare(const point2d &point) const{
        return algorithm::compare(x_, point.x_) && algorithm::compare(y_, point.y_);
    }
};

}




namespace agl {

namespace traits {

template<typename Type>
struct type_coordinate<point::decart::point2d<Type>>{
    using type = Type;
};

template<typename Type>
struct access_point<point::decart::point2d<Type>, 0>{
    inline constexpr static auto get(const point::decart::point2d<Type> &point){
        return point.x();
    }
};

template<typename Type>
struct access_point<point::decart::point2d<Type>, 1>{
    inline constexpr static auto get(const point::decart::point2d<Type> &point){
        return point.y();
    }
};

template<typename Type>
struct tag<point::decart::point2d<Type>>{
    using type_tag = object_point;
};

template<typename Type>
struct coordinate_system<point::decart::point2d<Type>>{
    using system = cartesian;
};

template<typename Type>
struct dimension<point::decart::point2d<Type>>{
    inline static constexpr std::size_t value(){
        return 2;
    }
};

}

}





// template<std::floating_point Type>
// class point3 : public point2<Type>{
// public:
//     constexpr point3() : point2<Type>(){}
//     constexpr point3(auto x, auto y, auto z) : point2<Type>(x,y){
//         set_z(z);
//     }
//     constexpr auto z() const{
//         return z_;
//     }
//     constexpr void set_z(auto z){
//         z_ = z;
//     }

//     constexpr bool is_valid() const{
//         return point2<Type>::is_valid() && algorithm::is_valid(z_);
//     }

//     constexpr friend bool operator==(const point3 &point1, const point3 &point2){
//         return point1.compare(point2);
//     }

// protected:
//     Type z_{};

//     constexpr bool compare(const point3 &point) const{
//         return point2<Type>::compare(point) && algorithm::compare(z_, point.z_);
//     }
// };

// template<std::floating_point Type>
// class polar2{
// public:
//     constexpr polar2(){}
//     constexpr polar2(Type psi, const angle_impl<Type> &fi){
//         set_psi(psi);
//         set_fi(fi);
//     }

//     constexpr auto psi() const{
//         return psi_;
//     }
//     constexpr void set_psi(Type psi){
//         psi_ = psi;
//     }

//     constexpr auto fi() const{
//         return fi_;
//     }
//     constexpr void set_fi(const angle_impl<Type> &fi){
//         fi_ = fi;
//     }

//     constexpr friend bool operator==(const polar2 &point1, const polar2 &point2){
//         return point1.compare(point2);
//     }

// protected:
//     Type psi_{};
//     angle_impl<Type> fi_;

//     constexpr bool compare(const polar2 &point) const{
//         return algorithm::compare(psi_, point.psi_) && algorithm::compare(fi_, point.fi_);
//     }
// };

// template<std::floating_point Type>
// constexpr auto angle(const point2<Type> &point1, const point2<Type> &point2){
//     return point_algo::angle(point1.x(), point1.y(), point2.x(), point2.y());
// }

// template<std::floating_point Type>
// constexpr auto distance(const point2<Type> &point1, const point2<Type> &point2){
//     return point_algo::distance<Type,2>({point1.x(),  point1.y()}, {point2.x(),  point2.y()});
// }

// template<std::floating_point Type, std::floating_point TypeAngle, std::floating_point TypeRange>
// constexpr point2<Type> new_point(const point2<Type> &point, const TypeAngle &angle, const TypeRange &range){
//     auto [x,y] = point_algo::new_point(point.x(), point.y(), angle, range);
//     return {x,y};
// }

// template<std::floating_point Type, std::floating_point TypeAngle>
// constexpr point2<Type> rotate(const point2<Type> &point, const TypeAngle &angle, const point2<Type> &reference){
//     auto [x,y] = point_algo::rotate(point.x(), point.y(), angle, reference.x(), reference.y());
//     return {x,y};
// }

// template<std::floating_point Type>
// constexpr point2<Type> midplane(const point2<Type> &p1, const point2<Type> &p2){
//     auto v = point_algo::midplane<Type,2>({p1.x(), p1.y()}, {p2.x(), p2.y()});
//     return {v[0], v[1]};
// }

// template<std::floating_point Type>
// constexpr polar2<Type> convert_polar(const point2<Type> &reference, const point2<Type> &point){
//     auto [x,y] = point_algo::convert_polar(reference.x(), reference.y(), point.x(), point.y());
//     return {x,y};
// }

// template<std::floating_point Type>
// constexpr point2<Type> convert_decart(const polar2<Type> &point, const point2<Type> &reference){
//     auto [x,y] = point_algo::new_point(point.fi(), point.psi(), reference.x(), reference.y());
//     return {x,y};
// }

// template<std::floating_point Type>
// constexpr bool is_co_directional(const polar2<Type> &start, const polar2<Type> &stop1, const polar2<Type> &stop2){
//     return point_algo::is_co_directional({start.x(), start.y()}, {stop1.x(), stop1.y()}, {stop2.x(), stop2.y()});
// }

// }

template<std::floating_point Type>
constexpr std::ostream& operator<<(std::ostream& os, const agl::point::decart::point2d<Type> &point){
    os << std::format("x={} y={}", point.x(), point.y());
    return os;
}

#endif // POINT_IMPL_H
