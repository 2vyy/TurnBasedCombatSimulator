#include <team.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Team Creation") {
	Character character_one("Test Character 1", 100, 50, 75);
	Character character_two("Test Character 2", 100, 50, 75);

	Team team("Test Team");
	team.add_member(character_one);
	team.add_member(character_two);

	REQUIRE(team.get_characters().size() == 2);
	REQUIRE(team.get_characters()[0].get_name_ref() == "Test Character 1");
	REQUIRE(team.get_characters()[1].get_name_ref() == "Test Character 2");
	REQUIRE(team.get_name_ref() == "Test Team");

	REQUIRE_FALSE(team.is_defeated());

	team.get_characters()[0].take_damage(9999);

	REQUIRE_FALSE(team.is_defeated());

	team.get_characters()[1].take_damage(9999);

	REQUIRE(team.is_defeated());
}