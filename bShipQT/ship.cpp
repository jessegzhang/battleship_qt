// ship.cpp
// Jesse Zhang
// 11 March 2016
//
// For CS 372
// Spring 2016
// Project 1
//
// Contains function declerations for Ship Class
#include "ship.h"
#include "game.h"
#include <QPointF>
#include <QVector>
#include <QPolygonF>
#include <QBrush>

extern Game* game;

// ********* Ship ctor *********

// default ctor
Ship::Ship() {};

// ctor
// sets up a valid ship at the specified location with the appropriate size
// Pre:
//    x and y coordinates are on active board
// Post:
//     sets ship values and draws the ship onto the _activeScene
Ship::Ship(int x, int y, int size, QColor color, QString name, QString owner)
	:_x(x), _y(y), _health(size), _name(name), _owner(owner), _color(color),
	_vertical(false), _size(size), _placed(false) {
	//creates a column of tiles at the specified location
	//with the specified number of rows
	for (size_t i = 0; i < _size; ++i) {
		Tile* tile = new Tile();
		tile->setShip(true);
		tile->setPos(_x + 41 * i, _y);
		tile->setOwner(this);
		_shipTiles.append(tile);
		QBrush brush;
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(_color);
		tile->setBrush(brush);
		game->_activeScene->addItem(tile);
	}
}

//updates the ship remove and places tile at the top of the scene

// ********* Member Functions *********

// shipUpdate
// updates ships location
// Pre:
//    ship must be active on _activescene
// Post:
//     regenerates the ship on its appropriate tile
void Ship::shipUpdate() {
	for (size_t i = 0; i < _size; ++i) {
		Tile* tile = _shipTiles[i];
		game->_activeScene->removeItem(tile);
		game->_activeScene->addItem(tile);
	}
}

// shipDraw
// draws the ship with the appropriate tile amount based on size
// Pre:
//    none
// Post:
//     generates the ship on the board
void Ship::shipDraw() {
	for (size_t i = 0; i < _size; ++i) {
			Tile* tile = _shipTiles[i];
			game->_activeScene->addItem(tile);
	}
}

// shipAllignment
// verifies who's ship it is modifying and calls setPOs based on it
// Pre:
//    QString is either PLAYER1 or PLAYER2
// Post:
//     calls setPos for the appropriate players ship
void Ship::shipAllignment(QString player) {

	if (isPlaced()) {
		Tile *tile;
		if (player == QString("PLAYER1")) {
			tile = game->_tileBoardOne->getTiles().value(getIndex());
		}
		else {
			tile = game->_tileBoardTwo->getTiles().value(getIndex());
		}
		setPos(tile->pos().x(), tile->pos().y());
	}
}

// establishPos
// calls setPos based on mouseEvent
// Pre:
//    event is an active event
// Post:
//     takes the x and y value and passes them as qreals into setPos
void Ship::establishPos(QMouseEvent *event) { 
	setPos(event->x(), event -> y());
}

void Ship::setPos(qreal x, qreal y) {
	for (int i = 0;i < _size; ++i) {
		Tile *tile = _shipTiles[i];
		if (_vertical) {
			tile->setPos(x,y + i * 41);
		}
		else {
			tile->setPos(x + i * 41, y);
		}
	}
}

// pos
// returns a QPointF for the ships first head position
// Pre:
//    none
// Post:
//     returns the first tile in the ships pos
const QPointF & Ship::pos() {
	Tile* tile = _shipTiles[0];
	return tile->pos();
}

// healthLoss
// decrements health of ship if broken
// Pre:
//    health should be greater than 0
// Post:
//     decrements ship _health by 1
void Ship::healthLoss() {
	_health--;
}

// destroyed
// checks for ships destruction
// Pre:
//    none
// Post:
//     return true if the ship's health is 0, otherwise returns false
bool Ship::destroyed() {
	if (_health == 0) {
		return true;
	}
	return false;
}