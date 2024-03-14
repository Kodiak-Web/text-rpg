#include "headers/globalstate.hpp"
#include "headers/combat.hpp" 
#include <iostream>

static combatantregister Combatants;
static attackregister attacks;

attackregister initAttacks() { 
    //threw compile error until attack got a default constructor
    attacks["punch"] = attack(1,2,2,5,"melee");
    attacks["badlynamedattack"] = attack(2,50,128,5,"debug");
    return attacks;
}
combatantregister initCombatants(attackregister attacks) {
    Combatants["Player"] = combatentity(10,10,128,attackMethod::none);    
    //use this syntax to add the kv pair verbatim to a combatant
    Combatants["Player"].add_attack(*attacks.find("punch"));
    //use this syntax when adding a unique attack, or you want to rename an existing attack from the table
    Combatants["Player"].add_attack("kick",attacks["badlynamedattack"]);
    Combatants["Dummy"] = combatentity(0,0,0,attackMethod::none,0);
    


    return Combatants;    
}
