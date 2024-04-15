/*Here is where the narrative is*/

#include <iostream>
using namespace std;

void lobby();
void hallway();
void Room101();
void Room117();
void Room123();
void Evilroom();

int main()
{

    cout << "It's a slow and rainy night in the streets of London."
        << "\nToday's date is Sunday, January 28th, 1897."
        << "\nYou've been following a local rumor that led you straight to a hotel that is owned by none other than John Evil. Hotel Malum is the name. "
        << "\nYou've caught wind that John Evil hidden somehwere in this hotel, and it's on you to put him away." << endl;

    cout << "\n\"We're here\" says the taxi driver"
        << "\nYou give the taxi driver a nod as you open the taxi door."
        << "\nWhen you step out of the car, a strong gust of cold wind hits you, nearly blowing your hat away."
        << "\nYou quickly secure your hat and rush inside the hotel." << endl << endl;

    
    cout << "Press enter to continue." << endl;
    cin.get();
    system("cls");

    lobby();

    return 0;
}

//The player enters the lobby and decideds whether or not they want to continue yet
void lobby()
{
    bool to_hallway = false;

    cout << "The faint scent of motor oil mingles with the smell of saltwater, hinting at a disconverting blend of neglect and eccentricity."
        << "\nYour eyes dart to the fish tank resting against the right wall, its glass clouded with oil residue, like a forgotten relic."
        << "\nWithin it, a few desolate fish swim listlessly, their colors muted and their movements sluggish, trapped in a world of darkness.\n";

    cout << "\n  Approaching the front desk on the right, you notice the once - polished wood is now weather and chipped."
        << "\nPapers lie scattered, some threatening to tumble to the floor at any moment.A lone lamp flickers weakly, casting eerie shadows that dance across the worn surface."
        << "\nAhead of you, a pair of imposing double doors beckon, their faded paint peeling away to reveal glimpses of what lies beyond."
        << "\nThey stand as silent guardians, promising both adventures and uncertainty to those who dare to pass through...\n";

   
   while (!to_hallway)
   {
      cout << "\nDo you wish to enter ?"
           << "\n1.) Yes"
           << "\n2.) Not Yet" << endl;
    
      cout << "Make your decision. (Enter 1 or 2): ";
       int choice;
       cin >> choice;

       switch (choice)
       {
       case 1: to_hallway = true;
           break;
       case 2: cout << "\n\nYou decide not to go into the hallway just yet. Something appears so off about this Hotel but you can't put your finger on it."
           << "\nNothing seems to be of major interest in the lobby.You have a feeling all of the meat will be in the hallway" << endl;
           break;
       default: cout << "\n\nYou try to picture a third option. Leave? No."
           << "\nYour job is here, and you decide you need to take one of two options." << endl;
           break;
       }
   }

   hallway();
}

