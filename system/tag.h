#ifndef AGL_SYSTEM_TAG_H
#define AGL_SYSTEM_TAG_H

namespace agl::system::tag{

template<typename Type>
struct value{
    inline constexpr static auto get(const Type &){
        static_assert(false, "Error value!");
    }
};

template<> struct value<int>{
    inline constexpr static auto get(int temp){
        return temp;
    }
};

template<> struct value<float>{
    inline constexpr static auto get(float temp){
        return temp;
    }
};

template<> struct value<double>{
    inline constexpr static auto get(double temp){
        return temp;
    }
};

template<> struct value<long double>{
    inline constexpr static auto get(const long double &temp){
        return temp;
    }
};


}

#endif // AGL_SYSTEM_TAG_H
