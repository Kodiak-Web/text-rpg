#include "headers/combat.hpp"
#include "headers/combatEntities.hpp"
#include "headers/combatActions.hpp"
#include <iostream>

void populateAttacks(combatantregister&);









attackMap getAttacks() {

    //DO NOT SET FOURTH VALUE TO 0, CAUSES MODULUS BY 0. WILL NOT BUILD ERROR CHECKING< NOT ENOUGH TIME
    attackregister Attacks = {
        attack(4,6,25,5,"Shoot"),//player
        attack(10,0,0,100,"Steam Punch"), //JE
        attack(2,1,10,3,"Oil Flamethrower"),//JE
        attack(0,0,5,20,"Eye Flash"),//player/worker
        attack(5,5,0,3,"Dagger Strike"),//worker
        attack(0,0,0,20,"Blundershot") //custom damage step, implements multiple pellet logic.
    };
    //inefficient but makes construction easier 
    attackMap attackDict;
    for(attack curAttack: Attacks) {
        attackDict.insert(std::pair(curAttack.name,curAttack));
    }
    populateEffects(attackDict);
    attackDict["Eye Flash"].cooldownTime = 3;

    return attackDict;

}



combatantregister getCombatants() {
    //memory enjoyers hate this one wierd trick!
    std::vector<combatentity> Combatants = {

        //player buff
        combatentity("Player",20,5,attackMethod::none),
        combatentity("Dummy",10,0,attackMethod::none),
        combatentity("John Evil",50,4,attackMethod::orderless),
        combatentity("Malum Worker",15,3,attackMethod::custom)
    };
    combatantregister combatantDict;
    attackAiMap AttackAIs = getAttackAI();
    for(combatentity curEntity: Combatants) {
        combatantDict.insert(std::pair(curEntity.name,curEntity));
    }
    combatantDict["Malum Worker"].chooseAttack = AttackAIs["Malum Worker"];
    populateAttacks(combatantDict);
    return combatantDict;
}
void populateAttacks(combatantregister& Combatants) {
    //this is imperfect, but it'll do
    auto Attacks = getAttacks();
try { 
    Combatants["Malum Worker"].add_attack(Attacks["Eye Flash"]);
    Combatants["Malum Worker"].add_attack(Attacks["Dagger Strike"]);
    Combatants["John Evil"].add_attack(Attacks["Steam Punch"]);
    Combatants["John Evil"].add_attack(Attacks["Oil Flamethrower"]);

    Combatants["Player"].add_attack(Attacks["Shoot"]);
    Combatants["Player"].add_attack(Attacks["Blundershot"]); }
catch(std::bad_alloc) {
    std::cout << "\n\n\n\n\nSomebody tried adding an attack to a combatant, and one of those attacks or combatants was invalid.\n\n\n\n" << std::endl;
    exit(1);
}
}
