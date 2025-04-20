#pragma once
#include <algorithm>
#include "effect.h"  
#include "character.h"  
#include "combat_logger.h"

class Regen_Effect : public Effect {
public:
    Regen_Effect(int _duration, int _health_gain)
        : duration(_duration), health_gain(_health_gain) {
    }

    void on_apply(Character& target) override {
        Combat_Logger::log_effect_apply(target, *this);
    }

    void on_tick(Character& target) override {
        Combat_Logger::log_effect_tick(
            target,
            *this,
            target.get_health(),
			std::clamp(target.get_health() + health_gain, 0, target.get_max_health())
        );
        if(target.get_health() + health_gain <= target.get_max_health()) {
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
    int duration;
    int health_gain;
    std::string name = "Regeneration";
    std::string modifer = "health";
};