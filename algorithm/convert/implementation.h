#ifndef AGL_ALGORITHM_CONVERT_IMPLEMENTATION_H
#define AGL_ALGORITHM_CONVERT_IMPLEMENTATION_H

#include "algorithm/traits.h"
#include "algorithm/distance/interface.h"
#include "algorithm/direction/interface.h"
#include "algorithm/create_point/interface.h"
#include "implementation_geo.h"
#include <cmath>

namespace agl::algorithm::dispatch {

template<typename Object,
         typename ObjectOut,
         typename CoordinateSystemObject,
         typename CoordinateSystemObjectOut,
         std::size_t Dimension>
struct convert{
    inline constexpr static auto get(const Object &){
        static_assert(false, "No 'convert' calculations have been implemented for these objects.");
    }
};

template<typename Object,
         typename ObjectOut>
struct convert<Object,
               ObjectOut,
               cartesian,
               polar,
               2>{
    inline constexpr static auto get(const Object &object){
        return ObjectOut{agl::algorithm::distance(Object{}, object), agl::algorithm::direction(Object{}, object)};
    }
};

template<typename Object,
         typename ObjectOut>
struct convert<Object,
               ObjectOut,
               polar,
               cartesian,
               2>{
    inline constexpr static auto get(const Object &object){
        return agl::algorithm::create_point(ObjectOut{}, traits::access_point<Object, 1>::get(object), traits::access_point<Object, 0>::get(object));
    }
};

template<typename Object,
         typename ObjectOut>
struct convert<Object,
               ObjectOut,
               geographical,
               polar,
               2>{
    inline constexpr static auto get(const Object &object){
        using system = traits::geo_coordinate_system<Object>::system;
        geo::convert<Object, ObjectOut, system, polar, 2>::get(object);
    }
};

template<typename Object,
         typename ObjectOut>
struct convert<Object,
               ObjectOut,
               polar,
               geographical,
               2>{
    inline constexpr static auto get(const Object &object){
        using system = traits::geo_coordinate_system<Object>::system;
        geo::convert<Object, ObjectOut, polar, system, 2>::get(object);
    }
};

template<typename Object,
         typename ObjectOut>
struct convert<Object,
               ObjectOut,
               geographical,
               cartesian,
               2>{
    inline constexpr static auto get(const Object &object){

    }
};

template<typename Object,
         typename ObjectOut>
struct convert<Object,
               ObjectOut,
               cartesian,
               geographical,
               2>{
    inline constexpr static auto get(const Object &object){

    }
};


}



namespace agl::algorithm::geometry {

template<typename Object, typename ObjectOut>
inline constexpr auto convert(const Object &object){
    using type_coordinate_system_input = traits::coordinate_system<Object>::system;
    using type_coordinate_system_out = traits::coordinate_system<ObjectOut>::system;

    constexpr auto dimension_input = traits::dimension<Object>::value();
    constexpr auto dimension_out = traits::dimension<ObjectOut>::value();

    static_assert(!std::is_same_v<type_coordinate_system_input, agl::undefined>, "Error!");
    static_assert(!std::is_same_v<type_coordinate_system_out, agl::undefined>, "Error!");

    static_assert((dimension_input == dimension_out) && (dimension_input > decltype(dimension_input){}), "Error!");

    return dispatch::convert<Object, ObjectOut, type_coordinate_system_input,
                             type_coordinate_system_out, dimension_out>::get(object);
}

}


#endif // AGL_ALGORITHM_CONVERT_IMPLEMENTATION_H
