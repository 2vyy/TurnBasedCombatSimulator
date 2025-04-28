#pragma once
#include <algorithm>
#include "effect.h"  
#include "character.h"  
#include "combat_logger.h"

class Regen_Effect : public Effect {
public:
    Regen_Effect() {}

    void on_apply(Character& target) override {
        Combat_Logger::log_effect_apply(target, *this);
    }
    
    void on_tick(Character& target) override {
        Character::CharacterStats stats = target.get_stats();
        Combat_Logger::log_effect_tick(
            target,
            *this,
            stats.curr_health,
			std::clamp(stats.curr_health + health_gain, 0, stats.curr_health)
        );
        if(stats.curr_health + health_gain <= stats.max_health) {
			target.change_health(health_gain);
		}
        duration--;
    }

    void on_expire(Character& target) override {
        Combat_Logger::log_effect_expire(target, *this);
    }

    bool is_expired() const override {
        return duration <= 0;
    }

    std::string_view get_name() const override {
        return name;
    }

    std::string_view get_modifer() const override {
        return modifer;
    }

    int get_modifer_value() const override {
        return health_gain;
    }

private:
    int duration = Constants::REGEN_DURATION;
    int health_gain = Constants::REGEN_DAMAGE;
    std::string name = Constants::REGEN_NAME;
    std::string modifer = Constants::REGEN_MODIFIER;
};