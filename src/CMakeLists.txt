set(files
        forecast.cpp
        http_weather_api.cpp
        data.cpp
        config.cpp
        commands/version_command.cpp
        commands/help_command.cpp)

add_library(weder_src ${files})
target_link_libraries(
        weder_src
        CONAN_PKG::nlohmann_json
        CONAN_PKG::cpp-httplib
        CONAN_PKG::fmt)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} weder_src)