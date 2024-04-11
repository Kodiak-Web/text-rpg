#include "headers/combat.hpp"
#include <iostream>
#include <iterator>
#include "headers/combatEntities.hpp"


combatentity::combatentity() {
        health = 1;
        takesDamage = 1;
        defense = 0;
        movementTime = 0; 
        strategy = attackMethod::none;
    };
//i hate that i'm repeating this 3 times.
//however, this pre-function list format runs the initializers for each variable listed
combatentity::combatentity(int health, int defense, int movementTime): 
    health(health),
    maxHealth(health),
    defense(defense),
    movementTime(movementTime),
    strategy(attackMethod::orderless),
    takesDamage(1)
    {}
combatentity::combatentity(int health, int defense, int movementTime, attackMethod strategy): 
    health(health),
    maxHealth(health),
    defense(defense),
    movementTime(movementTime),
    strategy(strategy),
    takesDamage(1)     
    {}
combatentity::combatentity(int health, int defense, int movementTime, attackMethod strategy,bool takesDamage): 
    health(health),
    maxHealth(health),
    defense(defense),
    movementTime(movementTime),
    strategy(strategy),
    takesDamage(takesDamage) 
    {}
void combatentity::damageStep(int damage, double DefenseModifier) { 
    defense = defense * DefenseModifier;
    damage = damage - defense;
    //my intuition of a func named min/max was that it would allow you to cap a value to a min/max value. 
    //what it actually does is selects the smaller/larger of two values
    health -=std::max(damage,1) * takesDamage;
    std::cout << " Took " << damage << "Damage" << std::endl;
    if(health <= 0) {
        Dead = true;
    }
    }
    
void combatentity::damageStep(int damage) {
    damageStep(damage,1.0);
    }
attack::attack(int damageBase, int damageDieSize, int attackTime,int priority,std::string damageType):
    damageBase(damageBase),
    damageDieSize(damageDieSize),
    attackTime(attackTime),
    priority(priority), 
    damageType(damageType) {}
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

//an enum like this is my response to the bool not being representative enough. an enum with every valid state defined is easy to handle, esp with something like a switch case.
//player is by reference to maintain health between fights. enemy is not to keep them fresh
combatStatus fightLoop(combatentity& player,combatentity enemy, bool PlayerInitiative) {
    bool PlayerTurn(PlayerInitiative);
    bool attemptFlee(0);

    while(!(player.Dead)&&!(enemy.Dead)) {
        if(PlayerTurn) {
            int input;
            std::cout << "1. Attack\n2. Block\n3. Item\n4. Flee" << std::endl;
            std::cin >> input;
            combatMenuSelection selection = static_cast<combatMenuSelection>(input-1);
            switch(selection) {
                case combatMenuSelection::Attack:
                    playerAttackMenu(player,enemy);
                    PlayerTurn = false;
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
            }

        }else {
            botCombatStep(enemy,player);
            PlayerTurn = true;
        }
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
            return atkIt->second;
            break;
        case attackMethod::ordered:
            break;
        case attackMethod::weighted:
            break; 
    }
    return attack();
}

void botCombatStep(combatentity& actor,combatentity& target) {
    attack selectedAttack = botPickAttack(actor);
    int damage = selectedAttack.rollDamage();
    //maybe a smart pseudorandom one would feel better; some games, like XCOM, fake the rng to guarantee that you get an effect every 2 or 3 usages or similar. 
    bool critRoll = (rand()%20==0 ? true : false);
    int damagemodifier = (critRoll ? 2 : 1);
    int finalDamage = damage * damagemodifier;
    int DefenseModifier = ( target.isBlocking ? target.BlockModifier : 1);
    target.damageStep(damage,DefenseModifier);

}

void playerAttackMenu(combatentity& player, combatentity &enemy) {
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
        int finalDamage = damageRoll * (critRoll ? 2:1);
        std::cout << finalDamage  << " damage\n" << std::endl;
        enemy.damageStep(damageRoll);
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

void combatentity::add_attack(std::map<std::string,attack>::iterator attackIterator) {
    add_attack(*attackIterator);
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
