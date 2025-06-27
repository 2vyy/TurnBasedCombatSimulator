#pragma once
#include <string>
#include <memory>
#include <vector>
#include "effect.h"

class Character {
public:
	struct CharacterStats {
		int max_health;
		int curr_health;
		int attack;
		int speed;
		int armor;
		double armor_percent;
		double crit_chance;
		double crit_multiplier;
	};

	Character(const std::string _name, const CharacterStats _stats);

	void process_turn(Character&);

	void change_health(int);

	void add_effect(Effect* effect);
	void clear_effects();
	std::vector<Effect*> get_effects() const;

	bool is_alive() const;
	std::string get_name_ref() const;
	CharacterStats& get_stats_ref();

private:
	CharacterStats stats;
	const std::string name;
	std::vector<Effect*> effects;
};

