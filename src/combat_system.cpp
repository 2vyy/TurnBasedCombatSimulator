#include "combat_system.h"
#include "combat_logger.h"
#include "damage_system.h"

Combat_System::Combat_System(Team& _team1, Team& _team2) :
	team1(_team1), team2(_team2), total_av(0), turn_count(0) {

	// Initialize action value and character-team mappings
	for (Character& character : team1.get_characters()) {
		Character::CharacterStats stats = character.get_stats();
		action_values[&character] = 10000.0f / stats.speed;
		character_to_team[&character] = &team1;
	}

	for (Character& character : team2.get_characters()) {
		Character::CharacterStats stats = character.get_stats();
		action_values[&character] = 10000.0f / stats.speed;
		character_to_team[&character] = &team2;
	}
}

void Combat_System::start_combat() {
	Combat_Logger::log_init(team1, team2);
	turn_count = 0;
	total_av = 0.0f;

	while (!team1.is_defeated() && !team2.is_defeated()) {
		Character* next_actor = nullptr; // next_actor is the character with the lowest action value
		float min_av = 100000.0f; // set starting av to very high value;
		// TODO: set to numerical limit

		// Find the alive character with the lowest action value
		for (auto& [character, av] : action_values) {
			if (character->is_alive() && av < min_av) {
				min_av = av;
				next_actor = character;
			}
		}

		// if the next_actor is null, it means no characters are alive
		if (!next_actor) { break; }

		//skip to when time equals the current lowest av;
		total_av += min_av;
		//then reduce all character's current av by that amount
		for (auto& [character, av] : action_values) {
			av -= min_av;
		}
		//this is the same as an iterative "tick" system that counts down, but skips all of the empty ticks

		// search character-team mapping to get the opposite team and an alive character from it.
		Team& opposing_team = get_opposing_team(next_actor);
		auto& targets = opposing_team.get_characters();
		Character* target = nullptr;
		int lowest_health = 9999; // TODO: please use numeric limits
		for (auto& t : targets) {
			Character::CharacterStats stats = t.get_stats();
			if (t.is_alive() && stats.curr_health < lowest_health) {
				target = &t;
				lowest_health = stats.curr_health;
			}
		}

		if (!target) { break; }
		// if the other team has no alive characters, break the loop
		// TODO: is this necessary? If the next_actor is alive, then the opposing team must have at least one alive character that just went

		Combat_Logger::log_turn(*next_actor,
								*character_to_team[next_actor],
								*target,
								opposing_team,
								++turn_count);

		CombatEventContext context{
			next_actor,
			target,
			min_av
		};

		notify_effects(CombatEventType::turn_start, context);
		if (context.cancel) {
			action_values[next_actor] = 10000.0f / next_actor->get_stats().speed;
			Combat_Logger::log_cancel(*next_actor);
			continue; //skip
		}

		notify_effects(CombatEventType::before_attack, context);
		resolve_attack(context, next_actor, target);
		notify_effects(CombatEventType::after_attack, context);

		notify_effects(CombatEventType::turn_end, context);

		if (!target->is_alive()) {
			Combat_Logger::log_death(*target, opposing_team);
		}


		// when next_actor has finished their turn, reset their action value
		action_values[next_actor] = 10000.0f / next_actor->get_stats().speed;
	}

	Combat_Logger::log_end(team1, team2, turn_count);
}


Team& Combat_System::get_opposing_team(Character* character) {
	Team* actor_team = character_to_team.at(character);
	return (actor_team == &team1) ? team2 : team1; // i love ternary operators :3
}

void notify_effects(CombatEventType type, CombatEventContext& ctx) {
	for (Effect* effect : ctx.attacker->get_effects()) {
		for (CombatEventType trigger : effect->get_triggers()) {
			if (trigger == type) {
				switch (type) {
					case CombatEventType::turn_start:
						effect->on_turn_start(*ctx.attacker);
						break;
					case CombatEventType::turn_end:
						effect->on_turn_end(*ctx.attacker);
						break;
					case CombatEventType::before_attack:
						effect->on_before_attack(*ctx.attacker);
						break;
					case CombatEventType::after_attack:
						effect->on_after_attack(*ctx.attacker);
						break;
					case CombatEventType::on_death:
						effect->on_death(*ctx.attacker);
						break;
					case CombatEventType::on_revive:
						effect->on_revive(*ctx.attacker);
						break;
					case CombatEventType::effect_apply:
						effect->on_effect_apply(*ctx.attacker);
						break;
					case CombatEventType::effect_expire:
						effect->on_effect_expire(*ctx.attacker);
						break;
					}
			}
		}
	}
}

void Combat_System::resolve_attack(CombatEventContext& context) {
	DamageSystem::DamageResult result = DamageSystem::calculate_damage(*context.attacker, *context.defender);
	Combat_Logger::log_attack(context,
		*character_to_team[context.attacker],
		result
	);
	if (!result.is_blocked && !result.is_dodged) {
		context.defender->change_health(-result.final_damage);
	}
};
