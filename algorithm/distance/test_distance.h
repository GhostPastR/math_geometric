#ifndef TEST_DISTANCE_H
#define TEST_DISTANCE_H

#include "algorithm/distance/interface.h"

namespace agl {

namespace traits {

template<>
struct access_point<int, 0>{
    inline constexpr static auto get(const int &point){
        return 10;
    }
};

template<>
struct access_point<int, 1>{
    inline constexpr static auto get(const int &point){
        return 10;
    }
};

template<>
struct tag<int>{
    using type_tag = tag_line;
};

template<>
struct coordinate_system<int>{
    using system = cartesian;
};

template<>
struct dimension<int>{
    inline static constexpr std::size_t value(){
        return 2;
    }
};

}

}



namespace agl::algorithm {

struct distance_point_to_line final{};

template<> struct algorithm_distance<tag_point, tag_line>{
    using type_algorithm = distance_point_to_line;
};


namespace dispatch {

template<typename Point, typename CoordinateSystem, std::size_t Dimension>
struct distance<Point, int, distance_point_to_line, CoordinateSystem, Dimension>{
    inline constexpr static auto get(const Point &a, const int &b){
        return 10000;
    }
};


}

}

#endif // TEST_DISTANCE_H
