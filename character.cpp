#include <string>
#include <iostream>
#include "team.h"
#include "character.h"

void Character::take_damage(int damage) {
	curr_health -= damage;
}

bool Character::is_alive() const {
	return curr_health > 0;
}

void Character::process_turn(Character& other) {
	other.take_damage(attack);
	std::cout << name << " (" << curr_health << " health) attacks "
		<< other.get_name() << " (" << other.get_health() << " health) for "
		<< attack << "!\n";

	if (!other.is_alive()) {
		std::cout << other.get_name() << " has been defeated!\n";
	}
}

int Character::get_speed() const {
	return speed;
}

int Character::get_health() const {
	return curr_health;
}

std::string Character::get_name() const {
	return name;
}