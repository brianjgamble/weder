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

#include "help_command.h"
#include "../version.h"
#include <fmt/core.h>

namespace weder {
    void HelpCommand::execute()
    {
        output.write(fmt::format("Usage:\n"));
        output.write(fmt::format("\t{} [--version] [--help] [options]\n", PROJECT_NAME));
        output.write(fmt::format("\nOptions:\n"));
        output.write(
            fmt::format("\t--zip         Specify the zip code for the current conditions\n"));
        output.write(fmt::format("\t--apiKey      Provide your OpenWeather API key\n"));
    }
}
