#include "commands/console_output.h"
#include "commands/help_command.h"
#include "commands/version_command.h"
#include "config.h"
#include "forecast.h"
#include "http_weather_api.h"
#include <fmt/core.h>

enum Commands { CURRENT, VERSION, HELP, UNKNOWN };

weder::Config::Parameters loadConfig();
Commands parseOptions(int argc, char* argv[], weder::Config::Parameters& params);
void getCurrentForecast(const weder::Config::Parameters& params);
void printVersion();
void usage();

auto output = weder::ConsoleOutput {};

int main(int argc, char* argv[]) {
    auto params  = loadConfig();
    auto command = parseOptions(argc, argv, params);

    switch (command) {
        case VERSION:
            printVersion();
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

    try {
        auto& data = forecast.currentConditions(params.zip);

        fmt::print("Current conditions:\n");
        fmt::print("{}\n", data.getCity());
        fmt::print("{}°F\n", data.getCurrentTemperature());
        fmt::print("{}\n", data.getWeatherParameters());
    }
    catch (std::runtime_error& ex) {
        fmt::print("Error: {}\n", ex.what());
        exit(1);
    }
}

void printVersion() {
    auto cmd = weder::VersionCommand {output};
    cmd.execute();
}

void usage() {
    auto cmd = weder::HelpCommand {output};
    cmd.execute();
}