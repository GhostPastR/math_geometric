cmake_minimum_required(VERSION 3.19)
project(math_geometric LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Test)
set(CMAKE_CXX_STANDARD 20)

qt_standard_project_setup()

qt_add_executable(math_geometric
    main.cpp
    unit_test.h
    unit_test.cpp




    algorithm/math_algorithm.h
    algorithm/point_algorithm.h

    algorithm/matrix_algorithm.h


    structs/struct_geo_imp.h
    structs/matrix.h
    structs/vector.h
    system/system_concept.h

    user_type.h

    unit/angle.h
    unit/distance.h
    unit/speed.h
    unit/time.h
    unit/weight.h
    unit/temperature.h
    iterator/matrix_iterator.h
    special_algorithms/navigation_route/figure_route.h
    unit_test_sa.h unit_test_sa.cpp
    special_algorithms/navigation_route/algorithm_route.h
    algorithm/distance/implementation.h algorithm/distance/interface.h

    algorithm/direction/implementation.h algorithm/direction/interface.h
    algorithm/convert/implementation.h algorithm/convert/interface.h algorithm/create_point/implementation.h algorithm/create_point/interface.h algorithm/midplane/implementation.h algorithm/midplane/interface.h algorithm/rotate/implementation.h algorithm/rotate/interface.h
    algorithm/tag_algoritm.h

    algorithm/convert/implementation_convert.h
    algorithm/create_point/implementation_geo.h
    algorithm/distance/implementation_cartesian.h
    algorithm/distance/implementation_geo.h

    unit/unit.h
    algorithm/distance/implementation_arc_cartesian.h
    algorithm/equation_of_line/implementation.h algorithm/equation_of_line/interface.h
    algorithm/distance/implementation_line_cartesian.h
    algorithm/belongs_to_area_of_line/implementation.h algorithm/belongs_to_area_of_line/interface.h
    algorithm/point_on_curve/implementation.h algorithm/point_on_curve/interface.h
    algorithm/intersection/implementation.h algorithm/intersection/interface.h
    algorithm/intersection/implementation_cartesian.h
    algorithm/contain/implementation.h algorithm/contain/interface.h
    algorithm/perpendicular/implementation.h algorithm/perpendicular/interface.h
    algorithm/parallel/implementation.h algorithm/parallel/interface.h
    testunit.h testunit.cpp
    algorithm/algorithm.h
    structs/geometric/arc.h structs/geometric/circle.h structs/geometric/decart_point2d.h structs/geometric/decart_point3d.h structs/geometric/geo_point2d.h structs/geometric/geo_point3d.h structs/geometric/half_line.h structs/geometric/line_section.h structs/geometric/polar_point2d.h structs/geometric/polar_point3d.h structs/geometric/straight_line.h
    structs/geometric_object.h
    unit/unit_object.h
    testgeometricstruct.h testgeometricstruct.cpp
    system/traits.h
    system/tag.h
    system/assert.h
    testalgorithm.h testalgorithm.cpp
    algorithm/distance/implementation_d2.h
    structs/geometric/polygon.h
    algorithm/is_correct_polygon/implementation.h algorithm/is_correct_polygon/interface.h
    algorithm/center/implementation.h algorithm/center/interface.h
    algorithm/create_polygon/implementation.h algorithm/create_polygon/interface.h
    algorithm/tangent_circle/implementation.h algorithm/tangent_circle/interface.h
    algorithm/create_circle/implementation.h algorithm/create_circle/interface.h
    algorithm/get_lines/implementation.h algorithm/get_lines/interface.h
    algorithm/point_coupling/implementation.h algorithm/point_coupling/interface.h
    system/traits_standart.h
    algorithm/scaling/implementation.h algorithm/scaling/interface.h
    structs/traits/traits_arc.h structs/traits/traits_circle.h structs/traits/traits_decart_point2d.h structs/traits/traits_decart_point3d.h structs/traits/traits_geo_point2d.h structs/traits/traits_geo_point3d.h structs/traits/traits_half_line.h structs/traits/traits_line_section.h structs/traits/traits_polar_point2d.h structs/traits/traits_polar_point3d.h structs/traits/traits_polygon.h structs/traits/traits_straight_line.h

    structs/geometric/model_point.h
    algorithm/splitting/implementation.h algorithm/splitting/interface.h


)

target_link_libraries(math_geometric PRIVATE Qt::Core Qt6::Test)
include_directories(${PROJECT_SOURCE_DIR})


include(GNUInstallDirs)

install(TARGETS math_geometric
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET math_geometric
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
add_subdirectory(TestGraphics)

