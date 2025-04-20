#pragma once

#include <string>
#include <vector>
#include "character.h"

class Team {
public:
	Team(const std::string&);
	void add_member(Character& character);
	bool is_defeated() const;
	std::vector<Character>& get_characters();
	int get_size() const;
	int get_alive_count() const;
	std::string get_name_ref() const;
private:
	const std::string name;
	std::vector<Character> characters;
};