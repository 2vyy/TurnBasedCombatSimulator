#include "poison_effect.h"
#include "combat_logger.h"
#include <fmt/core.h>

Poison_Effect::Poison_Effect() {}

std::vector<CombatEventType> Poison_Effect::get_triggers() const {
    return {
        CombatEventType::turn_end,
        CombatEventType::effect_apply,
        CombatEventType::effect_expire
    };
}

void Poison_Effect::on_turn_end(Character& target) {
	Combat_Logger::log_effect_tick(get_message(target));
    if (target.is_alive()) {
        target.change_health(-damage);
    }
    duration--;
}

void Poison_Effect::on_effect_apply(Character& target) {
    Combat_Logger::log_effect_apply(target, *this);
}

void Poison_Effect::on_effect_expire(Character& target) {
    Combat_Logger::log_effect_expire(target, *this);
}

std::string Poison_Effect::get_name() const {
	return "Poison";
}   

std::string Poison_Effect::get_message(const Character& target) const {
    return fmt::format("{} takes {} poison damage ({} turns remaining)",
        target.get_name_ref(),
        damage,
        duration
    );
}