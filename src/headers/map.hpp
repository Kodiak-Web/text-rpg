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
