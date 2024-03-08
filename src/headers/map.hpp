#pragma once
#include <string>
#include <vector>
template <typename A>
using VectorDict = std::vector<std::pair<std::string,A>>;
typedef int chance;

struct coords{
    int x;
    int y;
    coords():x(0),y(0) {};
    coords(int x,int y) : x(x),y(y) {};

};
struct enemy{};

class tile {
    public:
        std::string name;
        VectorDict<coords> NavigationDict;
        coords coordinates;
        std::string description;
        enemy Enemy;

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
