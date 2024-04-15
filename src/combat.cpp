#include "headers/combat.hpp"
#include <iostream>
#include <iterator>
#include "headers/combatEntities.hpp"
void nothing(combatentity& a, combatentity& b) {
}
static int Turn;
void SetTurnState(bool a) {
    Turn = a;
}



statusEffect::statusEffect():
    duration(1),
    onTurnBegin(nothing),
    onTurnEnd(nothing),
    onExpiration(nothing),
    applyAction(nothing)
{}
statusEffect::statusEffect(int duration,actionPointer applyAction, actionPointer onTurnBegin,actionPointer onTurnEnd,actionPointer onExpiration):
    applyAction(applyAction),
    duration(duration),
    onTurnBegin(onTurnBegin),
    onTurnEnd(onTurnEnd),
    onExpiration(onExpiration)
{} 

combatentity::combatentity() {
        health = 1;
        takesDamage = 1;
        defense = 0;
        movementTime = 0; 
        strategy = attackMethod::none;
    };
//i hate that i'm repeating this 3 times.
//however, this pre-function list format runs the initializers for each variable listed
combatentity::combatentity(int health, int defense): 
    health(health),
    maxHealth(health),
    defense(defense),
    movementTime(movementTime),
    strategy(attackMethod::orderless),
    takesDamage(1),
    maxDefense(defense)
    {}
combatentity::combatentity(int health, int defense, attackMethod strategy): 
    health(health),
    maxHealth(health),
    defense(defense),
    movementTime(movementTime),
    strategy(strategy),
    takesDamage(1),
    maxDefense(defense)
    {}
combatentity::combatentity(int health, int defense, attackMethod strategy,bool takesDamage): 
    health(health),
    maxHealth(health),
    defense(defense),
    movementTime(movementTime),
    strategy(strategy),
    takesDamage(takesDamage), 
    maxDefense(defense)
    {}

combatentity::combatentity(std::string name, int health, int defense, attackMethod strategy):
    name(name),
    health(health),
    maxHealth(health),
    defense(defense), 
    strategy(strategy),
    takesDamage(1),
    maxDefense(defense)
    {} 
void combatentity::damageStep(int damage, double DefenseModifier) {

    defense = defense * DefenseModifier;
    damage = damage - defense;
    //my intuition of a func named min/max was that it would allow you to cap a value to a min/max value. 
    //what it actually does is selects the smaller/larger of two values
    int finalDamage = (std::max(damage,1) * takesDamage);
    health -= finalDamage;
    std::cout << name << " took " << finalDamage << " damage" << std::endl;
    if(health <= 0) {
        Dead = true;
        std::cout << Dead << std::endl;
    }
    }
    
void combatentity::damageStep(int damage) {
    damageStep(damage,1.0);
    }
attack::attack(int damageBase, int damageDieSize, int attackTime,std::string name):
    damageBase(damageBase),
    damageDieSize(damageDieSize),
    attackTime(attackTime), 
    name(name),
    critDieSize(20)
{}

attack::attack(int damageBase, int damageDieSize, int attackTime,int critDieSize,std::string name):
    damageBase(damageBase),
    damageDieSize(damageDieSize),
    attackTime(attackTime),
    critDieSize(critDieSize), 
    name(name)
{}
attack::attack() {
    attack(1,0,128,128,"none");
}
int attack::rollDamage() {
    return damageBase + rand()%(damageDieSize+1);
}

//I'm warming up to enums. 
//makes it easy to exclusively represent valid states. 
//i understand why rustlang likes them so much now
//plus, if we change the order of the menu selection, 
//instead of screwing with the switch case, 
//at worst we have to edit the order of elements in this enum match
enum combatMenuSelection {
    Attack, 
    Block,
    Item,
    Flee,
    UnimplementedAction
};
void afterTurn(combatentity& actor, combatentity& target) {
    int idx(0);        
    auto EffectIt = actor.appliedStatusEffects.begin();
            for(;EffectIt!=actor.appliedStatusEffects.end();) {
                EffectIt = actor.appliedStatusEffects.begin();
                std::advance(EffectIt,idx);
                statusEffect curEffect = *EffectIt;
                curEffect.duration -= 1;
                if(!curEffect.duration) {
                    curEffect.onExpiration(actor,target); 
                    actor.appliedStatusEffects.erase(EffectIt);
                   
                } else {
                    idx++;
                }
            }


}
//an enum like this is my response to the bool not being representative enough. an enum with every valid state defined is easy to handle, esp with something like a switch case.
//player is by reference to maintain health between fights. changed to fix bug
//enemy is not to keep them fresh
combatStatus fightLoop(combatentity& player,combatentity enemy, bool PlayerInitiative) {
    Turn = PlayerInitiative;
    bool attemptFlee(0);

    while(!(player.Dead)&&!(enemy.Dead)) { 
        if(Turn) {
        for(statusEffect curEffect : player.appliedStatusEffects) {
                curEffect.onTurnBegin(player,enemy);
            }}
        if(!Turn)  {
            for(statusEffect curEffect : enemy.appliedStatusEffects) {
                curEffect.onTurnBegin(enemy,player);
            }
        
        }
        if(Turn) {
                        int input;
            std::cout << enemy.name << ": " << enemy.health << '/' << enemy.maxHealth << " HP" << '\n' << 
                        player.name << ": " << player.health <<'/'<< player.maxHealth << " HP\n" << 
                "1. Attack  2. Block  3. Item  4. Flee\n > ";
                ;
            std::cin >> input;
            combatMenuSelection selection = static_cast<combatMenuSelection>(input-1);
            switch(selection) {
                case combatMenuSelection::Attack:
                    playerAttackMenu(player,enemy);
                    break;
                case combatMenuSelection::Flee:
                    //TODO: AttemptFlee roll
                    return combatStatus::PlayerFled; 
                    break;
                case combatMenuSelection::Block:
                    player.isBlocking = true;
                    break;

                case combatMenuSelection::Item:
                    std::cout << "Unimplemented Action\n" << std::endl;
                    break;
                case UnimplementedAction:
                    std::cout << "Unimplemented Action\n" << std::endl;
            }
            afterTurn(player,enemy); 

        }else { 
            botCombatStep(enemy,player);
            afterTurn(enemy,player); 
        }

            Turn = !Turn;

    }
    if(player.Dead) {
        std::cout << enemy.name << " won" << std::endl;
    } else if(enemy.Dead) {
        std::cout << player.name << " won" << std::endl;
    }
    return combatStatus::errorOccured;
}

