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

#include "current_command.h"
#include <fmt/core.h>

namespace weder {
    void CurrentCommand::execute() {
        try {
            auto& data = forecast.currentConditions(zipCode);

            output.write(fmt::format("Current conditions:\n"));
            output.write(fmt::format("{}\n", data.getCity()));
            output.write(fmt::format("{}°F\n", data.getCurrentTemperature()));
            output.write(fmt::format("{}\n", data.getWeatherParameters()));
        }
        catch (std::runtime_error& ex) {
            output.write(fmt::format("Error: {}\n", ex.what()));
        }
    }
}