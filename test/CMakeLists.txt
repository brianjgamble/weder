add_executable(tests test_example.cpp)
target_link_libraries(tests doctest::doctest)

add_test(
        NAME UnitTests
        COMMAND tests
)