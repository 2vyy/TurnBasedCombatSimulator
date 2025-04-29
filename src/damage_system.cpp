#include "damage_system.h"
#include <random>

namespace DamageSystem {
	DamageResult calculate_damage(const Character& attacker, const Character& defender, const DamageSettings& settings) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> float_rng(0, 1);

		DamageResult result{};

		Character::CharacterStats attacker_stats = attacker.get_stats();
		Character::CharacterStats defender_stats = defender.get_stats();

		result.base_damage = attacker_stats.attack;
		result.outgoing_damage = result.base_damage;


		// effects here
		// this will need to check the "type" of the effect and tick it if it applies on hit
		for (Effect* effect : attacker.get_effects()) {
			if (effect->triggers_on(EffectTrigger::AttackHit)) {
				effect->apply_to(defender);
				result.effects_applied.push_back(effect->get_description());
			}
		})


		if (float_rng(gen) <= attacker_stats.crit_chance) {
			result.is_crit = true;
			result.outgoing_damage *= attacker_stats.crit_multiplier;
		}
		else {
			result.is_crit = false;
		}

		bool dodge_chance = defender_stats.speed * 0.001f;
		if (float_rng(gen) <= dodge_chance) {
			result.is_dodged = true;
			result.outgoing_damage = 0;
		}
		else {
			result.is_dodged = false;
		}

		bool block_chance = defender_stats.armor * 0.02f;
		if (float_rng(gen) <= dodge_chance) {
			result.is_blocked = true;
			result.outgoing_damage /= 2;
		}
		else {
			result.is_blocked = false;
		}

		// armor calculation
		result.outgoing_damage = result.outgoing_damage * (1 - defender_stats.armor_percent) - defender_stats.armor;

		// damage clamping
		result.outgoing_damage = std::max(0, result.outgoing_damage);

		result.final_damage = result.outgoing_damage;
		return result;
	}
}

