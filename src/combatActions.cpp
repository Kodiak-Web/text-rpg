#include "headers/combat.hpp"
#include "headers/combatActions.hpp"
#include "headers/combatEntities.hpp"
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <random>

// i don't know fully what i'll put here yet, but everything must be a void function that takes two actors in currently.
// this can allow arbitrary behaviour quite easily. 
// NOTE TO SELF: please don't do anything that involves memory allocation in these functions or you might make a memory leak.
//

typedef attack(*attackPicker)(combatentity& actor, combatentity& target);
attack MalumWorkerAI(combatentity& actor,combatentity& target) {
    static int attackindex;
    attack returnvalue;
    switch(attackindex) {
        case 0:
            //eye flash. reference by index instead of reference by name 
            //is terrible for readability but too late to refactor for readability now
            returnvalue = actor.attacks[0];
            break;
        case 1:
        case 2:
        case 3:
        default:
            returnvalue = actor.attacks[1];
            break;
    }
    attackindex++;
    //keep index valid;
    attackindex %=4;
    return returnvalue;
};

void blunderbussDamageStep(combatentity& actor, combatentity& target) {
    
    
    std::random_device rd; 
    std::normal_distribution numPelletsHit{1.0,5.0};
    std::normal_distribution pelletDamage{3.0,10.0};
    int numPellets = (int)(numPelletsHit(rd)+0.5);
    for(int idx(0);idx<numPellets;idx++) {
        target.damageStep((int)(pelletDamage(rd)+.5),1);
    }
}


void heal(combatentity& actor, combatentity& target) {
    int roll = (rand()%6)+1;
    int newhealth = actor.health + roll;
    actor.health = std::min(actor.maxHealth,newhealth);
    std::cout << actor.name << " Healed " << roll << " HP" << std::endl;
}
int rollBurn() {
    return (rand()%3)+1;

}
void burnDamageStep(combatentity& actor, combatentity& target) {
    int burnDamage(0);
    int burnCount(0);
    
    for(auto effect : actor.appliedStatusEffects) {
        if(effect.onTurnBegin == burnDamageStep) {
            burnCount++;
            burnDamage+= rollBurn();
         }
    }
    std::cout << actor.name << " is burned!" << std::endl; 
    actor.damageStep(burnDamage,0.4);
}
void applyBurn(combatentity& actor, combatentity& target) {
    
    target.appliedStatusEffects.push_back(Effects["burn"]);
}
void burnExpire(combatentity& actor, combatentity& target) {
   //for some reason nothing segfaults so i'm making an identical function with a different name
    std::cout << "bruh" << std::endl;
    return; 
}
void applyStunEffect(combatentity& actor, combatentity& target) {
    std::cout << actor.name << " stunned " << target.name << "!"<< std::endl;
    bool isAlreadyStunned = false;
    auto effectIt = target.appliedStatusEffects.begin();
    auto curEffect = effectIt;
    for(int idx(0);curEffect!=target.appliedStatusEffects.end();idx++) {
        curEffect = std::next(effectIt,idx);
        if(curEffect->applyAction==applyStunEffect) {
            isAlreadyStunned=true;
            curEffect->duration--;
        }
    }
    if(!isAlreadyStunned) {
        target.appliedStatusEffects.push_back(Effects["stun"]);
    }
    }

int decrementStunEffect(combatentity& target) {
    bool isAlreadyStunned = false;
    auto effectIt = target.appliedStatusEffects.begin();
    auto curEffect = effectIt;
    statusEffect stun;
    int idx = 0;
    int stunidx;
    for(;idx<target.appliedStatusEffects.size();idx++) {
        curEffect = std::next(effectIt,idx);
        if(curEffect->applyAction==applyStunEffect) {
            isAlreadyStunned=true;
            curEffect->duration--;
            stun = *curEffect;
            stunidx = idx;
            if(!curEffect->duration) {
                curEffect->onExpiration(target,target);
            } else {
                idx++;
            }
        } else {
        idx++;
        }
    }
    return stunidx; 
}



void stunEffect(combatentity& actor, combatentity& target) {
    actor.defense = (int)((double)actor.maxDefense * 0.6);
    actor.appliedStatusEffects.erase(
            std::next(actor.appliedStatusEffects.begin(),
                     decrementStunEffect(actor)
                     )              ); 

    if(actor.name == "Player") {
        SetTurnState(0); 
    } else {
        SetTurnState(1);
    }

}
//used from status effect
void expireStunEffect(combatentity& actor, combatentity& target) {
    actor.defense = actor.maxDefense;
}

void buildEffects() {
    Effects.insert(std::pair("stun",statusEffect(1,applyStunEffect,stunEffect,expireStunEffect,expireStunEffect)));
    Effects.insert(std::pair("burn",statusEffect(3,applyBurn,burnDamageStep,burnExpire,burnExpire)));
}


void setDamageSteps(attackMap& attacks) {
    attacks["Blundershot"].onUsage = blunderbussDamageStep;

}

//must be called 
void populateEffects(attackMap& attacks) {
    setDamageSteps(attacks);
    buildEffects();
    attacks["Eye Flash"].onUsage = applyStunEffect;
    attacks["Oil Flamethrower"].onUsage = applyBurn;
}

attackAiMap getAttackAI() {
    attackAiMap attackAIs;
    attackAIs["Malum Worker"] = MalumWorkerAI;
    return attackAIs;
}


