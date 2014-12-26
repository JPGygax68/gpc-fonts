project(Font_Tests)

find_package(boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_CharacterSet EXCLUDE_FROM_ALL test_CharacterSet.cpp)
#target_include_directories(test_CharacterSet PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(test_CharacterSet Fonts)
target_link_libraries(test_CharacterSet ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME test_CharacterSet COMMAND test_CharacterSet)

add_dependencies(build_and_test test_CharacterSet)