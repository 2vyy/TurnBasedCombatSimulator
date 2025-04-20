#pragma once  
//#include "character.h"  // Include the full definition of Character  

class Character;  

class Effect {  
   public:  
       virtual ~Effect() = default;  // Must be virtual  

       virtual void on_apply(Character& target) = 0;  
       virtual void on_tick(Character& target) = 0;  
       virtual bool is_expired() const = 0;  
};