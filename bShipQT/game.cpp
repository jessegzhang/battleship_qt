// game.cpp
// Jesse Zhang
// 11 March 2016
//
// For CS 372
// Spring 2016
// Project 1
//
// Contains function declerations for Game Class

#include "game.h"
#include "tileboard.h"
#include "menubutton.h"
#include "ship.h"
#include <QGraphicsTextItem>
#include <QMessageBox>

// ********* Game ctor *********
//ctor
//generates necessary resources for the battleship Game
Game::Game(QWidget *parent) {
	//set up the screen
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFixedSize(1024, 768);

	//set up setup Scene1
	_scene1 = new QGraphicsScene();
	_scene1->setSceneRect(0, 0, 1024, 768);

	//set up setup Scene2
	_scene2 = new QGraphicsScene();
	_scene2->setSceneRect(0, 0, 1024, 768);

	//set up setup GameBoard 1
	_gameBoard1 = new QGraphicsScene();
	_gameBoard1->setSceneRect(0, 0, 1024, 768);

	//set up blank screen
	_gameBoard2 = new QGraphicsScene();
	_gameBoard2->setSceneRect(0, 0, 1024, 768);

	_activeScene = _scene1;
	setScene(_activeScene);

	_setupActive = false;
	_gameStarted = false;
	_activeShips = 0;
	_whosTurnText = new QGraphicsTextItem();
	shipTitle = new QGraphicsTextItem("Ships");
	board = new QGraphicsTextItem("Board");
	_fleetText = new QGraphicsTextItem("Your Fleet");
	_enemyText = new QGraphicsTextItem("Targeting System");
}

// ********* Member Functions *********

// startPlayerOne
// Player ones turn to place ships and generates player ones tileboard
// Pre:
//    none
// Post:
//     generates GUI and appropriate booleans for PLAYER1
void Game::startPlayerOne() {
	_activeScene->clear();

	setWhosTurn(QString("PLAYER1"));
	drawSetupGUI();

	_tileBoard = new TileBoard();
	_tileBoard->placeTiles(100, 100, 10, 10);


	createInitialShips(_whosTurn);
	_tileBoardOne = _tileBoard;


	//initalize variables
	_shipToPlace = nullptr;
	_setupActive = true;

}

// startPlayerTwo
// Player twos turn to place ships and generates player twos tileboard
// Pre:
//    none
// Post:
//     generates GUI and appropriate booleans for PLAYER2 
void Game::startPlayerTwo() {

	_activeScene = _scene2;
	setScene(_activeScene);
	_activeShips = 0;

	drawSetupGUI();
	nextPlayersTurn();

	_tileBoard = new TileBoard();
	_tileBoard->placeTiles(100, 100, 10, 10);

	createInitialShips(_whosTurn);
	_tileBoardTwo = _tileBoard;
	
	_shipToPlace = nullptr;
	_setupActive = true;

}

// gamePlayer
// manages after player twos ready butotn has been hit
// Pre:
//    none
// Post:
//     initailizes the gameboard after setup phase is done
void Game::gamePlayer() {
	setScene(_gameBoard2);
	nextPlayersTurn();
	QMessageBox::information(
		this,
		tr("Game has started"),
		tr("Please Give Computer to Player One"));

	setScene(_activeScene);
	int XL_CENTER = 51;
	int Y_CENTER = 179;
	int XR_CENTER = 563;

	_player1ShipsLeft = 5;
	_player2ShipsLeft = 5;
	//initalize these with low health for debugging

	_setupActive = false;
	//initalizes black board
	_activeScene = _gameBoard2;
	drawSetup(0, 0, 1024, 768, Qt::white, 1.0);


	//sets up the gameboard for the rest of the game to be played out
	_activeScene = _gameBoard1;
	_tileBoardOne->moveTileBoard(XL_CENTER, Y_CENTER);
	_tileBoardTwo->moveTileBoard(XR_CENTER, Y_CENTER);
	_tileBoardOne->regenerateTileBoard();
	_tileBoardTwo->regenerateTileBoard();
	drawShips("PLAYER1");
	drawShips("PLAYER2");
	_player1Buttons = new AttackBoard(_tileBoardTwo->getTiles());
	_player2Buttons = new AttackBoard(_tileBoardOne->getTiles());
	_player2Buttons->hideBoard();
	setWhosTurn(QString("PLAYER1"));
	drawBoardGUI();
	_activeScene->addItem(_fleetText);
	_activeScene->addItem(_enemyText);
	_gameStarted = true;
	setScene(_activeScene);


}

