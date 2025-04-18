#include "combat_system.h"
#include <iostream>

int main() {
    Character goblin1{ "Red Goblin", 100, 17, 75 };
    Character goblin2{ "Blue Goblin", 120, 26, 50 };
    Character goblin3{ "Green Goblin", 105, 21, 60 };
    Team goblins{ "Goblin" };
    goblins.add_member(goblin1);
    goblins.add_member(goblin2);
    goblins.add_member(goblin3);
    
    Character knight2{ "Iron Knight", 110, 22, 65 };
    Character knight1{ "Silver Knight", 125, 28, 55 };
    Character knight3{ "Bronze Knight", 95, 18, 80 };
    Team knights{ "Knights" };
    knights.add_member(knight1);
    knights.add_member(knight2);
    knights.add_member(knight3);

    Combat_System combat_system{ knights, goblins };
    combat_system.start_combat();

    std::cout << "Ending";

    return 0;
}