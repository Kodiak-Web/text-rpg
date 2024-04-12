/*A Prototype mapping system to host different objects within the game*/

#include <iostream>
#include <map>
#include <unordered_set>

using namespace std;

//Represents an Object on a tile in the map
class Object {
public:
	Object(int id) :id(id) {}

	int getId() const {
		return id;
	}

private:
	int id;
};

//Class representing a tile on the map
class Tile {
public:
	void addObject(const Object& object) {
		objects.insert(object.getId());
	}

	void removeObject(const Object& object) {
		objects.erase(object.getId());
	}

	bool hasObject(const Object& object) const {
		return objects.find(object.getId()) != objects.end();
	}

private:
	unordered_set<int> objects;
};

//Coordinates struct to represent coordinate positions of tiles
struct Coordinates {
	int x;
	int y;

	bool operator<(const Coordinates& other) const {
		return x < other.x || (x == other.x && y < other.y);
	}
};

//Worldmap class to represent the overall map behavior
class Worldmap {
public: 
	Worldmap(int width, int height) : width(width), height(height) {
		for (int y = 0; y < height;++y) {
			for (int x = 0; x < width; ++x) {
				tiles[{ x,y }] = Tile();
			}
		}
	}

	void addObject(const Coordinates& coords, const Object& object) {
		if (isValidTile(coords)) {
			tiles[coords].addObject(object);
		}
	}

	void removeObject(const Coordinates& coords, const Object& object) {
		if (isValidTile(coords)) {
			tiles[coords].removeObject(object);
		}
	}

	bool hasObject(const Coordinates& coords, const Object& object) const {
		if (isValidTile(coords)) {
			return tiles.at(coords).hasObject(object);
		}
		return false;
	}

private:
	bool isValidTile(const Coordinates& coords) const {
		return coords.x >= 0 && coords.x < width && coords.y >= 0 && coords.y < height;
	}

	int width;
	int height;
	std::map<Coordinates, Tile> tiles;
};

int main()
{
	//Creates a 3 x 3 lobby map
	Worldmap lobby(3, 3); 

}
