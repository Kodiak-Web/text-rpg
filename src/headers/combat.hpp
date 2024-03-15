#pragma once
#include <iterator>
#include <string>
#include <vector>
#include <map>

enum attackMethod {
    //random is already defined; "orderless" is what i'm using instead.
    orderless,ordered,weighted,none

};

struct attack{
    int damageBase;
    int damageDieSize; 
    int attackTime;
    int priority;//if both the player and the enemy "tie" in movementTime one turn, priority should determine which attack goes first.
    std::string damageType;
    attack(int damageBase,int damageDieSize, int attackTime,int priority,std::string damageType);
    attack();
    int rollDamage();
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
    void add_attack(std::string name,attack);
    void add_attack(std::pair<std::string,attack>);
    
    //pass attack through map.find["attackname"]
    void add_attack(std::map<std::string,attack>::iterator);
    combatentity();
    combatentity(int health, int defense, int movementTime); 
    combatentity(int health, int defense, int movementTime, attackMethod strategy);

    combatentity(int health, int defense, int movementTime, attackMethod strategy, bool takesDamage);
     
    void damageStep(int damage, double DefenseModifier); 
    void damageStep(int damage);
};
//idea being you register enemy types in this class as needed and pull them for convenience so you don't have to package the same skeleton definition in every tile.
typedef std::map<std::string,combatentity> combatantregister;
typedef std::map<std::string,attack> attackregister;

//player is combatentity 1
bool fightLoop(combatentity&, combatentity&, bool PlayerGoesFirst);
void playerAttackMenu(combatentity, combatentity);
