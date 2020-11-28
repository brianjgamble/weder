set(testFiles
        data/factory.cpp
        commands_tests.cpp)

add_library(doctest_main STATIC doctest_main.cpp)
target_link_libraries(doctest_main PUBLIC CONAN_PKG::doctest)

add_executable(tests tests.cpp ${testFiles})
target_link_libraries(
        tests
        PRIVATE
        doctest_main
        weder_src
        CONAN_PKG::fmt)