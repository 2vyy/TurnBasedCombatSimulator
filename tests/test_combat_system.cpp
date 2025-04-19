#include "combat_system.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Action Value Test") {
	Character fast{ "Test Character", 100, 50, 50 };
	Character slow{ "Test Character", 100, 50, 25 };

	Team fast_team{ "Fast Team" };
	fast_team.add_member(fast);
	Team slow_team{ "Slow Team" };
	slow_team.add_member(slow);

	Combat_System combat_system{ fast_team, slow_team };
	combat_system.start_combat();

	REQUIRE(slow_team.is_defeated());
}