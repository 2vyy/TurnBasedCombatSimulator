#include <character.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Character Creation") {
	Character character("Test Character", 100, 50, 75);
	REQUIRE(character.get_name_ref() == "Test Character");
	REQUIRE(character.get_health() == 100);
	REQUIRE(character.get_attack() == 50);
	REQUIRE(character.get_speed() == 75);
	REQUIRE(character.is_alive());
}

TEST_CASE("Character Health Changes") {
	Character character("Test Character", 100, 50, 75);
	character.take_damage(90);

	REQUIRE(character.get_health() == 10);
	REQUIRE(character.is_alive());

	character.take_damage(15);
	REQUIRE(character.get_health() == 0);
	REQUIRE_FALSE(character.is_alive());

	character.take_damage(10); // shouldnt go below 0
	REQUIRE(character.get_health() == 0);
	REQUIRE_FALSE(character.is_alive());
}