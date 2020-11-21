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

#include "http_weather_api.h"
#include <fmt/format.h>
#include <httplib.h>

using namespace httplib;

json weder::HttpWeatherApi::get(std::string_view path) {
    Client cli(host);

    std::string url = fmt::format("{}&appid={}", path, apiKey);

    if (auto res = cli.Get(url.c_str())) {
        if (res->status == 200) {
            return json::parse(res->body);
        }
    }

    return json();
}
