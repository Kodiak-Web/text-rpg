#include "headers/map.hpp"
#include "headers/combat.hpp"
#include <ctime>
#include <iostream>
#include <random>
void init() {
    srand(std::time(0));

}


int main() {
    init();
    combatantregister Combatants = initCombatants();
    tile debugroom(-256,-256);
    debugroom.Enemy = Combatants["Malum Worker"]; 
    fightLoop(Combatants["Player"],debugroom.Enemy,true);
    return 0;
}
