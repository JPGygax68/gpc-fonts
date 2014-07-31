
find_package(boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_fonts EXCLUDE_FROM_ALL test_fonts.cpp)

target_include_directories(test_fonts PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(test_fonts ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_dependencies(CHECK test_fonts)
add_test(NAME test_fonts COMMAND test_fonts)
