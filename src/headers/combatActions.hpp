#include "combat.hpp"
#include "combatEntities.hpp"
typedef std::map<std::string,statusEffect> effectMap;
static effectMap Effects;
typedef attack(*attackPicker)(combatentity& actor, combatentity& target);
typedef std::map<std::string, attackPicker> attackAiMap;
void populateEffects(attackMap& attacks);
attackAiMap getAttackAI();
typedef std::map<std::string,actionPointer> damageStepMap; 
