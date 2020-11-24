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

#include "forecast.h"
#include <fmt/core.h>

weder::Data& weder::Forecast::currentConditions(int zip) {
    auto response = api->get(fmt::format("/data/2.5/weather?zip={}&units=imperial", zip));
    if (response.status == 200) {
        static weder::Data data {response.content};
        return data;
    }
    else {
        switch (response.status) {
            case 401:
                throw std::runtime_error {"Invalid API key"};

            case 404:
                throw std::runtime_error {"City not found"};

            default:
                auto msg = response.content["message"].get<std::string>();
                throw std::runtime_error {msg};
        }
    }
}
