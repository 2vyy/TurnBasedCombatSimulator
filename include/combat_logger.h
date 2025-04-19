#include "team.h"

class Combat_Logger {
	public:
		static void log_init(Team& team1, Team& team2);
		static void log_turn(const Character& actor, const Character& target, float av);
		static void log_death(const Character& character);
		static void log_end(const Team& winning_team);
};

/*
TODO:
Show initial stats and teams
Damage changes
Death announcements
Victory conditions
color-coded teams
action_value rounding
turn counter
*/