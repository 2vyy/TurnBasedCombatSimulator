#include <string>
#include "team.cpp";

class Character {
public:
	Character(std::string& _name, int _attack, int _max_health, int _speed) : 
		name(_name), attack(_attack), max_health(_max_health), curr_health(_max_health), speed(_speed) {}
	//
	void take_damage(int damage) {
		curr_health -= damage;
	}

	bool is_alive() {
		return curr_health > 0;
	}

	void process_turn(Character& other) {
		other.take_damage(attack);
		std::cout << actor->get_name() << " attacks "
			<< target->get_name() << "!\n";
	}

	int get_speed() {
		return speed;
	}

private:
	std::string& name;
	int attack;
	int max_health;
	int curr_health;
	int speed;
};