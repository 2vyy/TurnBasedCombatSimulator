#include "combat_system.cpp";
#include "character.cpp";
#include "team.cpp";
#include <iostream>;
//
int main() {
    Character goblin1{ "Red Goblin", 17, 100, 75 };
    Character goblin2{ "Blue Goblin", 26, 120, 50 };
    Character goblin3{ "Green Goblin", 21, 105, 60 };
    Team goblins{ "Goblin" };
    goblins.add_member(goblin1);
    goblins.add_member(goblin2);
    goblins.add_member(goblin3);

    Character knight1{ "Silver Knight", 28, 125, 55 };
    Character knight2{ "Iron Knight", 22, 110, 65 };
    Character knight3{ "Bronze Knight", 18, 95, 80 };
    Team knights{ "Knights" };
    knights.add_member(knight1);
    knights.add_member(knight2);
    knights.add_member(knight3);

    Combat_System combat_system{ knights, goblins };
    combat_system.start_combat();

    std::cout << "Ending";

    return 0;


}
