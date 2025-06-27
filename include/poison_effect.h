// poison_effect.h
#pragma once
#include "effect.h"

class Poison_Effect : public Effect {
public:
    Poison_Effect();

    std::vector<CombatEventType> get_triggers() const override;
    std::string get_message(const Character& target) const override;
    std::string get_name() const override;

    void on_turn_end(Character& target) override;
    void on_effect_apply(Character& target) override;
    void on_effect_expire(Character& target) override;

private:
    int damage = 5;
    int duration = 3;
};

