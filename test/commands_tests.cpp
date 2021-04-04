/*
 * Copyright 2020 Brian J. Gamble
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "../src/commands/current_command.h"
#include "../src/commands/help_command.h"
#include "../src/commands/version_command.h"
#include "../src/version.h"
#include "helpers/fake_forecast.h"
#include "helpers/string_output.h"
#include <doctest/doctest.h>
#include <fmt/format.h>

TEST_CASE("version command prints the current version")
{
    auto output          = StringOutput{};
    auto cmd             = weder::VersionCommand{output};
    std::string expected = fmt::format("weder version {}\n", PROJECT_VERSION);

    cmd.execute();

    REQUIRE(output.captured(expected));
}

TEST_CASE("help command prints the usage information")
{
    auto output = StringOutput{};
    auto cmd    = weder::HelpCommand{output};

    std::string expected = R"(Usage:
	weder [--version] [--help] [options]

Options:
	--zip         Specify the zip code for the current conditions
	--apiKey      Provide your OpenWeather API key
)";

    cmd.execute();

    REQUIRE(output.captured(expected));
}

TEST_CASE("current command prints the current conditions")
{
    auto output       = StringOutput{};
    auto fakeForecast = FakeForecast{};
    auto cmd          = weder::CurrentCommand{output, fakeForecast, 98502};

    std::string expected = R"(Current conditions:
Olympia
45°F
Rain, Mist
)";

    cmd.execute();

    REQUIRE(output.captured(expected));
}