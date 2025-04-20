#include "character.h"
#include "poison_effect.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Poison Test") {
	Character character{ "Test Character", 100, 50, 50 };
	Character testing_dummy{ "Testing Dummy", 100, 50, 50 };

	character.add_effect(new Poision_Effect(3, 5));

	character.update_effects();
	REQUIRE(character.get_health() == 100 - 5);

	character.update_effects();
	REQUIRE(character.get_health() == 100 - 5 * 2);

	character.update_effects();
	REQUIRE(character.get_health() == 100 - 5 * 3);

	character.update_effects();
	REQUIRE(character.get_health() == 100 - 5 * 3);
}