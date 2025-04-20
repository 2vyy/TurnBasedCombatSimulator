#pragma once  

class Character;  

class Effect {  
   public:  
       virtual ~Effect() = default;  // Must be virtual  

       virtual void on_apply(Character& target) = 0;  
       virtual void on_tick(Character& target) = 0;
       virtual void on_expire(Character& target) = 0;
       virtual bool is_expired() const = 0;  
	   virtual std::string_view get_name() const = 0;
       virtual std::string_view get_modifer() const = 0;
       virtual int get_modifer_value() const = 0;
};