#pragma once

#include "team.h"
#include <unordered_map>

class Combat_System {
public:
	Combat_System(Team&, Team&);
	void start_combat();
private:
	Team& team1;
	Team& team2;
	std::unordered_map<Character*, float> action_values;
	std::unordered_map<Character*, Team*> character_to_team;

	Team& get_opposing_team(Character*);
};