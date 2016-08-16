// game.h
// Jesse Zhang
// March 10th 2016
//
// For CS 372 Fall 2016
// Header for the Game class
#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "tileboard.h"
#include "tile.h"
#include "ship.h"
#include "attackboard.h"
#include <QPair>

// *********************************************************************
// class Game - Class Deceleration
// *********************************************************************

// class Game
// Class that handles the general flow of the game 
// includes main menu and turn managers
// Invariants:
//		Game manages which scene is active and interacts with all classes
//		to generate the graphical user interface
class Game : public QGraphicsView {
Q_OBJECT

public:
	//constructors
	Game(QWidget* parent = NULL);

	//public methods
	void displayMainMenu();
	QString getWhosTurn();
	void setWhosTurn(QString player);
	void pickUpShip(Ship* shipEvent);
	void placeShip(Tile *tileReplace);
	bool validShipPlacement(QMouseEvent *event);
	bool checkShipCollision(QMouseEvent *event);
	void redrawBoard(Ship * ship);

	//manages turns
	void gameTurnManager();

	//events
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

	//Tileboard pointers
	TileBoard* _tileBoard;
	TileBoard* _tileBoardOne;
	TileBoard* _tileBoardTwo;

	QGraphicsScene* _activeScene;

	//ints for ship counts
	int _player1ShipsLeft;
	int _player2ShipsLeft;

public slots:
	void startPlayerOne();
	void startPlayerTwo();
	void gamePlayer();

private:

	//private methods
	void drawSetup(int x, int y, int width, int height, QColor color, double opacity);
	void drawBoardGUI();
	void drawSetupGUI();
	void readyButton(bool ready);

	void nextPlayersTurn();
	void createInitialShips(QString player);
	void drawShips(QString player);

	//private attributes
	QString _whosTurn;
	QGraphicsTextItem* _whosTurnText;
	QList<Ship*> _player1Ships;
	QList<Ship*> _player2Ships;

	bool _setupActive;
	bool _gameStarted;
	int _activeShips;

	//private attributes for Game
	QGraphicsTextItem* shipTitle;
	QGraphicsTextItem* board; 
	QGraphicsTextItem* _fleetText;
	QGraphicsTextItem* _enemyText;
	QGraphicsScene* _scene1;
	QGraphicsScene* _scene2;
	QGraphicsScene* _gameBoard1;
	QGraphicsScene* _gameBoard2;

	AttackBoard* _player1Buttons;
	AttackBoard* _player2Buttons;

	Ship* _shipToPlace;

	QList<QPair<Ship*, QPointF>> _originalPos;
};

#endif