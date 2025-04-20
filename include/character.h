#pragma once
#include <string>
#include <memory>
#include <vector>
#include "effect.h"

class Character {
public:
	Character(const std::string _name, const int _max_health, const int _attack, const int _speed);

	void process_turn(Character&) const;

	void take_damage(int);

	void add_effect(Effect* effect);
	void update_effects();

	bool is_alive() const;
	std::string get_name_ref() const;
	int get_max_health() const;
	int get_health() const;
	int get_attack() const;
	int get_speed() const;
private:
	const std::string name;
	std::vector<Effect*> effects;
	const int max_health;
	int curr_health;
	const int attack;
	const int speed;
};

