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

namespace tag {

struct tag_point final{};

struct tag_circle final{};
struct tag_arc final{};

struct tag_straight_line final{};
struct tag_half_line final{};
struct tag_line_section final{};

struct tag_polygon final{};
struct tag_convex_polygone final{};
struct tag_rectangle final{};
struct tag_triangle final{};
struct tag_regular_polygon final{};

}

namespace group {

struct group_point final {};
struct group_line final {};
struct group_elements_circle final {};
struct group_polygon final {};

}

}

#endif // TAG_H
