cmake_minimum_required(VERSION 3.19)
project(math_geometric LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Test)
set(CMAKE_CXX_STANDARD 20)

qt_standard_project_setup()

qt_add_executable(math_geometric
    main.cpp
    unit_test.h
    unit_test.cpp
    algorithm/approximation_algorithm.h
    algorithm/circle_algorithm.h
    algorithm/geo_algorithm.h
    algorithm/line_algorithm.h
    algorithm/math_algorithm.h
    algorithm/point_algorithm.h
    algorithm/polygon_algorithm.h
    algorithm/matrix_algorithm.h
    structs/circle_impl.h
    structs/line_impl.h
    structs/point_impl.h
    structs/polygon_impl.h
    structs/struct_geo_imp.h
    structs/matrix.h
    structs/vector.h
    system/system_concept.h
    system/system_function.h
    user_type.h
    system/system_unit.h
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
)

target_link_libraries(math_geometric PRIVATE Qt::Core Qt6::Test)

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
