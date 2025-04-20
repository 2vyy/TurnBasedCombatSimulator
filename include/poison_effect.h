#include "effect.h"  
#include "character.h"  

class Poision_Effect : public Effect {  
   public:  
       Poision_Effect(int _duration, int _damage_per_turn)  
           : duration(_duration), damage(_damage_per_turn) {  
       }  

       void on_apply(Character& target) override {  
           // Implementation for on_apply (even if empty, it must be defined)  
       }  

       void on_tick(Character& target) override {  
           target.take_damage(damage);  
           duration--;  
       }  

       bool is_expired() const override {  
           return duration <= 0;  
       }  

   private:  
       int duration;  
       int damage;  
};