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

#include "config.h"
#include <fmt/format.h>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

json weder::Config::load()
{
    json j;
    auto homePath = std::getenv("HOME");

    if (homePath != nullptr) {
        // Read in the json parameters from the config file
        try {
            auto filename = fmt::format("{}/.weder.json", homePath);
            std::ifstream i(filename);
            i >> j;
        }
        catch (...) {
        }
    }

    return j;
}

weder::Config::Parameters weder::Config::parse(json j)
{
    auto params = weder::Config::Parameters();

    if (j.contains("zip")) {
        params.zip = j["zip"].get<int>();
    }

    if (j.contains("apiKey")) {
        params.apiKey = j["apiKey"].get<std::string>();
    }

    return params;
}

bool weder::Config::Parameters::valid() const
{
    return zip > 0 && !apiKey.empty();
}
