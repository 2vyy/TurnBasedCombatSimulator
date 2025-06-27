#pragma once
#include <algorithm>
#include "effect.h"  
#include "character.h"  
#include "combat_logger.h"

class Weakness_Effect : public Effect {  
   public:  
       Weakness_Effect() {};

       void on_apply(Character& target) override {  
           Combat_Logger::log_effect_apply(target, *this);
       }  

       void on_tick(Character& target) override {
		   Character::CharacterStats stats = target.get_stats();
           Combat_Logger::log_effect_tick(
               target,
               *this,
               stats.attack,
               std::clamp(stats.attack + damage_reduction, 0, stats.attack);
           );
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
           return damage_reduction;
       }

   private:  
       int duration = Constants::WEAKNESS_DURATION;
       int damage_reduction = Constants::WEAKNESS_DAMAGE;
	   std::string name = Constants::WEAKNESS_NAME;
       std::string modifer = Constants::WEAKNESS_MODIFIER;
};