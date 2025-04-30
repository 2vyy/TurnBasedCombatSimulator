#pragma once  

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

struct CombatEventContext {
    Character* attacker;
    Character* defender;
    float action_value;
    bool cancel = false;
};

class Effect {

   public:  
       virtual ~Effect() = default;
	   virtual std::vector<CombatEventType> get_triggers() const = 0;
       virtual void on_turn_start(Character& target) = 0;  
       virtual void on_turn_end(Character& target) = 0;
       virtual void on_before_attack(Character& target) = 0;
       virtual void on_after_attack(Character& target) = 0;
       virtual void on_death(Character& target) = 0;
       virtual void on_revive(Character& target) = 0;
       virtual void on_effect_apply(Character& target) = 0;
       virtual void on_effect_expire(Character& target) = 0;

       int duration;
       const std::string name;
};