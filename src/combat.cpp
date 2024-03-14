#include "headers/combat.hpp"
#include <iostream>
#include <random>



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
attack::attack(int damageBase, int damageDieSize, int attackTime,int priority,std::string damageType):damageBase(damageBase),damageDieSize(damageDieSize),attackTime(attackTime) ,priority(priority), damageType(damageType) {}
attack::attack() {
    attack(1,0,128,128,"none");
}
int attack::rollDamage() {
    return damageBase + rand()%(damageDieSize+1);
}

//returns 1 if fight win, 0 if fight loss.
bool fightLoop(combatentity& player,combatentity& enemy, bool PlayerInitiative) {
    bool PlayerTurn(PlayerInitiative);
    bool attemptFlee(0);
    while(true) {
        if(PlayerTurn) {
            int input;
            std::cout << "1. Fight\n2.Flee" << std::endl;
            std::cin >> input;
            switch(input) {
                case 1:
                    playerAttackMenu(player,enemy);
                    break;
                case 2:
                    attemptFlee = 1;
                    break;
            }
        }else {
            //enemy attack
            PlayerTurn = true;
        }
    if (attemptFlee) {
        return 1;
        }
    }
    return 0;
}

void playerAttackMenu(combatentity player, combatentity enemy) {
    std::string input;
    for (const auto& [attackName, atkStruct] : player.attacks) {
        std::cout << "- " << attackName << ": " << atkStruct.damageBase << 
        '-' << atkStruct.damageBase + atkStruct.damageDieSize << " " << 
        atkStruct.damageType << " damage" << std::endl;
    }
    std::cout << "Select attack by typing name.\n> ";
    std::cin >> input;
    try {
        int damageRoll = (player.attacks[input].rollDamage());
        bool critRoll = (rand()%20==0 ? true : false);
        std::cout << damageRoll * (critRoll ? 2 : 1) << " damage" << std::endl;
        enemy.damageStep(damageRoll,(critRoll ? 2 : 1));
        std::cout << enemy.health << " HP" << std::endl;
    }
    catch(...) {
        std::cout << "You don't know that attack" << std::endl;
    }
}
void combatentity::add_attack(std::string attackName,attack Attack){
    combatentity::attacks[attackName] = Attack; 
}
void combatentity::add_attack(std::pair<std::string,attack> attackElement) {
    add_attack(attackElement.first,attackElement.second); 
}
void combatentity::add_attack(std::pair<std::string,attack>* attackElementPtr) {
    add_attack(*attackElementPtr);
}
