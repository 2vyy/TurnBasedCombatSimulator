#pragma once
#include <string>

class Character;

class Effect {
    public:
        virtual ~Effect() = default;  // Inline defaulted destructor

        virtual void on_apply(Character& target) = 0;
        virtual void on_turn_start(Character& target) = 0;
        virtual void on_remove(Character& target) = 0;
        virtual bool is_expired() const = 0;
        virtual std::string get_name() const = 0;
};