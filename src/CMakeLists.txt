add_library(weder_src forecast.cpp http_weather_api.cpp data.cpp)
target_link_libraries(
        weder_src
        CONAN_PKG::nlohmann_json
        CONAN_PKG::cpp-httplib
        CONAN_PKG::fmt)

add_executable(weder main.cpp)
target_link_libraries(weder weder_src)