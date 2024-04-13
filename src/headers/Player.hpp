/*Makes the Player object subclass with the ability to move within a space provided*/

#include "MapCreator.h"
using namespace std;

//Makes a working movable player object that is compatible with any created map
class Player : public Object {
public:
	Player(int id, const Coordinates& initialCoords = { 0,0 }) : Object(id), coords(initialCoords) {}

	Coordinates getCoordinates() const {
		return coords;
	}

	void setCoordinates(const Coordinates& newCoords) {
		coords = newCoords;
	}

	void move(Worldmap& worldmap, int dx, int dy) {
		Coordinates newCoords = { coords.x + dx, coords.y + dy };
		if (worldmap.isValidTile(newCoords)) {
			worldmap.removeObject(coords, *this);
			coords = newCoords;
			worldmap.addObject(coords, *this);
			setCoordinates(coords);
		}
		else
			cout << "That, my dear Watson, would be hitting a wall." << endl;
	}

private:
	Coordinates coords;
};
