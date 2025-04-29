#pragma once
#include <algorithm>
#include "constants.h"
#include "effect.h"  
#include "character.h"  
#include "combat_logger.h"

class Poison_Effect : public Effect {  
   public:  
       Poison_Effect(int damage_per_turn, int duration) : 
		   damage_per_turn(damage_per_turn) {
		   this->duration = duration;
		   this->name = "Poison";
	   }

	   EffectType get_type() const override {
		   return EffectType::onHit;
	   }

       void on_apply(Character& target) override {  
           Combat_Logger::log_effect_apply(target, *this);
       }  

       void on_tick(Character& target) override {
		   Character::CharacterStats stats = target.get_stats();
           Combat_Logger::log_effect_tick(
               target,
               *this,
               stats.curr_health,
               std::clamp(stats.curr_health + damage, 0, stats.max_health)
           );
           target.change_health(damage);
           duration--;  
       }

       void on_expire(Character& target) override {
		   Combat_Logger::log_effect_expire(target, *this);
	   }

   private:
       int damage_per_turn;
};