/*Here is where the narrative is*/

#include <iostream>
using namespace std;

void lobby();
void hallway();

int main()
{

    cout << "   It's a slow and rainy night in the streets of London."
        << "\nToday's date is Sunday, January 28th, 1897."
        << "\nYou've been following a local rumor that led you straight to a hotel that is owned by none other than John Evil. Hotel Malum is the name. "
        << "\nYou've caught wind that John Evil hidden somehwere in this hotel, and it's on you to put him away." << endl;

    cout << "\n    \"We're here\" says the taxi driver"
        << "\nYou give the taxi driver a nod as you open the taxi door."
        << "\nWhen you step out of the car, a strong gust of cold wind hits you, nearly blowing your hat away."
        << "\nYou quickly secure your hat and rush inside the hotel." << endl << endl;

    
    cout << "Press enter to continue." << endl;
    cin.get();
    system("cls");

    lobby();
}

//The player enters the lobby and decideds whether or not they want to continue yet
void lobby()
{
    bool to_hallway = false;

    cout << "The fiant scent of motor oil mingles with the smell of saltwater, hinting at a disconverting blend of neglect and eccentricity."
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

       int choice;
       cin >> choice;

       switch (choice)
       {
       case 1: cout << "\n\nYou make your way to the worn double doors. You take a deep breath in, and as you exhale, you make your way into the hallway." << endl << endl;
           to_hallway = true;
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

    if (first_time)
    {
        cout << "   You're rushed with a sudden surge of excitement. You're ready to investigate."
            << "\nFive doors stand in front of you.Two on the left, two on the right, and one directly ahead. "
            << "\nTo your left, the door labeled 101 emits a faint but persistent banging noise, hinting at unseen activity from within"
            << "\nThe door adjacent to it is marked 117. It's slightly open. You see a flickering light peeking through its cracks."
            << "\nOn your right, the door labeled 129 presents itself without any obvious abnormalities.But you can't help but feel something is off."
            << "\nFurther down on the right is the door labeled 123. It catches your attention with its seemingly normal nature,"
            <<"\nyet the presence of the doormat adds a subtle layer of intrigue."
            << "\nFinally, directly ahead, the unmarked door stands as a silent sentinel, its purpose is a mystery."
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
        << "\n4.) To Room 129"
        << "\n5.) To Room-- - " << endl;

    int choice;
    cin >> choice;
}