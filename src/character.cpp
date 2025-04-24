#include "character.h"
#include "effects/poison_effect.h"
#include "effects/regen_effect.h"
#include "combat_logger.h"
#include "random.h"

Character::Character(const std::string _name, const int _max_health, const int _attack, const int _speed) :
	name(_name), max_health(_max_health), curr_health(_max_health), attack(_attack), speed(_speed) {};

void Character::process_turn(Character& other) {
	other.change_health(-attack);

	//only temporary for testing
	if (Random::get(0, 100) < 10 && other.is_alive()) {
		other.add_effect(new Poison_Effect());
	}

	if (Random::get(0, 100) < 10) {
		add_effect(new Regen_Effect());
	}
}

void Character::change_health(int damage) {
	curr_health += damage;
	if (curr_health < 0) {
		curr_health = 0;
	}
	if (!is_alive()) {
		clear_effects();
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

		if (!is_alive()) {
			clear_effects();
			break;
		}

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

void Character::clear_effects() {
	for (Effect* effect : effects) {
		delete effect;
	}
	effects.clear();
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
//
/*
Plans for refactor:
0. Base character file stays somewhat similar. The idea is to offload the logic into seperate files
1. Effect class with a lookup table and id for each effect
 - Very high level, can be applied to characters and teams
2. Damage class dedicated to calculating damage output
 - base attack, crit chance, crit multiplier, defense, parry, etc.
*/

/* more yapping about engine features
* CORE FEATURES (i will definitely do these)
*  1. critical hits
*      - crit chance, crit multiplier
*      - damage = attack * ( 1 * crit_multiplier )
*      - could probably be a struct because the two values are always connected
*  2. accuracy & evasion
*      - based on speed and armor (more on that later)
*      - speed determines your base accuracy (chance to hit)
*      - speed and armor determinines the opponents evasion (chance to dodge)
*	   - accuracy = speed * constant
*	   - evasion = speed * constant + armor * constant
*      - hit_chance = accuracy / (accuracy + evasion)
* 3. armor & armor types (really just damage reduction)
*      - flat_armor is very simply flat reduction of damage
*	   - armor% is a percentage reduction of damage
*      - attack = (attack - flat_armor) * (1 - armor%)
*      - armor types are what give different armor% while armor is an individual stat
* 
* I WILL PROBABLY DO THESE
*  4. damage types
*      - physical, elemental, etc.
*      - mainly just a form of resistance/weakness
*      - damage = attack * (1 - resistance%)
*  5. weapon proficiency
*      - weapons have different levels that affect accuracy and damage (need to think about this more)
*  6. environmental effects
*      - really just an enum that applies status effects
* 
* END GOAL
*  7. more effects (also teamwide)
*	   - currently there is only poison and regen
*      - TODO: come up with more later
*  8. castorice global passive
*      - will need a brief detour into networking for this
*  9. actual class system (so that this program actually has any sort of interaction)
* 
* am i cooking or am i cooked?
*/