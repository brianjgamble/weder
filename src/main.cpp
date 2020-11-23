#include "config.h"
#include "forecast.h"
#include "http_weather_api.h"
#include "version.h"
#include <fmt/core.h>

enum Commands { CURRENT, VERSION, HELP, UNKNOWN };

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

        case HELP:
            usage();
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
    Commands cmd = CURRENT;
    int i        = 1;

    if (argc > 1) {
        if (std::string("--version") == argv[i]) {
            cmd = VERSION;
        }
        else if (std::string("--help") == argv[i] || std::string("-h") == argv[i]) {
            cmd = HELP;
        }
        else {
            while (i < argc) {
                if (std::string("--zip") == argv[i]) {
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
                else if (std::string("--apiKey") == argv[i]) {
                    if (++i < argc) {
                        params.apiKey = argv[i++];
                        continue;
                    }
                }
                else {
                    fmt::print("Unknown option: {}\n\n", argv[i]);
                    cmd = UNKNOWN;
                    break;
                }
            }
        }
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
    fmt::print("Usage:\n\t{} [--version] [--help] [options]\n", PROJECT_NAME);
    fmt::print("\nOptions:\n");
    fmt::print("\t--zip         Specify the zip code for the current conditions\n");
    fmt::print("\t--apiKey      Provide your OpenWeather API key\n");
}