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

#include "factory.h"

json Factory::currentConditions() {
    return R"(
        {
          "coord": {
            "lon": -122.88,
            "lat": 47.01
          },
          "weather": [{
            "id": 501,
            "main": "Rain",
            "description": "moderate rain",
            "icon": "10n"
          }, {
            "id": 701,
            "main": "Mist",
            "description": "mist",
            "icon": "50n"
          }],
          "base": "stations",
          "main": {
            "temp": 44.76,
            "feels_like": 37.11,
            "temp_min": 43,
            "temp_max": 45,
            "pressure": 1029,
            "humidity": 93
          },
          "visibility": 8047,
          "wind": {
            "speed": 9.17,
            "deg": 200
          },
          "rain": {
            "1h": 1.15
          },
          "clouds": {
            "all": 90
          },
          "dt": 1605851107,
          "sys": {
            "type": 1,
            "id": 5197,
            "country": "US",
            "sunrise": 1605799302,
            "sunset": 1605832366
          },
          "timezone": -28800,
          "id": 0,
          "name": "Olympia",
          "cod": 200
        }
    )"_json;
}
