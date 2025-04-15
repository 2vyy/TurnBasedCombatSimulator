#include <string>
#include <vector>
#include "character.cpp"

class Team {
public:
	Team(std::string& _name) :
		name(_name) {
		characters = {};
	}
	//
	void add_member(Character& character) {
		characters.push_back(character);
	}

	void remove_dead() {
		for (int i = 0; i < characters.size(); i++) {
			if (!characters[i].is_alive()) {
				characters.erase(characters.begin() + i);
			}
		}
	}

	bool is_defeated() {
		return characters.size() == 0;
	}

	std::vector<Character&> get_characters() {
		return characters;
	}


private:
	std::string& name;
	std::vector<Character&> characters;

};