#include "config.h"
#include "forecast.h"
#include "http_weather_api.h"
#include <fmt/core.h>

void usage() {
    fmt::print("Usage:\n\t{} [options]\n", PROJECT_NAME);
    fmt::print("\nOptions:\n");
    fmt::print("\t--zip         Specify the zip code for the current conditions\n");
    fmt::print("\t--apiKey      Provide your OpenWeather API key\n\n");
    fmt::print("\t--version     Display the current version\n");
}

int main(int argc, char* argv[]) {
    int zip;
    std::string apiKey {};

    if (argc == 5 or argc == 2) {
        std::string zipToken     = "--zip";
        std::string apiKeyToken  = "--apiKey";
        std::string versionToken = "--version";

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
            else if (s == versionToken) {
                fmt::print("{} version {}\n", PROJECT_NAME, PROJECT_VERSION);
                return 0;
            }
            else {
                fmt::print("Invalid option: {}\n\n", s);
                usage();
                return 1;
            }
        }
    }
    else {
        usage();
        return 1;
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
