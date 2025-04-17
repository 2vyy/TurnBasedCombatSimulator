#pragma once

#include <string>

class Character {
	public: 
		Character(const std::string _name, const int _attack, const int _max_health, const int _speed) :
			name(_name), attack(_attack), max_health(_max_health), curr_health(_max_health), speed(_speed) {};

		void take_damage(int);

		bool is_alive() const;

		void process_turn(Character&);

		int get_speed() const;

		std::string get_name();

		int get_health() const;


	private:
		const std::string name;
		const int attack;
		const int max_health;
		int curr_health;
		const int speed;
};


