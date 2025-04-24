#include "character.h"
#include "effects/poison_effect.h"
#include "effects/regen_effect.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Poison Test: Basic") {
	Character character{ "Test Character", 100, 50, 50 };
	character.add_effect(new Poison_Effect());

	// TODO: derive these from constants
	character.update_effects();
	REQUIRE(character.get_health() == 95);

	character.update_effects();
	REQUIRE(character.get_health() == 90);

	character.update_effects();
	REQUIRE(character.get_health() == 85);

	character.update_effects();
	REQUIRE(character.get_health() == 85);
}

TEST_CASE("Poison Effect: Overflow") {
	Character character{ "Test Character", 100, 50, 50 };
	character.add_effect(new Poison_Effect());
	character.change_health(-90);

	character.update_effects();
	REQUIRE(character.get_health() == 5);

	character.update_effects();
	REQUIRE(character.get_health() == 0);
	REQUIRE_FALSE(character.is_alive());

	character.update_effects();
	REQUIRE(character.get_health() == 0);
	REQUIRE_FALSE(character.is_alive());
}

TEST_CASE("Regeneration Test: Basic") {
	Character character{ "Test Character", 100, 50, 50 };
	character.change_health(-50);

	character.add_effect(new Regen_Effect());

	character.update_effects();
	REQUIRE(character.get_health() == 55);

	character.update_effects();
	REQUIRE(character.get_health() == 60);

	character.update_effects();
	REQUIRE(character.get_health() == 65);

	character.update_effects();
	REQUIRE(character.get_health() == 65);
}

TEST_CASE("Regeneration Test: Overflow") {
	Character character{ "Test Character", 100, 50, 50 };
	character.change_health(-10);

	character.add_effect(new Regen_Effect());

	character.update_effects();
	REQUIRE(character.get_health() == 95);

	character.update_effects();
	REQUIRE(character.get_health() == 100);

	character.update_effects();
	REQUIRE(character.get_health() == 100);
}