// drawSetup
// generates colored panels based on values given
// Pre:
//    x and y are valid values within the 1024x768 board
// Post:
//     draws a panel on the _activeScene with x and y with associade width ahd height
//		also may set color and opacity
void Game::drawSetup(int x, int y, int width, int height, QColor color, double opacity) {
	//daws a panel at the specified location with the specified properties
	QGraphicsRectItem* panel = new QGraphicsRectItem(x, y, width, height);
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(color);
	panel->setBrush(brush);
	panel->setOpacity(opacity);
	_activeScene->addItem(panel);

}

// drawBoardGUI
// Draws the Board's GUI, based on who's players turn
// Pre:
//    game has started
// Post:
//     Draws and spawns text and places a line down the middle
void Game::drawBoardGUI() {

	QFont titleFont("Times", 25);
	_fleetText->setFont(titleFont);
	int fxPos = this->width() / 4 - _fleetText->boundingRect().width() / 2;
	int yPos = 75;


	_enemyText->setFont(titleFont);
	int txPos = (this->width() * 3) / 4 - _enemyText->boundingRect().width() / 2;

	drawSetup(512, 0, 2, 768, Qt::black, 1.0);

	if (getWhosTurn() == "PLAYER2") {

		txPos = this->width() / 4 - _enemyText->boundingRect().width() / 2;
		fxPos = (this->width() * 3) / 4 - _fleetText->boundingRect().width() / 2;
	}
	_fleetText->setPos(fxPos, yPos);
	_enemyText->setPos(txPos, yPos);

	if (_gameStarted == true) {
		_activeScene->removeItem(_fleetText);
		_activeScene->removeItem(_enemyText);
		_activeScene->addItem(_fleetText);
		_activeScene->addItem(_enemyText);
	}

}

// drawSetupGUI
// draws the setup board
// Pre:
//    game has not started
// Post:
//     draws the text and panel and adds them to _activeScene
void Game::drawSetupGUI() {
	//draw the ship holders
	drawSetup(700, 0, 324, 768, Qt::darkCyan, 1.0);
	
	//place board text
	
	board->setPos(50, 10);
	_activeScene->addItem(board);

	//place ship title
	
	shipTitle->setPos(700+158, 0);
	_activeScene->addItem(shipTitle);


	// place whosTurnText
	_whosTurnText->setPos(490, 0);
	_activeScene->addItem(_whosTurnText);
}

// dispalyMainMenu
// generates mainMenu text
// Pre:
//    none
// Post:
//     generates buttons and text for the main menu of battleship
void Game::displayMainMenu() {

	//create the title text
	QGraphicsTextItem* titleText = new QGraphicsTextItem("Battleship");
	QFont titleFont("Times", 50);
	titleText->setFont(titleFont);
	int txPos = this->width() / 2 - titleText->boundingRect().width() / 2;
	int tyPos = 175;
	titleText->setPos(txPos, tyPos);
	_activeScene->addItem(titleText);

	//create the play button
	MenuButton* playButton = new MenuButton(QString("Play"));
	int bxPos = this->width() / 2 - playButton->boundingRect().width() / 2;
	int byPos = 275;
	playButton->setPos(bxPos, byPos);
	connect(playButton, SIGNAL(clicked()), this, SLOT(startPlayerOne()));
	_activeScene->addItem(playButton);

	//create the quit button
	MenuButton* quitButton = new MenuButton(QString("Quit"));
	int qxPos = this->width() / 2 - quitButton->boundingRect().width() / 2;
	int qyPos = 350;
	quitButton->setPos(qxPos, qyPos);
	connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
	_activeScene->addItem(quitButton);
}

