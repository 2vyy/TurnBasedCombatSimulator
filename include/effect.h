// effect.h
#pragma once
#include <vector>
#include <string>

class Character;

enum class CombatEventType {
    turn_start,
    turn_end,
    before_attack,
    after_attack,
    on_death,
    on_revive,
    effect_apply,
    effect_expire
};

class Effect {
public:
    virtual ~Effect() = default;

    // Core interface
    virtual std::vector<CombatEventType> get_triggers() const = 0;
    virtual std::string get_message(const Character& target) const = 0;

    // Optional handlers with default implementations
    virtual void on_turn_start(Character& target) {}
    virtual void on_turn_end(Character& target) {}
    virtual void on_before_attack(Character& target) {}
    virtual void on_after_attack(Character& target) {}
    virtual void on_death(Character& target) {}
    virtual void on_revive(Character& target) {}
    virtual void on_effect_apply(Character& target) {}
    virtual void on_effect_expire(Character& target) {}

    // Common properties
    int duration = 0;
    virtual std::string get_name() const = 0;
};