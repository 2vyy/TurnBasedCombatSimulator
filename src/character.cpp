#include "character.h"
#include "poison_effect.h"
#include "combat_logger.h"
#include "random.h"

Character::Character(const std::string _name, const int _max_health, const int _attack, const int _speed) :
	name(_name), max_health(_max_health), curr_health(_max_health), attack(_attack), speed(_speed) {};

void Character::process_turn(Character& other) const {
	other.take_damage(attack);

	if (Random::get(0, 100) < 10 && other.is_alive()) {
		other.add_effect(new Poision_Effect(3, 5));
	}
}

void Character::add_effect(Effect* effect) {
	effects.push_back(effect);
	effects.back()->on_apply(*this);
}

void Character::update_effects() {
	// apply effects and remove expired ones
	auto it = effects.begin();
	while (it != effects.end()) {
		(*it)->on_tick(*this);

		if ((*it)->is_expired()) {
			(*it)->on_expire(*this);
			delete* it;
			it = effects.erase(it);
		}
		else {
			++it;
		}
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

std::string Character::get_name_ref() const {
	return const_cast<std::string&>(name);
}

int Character::get_max_health() const {
	return max_health;
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

/*
Plans for refactor:
0. Base character file stays somewhat similar. The idea is to offload the logic into seperate files
1. Effect class with a lookup table and id for each effect
 - Very high level, can be applied to characters and teams
2. Damage class dedicated to calculating damage output
 - base attack, crit chance, crit multiplier, defense, parry, etc.
3. Characters will be defined by a simple struct and class type
4. Action class to distinguish between attacking and healing
5. Look into unique_ptr


*/