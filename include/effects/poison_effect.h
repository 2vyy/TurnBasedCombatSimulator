#pragma once
#include <algorithm>
#include "constants.h"
#include "effect.h"  
#include "character.h"  
#include "combat_logger.h"

class Poison_Effect : public Effect {  
   public:  
       Poison_Effect() {};

       void on_apply(Character& target) override {  
           Combat_Logger::log_effect_apply(target, *this);
       }  

       void on_tick(Character& target) override {
           Combat_Logger::log_effect_tick(
               target,
               *this,
               target.get_health(),
               std::clamp(target.get_health() + damage, 0, target.get_max_health())
           );
           target.change_health(damage);
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
           return damage;
       }

   private:  
       int duration = Constants::POISON_DURATION; 
       int damage = Constants::POISON_DAMAGE;
	   std::string name = Constants::POISON_NAME;
       std::string modifer = Constants::POISON_MODIFIER;
};