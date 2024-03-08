#pragma once
#include <string>
#include <vector>
struct coords{
    int x;
    int y;
    coords(int x,int y) : x(x),y(y) {};

};

class tile {
    public:
        std::string name;
        std::vector<std::string,coords>;
    private:
};

class map {
    private:
        std::vector<std::vector<tile>> maparray;
    public:
        tile get_tile(int x,int y) {
            if(maparray.size()-1<=x) {
                if(maparray[x].size()-1<=y) {
                    return maparray[x][y];
                }
            }
        }

};
