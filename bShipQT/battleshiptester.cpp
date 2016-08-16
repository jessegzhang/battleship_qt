
// battleshiptester.cpp
// Jesse Zhang
// 11 march 2016
//
// For CS 372 Spring 2016
// Unit tests for Project 1
// Uses the "Catch" C++ Unit-Testing Framework

#define CATCH_CONFIG_MAIN  // We want Catch to write function main
#include "catch.hpp"       // For the "Catch" unit-testing framework

// Double inclusion test
#include "game.h"
#include "tileboard.h"
#include "menubutton.h"
#include "ship.h"
#include "tile.h"
#include "bshipqt.h"
#include "attackboard.h"
#include "attackButton.h"
#include "game.h"
#include "tileboard.h"
#include "menubutton.h"
#include "ship.h"
#include "tile.h"
#include "bshipqt.h"
#include "attackboard.h"
#include "attackButton.h"

#include <QtWidgets/QApplication>
#include <vector>
using std::vector;
#include <algorithm>
using std::equal;
#include <cstddef>
using std::size_t;
#include <functional>
using std::function;
using std::bind;
using namespace std::placeholders;


extern QApplication* app;

Tile *testTile = new Tile();
Ship *testShip = new Ship();
TileBoard *testBoard = new TileBoard();

Game *testGame;

//testing game class
TEST_CASE("Checking game default constructor") {
	testGame = new Game();
	//class cannot be tested that well based on gui interaction
	//used to initalize for other classes that base itself on ship
}

//Testing Tile Class
TEST_CASE("Checking default constructor for tile") {

	void mousePressEvent(QGraphicsSceneMouseEvent *event);

	REQUIRE(testTile->getHit()==false);
	REQUIRE(testTile->getOccupied() == false);
	REQUIRE(testTile->getShip() == false);

}
//Testing setFunctions
TEST_CASE("Checking set functions for tile") {

	testTile->setOccupied(true);
	REQUIRE(testTile->getOccupied() == true);
	testTile->setOccupied(false);
	REQUIRE(testTile->getOccupied() == false);
	testTile->setHit(true);
	REQUIRE(testTile->getHit() == true);
	testTile->setHit(false);
	REQUIRE(testTile->getHit() == false);
	testTile->setShip(true);
	REQUIRE(testTile->getShip() == true);
	testTile->setShip(false);
	REQUIRE(testTile->getShip() == false);

	testTile->setOwner(testShip);

	bool testOwner = false;
	if (testTile->getOwner() == testShip) {
		testOwner = true;
	}
	REQUIRE(testOwner == true);
	testTile->setOwner(nullptr);

	testOwner = false;
	if (testTile->getOwner() == nullptr) {
		testOwner = true;
	}
	REQUIRE(testOwner == true);
}
//checking the testBoard
TEST_CASE("Checking testBoard return tiles") {
	//testBoard->placeTiles(100, 100, 10, 10); Cannot be intialized breaks
	REQUIRE(testBoard->getTiles().isEmpty() == true);
	REQUIRE(testBoard->getTiles().size() == 0);
}

//note main constructor for ship places trings on _activescene which breaks catch framework
TEST_CASE("Ship class check applicable getters and setters") {

	testShip->setVertical(true);
	REQUIRE(testShip->isVertical() == true);
	testShip->setVertical(false);
	REQUIRE(testShip->isVertical() == false);
	testShip->setIndex(1);
	//REQUIRE(testShip->getSize() == 1);
	testShip->setIndex(2);
	//REQUIRE(testShip->getSize() == 2);
	testShip->setPlaced(true);
	REQUIRE(testShip->isPlaced() == true);
	testShip->setPlaced(false);
	REQUIRE(testShip->isPlaced() == false);

}

//testing with QDialogue and Scene is buggy and breaks catch framework, Behavior driven development was used for things like button and gui
//Ships should rotate on RMB
//ships should not have collisions
//Ships should go back to origin on collision
//Board state should hold and allow ships to place on it
//Buttons should work binding start to start event, close to close event
//attackbuttons should only be clickable once
//should mark green if hit and red if miss