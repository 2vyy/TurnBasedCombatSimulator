#include "combat_system.h"
#include <iostream>

int main() {
    Character goblin1{
        "Red Goblin",
		{110, 110, 17, 75, 7, 0.05, 0.20, 1.50} // TODO: if we upgrade to c++20, we can use designated initializers
    };
    Character goblin2{
        "Blue Goblin",
        {120, 120, 26, 50, 5, 0.08, 0.35, 1.25}
    };
    Character goblin3{
        "Green Goblin",
        {105, 105, 21, 60, 4, 0.02, 0.50, 1.65}
    };

    Team goblins{ "Goblins" };
    goblins.add_member(goblin1);
    goblins.add_member(goblin2);
    goblins.add_member(goblin3);
    
    Character knight1{
        "Iron Knight",
		{110, 110, 22, 65, 4, 0.05, 0.22, 1.54}
    };
    Character knight2{
        "Silver Knight",
        {125, 125, 28, 55, 10, 0.12, 0.25, 1.40}
    };
    Character knight3{
        "Bronze Knight",
        {95, 95, 18, 80, 10, 0.17, 0.15, 1.25}
    };
    Team knights{ "Knights" };
    knights.add_member(knight1);
    knights.add_member(knight2);
    knights.add_member(knight3);

    Combat_System combat_system{ knights, goblins };
	for (int i = 0; i < 1; i++) {
        combat_system.start_combat();
	}

    return 0;
}