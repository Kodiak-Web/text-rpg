#include <map>
#include <string>
#include <iostream>
#include "../../headers/combat.hpp"
typedef std::map<std::string,std::pair<std::string,std::string>> attackTextMap; 
static std::map<std::string,std::pair<std::string,std::string>> attackText;


std::map<std::string,std::pair<std::string,std::string>> insertAttackText() {
    std::string hit = 
R"(Malun Worker lunges at you, and his dagger pierces into you. You push him off quickly, but you're hurt. It's nothing you can't handle.)";


std::string miss =  
R"(Malun Worker lunges at you with his dagger! But you sidestep the attack, and the worker stumbles.)";

    
    attackText.insert(std::pair("Dagger Strike",std::pair(hit,miss)));
    hit = 
R"( In the blink of an eye, a searing stream of flames engulfs you. John Evil's Oil Flamethrower strikes, inflicting intense pain. It hurts, but you press onward.
Oil Flamethrower dealt %DAMAGE% damage!)";



miss = 
R"( In the blink of an eye, a searing stream of flames grows towards you. But you dodge it! You feel the heat, but it's better than being engulfed in it.)";


    attackText.insert(std::pair("Oil Flamethrower",std::pair(hit,miss)));
miss = 
R"(You missed!)";



hit = 
R"(You hit %TARGET% for %DAMAGE% damage!)";
    attackText.insert(std::pair("Revolver",std::pair(hit,miss)));
    hit = 
R"(John Evil hits you with a powerful Steam Punch! You get lightheaded from the steam, but you shake it off.
Steam Punch dealt %DAMAGE% damage!)";


miss = 
R"(John Evil swiftly extends his arm to punch you, but you dodged it! You stumble for a brief moment but you get back up. You're full of adrenaline.)";
    attackText.insert(std::pair("Steam Punch",std::pair(hit,miss)));
    hit = 
R"(%ACTOR% flashes thier eye! Despite trying to look away, %TARGET% is struck with a white flash. %TARGET%'s defense is lowered to 60% and thier next turn is skipped.)";



miss= 
R"(%ACTOR% flashes thier eye! %TARGET% reacts quick enough and turns away.)";
    attackText.insert(std::pair("Eye Flash",std::pair(hit,miss)));



    return attackText;

}


std::string formatAttackText(combatentity& actor, combatentity& target,attack Attack) {
    std::string attackName = Attack.name; 
    std::string actorVar = "\%ACTOR%";
    std::string targetVar = "\%TARGET%";
    std::string hitmessage = attackText.find(attackName)->second.first;
    //std::string missmessage = attackText.find(attackName)->second.second;
    int actorPos = hitmessage.find(actorVar);
    if(actorPos != -1) {
        hitmessage.erase(actorPos,actorVar.size());
        hitmessage.insert(actorPos,actor.name);}
    int targetPos = hitmessage.find(targetVar);
    if(targetPos!=-1) {
        hitmessage.erase(targetPos,targetVar.size());
        hitmessage.insert(targetPos,target.name);}
    /*actorPos = missmessage.find(actorVar);
        missmessage.erase(actorPos,actorVar.size());
        missmessage.insert(actorPos,actor.name);
    targetPos = missmessage.find(targetVar);
        missmessage.erase(targetPos,targetVar.size());
        missmessage.insert(targetPos,target.name);*/
    return hitmessage; 
}
