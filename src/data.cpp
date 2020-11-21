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

#include "data.h"
#include <string>

std::string weder::Data::getCity() {
    if (j.contains("name"))
        return j["name"].get<std::string>();
    else
        return std::string {};
}

std::string weder::Data::getCurrentTemperature() {
    if (j.contains("main") && j["main"].contains("temp")) {
        auto rounded = (int)round(j["main"]["temp"].get<double>());
        return std::to_string(rounded);
    }
    else
        return std::string {};
}

std::string weder::Data::getWeatherParameters() {
    std::string conditions {};

    if (j.contains("weather")) {
        for (auto condition : j["weather"]) {
            if (!conditions.empty())
                conditions += ", ";
            conditions += condition["main"];
        }
    }
    
    return conditions;
}