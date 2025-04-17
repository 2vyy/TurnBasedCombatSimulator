#include "team.h"
#include "character.h"
#include "combat_system.h"
#include <unordered_map>
#include <algorithm>

	Combat_System::Combat_System(Team& _team1, Team& _team2) :
		team1(_team1), team2(_team2) {
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
			Character* next_actor = nullptr;
			float min_av = 100000.0f;

			// Manual search through all characters
			for (auto& [character, av] : action_values) {
				if (character->is_alive() && av < min_av) {  // Add alive check
					min_av = av;
					next_actor = character;
				}
			}

			if (!next_actor) {break;}

			//skip to when time equals the current lowest av;
			float time = min_av;
			//then reduce all character's current av by that amount
			for (auto& [character, av] : action_values) {
				av -= time;
			}

			Team& opposing_team = get_opposing_team(next_actor);
			auto& targets = opposing_team.get_characters();
			Character* target = nullptr;
			for (auto& t : targets) {
				if (t.is_alive()) {
					target = &t;
					break;
				}
			}

			if (!target) { break; }

			next_actor->process_turn(*target);

			action_values[next_actor] = 10000.0f / next_actor->get_speed();

		}
	};

	Team& Combat_System::get_opposing_team(Character* character) {
		Team* actor_team = character_to_team.at(character);
		return (actor_team == &team1) ? team2 : team1;
	}
	