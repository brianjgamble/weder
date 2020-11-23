#include "config.h"
#include "forecast.h"
#include "http_weather_api.h"
#include "version.h"
#include <fmt/core.h>

enum Commands { CURRENT, VERSION, UNKNOWN };

weder::Config::Parameters loadConfig();
Commands parseOptions(int argc, char* argv[], weder::Config::Parameters& params);
void getCurrentForecast(const weder::Config::Parameters& params);
void usage();

int main(int argc, char* argv[]) {
    auto params  = loadConfig();
    auto command = parseOptions(argc, argv, params);

    switch (command) {
        case VERSION:
            fmt::print("{} version {}\n", PROJECT_NAME, PROJECT_VERSION);
            break;

        case CURRENT:
            getCurrentForecast(params);
            break;

        default:
            usage();
            return 1;
    }

    return 0;
}

weder::Config::Parameters loadConfig() {
    auto j = weder::Config::load();
    return weder::Config::parse(j);
}

Commands parseOptions(int argc, char* argv[], weder::Config::Parameters& params) {
    Commands cmd             = UNKNOWN;
    std::string zipToken     = "--zip";
    std::string apiKeyToken  = "--apiKey";
    std::string versionToken = "--version";

    int i = 1;

    if (argc > 1 && versionToken == argv[i]) {
        cmd = VERSION;
    }
    else {
        while (i < argc) {
            auto s = std::string {argv[i]};

            if (s == zipToken) {
                if (++i < argc) {
                    try {
                        params.zip = std::stoi(argv[i++]);
                        continue;
                    }
                    catch (...) {
                        break;
                    }
                }
            }
            else if (s == apiKeyToken) {
                if (++i < argc) {
                    params.apiKey = argv[i++];
                    continue;
                }
            }
            else {
                break;
            }
        }

        cmd = CURRENT;
    }

    return cmd;
}

void getCurrentForecast(const weder::Config::Parameters& params) {
    auto* lib = new weder::HttpWeatherApi {params.apiKey};
    weder::Forecast forecast {lib};
    auto& data = forecast.currentConditions(params.zip);

    fmt::print("Current conditions:\n");
    fmt::print("{}\n", data.getCity());
    fmt::print("{}°F\n", data.getCurrentTemperature());
    fmt::print("{}\n", data.getWeatherParameters());
}

void usage() {
    fmt::print("Usage:\n\t{} [options]\n", PROJECT_NAME);
    fmt::print("\nOptions:\n");
    fmt::print("\t--zip         Specify the zip code for the current conditions\n");
    fmt::print("\t--apiKey      Provide your OpenWeather API key\n\n");
    fmt::print("\t--version     Display the current version\n");
}