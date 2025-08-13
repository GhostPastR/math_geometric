#ifndef AGL_ALGORITHM_<>_INTERFACE_H
#define AGL_ALGORITHM_<>_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//метод расчитывает координаты новой точки
template<>
inline constexpr auto <>(){
    return geometry::create_point<>();
}

}

#endif // AGL_ALGORITHM_<>_INTERFACE_H
