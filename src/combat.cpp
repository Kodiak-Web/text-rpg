#include "headers/combat.hpp"



combatentity::combatentity() {
        health = 1;
        takesDamage = 1;
        defense = 0;
        movementTime = 0; 
        strategy = attackMethod::none;
    };
combatentity::combatentity(int health, int defense, int movementTime, attackMethod strategy): 
        health(health),
        defense(defense),
        movementTime(movementTime),
        strategy(strategy)     
    {};
combatentity::combatentity(int health, int defense, int movementTime, attackMethod strategy,bool takesDamage): 
        health(health),
        defense(defense),
        movementTime(movementTime),
        strategy(strategy),
        takesDamage(takesDamage) 
    {};
void combatentity::damageStep(int damage, double DefenseModifier) { 
            defense = defense * DefenseModifier;
            damage = damage - defense;
            //my intuition of a func named min/max was that it would allow you to cap a value to a min/max value. 
            //what it actually does is selects the smaller/larger of two values
            health -= std::max(damage,0) * takesDamage;
    }
    
void combatentity::damageStep(int damage) {
        damageStep(damage,1.0);
    }

