#include "damage_system.h"
#include <random>

namespace DamageSystem {
	DamageResult calculate_damage(Character& attacker, Character& defender) {

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> float_rng(0, 1);

		DamageSystem::DamageResult result{};

		Character::CharacterStats attacker_stats = attacker.get_stats_ref();
		Character::CharacterStats defender_stats = defender.get_stats_ref();

		result.base_damage = attacker_stats.attack;
		result.outgoing_damage = result.base_damage;


		// effects here
		// this will need to check the "type" of the effect and tick it if it applies on hit
		/*for (Effect* effect : attacker.get_effects()) {
			for (CombatEventType trigger : effect->get_triggers()) {
				if (trigger == CombatEventType::before_attack) {
					effect->on_before_attack(attacker);
					result.effect_messages.push_back(effect->message);
				}
			}
		}*/


		if (float_rng(gen) <= attacker_stats.crit_chance) {
			result.is_crit = true;
			result.outgoing_damage *= attacker_stats.crit_multiplier;
		}
		else {
			result.is_crit = false;
		}

		// armor calculation
		result.outgoing_damage = result.outgoing_damage * (1 - defender_stats.armor_percent) - defender_stats.armor;

		// damage clamping
		result.outgoing_damage = std::max(0, result.outgoing_damage);

		result.final_damage = result.outgoing_damage;
		return result;
	}
}