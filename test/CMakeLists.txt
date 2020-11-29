set(testFiles
        helpers/factory.cpp
        helpers/fake_forecast.cpp
        helpers/string_output.h
        data_tests.cpp
        commands_tests.cpp)

add_library(doctest_main STATIC doctest_main.cpp)
target_link_libraries(doctest_main PUBLIC CONAN_PKG::doctest)

add_executable(tests ${testFiles})
target_link_libraries(
        tests
        PRIVATE
        doctest_main
        weder_src
        CONAN_PKG::fmt)