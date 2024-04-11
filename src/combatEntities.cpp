#include "headers/combat.hpp"
#include "headers/combatEntities.hpp"
std::map<std::string,std::vector<attack>> attackDict;

void populateAttacks(combatantregister&);

attackregister getAttacks() {
    attackregister Attacks = {
        {"slimeBounce",attack(4,5,3,5,"blunt")},
        {"playerUnarmed",attack(2,2,25,2,"melee")},
        {"Sword",attack(4,6,25,5,"sword")}
    };

    for(auto [name,curAttack]: Attacks) {
       //this is display name. explicit display names could be set later, if needed.
        curAttack.name = name; 
    }
    return Attacks;
}

combatantregister getCombatants() {
    attackregister Attacks = getAttacks();
    combatantregister Combatants = {
        {"Player",combatentity(10,5,50,attackMethod::none)},
        {"Dummy", combatentity(10,0,0,attackMethod::none)},
        {"Slime", combatentity(10,3,50,attackMethod::orderless)}
    };
    for(auto [name,curEntity]: Combatants) {
        curEntity.name = name;
    }
    populateAttacks(Combatants);
    return Combatants;
}

void populateAttacks(combatantregister& Combatants) {
    //this is imperfect, but it'll do
    attackregister Attacks = getAttacks();
    Combatants["Slime"].add_attack(Attacks.find("slimeBounce"));
    Combatants["Player"].add_attack(Attacks.find("Sword"));

}
