#include "headers/combat.hpp"
#include "headers/combatActions.hpp"
#include <cstdlib>
#include <iostream>

// i don't know fully what i'll put here yet, but everything must be a void function that takes two actors in currently.
// this can allow arbitrary behaviour quite easily. 
// NOTE TO SELF: please don't do anything that involves memory allocation in these functions or you might make a memory leak.
//
void heal(combatentity& actor, combatentity& target) {
    int roll = (rand()%6)+1;
    int newhealth = actor.health + roll;
    actor.health = std::min(actor.maxHealth,newhealth);
    std::cout << actor.name << " Healed " << roll << " HP" << std::endl;
}

void fireDamageStep(combatentity& actor, combatentity& target) {
    int roll = (rand()%3)+1;
    actor.damageStep(roll,0.2);
}

//used from attack; actor is person applying status effect;
void applyStunEffect(combatentity& actor, combatentity& target) {
    std::cout << "stun applied!" << std::endl;
    target.appliedStatusEffects.push_back(Effects["stun"]);
    //does not care about whether it stacks with 
}
void stunEffect(combatentity& actor, combatentity& target) {
    std::cout << "before cast" << std::endl;
    actor.defense = (int)((double)actor.maxDefense * 0.6);
    std::cout << "after cast" << std::endl;
    Turn = !Turn;
    
}
//used from status effect
void expireStunEffect(combatentity& actor, combatentity& target) {
    actor.defense = actor.maxDefense;
}
//must be called before everything else.
void populateEffects() { 
    Effects.insert(std::pair("stun",statusEffect(1,applyStunEffect,stunEffect,nothing,expireStunEffect))); 
}
