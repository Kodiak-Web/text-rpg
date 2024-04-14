/*A Prototype mapping system to host different objects within the game*/

#include <iostream>
#include <map>
#include <unordered_set>

using namespace std;

//Represents an Object on a tile in the map
class Object {
public:
	Object(int id, const string& desc = " ") :id(id), desc(desc) {}

	int getId() const {
		return id;
	}

	void setDescription(const string& newDesc) {
		desc = newDesc;
	}

	string getDescription() const {
		return desc;
	}

private:
	int id;
	string desc;
};

//Class representing a tile on the map
class Tile {
public:
	void addObject(const Object& object) {
		objects.insert({ object.getId(), object });
	}

	void removeObject(const Object& object) {
		objects.erase(object.getId());
	}

	const Object& getObject(int objectId) const {
		if (hasObject(objectId)) {
			return objects.at(objectId);
		}
	}

	bool hasObject(int objectId) const {
		return objects.find(objectId) != objects.end();
	}

private:
	std::map<int, Object> objects;
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

	Tile& getTile(const Coordinates& coords) {
		return tiles.at(coords);
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

	bool hasObject(const Coordinates& coords, int objectId) const {
		if (isValidTile(coords)) {
			return tiles.at(coords).hasObject(objectId);
		}
		return false;
	}

	bool isValidTile(const Coordinates& coords) const 
	{
		return coords.x >= 0 && coords.x < width && coords.y >= 0 && coords.y < height;
	}

private:

	int width;
	int height;
	std::map<Coordinates, Tile> tiles;
};