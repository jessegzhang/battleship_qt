// ship.h
// Jesse Zhang
// March 10th 2016
//
// For CS 372 Fall 2016
// Header for the Ship class
#ifndef SHIP_H
#define SHIP_H
#include "tile.h"
#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

// *********************************************************************
// class Ship - Class Deceleration
// *********************************************************************

// class Ship
// Class that contains the functions for ships on the board
class Ship{

public:

	Ship();//should be set to private but only used for testing purposes

	Ship(int x, int y, int size, QColor color, QString name, QString owner);

	void shipDraw();
	void shipUpdate();
	void shipAllignment(QString player);

	//overwrite setPos function
	void setPos(qreal x, qreal y);
	void establishPos(QMouseEvent *event);

	//setter functions
	void setVertical(bool position) { _vertical = position; }
	void setPlaced(bool place) { _placed = place; }
	void setIndex(int i) { _myIndex = i; }
	
	//getter functions
	QList<Tile *> getShipTiles() { return _shipTiles; }
	bool isPlaced() { return _placed; }
	bool isVertical() {	return _vertical; }
	int getSize(){ return _size; }
	int getIndex() { return _myIndex; }
	QString getName() { return _name; }
	
	void healthLoss();
	bool destroyed();

	//overwrite pos function
	const QPointF & pos();

private:
	int _x, _y, _health, _size;
	QString _owner, _name;
	QColor _color;
	bool _placed, _sunk, _vertical;
	QList<Tile*> _shipTiles;
	int _myIndex;
};

#endif