#include "forecast.h"
#include "http_weather_api.h"
#include <fmt/core.h>

void usage() {
    fmt::print("Usage:\n\tweder [options]\n");
    fmt::print("\nOptions (required):\n");
    fmt::print("\t--zip         Specify the zip code for the current conditions\n");
    fmt::print("\t--apiKey      Provide your OpenWeather API key\n");
}

int main(int argc, char* argv[]) {
    int zip;
    std::string apiKey {};

    if (argc != 5) {
        usage();
        return 1;
    }
    else {
        std::string zipToken    = "--zip";
        std::string apiKeyToken = "--apiKey";

        int i = 1;
        while (i < argc) {
            auto s = std::string {argv[i]};

            if (s == zipToken) {
                if (++i < argc) {
                    try {
                        zip = std::stoi(argv[i++]);
                        continue;
                    }
                    catch (...) {
                        fmt::print("Invalid zip\n");
                        return 1;
                    }
                }
            }
            else if (s == apiKeyToken) {
                if (++i < argc) {
                    apiKey = argv[i++];
                    continue;
                }
            }
            else {
                fmt::print("Invalid option: {}\n\n", s);
                usage();
                return 1;
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
