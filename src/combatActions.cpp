#include "headers/combat.hpp"
#include <iostream>

// i don't know fully what i'll put here yet, but everything must be a void function that takes two actors in currently.
// this can allow arbitrary behaviour quite easily. 
// NOTE TO SELF: please don't do anything that involves memory allocation in these functions or you might make a memory leak.
//


void heal(combatentity actor, combatentity target) {
    int roll = rand()%6+1;
    int newhealth = actor.health + roll;
    actor.health = std::min(actor.maxHealth,newhealth);
    std::cout << actor.name << " Healed " << roll << " HP" << std::endl;
}


