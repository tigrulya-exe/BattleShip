#pragma once
#include "Field.h"
enum Orientation {Horizontal, Vertical};

enum ShipState {Undamaged, Damaged, Destroyed};


namespace {
	const int FOURDECK_REMAINING_COUNT = 1;
	const int THREEDECK_REMAINING_COUNT = 2;
	const int DOUBLEDECK_REMAINING_COUNT = 3;
	const int SINGLEDECK_REMAINING_COUNT = 4;

	const int START_X = 0;
	const int START_Y = 0;

	const int SHIP_TYPE_COUNT = 4;

	const int SINGLEDECK_SIZE = 1;
	const int DOUBLEDECK_SIZE = 2;
	const int THREEDECK_SIZE = 3;
	const int FOURDECK_SIZE = 4;
}

 class Battleship
 {
public:
	using Coords = std::vector<std::pair<int, int>>;

	Battleship(int);
	int getSize();
	virtual int& getCount() = 0;
	virtual void refresh() = 0;
	
	Orientation getOrientation();
	
	Coords&  getCoords();
	Coords&  getBorders();
	void refreshCoords();

	void setCoords(int, int);

	void changeOrientation();
	void moveRight(Field&);
	void moveLeft(Field&);
	void moveUp(Field&);
	void moveDown(Field&);
	void placeBorders(Field&);

	bool isCorrectPlaced(Field&);
	bool isPlaced();
	void setAsPlaced();
	
	void clear();
	bool isContains(int, int);
	void takeHit();
	ShipState getState();
	virtual int& getNumber() = 0; 
	virtual ~Battleship() {};
private:
	int _x;
	int _y;
	int _lifes;
	int _size;

	ShipState _state;
	bool _is_placed;
	Orientation _orientation;

	Coords _borders;
	Coords _coords;
	void setBorders();
};

class SingleDeck : public Battleship {
	static int _remaining_count;
	static int _number;
public:
	SingleDeck() : Battleship(SINGLEDECK_SIZE) {}
	void refresh() override;
	int& getCount() override; 
	int& getNumber();

};

class DoubleDeck : public Battleship {
	static int _remaining_count;
	static int _number;
public:
	DoubleDeck() : Battleship(DOUBLEDECK_SIZE) {}
	void refresh() override;
	int& getCount() override;
	int& getNumber();
};

class ThreeDeck : public Battleship {
	static int _remaining_count;
	static int _number;
public:
	ThreeDeck() : Battleship(THREEDECK_SIZE) {}
	void refresh() override;
	int& getCount() override;
	int& getNumber();

};

class FourDeck : public Battleship {
	static int _remaining_count;
	static int _number;
public:
	FourDeck() : Battleship(FOURDECK_SIZE) {}
	void refresh() override;
	int& getCount() override;
	int& getNumber();
};