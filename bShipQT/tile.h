// tile.h
// Jesse Zhang
// March 10th 2016
//
// For CS 372 Fall 2016
// Header for the Tile class
#ifndef TILE_H
#define TILE_H
#include <QGraphicsPolygonItem>
// *********************************************************************
// class Tile - Class Deceleration
// *********************************************************************

// class Tile
// Class that spawns tiles that will hold ships 
// Invariants:
//		tile will point to null if it doesn't have a ship on top of it
class Tile : public QGraphicsPolygonItem {
	friend class Ship;

public:
	//constructors
	Tile(QGraphicsItem* parent = nullptr);

	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	//void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

	//getters
	bool getOccupied();
	bool getHit();
	bool getShip() { return _isShip; }
	Ship* getOwner() { return _owner; }

	//setters
	void setOccupied(bool b);
	void setHit(bool h);
	void setShip(bool s) { _isShip = s; }
	void setOwner(Ship *owner) { _owner = owner; }

private:
	Ship* _owner;
	bool _isShip;
	bool _isOccupied;
	bool _isHit;
};

#endif;