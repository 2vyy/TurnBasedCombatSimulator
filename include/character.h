#pragma once

#include <string>

class Character {
public:
	Character(const std::string _name, const int _max_health, const int _attack, const int _speed);
	void process_turn(Character&);
	void take_damage(int);
	bool is_alive() const;
	std::string& get_name_ref() const;
	int get_max_health() const;
	int get_health() const;
	int get_attack() const;
	int get_speed() const;
private:
	const std::string name;
	const int max_health;
	int curr_health;
	const int attack;
	const int speed;
};