// getWhosTurn
// getter function
// returns QString of _whosTurn
QString Game::getWhosTurn() {
	return _whosTurn;
}

// setWhosTurn
// setter functoin
//Pre: 
//		QString player is either PLAYER1 or PLAYER2
//Post:
//		sets turn to QString player
void Game::setWhosTurn(QString player) {
	
	//change the QString
	_whosTurn = player;

	//change the QGraphicsTextItem
	QString setText = ("Whose turn: ") + player;
	_whosTurnText->setPlainText(setText);
}

// mouseMoveEvent
// based on mouse event will move the ships
// Pre:
//     setup is active and game is not started
// Post:
//		moves ship around based on hover, and sends the event
void Game::mouseMoveEvent(QMouseEvent *event)
{
	if (_setupActive&&!_gameStarted) {
		//if there is a ship to place, then make it follow the mouse
		if (_setupActive&&_shipToPlace != nullptr) {

			_shipToPlace->establishPos(event); //need to add conditions
		}
	}
	QGraphicsView::mouseMoveEvent(event);
}

// mousePressEvent
// based on righ tmouse button event will rotate the ship
// Pre:
//    setup is active and game is not started
// Post:
//     if mouse is pressed checks if over an active ship it will rotate the ship
void Game::mousePressEvent(QMouseEvent *event) {
	if (_setupActive&&!_gameStarted) {
		if (event->button() == Qt::RightButton) {
			if (_setupActive&&_shipToPlace != nullptr) {
				_shipToPlace->setVertical(!_shipToPlace->isVertical());
				_shipToPlace->establishPos(event);
				_shipToPlace->shipUpdate();
			}
		}
	}
	QGraphicsView::mousePressEvent(event);
}

// mouseReleaseEvent
// If holding a ship it will release it if appropriate
// Pre:
//    setup is active and game is not started
// Post:
//     Places ship if it is an active placement, if not will place it back at its original location
void Game::mouseReleaseEvent(QMouseEvent *event) {
	//only if game is ready
	if (_setupActive&&!_gameStarted) {
		//when left button is released
		if (event->button() == Qt::LeftButton) {
			//and im holding onto a ship
			if (_shipToPlace) {
				//see if it can be placed validly and has no collisions
				if (validShipPlacement(event) && checkShipCollision(event)) {
					placeShip(_tileBoard->findTile(event->x(), event->y()));
				}
				//otherwise reset its slot
				else {
					int i = 0;
					while (_shipToPlace != _originalPos[i].first) {
						i++;
					}
					_shipToPlace->setVertical(false);
					_shipToPlace->setPos(_originalPos[i].second.x(), _originalPos[i].second.y());
					if (_shipToPlace->isPlaced())
					{
						readyButton(false);
					}
					_shipToPlace = nullptr;
				}
			}
		}
	}
}

// createInitialShips
// generates Ships and their associated owner
// Pre:
//    QString must either be PLAYER1 or PLAYER2
// Post:
//     generates each ship with ites size and colors and generates them.
void Game::createInitialShips(QString player) {
	//generate ships
	Ship* destroyer = new Ship(750, 34 + 20, 2, Qt::darkRed,
		"Destroyer", player);
	Ship* cruiser = new Ship(750, 34 + 140 + 20, 3, Qt::darkCyan,
		"Cruiser", player);
	Ship* submarine = new Ship(750, 34 + 140 * 2 + 20, 3, Qt::darkGreen,
		"Submarine", player);
	Ship* battleship = new Ship(750, 34 + 140 * 3 + 20, 4, Qt::darkGray,
		"Battleship", player);
	Ship* aircraftCarrier = new Ship(750, 34 + 140 * 4 + 20, 5, Qt::darkMagenta,
		"Aircraft Carrier", player);

	//place them within the respective lists
	if (player == QString("PLAYER1")) {
		_player1Ships.append(destroyer);
		_player1Ships.append(cruiser);
		_player1Ships.append(submarine);
		_player1Ships.append(battleship);
		_player1Ships.append(aircraftCarrier);
	}
	else {
		_player2Ships.append(destroyer);
		_player2Ships.append(cruiser);
		_player2Ships.append(submarine);
		_player2Ships.append(battleship);
		_player2Ships.append(aircraftCarrier);
	}


}

