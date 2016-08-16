// tileboard.h
// Jesse Zhang
// March 10th 2016
//
// For CS 372 Fall 2016
// Header for the TileBoard class
#ifndef TILEBOARD_H
#define TILEBOARD_H
#include <QList>
#include <QMouseEvent>
#include "tile.h"

#include <QGraphicsPolygonItem>
// *********************************************************************
// class TileBoard - Class Deceleration
// *********************************************************************

// class TileBoard
// Class that spawns tiles and puts them into a QList 
class TileBoard {
public:
	//constructors
	TileBoard();
	
	//getters
	QList<Tile*> getTiles();
	

	//public methods
	void moveTileBoard(int x, int y);
	void regenerateTileBoard();
	void placeTiles(int x, int y, int cols, int rows);
	Tile* findTile(int xVal, int yVal);
private:
	void createTileColumn(int x, int y, int numRows);
	QList<Tile*> _tiles;

};

#endif //TILEBOARD_H