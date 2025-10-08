#ifndef TAG_H
#define TAG_H

namespace agl{

struct undefined final{};

namespace system_coordinat {

struct cartesian final{};
struct polar final{};
struct spherical final{};
struct geographical final{};

namespace geo {

struct sc_default final{};
struct wgs_84 final{};
struct pz_90_02 final{};

}

}

namespace tag::point {

struct point final{};

}

namespace tag::elements_circle {

struct circle final{};
struct arc final{};

}

namespace tag::line {

struct straight_line final{};
struct half_line final{};
struct line_section final{};

}

namespace tag::polygon {

//tag polygon
struct non_convex final{};
struct convex final{};
struct self_intersecting final{};
struct regular final{};
//triangles
struct triangle final{};
struct rectangular_triangle final{};

//quadrilaterals
struct rectangle final{};

}


namespace group {

struct points final {};
struct lines final {};
struct elements_circles final {};
struct polygons final {};

}

}


#endif // TAG_H
