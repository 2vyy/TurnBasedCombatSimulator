#pragma once
#include <algorithm>
#include "constants.h"
#include "effect.h"  
#include "character.h"  
#include "combat_logger.h"

class Poison_Effect : public Effect {  
   public:
       std::vector<CombatEventType> get_triggers() const {
		   return {
               CombatEventType::turn_end,
			   CombatEventType::effect_apply,
               CombatEventType::effect_expire, 
           };
       };
       void on_turn_end(Character& target) {
		   Character::CharacterStats stats = target.get_stats();
		   Combat_Logger::log_effect_tick(
			   target,
			   *this,
			   stats.curr_health,
			   std::clamp(stats.curr_health - damage, 0, stats.curr_health)
		   );

		   if (stats.curr_health - damage >= 0) {
			   target.change_health(-damage);
		   }

		   duration--;
       };
	   void on_effect_apply(Character& target) {
		   Combat_Logger::log_effect_apply(target, *this);
	   };
	   void on_effect_expire(Character& target) {
		   Combat_Logger::log_effect_expire(target, *this);
	   };

	   const int damage = 5;
       int duration = 3;
       const std::string name = "Poison";
};