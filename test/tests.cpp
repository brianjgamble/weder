#include "../src/data.h"
#include "data/factory.h"
#include <doctest/doctest.h>

TEST_CASE("can handle valid json weather data") {
    auto j = Factory::currentConditions();
    weder::Data data {j};

    SUBCASE("returns the valid city") {
        CHECK(data.getCity() == "Olympia");
    }

    SUBCASE("returns the currentConditions temperature") {
        CHECK(data.getCurrentTemperature() == "45");
    }

    SUBCASE("returns the weather parameters") {
        CHECK(data.getWeatherParameters() == "Rain, Mist");
    }
}

TEST_CASE("can handle blank json weather data") {
    weder::Data data {json {}};

    SUBCASE("returns a blank city") {
        CHECK(data.getCity() == "");
    }

    SUBCASE("returns the currentConditions temperature") {
        CHECK(data.getCurrentTemperature() == "");
    }

    SUBCASE("returns the weather parameters") {
        CHECK(data.getWeatherParameters() == "");
    }
}