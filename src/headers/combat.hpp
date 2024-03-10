#include "datatypes.hpp"
#include <string>
#include <vector>
#include <map>
//proper practice to have definitions in a c file and just the declarations here; 
//this is not that, i can move the definitions to a cpp file later

enum attackMethod {
    //random is already defined; "orderless" is what i'm using instead.
    orderless,ordered,weighted,none

};

struct attack{
    std::pair<int,int> damage;//the two value format allows a dice roll + base damage. maybe first is floor, second is die size?
    int attackTime;
    int priority;//if both the player and the enemy "tie" in movementTime one turn, priority should determine which attack goes first.
    std::string damageType; 
};
typedef std::string damageType;
struct statusEffect: attack{
    int duration; //this is in
};
struct combatentity{
    int health;
    bool takesDamage;
    int defense;
    int movementTime;
    attackMethod strategy;
    std::map<std::string,attack> attacks;
    std::vector<statusEffect> appliedStatusEffects;
    //concept
    std::vector<std::pair<
        damageType,double>> typeModifiers; 
    //idea: some kind of generalized state watcher that can watch variables and do events based on conditions. 

    combatentity();/* {
        health = 1;
        takesDamage = 1;
        defense = 0;
        movementTime = 0; 
        strategy = attackMethod::none;
    };*/
    combatentity(int health, int defense, int movementTime, attackMethod strategy);
       /* health(health),
        defense(defense),
        movementTime(movementTime),
        strategy(strategy)     
    {};*/
    combatentity(int health, int defense, int movementTime, attackMethod strategy,bool takesDamage);/*
        health(health),
        defense(defense),
        movementTime(movementTime),
        strategy(strategy),
        takesDamage(takesDamage) 
    {};*/
    void damageStep(int damage, double DefenseModifier);/* { 
            defense = defense * DefenseModifier;
            damage = damage - defense;
            //my intuition of a func named min/max was that it would allow you to cap a value to a min/max value. 
            //what it actually does is selects the smaller/larger of two values
            health -= std::max(damage,0) * takesDamage;
    }*/
    
    void damageStep(int damage);/* {
        damageStep(damage,1.0);
    }*/
};
//idea being you register enemy types in this class as needed. tiles can pull from this, create thier own entity if they want, or edit exi 
class enemyRegistry{
    std::map<std::string,combatentity> enemies;
    
};
