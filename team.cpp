#include <string>
#include <vector>
#include <algorithm>
#include "character.h"
#include "team.h"

Team::Team(const std::string& _name) :
	name(_name) {}

void Team::add_member(Character& character) {
    characters.push_back(character);
}

bool Team::is_defeated() const {
	return std::none_of(characters.begin(), characters.end(),
		[](const Character& c) { return c.is_alive(); });
}

std::vector<Character>& Team::get_characters() {
	return characters;
}