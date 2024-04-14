#include "headers/combat.hpp"
#include "headers/combatEntities.hpp"
#include "headers/combatActions.hpp"
#include <iostream>
std::map<std::string,std::vector<attack>> attackDict;

void populateAttacks(combatantregister&);
typedef std::map<std::string,attack> attackMap; 
attackMap getAttacks() {
    attackregister Attacks = {
        attack(4,6,25,5,"Shoot"),
        attack(5,10,50,10,"Steam Punch"), //JE
        attack(2,5,10,3,"Oil Flamethrower"),//JE
        attack(0,0,5,0,"Eye Flash"),
        attack(4,2,20,10,"Dagger Strike"),
        attack(5,5,0,0,"Blundershot")
    };
    //inefficient but makes construction easier 
    attackMap attackDict;
    for(attack curAttack: Attacks) {
        attackDict.insert(std::pair(curAttack.name,curAttack));
    }


    



    return attackDict;
}
attackMap assignStatusEffects(attackMap attacks) {
    populateEffects(); 
    attacks["Eye Flash"].onUsage = Effects["stun"].applyAction;

}


combatantregister getCombatants() {
    //memory enjoyers hate this one wierd trick!

    attackMap Attacks = getAttacks();
    std::vector<combatentity> Combatants = {
        combatentity("Player",20,5,attackMethod::none),
        combatentity("Dummy",10,0,attackMethod::none),
        combatentity("Slime",10,3,attackMethod::orderless),
        combatentity("John Evil",50,7,attackMethod::orderless),
        combatentity("Malum Worker",15,3,attackMethod::orderless)
    };
    combatantregister combatantDict;
    for(combatentity curEntity: Combatants) {
        combatantDict.insert(std::pair(curEntity.name,curEntity));
    }
    populateAttacks(combatantDict);
    return combatantDict;
}
//BAD ALLOC? LOOK HERE
void populateAttacks(combatantregister& Combatants) {
    //this is imperfect, but it'll do
    auto Attacks = getAttacks();
try { 
    Combatants["Malum Worker"].add_attack(Attacks["Eye Flash"]);
    Combatants["Player"].add_attack(Attacks["Shoot"]); }
catch(std::bad_alloc) {
    std::cout << "\n\n\n\n\nSomebody tried adding an attack to a combatant, and one of those attacks or combatants was invalid.\n\n\n\n" << std::endl;
    exit(1);
}
}