attack botPickAttack(combatentity& Actor) {
    auto attacks = Actor.attacks;
    auto static atkIt = attacks.begin();
    switch(Actor.strategy) {
        case attackMethod::none:
            break;
        case attackMethod::orderless:
            atkIt = attacks.begin();
            std::advance(atkIt,rand()%attacks.size());
            return *atkIt;
            break;
        case attackMethod::ordered:
            break;
        case attackMethod::custom:
            //i hate this but again, mess for speed.
           return Actor.chooseAttack(Actor,Actor);

    }
    return attack();
}

combatStatus fightLoop(combatentity& player,combatentity enemy) {
    return fightLoop(player,enemy,Turn);
}
void botCombatStep(combatentity& actor,combatentity& target) {
    attack selectedAttack = botPickAttack(actor);
    std::cout << actor.name << " used " << selectedAttack.name << std::endl;
    int damage = selectedAttack.rollDamage();
    //maybe a smart pseudorandom one would feel better; some games, like XCOM, fake the rng to guarantee that you get an effect every 2 or 3 usages or similar.
    bool critRoll = ((rand()%selectedAttack.critDieSize)==0 ? true : false);
    int damagemodifier = (critRoll ? 2 : 1);
    int finalDamage = damage * damagemodifier;
    int DefenseModifier = ( target.isBlocking ? target.BlockModifier : 1);
    target.damageStep(damage,DefenseModifier);

    selectedAttack.onUsage(actor,target);


}


void playerAttackMenu(combatentity& player, combatentity &enemy) {
    std::string input;
    auto atkIt = player.attacks.begin();
    int  iterCount;
    auto currentVal = atkIt;
    /*for (const auto& [attackName, atkStruct] : player.attacks) {
        std::cout << "- " << attackName << ": " << atkStruct.damageBase << 
        '-' << atkStruct.damageBase + atkStruct.damageDieSize << " " << 
        atkStruct.damageType << " damage" << std::endl;
    }*/
    std::cout << std::endl << std::endl << std::endl;
        for(int idx(0);idx<player.attacks.size();idx++) {
            auto currentVal = std::next(atkIt,idx);
            std::string damageString = std::to_string(currentVal->damageBase) +"-"+ std::to_string(currentVal->damageBase + currentVal->damageDieSize);
            std::cout <<idx <<" - " << currentVal->name << ": " << damageString << " damage" << "\n\n\n" << std::endl; 
        
        }
    std::cout << "Select attack by typing number\n> ";
    std::cin >> input;
    int intput = -1;
    if(input.length()==1) {
    if('0'<=input.c_str()[0]&& input.c_str()[0]<='9') {
        intput = atoi(input.c_str()); 
    try {
        auto atkIt = player.attacks.begin();
        attack currentAttack = *std::next(atkIt,intput);
        std::cout << player.name << " used " << currentAttack.name << std::endl;
        int damageRoll = currentAttack.rollDamage();
        bool critRoll = (rand()%20==0 ? true : false);
        int finalDamage = damageRoll * (critRoll ? 2:1);
        enemy.damageStep(damageRoll);
    }
    catch(...) {
        std::cout << "You don't know that attack" << std::endl;
    }
    }

    }
}

void combatentity::add_attack(attack Attack){
    combatentity::attacks.push_back(Attack); 
}
/*void combatentity::add_attack(std::pair<std::string,attack> attackElement) {
    add_attack(attackElement.first,attackElement.second); 
}*/

void combatentity::add_attack(attack* Attack) {
    add_attack(*Attack);
}

combatantregister initCombatants() {
   /* combatantregister Combatants = {
        {"Player",combatentity(10,5,50,attackMethod::none)},
        {"Dummy", combatentity(10,0,0,attackMethod::none)},
        {"Slime", combatentity(10,3,50,attackMethod::orderless)}
    };
    for(auto [name,curEntity]: Combatants) {
        curEntity.name = name;
    }
    return Combatants;*/
    return getCombatants();
}