//The player enters the hallway
void hallway()
{
    static bool first_time = true;
    
    system("cls");

    if (first_time)
    {
        cout << "You make your way to the worn double doors. You take a deep breath in, and as you exhale, you make your way into the hallway." << endl << endl;

        cout << "You're rushed with a sudden surge of excitement. You're ready to investigate."
            << "\nFour doors stand in front of you.Two on the left, one on the right, and one directly ahead. "
            << "\n\nTo your left, the door labeled 101 emits a faint but persistent banging noise, hinting at unseen activity from within"
            << "\n\nThe door adjacent to it is marked 117. It's slightly open. You see a flickering light peeking through its cracks."
            << "\n\nFurther down on the right is the door labeled 123. It catches your attention with its seemingly normal nature,"
            <<"\nyet the presence of the doormat adds a subtle layer of intrigue."
            << "\n\nFinally, directly ahead, the unmarked door stands as a silent sentinel, its purpose is a mystery."
            << "\nYou can choose to go to the door straight ahead, but something is telling you to explore the four rooms first";

        cout << "\n\nPress enter to continue." << endl;
        cin.ignore();
        cin.get();
        system("cls");

        first_time = false;
    }

    cout << "Standing in the hallway, you choose to head: "
        << "\n1.) To Room 101 "
        << "\n2.) To Room 117 "
        << "\n3.) To Room 123 "
        << "\n4.) To Room-- - " << endl;

    bool valid_room = false;
    
    while (!valid_room) {
        cout << "\nMake your choice (Enter 1-5): ";
        
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: Room101();
            valid_room = true;
            break;
        case 2: Room117();
            valid_room = true;
            break;
        case 3: Room123();
            valid_room = true;
            break;
        case 4: Evilroom();
           valid_room = true;
           break;
        default: cout << "The other rooms within this building are not of interest to you." << endl;
        }
    }
}
//The player finds themselves in a room with a man with a purpose
void Room101()
{
    static bool first_time = true;

    system("cls");

    if (first_time) {
        cout << "   As you cautiously push open the door of 101, you're immediately met by a scene straight from a nightmare."
            << "\nBefore you stands a man, his silhouette athed in the sickly glow of flickering lights, surrounded by the horrifying scene of his work."
            << "\nWith a sinking feeling in your stomach, you watch in horror as the man brutally dismantles a mechanical construct,"
            << "\ntearing it limb from limb with little to no effort. Oil splatters the floor. Frozen in place, you can only watch as the man's gaze slowly drifts to you,"
            << "\nhis eyes burning with a fierce intensity."
            << "\n   He rises to his full height, towering over you.Every inch of you tells you to flee, but you can't."
            << "\nAs he gets closer, his features become clearer. The dim light in the middle of the room reveals a figure weathered by time and grizzled with age."
            << "\nHis mechanical hand reflects the light. He finally approaches you." << endl;

        cout << "\nPress enter to continue.";
        cin.ignore();
        cin.get();
        system("cls");


        cout << "You try speaking up.\n"
            << "\"I'm here to investigate this hotel. Who are you and what is your business here?\"\n"
            << "*silence*\n"
            << "\"I said w-\"\n"
            << "\"Silence.\"\n"
            << "\"...\"\n"
            << "\n"
            << "You watch as he pulls a picture from out his large black coat. It's a picture of a familiar man.\n" << endl
            << "\"Him. I'm here for him. John Evil\"\n"
            << "\"What is your business with John Evil?\"\n"
            << "\"My name is Gideon. My business with John Evil is mine and mine only. You ask too many questions.\"\n"
            << "\"I'm doing my job. I'm here to find John Evil too. Do you know where he could be?\"\n"
            << "\"I know who you are. I'm going off the same rumor as you. I'm simply just making my way through this dumpster of a hotel\"\n"
            << "\"Right. Okay so I j-\"\n"
            << "\"I dont work with others. Leave me be\"\n";

        cout << "\nPress enter to continue.";
        cin.get();
        system("cls");
    }

    first_time = false;
    
    cout << "His back is turned. Mindlessly destroying a construct. You decide it's time to leave." << endl;
    
    bool valid_choice = false;

        while (!valid_choice)
        {
            cout << "\nHowever, do you wish to leave?"
                << "\n 1.) Yes"
                << "\n 2.) Not yet."
                << "\nMake your decision. (Enter 1 or 2): ";

            int choice;
            cin >> choice;

            switch (choice)
            {
            case 1: cout << "\nYou walk back to the door, swiftly making your way back into the hallway." << endl;
                valid_choice = true;
                break;
            case 2: cout << "\nYou can't help but stare at Gideon. Who is he?\n"
                << "\"Leave.\"\n";
                break;
            default: cout << "\nThat isn't an option." << endl;
                break;
            }
        }

        cout << "\n Press enter to continue.";
        cin.ignore();
        cin.get();
        hallway();
}