// drawShips
// draws players ships based on QString
// Pre:
//    QString player must either be PLAYER1 or PLAYER2
// Post:
//     draws the appropriate ships based on QString
void Game::drawShips(QString player) {
	//traverse through and draw the ships

	//draw player1's ships
	if (player == QString("PLAYER1")) {
		for (size_t i = 0; i < _player1Ships.size(); ++i) {
			Ship* ship = _player1Ships[i];
			ship->shipAllignment(player);
			ship->shipDraw();
		}
	}
	else {
		for (size_t i = 0; i < _player2Ships.size(); ++i) {
			Ship* ship = _player2Ships[i];
			ship->shipAllignment(player);
			ship->shipDraw();
		}
	}
}

// pickUpShip
// pickups the ship over mouse pointer
// Pre:
//    setup is active and game has not started
// Post:
//     sets _shipToPlace to active ship, and places ship at mouse pointer
void Game::pickUpShip(Ship* shipEvent) {
	if (_setupActive&&!_gameStarted) {
		if (_shipToPlace == nullptr && shipEvent->isPlaced()) {
			_shipToPlace = shipEvent;
			readyButton(false);
			redrawBoard(shipEvent);
			_shipToPlace->shipUpdate();
			return;
		}
		if (_shipToPlace == nullptr) {
			_shipToPlace = shipEvent; //needs to pickup ship, or alternatively it can pick up the ships tiles.
			_shipToPlace->shipUpdate();
			QPointF cord;
			cord.setX(shipEvent->pos().x());
			cord.setY(shipEvent->pos().y());
			_originalPos.append(qMakePair(shipEvent, cord));
			return;
		}
	}
}

//note +10 goes to the right
//note +1 goes down one
// placeShip
// placesShip if over a Tileboard
// Pre:
//    none
// Post:
//     Places the ship on the tiles
void Game::placeShip(Tile *tileReplace) {
	int n = _tileBoard->getTiles().indexOf(tileReplace);
	_shipToPlace->setIndex(n);
	_shipToPlace->setPos(tileReplace->pos().x(), tileReplace->pos().y());
	for (int i = 0; i < _shipToPlace->getSize(); i++) {
		if (_shipToPlace->isVertical()) {
			_activeScene->removeItem(_tileBoard->getTiles().value(n + 1 * i));
			_tileBoard->getTiles().replace(n + 1 * i,_shipToPlace->getShipTiles().value(i));
			_tileBoard->getTiles().value(n + 1 * i)->setOccupied(true);
			_tileBoard->getTiles().value(n + 1 * i)->setOwner(_shipToPlace);
		}

		else {

			_activeScene->removeItem(_tileBoard->getTiles().value(n + 10 * i));
			_tileBoard->getTiles().replace(n + 10 * i, _shipToPlace->getShipTiles().value(i));
			_tileBoard->getTiles().value(n+10*i)->setOccupied(true);
			_tileBoard->getTiles().value(n + 10 * i)->setOwner(_shipToPlace);

		}
	}
	readyButton(true);
	_shipToPlace = nullptr;
	
}

// validShipPlacement
// checks to see if this is a validShipPlacement
// Pre:
//    none
// Post:
//     returns whether the ship is in an appropriate location for a ship placement
bool Game::validShipPlacement(QMouseEvent * event)
{
	bool theCheck = false;
	//checks if its within bounds
	int i = _shipToPlace->getSize();
	//bases its check on its orientation
	if (_shipToPlace->isVertical()) {
		//checks if ship can be placed within the confines
		if (event->x() > 90 && event->x() < 530 && event->y() > 90 && event->y() + 41 * i < 530) {
			theCheck = true;
		}
	}
	else {
		if (event->x() > 90 && event->x() + 41 * i < 530 && event->y() > 90 && event->y() < 530) {
			theCheck = true;
		}
	}
	
	return theCheck;
}

