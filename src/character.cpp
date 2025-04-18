#include <iostream>
#include "character.h"

Character::Character(const std::string _name, const int _max_health, const int _attack, const int _speed) :
	name(_name), max_health(_max_health), curr_health(_max_health), attack(_attack), speed(_speed) {};

void Character::process_turn(Character& other) {
	other.take_damage(attack);
	std::cout << name << " (" << curr_health << " health) attacks "
		<< other.get_name_ref() << " (" << other.get_health() << " health) for "
		<< attack << "!\n";

	if (!other.is_alive()) {
		std::cout << other.get_name_ref() << " has been defeated!\n";
	}
}

void Character::take_damage(int damage) {
	curr_health -= damage;
	if (curr_health < 0) {
		curr_health = 0;
	}
}

bool Character::is_alive() const {
	return curr_health > 0;
}

std::string& Character::get_name_ref() const {
	return const_cast<std::string&>(name);
}

int Character::get_health() const {
	return curr_health;
}

int Character::get_attack() const {
	return attack;
}

int Character::get_speed() const {
	return speed;
}