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

	private:
		const std::string name;
		std::vector<Character> characters;
};
