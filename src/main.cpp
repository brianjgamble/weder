#include "forecast.h"
#include "http_weather_api.h"
#include <fmt/core.h>

int main(int argc, char* argv[]) {
    int zip;
    std::string apiKey {};

    if (argc != 3) {
        fmt::print("Usage:\n\tweder [flags]\n");
        fmt::print("\nFlags:\n");
        fmt::print("\t--zip         Specify the zip code for the current conditions\n");
        fmt::print("\t--apiKey      Provide your OpenWeather API key\n");
        return 1;
    }
    else {
        std::string zipToken    = "--zip=";
        std::string apiKeyToken = "--apiKey=";

        for (int i = 0; i < argc; i++) {
            auto s = std::string {argv[i]};

            if (s.find(zipToken) != std::string::npos) {
                zip = std::stoi(s.substr(6));
            }
            else if (s.find(apiKeyToken) != std::string::npos) {
                apiKey = s.substr(9);
            }
        }
    }

    auto* lib = new weder::HttpWeatherApi {apiKey};
    weder::Forecast forecast {lib};
    auto& data = forecast.currentConditions(zip);

    fmt::print("Current conditions:\n");
    fmt::print("{}\n", data.getCity());
    fmt::print("{}°F\n", data.getCurrentTemperature());
    fmt::print("{}\n", data.getWeatherParameters());

    return 0;
}