//The player finds themselves in a room with the destroyed automaton
void Room117()
{
    system("cls");

    static bool first_time = true;

    if (first_time)
    {
        cout << "You walk towards room 117 with caution. Something could be in here."
            << "\nAs you step towards the door, you slowly open it and peek inside.As the door opens, nothing is wrong."
            << "\nAll you see is a bed and a bedside table.Until the door is wide open, and in the corner, you see a construct."
            << "\n\nThe flickering light is coming from the face of this thing.You start to creep inside, checking every corner."
            << "\nYou walk towards the construct and inspect it.The screen is just a dim flickering white light. But suddenly, the screen changes!"
            << "\nYou become startled and back up a few steps.The screen suddenly displays two human - like eyes, which slowly turn towards you.";

        cout << "\n\nPress enter to continue." << endl;
        cin.ignore();
        cin.get();
        system("cls");

        cout << "\"Hu- human. Please...you must help me\"\n"
            << "\"What's happened here? Explain to me\"\n"
            << "\"A man. H- h- he bursted into the room while I was cleaning. It was scary.\"\n\"I was scared. He st- st- started to attack me. I begged for mercy but he did no- no- not hear me.\"\n"
            << "\"Which man? What did he look like\"\n"
            << "\"Tall. Grizzled. He had a mechan- mec- mechanical hand. He used that thing to destroy me so effortlessly\"\n"
            << "\"Mechanical hand? That's odd\"\n"
            << "\"He surely was not human. He may look like one, but I've onl- only seen constr- cons- constructs with the power\"\n"
            << "\"Are you going to be okay?\"\n"
            << "\"I will. Please just put an end to whatever is happening here. Quickly\"\n";

        cout << "\nYou find yourself with a newfound sense of determination. You make your way to the door, ready for what\'s next." << endl;

        cout << "\nPress enter to continue." << endl;
        cin.get();
        system("cls");
    }


    cout << "You're standing in the doorway, looking back at the construct." << endl;

    bool valid_choice = false;

    while (!valid_choice) {
        int choice;

        cout << "\nWhat would you like to do? \n"
            << "1.) Leave\n"
            << "2.) Stay\n";
        cout << "It's up to you. (Enter 1 or 2): ";

        cin >> choice;

        switch (choice) {
        case 1: cout << "You open the door, swiftly making your way back into the hallway." << endl;
            valid_choice = true;
            break;
        case 2: cout << "You decide to look around for a few more minutes\n"
            << "\"Please, pl- please save us\"\n"
            << "\"Whos us?\"\n"
            << "\"You.Me.Them\"\n"
            << "You stare at the construct. Dumbfounded, you make your way back to the door." << endl;
            break;
        default: cout << "That's not an option" << endl;
            break;
        }
    }

    cout << "\nPress enter to continue." << endl;
    cin.ignore();
    cin.get();
    hallway();
}

