// tile.cpp
// Jesse Zhang
// 11 March 2016
//
// For CS 372
// Spring 2016
// Project 1
//
// Contains function declerations for Tile Class
#include "tile.h"
#include "game.h"

extern Game* game;

// ********* Tile ctor *********

// ctor
// sets proper pointer and bool's, generates the Tile's graphics
// Pre:
//    none
// Post:
//     sets booleans and draws the polygon for each tile
Tile::Tile(QGraphicsItem *parent) {
	_isShip = false;
	_isOccupied = false;
	_owner = nullptr;
	_isHit = false;
	QVector<QPointF> tilePoints;
	tilePoints << QPointF(0, 0) << QPointF(0, 1)
		<< QPointF(1, 1) << QPointF(1, 0);

	//scale up points
	int SCALE_BY = 40;
	for (size_t i = 0, n = tilePoints.size(); i < n; ++i) {
		tilePoints[i] *= SCALE_BY;
	}

	//create a polygon with the scaled points
	QPolygonF square(tilePoints);

	//draw the square
	setPolygon(square);
}

// ********* Member Functions *********
// getHit
//getter function
// return _isHit
bool Tile::getHit() {
	return _isHit;
}

// getOccupied
//getter function
// return _isOccupied
bool Tile::getOccupied() {
	return _isOccupied;
}

// setOccupied
//setter function
// set _isOccupied to bool b
void Tile::setOccupied(bool b) {
	_isOccupied = b;
}

// setHit
//setter function
// sets _isHit to bool h
void Tile::setHit(bool h) {
	_isHit = h;
}

// mousePressEvent
// finds the owner of the tile on leftclick
// Pre:
//    none
// Post:
//     if the left mouse button is pressed returns the ships owner
void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	
	if (event->button()==Qt::LeftButton) {
		if (getShip()) {
			game->pickUpShip(getOwner());
		}
	}

}
