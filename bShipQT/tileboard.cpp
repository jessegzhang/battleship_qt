// tileboard.cpp
// Jesse Zhang
// 11 March 2016
//
// For CS 372
// Spring 2016
// Project 1
//
// Contains function declerations for TileBoard Class
#include "tileboard.h"
#include "game.h"

extern Game* game;
// ********* TileBoard ctor *********

//default ctor
TileBoard::TileBoard() {

}

// ********* Member Functions *********

// getTiles
// getter function
// returns QList of Tile pointers contained in TileBoard
QList<Tile *> TileBoard::getTiles() {
	return _tiles;
}

// fineTile
// finds the tile based on x and y coordinates
// Pre:
//    none
// Post:
//     returns tile underneath the xVal and yVal
Tile* TileBoard::findTile(int xVal, int yVal) {
	int x = xVal;
	int y = yVal;

	int xIndex = 10;
	int yIndex = 10;

	x = x - 510;
	y = y - 510;
	//find xIndex
	while (x < 0) {
		x = x + 41;
		--xIndex;
	}
	//find yIndex
	while (y < 0) {
		y = y + 41;
		--yIndex;
	}
	int i = yIndex + 10 * xIndex;
	return getTiles().value(i);
}

// moveTileBoard
// moves tileboard to x and y position
// Pre:
//    x and y are valid ints within the 1024x768 board
// Post:
//     moves the board to the appropriate position
void TileBoard::moveTileBoard(int x, int y) {
	int X_SHIFT = 41;
	int Y_SHIFT = 41;
	for (size_t xi = 0; xi < 10; ++xi) {
		for (size_t yi = 0; yi < 10; ++yi) {
			Tile *tile = _tiles[yi + xi*10];
			tile->setPos(x + X_SHIFT*xi, y + Y_SHIFT*yi);
		}
	}
}

// regenerateTileBoard
// for each tile regerenerates the Tiles in the GUI
// Pre:
//    TileBoard is not yet placed into the scene
// Post:
//     places each TileBoard in to _activeScene
void TileBoard::regenerateTileBoard() {
	for (int i = 0; i < _tiles.size();++i) {
		game->_activeScene->addItem(_tiles[i]);
	}
}

// placeTiles
// generates the associated tileboard and places it at the x and y coordinate
// Pre:
//    x and y are valid values within 1024x768 board
// Post:
//     Generates the rows
void TileBoard::placeTiles(int x, int y, int cols, int rows) {
	int X_SHIFT = 41;
	for (size_t i = 0; i < cols; ++i) {
		createTileColumn(x+X_SHIFT*i, y, rows);
	}
	
}

// createTileColumn
// Generates a column of tiles based on what placeTiles provides it
// Pre:
//    x and y are valid values within the 1024x768 board
// Post:
//     generates the appropriate tiles and pushes it into the _tiles QList
void TileBoard::createTileColumn(int x, int y, int numofRows) {
	//creates a column of tiles at the specified location
	//with the specified number of rows
	int Y_SHIFT = 41;
	for (size_t i = 0; i < numofRows; ++i) {
		Tile* tile = new Tile();
		tile->setPos(x, y + Y_SHIFT * i);
		_tiles.append(tile);
		game->_activeScene->addItem(tile);
		tile->setOccupied(false);
		tile->setHit(false);
	}
}

