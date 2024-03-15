#include "headers/globalstate.hpp"
#include "headers/combat.hpp" 
#include <iostream>

static combatantregister Combatants;
static attackregister attacks;

attackregister initAttacks() { 
    //threw compile error until attack got a default (empty) constructor
    attacks["punch"] = attack(1,2,2,5,"melee");
    attacks["badlynamedattack"] = attack(2,50,128,5,"debug");
    return attacks;
}
combatantregister initCombatants(attackregister attacks) {
    /*
    These are examples of adding individual enemies;
    Combatants["Player"] = combatentity(10,10,128,attackMethod::none);    
    //use this syntax to add the kv pair to a combatant.
    //note: this function is overloaded to automatically dereference the iterator for you. 
    //otherwise you would have to do *attacks.find["attackname"] as map::find returns an iterator
    Combatants["Player"].add_attack(attacks.find("punch"));
    //use this syntax when adding a unique attack, or you want to rename an existing attack from the table
    Combatants["Player"].add_attack("kick",attacks["badlynamedattack"]);
    Combatants["Dummy"] = combatentity(0,0,0,attackMethod::none,0);
    */
    Combatants = 
   {{"Player",          combatentity(10,10,28,attackMethod::none)},
    {"Dummy" ,          combatentity(0,0,10,attackMethod::none,false)},//false here makes this dummy immortal
    {"FragileDummy",    combatentity(50,0,0,attackMethod::none)}};
    Combatants["Player"].add_attack(attacks.find("punch"));
    Combatants["Player"].add_attack("kick",attacks["badlynamedattack"]);
    //attacks are not by reference, this only affects Player's kick.
    //Combatants["Player"].attacks["kick"].damageDieSize/=2;
    return Combatants;    
}
