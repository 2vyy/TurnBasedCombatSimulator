#include "team.h"

Team::Team(const std::string& _name) :
	name(_name) {}

void Team::add_member(Character& character) {
	characters.push_back(character);
}

bool Team::is_defeated() const {
	for (auto& c : characters) {
		if (c.is_alive()) {
			return false; // If any character is alive, the team is not defeated
		}
	}
	return true;
}

std::vector<Character>& Team::get_characters() {
	return characters;
}

std::string& Team::get_name_ref() const {
	return const_cast<std::string&>(name);
}