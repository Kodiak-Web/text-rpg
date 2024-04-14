#pragma once
#include <iterator>
#include <string>
#include <vector>
#include <map>
// true is player, false is bot. can set before battle to determine who goes first.
static bool Turn = (0);

enum combatStatus {
    PlayerDied,EnemyDied,PlayerFled,errorOccured
};
struct combatentity;
typedef void(*actionPointer)(combatentity actor, combatentity target);
enum attackMethod {
    //random is already defined; "orderless" is what i'm using instead.
    orderless,ordered,weighted,none

};

void nothing(combatentity a, combatentity b);

struct attack{
    int damageBase;
    int damageDieSize; 
    int attackTime;
    int critDieSize;
    std::string name;
    std::string description;//keep me short
    std::string damageType;
    attack(int damageBase,int damageDieSize, int attackTime,int critDieSize,std::string name);
    attack(int damageBase, int damageDieSize, int attackTime,std::string name);
    attack();
    int rollDamage();

    //use for things like status effects.
    actionPointer onUsage;
};

typedef std::string damageType;
struct statusEffect{
    int duration;
    actionPointer applyAction;
    actionPointer onTurnBegin;
    actionPointer onTurnEnd;
    //made in response to the hypothetical "how do i make,say, an invincibility effect that ends"
    actionPointer onExpiration;
    statusEffect();
    statusEffect(int duration,actionPointer applyAction, actionPointer onTurnBegin,actionPointer onTurnEnd,actionPointer onExpiration);
};
//considering making this a class so that random code can't come in and change values;
struct combatentity{
    std::string name;
    int health;
    int maxHealth; 
    bool takesDamage; 
    bool Dead = false; 
    int movementTime;
    int maxDefense;
    double BlockModifier = 2;
    bool isBlocking = false;
    int defense; 
    attackMethod strategy;
    std::vector<attack> attacks;
    std::vector<statusEffect> appliedStatusEffects;
    std::vector<actionPointer> actions;
    //concept
    std::vector<std::pair<
        damageType,double>> typeModifiers; 
    void add_attack(attack);
    void add_attack(attack*); 
    combatentity();
    combatentity(std::string name, int health, int defense, attackMethod strategy);
    combatentity(int health, int defense); 
    combatentity(int health, int defense, attackMethod strategy);
    combatentity(int health, int defense, attackMethod strategy, bool takesDamage);
    void damageStep(int damage, double DefenseModifier); 
    void damageStep(int damage);
};



//idea being you register enemy types in this class as needed and pull them for convenience so you don't have to package the same skeleton definition in every tile.
typedef std::map<std::string,combatentity> combatantregister;
typedef std::vector<attack> attackregister;

//player is combatentity 1
combatStatus fightLoop(combatentity& player, combatentity opponent, bool PlayerGoesFirst);
void playerAttackMenu(combatentity& player, combatentity& opponent);
attack botPickAttack(combatentity& actor);
void botCombatStep(combatentity& actor,combatentity& target);
combatantregister initCombatants();

