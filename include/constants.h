#pragma once

namespace Constants {
	// CHARACTER STATS
	static const int DEFAULT_HEALTH = 1000;
	static const float MIN_HEALTH_RANGE = 0.5f;
	static const float MAX_HEALTH_RANGE = 2.00f;

	static const int DEFAULT_ATTACK = 500;
	static const float MIN_ATTACK_RANGE = 0.5f;
	static const float MAX_ATTACK_RANGE = 1.5f;

	static const int DEFAULT_SPEED = 100;
	static const float MIN_SPEED_RANGE = 0.7f;
	static const float MAX_SPEED_RANGE = 1.3f;
	// EFFECTS
	// POISON
	// TODO: maybe just store all of these in the actual effect files
	static const std::string POISON_NAME = "Poison";
	static const std::string POISON_MODIFIER = "health";
	static const double POISON_CHANCE = 0.25;
	static const int POISON_DURATION = 3;
	static const int POISON_DAMAGE = -5;

	// REGENERATION
	static const std::string REGEN_NAME = "Regeneration";
	static const std::string REGEN_MODIFIER = "health";
	static const double REGEN_CHANCE = 0.25;
	static const int REGEN_DURATION = 3;
	static const int REGEN_DAMAGE = 5;

}