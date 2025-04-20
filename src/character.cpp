#include "character.h"
#include "poison_effect.h"
#include "combat_logger.h"

Character::Character(const std::string _name, const int _max_health, const int _attack, const int _speed) :
	name(_name), max_health(_max_health), curr_health(_max_health), attack(_attack), speed(_speed) {};

void Character::process_turn(Character& other) const {
	other.take_damage(attack);
	other.add_effect(new Poision_Effect(3, 5));
	Combat_Logger::log_poison(other, 5);

}

/*incoming yap session about why this effect system has to be like this
* 1. if we treated these as objects, there would be problems with memory management
*  - who deletes it?
*  - trying to use pointers to them would be a nightmare with ownership abiguity and such in order to avoid memory leaks
* 2. smart pointers (unique_ptr) fix this
*  - they manage their own memory
*  - ownership can easily be moved (only 1 owner)
* 3. first line essentially converts effect into an rvalue reference that is owned by effects
* 4. second line dereferences the newly moved effect reference and calls on_apply.
* 5. thank you c++
*/

void Character::add_effect(Effect* effect) {
	effects.push_back(effect);
}

void Character::update_effects() {
	// apply effects and remove expired ones
	auto it = effects.begin();
	while (it != effects.end()) {
		(*it)->on_apply(*this);

		(*it)->on_tick(*this);

		if ((*it)->is_expired()) {
			delete* it;  // this is probably not the best way to do this but all good 
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