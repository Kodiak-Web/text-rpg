#include "headers/map.hpp"
#include "headers/globalstate.hpp"
#include "headers/combat.hpp"
#include <ctime>
#include <iostream>
#include <random>
void init() {
    srand(std::time(0));

}


int main() {
    init();
    attackregister Attacks = initAttacks();
    combatantregister Combatants = initCombatants(Attacks);
    tile debugroom(-256,-256);
    debugroom.Enemy = Combatants["Dummy"]; 
    fightLoop(Combatants["Player"],Combatants["Dummy"],true);
    return 0;
}
