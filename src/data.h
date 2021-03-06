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

#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <utility>

using json = nlohmann::json;

namespace weder {
    class Data {
    public:
        explicit Data(json j) :
            j{std::move(j)} {}
        std::string getCity();
        std::string getCurrentTemperature();
        std::string getWeatherParameters();

    private:
        json j;
    };
}
