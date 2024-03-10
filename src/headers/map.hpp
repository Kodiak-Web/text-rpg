#pragma once
#include "datatypes.hpp"
#include "combat.hpp"
typedef int chance;

struct coords{
    int x;
    int y;
    coords():x(0),y(0) {};
    coords(int x,int y) : x(x),y(y) {};

};
class tile {
    public:
        std::string name;
        std::map<std::string,tile> NavigationDict;
        coords coordinates;
        std::string description;
        combatentity Enemy;
        tile():coordinates() {}; 
        tile(int x, int y): coordinates(x,y) {};

};

class map {
    private:
        std::vector<std::vector<tile>> maparray;
    public:
        tile currentTile;
        map() {};
        
        tile get_tile(int x,int y) {
            if(maparray.size()-1<=x) {
                if(maparray[x].size()-1<=y) {
                    return maparray[x][y];
                }
            }
            return currentTile;
        }
 
};
