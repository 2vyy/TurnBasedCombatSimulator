#include "team.cpp";
#include "character.cpp";
#include <unordered_map>;

class Combat_System {
	public:
		Combat_System(Team& _team1, Team& _team2) :
			team1(_team1), team2(_team2) {
			for (Character& character : _team1.get_characters()) {
				action_values[&character] = 10000.0f / character.get_speed();
				character_to_team_[&character] = &_team1;
			}

			for (Character& character : _team2.get_characters()) {
				action_values[&character] = 10000.0f / character.get_speed();
				character_to_team_[&character] = &_team2;
			}
		}
		//
		void start_combat() {
			while (!team1.is_defeated() && !team1.is_defeated()) {

				Character* next_actor;
				float min_av = 100000.0f;

				// Manual search through all characters
				for (auto& pair : action_values) {
					if (pair.second < min_av) {
						min_av = pair.second;
						next_actor = pair.first;
					}
				}

				//skip to when time equals the current lowest av;
				float time = min_av;
				//then reduce all character's current av by that amount
				for (auto& [character, av] : action_values) {
					av -= time;
				}

				Team& opposing_team = get_opposing_team(next_actor);
				Character* target = opposing_team[0];
				next_actor.process_turn(target); 

				action_values[next_actor] = 10000.0f / next_actor.get_speed();

				team1.remove_dead();
				team2.remove_dead();

			}
		};

	private:
		Team& team1;
		Team& team2;
		std::unordered_map<Character*, float> action_values;
		std::unordered_map<Character*, Team*> character_to_team_;  // New tracking map

		Team& get_opposing_team(Character* actor) {
			if (character_to_team_[actor] == &team1) {
				return team2;
			}
			else {
				return team1;
			}
};