// checkShipCollision
//checks to make sure there are no ship collisions
// Pre:
//    none
// Post:
//     returns to make sure that when placing the ship they do not overlap with another ship
bool Game::checkShipCollision(QMouseEvent *event) {
	int correctCheck = 0;
	for (int i = 0; i < _shipToPlace->getSize(); ++i) {
		if (_shipToPlace->isVertical()) {
			if (!_tileBoard->findTile(event->x(), event->y() + 41 * i)->getOccupied()) {
				++correctCheck;
			}
		}
		else {
			if (!_tileBoard->findTile(event->x() + 41 * i, event->y() )->getOccupied()) {
				++correctCheck;
			}
		}
	}
	if (correctCheck == _shipToPlace->getSize()) {
		return true;
	}
	return false;
}

// redrawBoard
// redraws the board for when ship is picked back up
// Pre:
//    none
// Post:
//     redraws the tiles and sets its owners and occupied back to its empty values when ship is picked up
void Game::redrawBoard(Ship* ship) {
	for (int i = 0;i < ship->getSize(); ++i) {
		Tile *tile = _tileBoard->findTile(_shipToPlace->getShipTiles().value(i)->x(), _shipToPlace->getShipTiles().value(i)->y());
		tile->setOccupied(false);
		tile->setOwner(nullptr);
		_activeScene->addItem(tile);
	}
}

// readyButton
// shows the readyButton to manage the flow of the game
// Pre:
//    none
// Post:
//     Will only display the ready button if all 5 ships are placed on the board
void Game::readyButton(bool ready) {
	_shipToPlace->setPlaced(ready);
	MenuButton* readyUpButton = new MenuButton(QString("Ready!"));
	int qxPos = 215;
	int qyPos = 575;
	readyUpButton->setPos(qxPos, qyPos);
	if (ready) {
		++_activeShips;
	}
	else if(_activeShips==5&&!ready) {
		--_activeShips;

		if(_activeScene->itemAt(QPointF(qxPos, qyPos), QTransform())!=0)
			_activeScene->removeItem(_activeScene->itemAt(QPointF(qxPos, qyPos), QTransform()));
	}
	else {
		--_activeShips;
	}
	if (_activeShips == 5) {
		_activeScene->addItem(readyUpButton);

		if (_whosTurn == QString("PLAYER1"))
		{
			connect(readyUpButton, SIGNAL(clicked()), this, SLOT(startPlayerTwo()));
		}
		else {
			connect(readyUpButton, SIGNAL(clicked()), this, SLOT(gamePlayer()));
		}

	}

}

// gameTurnManager
// manages the game, for appropriate turns, blacks out the screen and notifies next turn
// Pre:
//    none
// Post:
//     shows appropriate players board and makes sure that it notifies its next players turn
void Game::gameTurnManager() {

	setScene(_gameBoard2);
	nextPlayersTurn();
	QMessageBox::information(
		this,
		tr("Next Turn"),
		tr("Next players turn please switch players"));
	
	setScene(_activeScene);
	if (getWhosTurn() == "PLAYER1"){
		_player2Buttons->hideBoard();
		_player1Buttons->showBoard();
		drawBoardGUI();
	}
	else {
		_player1Buttons->hideBoard();
		_player2Buttons->showBoard();
		drawBoardGUI();
	}
}

// nextPlayerTurn
// changes QSTring to the other player
// Pre:
//    none
// Post:
//     sets QString to the other PLAYER1 or PLAYER2
void Game::nextPlayersTurn() {
	if (getWhosTurn() == QString("PLAYER1")) {
		setWhosTurn(QString("PLAYER2"));
	}
	else {
		setWhosTurn(QString("PLAYER1"));
	}
}