//The player finds themselves in a rather homely room alongside an automaton with a deathwish
void Room123()
{
    system("cls");
    static bool first_time = true;

    if (first_time)
    {
        cout << "Before you enter room 123, you look down towards your feet at the doormat. The doormat reads \"Hello\"."
            << "\nStrange.You wipe your feet like the gentleman you are and enter."
            << "\nAs you open the door, a strange man with a briefcase stands across the room."
            << "\n\nHe is standing straight up, with a creepy smile on his face.\n";

        cout << "\nPress enter to continue" << endl;
        cin.ignore();
        cin.get();
        system("cls");

        cout << "\"How long have you been standing there?\"\n"
            << "\"Hello. I assume you're here for a part...?\"\n"
            << "\"I guess you could say something like that. Do you have it?\"\n"
            << "\"I sure do. But I wont hand it over unless you humor me.\"\n"
            << "\"Humor you how?\"\n"
            << "\"Oh you know, a duel\"\n"
            << "\nThe worker pulls out a dagger and lunges towards you." << endl;

        cout << "\nPress enter to continue" << endl;
        cin.get();
        system("cls");

        //innitiate combat here 

        cout << "Frozen in shock, you stand amidst the battle's aftermath, the unsettling sight of the hotel worker's lifeless form crashing down before you."
            << "\nThough not one to embrace sudden violence, the worker's aggression had left you with no choice but to humor him."
            << "\nYou stride purposefully toward the briefcase.You go to open it, but you realize it remains stubbornly sealed, missing a gear."
            << "\n\nScouring the room in a frantic search, you gaze upon the worker's prone form, a gear is glued to the back of his head."
            << "\nYou pluck the gear from its resting place and affix it onto the briefcase, its mechanism springing to life with a click."
            << "\nAs the lid swings open, it reveals... disappointment.There's nothing in here."
            << "\nYou stand back up slowly.You let out a sigh.You walk back over to the door." << endl;

        cout << "\nPress enter to continue" << endl;
        cin.get();
        system("cls");

        first_time = false;
    }

    bool valid_choice = false;
    
    cout << "You find yourself in another doorway, this time of a room that once held pseudo-life.\n";
    cout << "Do you wish to leave?\n"
        << "1.) Yes\n"
        << "2.) Not yet.";

    while (!valid_choice) 
    {
        cout << "\nMake your decision. (Enter 1 or 2): ";
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1: cout << "You open the door, and swifly make your exit back into the hallway. \n";
            valid_choice = true;
            break;
        case 2: cout << "You survey the room once more. You're unsure why the worker immediately wanted trouble."
            << "\nDid he have a death wish? It doesn't matter much anymore, the job is finished." << endl;
            break;
        default: cout << "That isn't an option." << endl;
            break;
        }
    }
    cout << "\nPress enter to continue." << endl;
    cin.ignore();
    cin.get();
    hallway();
}

//The player  Fights John Evil
void Evilroom()
{
    system("cls");

    cout << "As you approach the door at the far end of the hallway, its scratched-off number gives you the chills."
        << "\nYour hand recoils in shock as the doorknob scorches your palm, leaving an imprint of agony."
        << "\n\nWith a determined grin, you steel yourself and with a swift kick, the door is knocked down. "
        << "\nBefore you is a vast expanse of emptiness, the cold, unyielding stone of the room enclosing you like a tomb."
        << "\nAmidst the empty room is a lone wooden platform. It's suspended by chains that vanish into the void above. "
        << "\nYou step forth onto the platform, the faint sound of clicking machinery heralding its ascent into the unknown."
        << "\n\nThe lift carries you ever closer to your target, John Evil."
        << "\nHis name is a whisper of fear on the lips of those who know who he is."
        << "\nFinally, the lift halts, and before you stands a door.With a steady breath, you step onto the threshold, and the platform clicks back into the motion."
        << "\nYou can't go back now.The door swings open, and a wave of blistering heat washes over you.You fall over, stunned by what just happened."
        << "\n\nThrough the haze, you catch a glimpse of him - John Evil."
        << "\nLanterns flicker, casting shadows that seem to mock your presence."
        << "\nWith every ounce of your determination, you rise to your feet, the fire of purpose burning within you."
        << "\nThis...this is the moment you've been waiting for.You step forward, ready to confront the darkness.";

    cout << "\nPress enter to continue." << endl;
    cin.ignore();
    cin.get();
    system("cls");

    cout << "You speak out.\n"
        << "\"John Evil. I'm here to take you down once and for all and put an end to your tyranny\"\n"
        << "\"And what makes you think that you could stop me? Look at you. A mere human. You stand no chance.\"\n"
        << "\n...\n"
        << "\"I will take you down, John!\"\n"
        << "\"Let the battle commence, then.\"\n";

    cout << "\nPress enter to continue." << endl;
    cin.get();
    system("cls");

    //Encounter goes here

    cout << "\"Mr. Evil, you are under arrest.\"\n"
        << "You fiercely walk over to the now knocked-out John Evil and you lock handcuffs on him with the force of three suns."
        << "\nJohn Evil is escorted out of the building to a sky which is a deep blue hue, speckled with stars as the rain and wind subside."
        <<"\nYou feel content knowing this will be the last night John Evil ever has the chance to see the stars"
        << "\n\n\n..Hopefully, the first night of many more for you.";
}