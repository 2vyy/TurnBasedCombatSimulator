#include "combat_system.h"
#include <iostream>

Combat_System::Combat_System(Team& _team1, Team& _team2) :
	team1(_team1), team2(_team2) {

	// Initialize action value and character-team mappings
	for (Character& character : team1.get_characters()) {
		action_values[&character] = 10000.0f / character.get_speed();
		character_to_team[&character] = &team1;
	}

	for (Character& character : team2.get_characters()) {
		action_values[&character] = 10000.0f / character.get_speed();
		character_to_team[&character] = &team2;
	}
}

void Combat_System::start_combat() {
	while (!team1.is_defeated() && !team2.is_defeated()) {
		Character* next_actor = nullptr; // next_actor is the character with the lowest action value
		float min_av = 100000.0f; // set starting av to very high value;
		// could likely be optimized

		// Find the alive character with the lowest action value
		for (auto& [character, av] : action_values) {
			if (character->is_alive() && av < min_av) {
				min_av = av;
				next_actor = character;
			}
		}

		// if the next_actor is null, it means no characters are alive
		if (!next_actor) { break; }

		//skip to when time equals the current lowest av;
		float time = min_av;
		//then reduce all character's current av by that amount
		for (auto& [character, av] : action_values) {
			av -= time;
		}
		//this is the same as an iterative "tick" system that counts down, but skips all of the empty ticks

		// Search character-team mapping to get the opposite team and an alive character from it.
		Team& opposing_team = get_opposing_team(next_actor);
		auto& targets = opposing_team.get_characters();
		Character* target = nullptr;
		for (auto& t : targets) {
			if (t.is_alive()) { //TODO: should optimize to get the character with the lowest health
				target = &t;
				break;
			}
		}

		if (!target) { break; }
		// if the other team has no alive characters, break the loop
		// TODO: is this necessary? If the next_actor is alive, then the opposing team must have at least one alive character that just went

		std::cout << "Current AV: " << time << " | ";
		next_actor->process_turn(*target);

		// When next_actor has finished their turn, reset their action value
		action_values[next_actor] = 10000.0f / next_actor->get_speed();
	}
}


Team& Combat_System::get_opposing_team(Character* character) {
	Team* actor_team = character_to_team.at(character);
	return (actor_team == &team1) ? team2 : team1; // i love ternary operators :3
}
