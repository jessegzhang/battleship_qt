// attackboard.cpp
// Jesse Zhang
// 11 March 2016
//
// For CS 372
// Spring 2016
// Project 1
//
// Contains function declerations for AttackBoard Class
#include "attackboard.h"
#include "game.h"
#include <QSignalMapper>
#include <QMessageBox>

extern Game* game;
// ********* AttackBoard ctor *********
// ctor
// Pre:
//     tiles must be a valid QList of Tile
// Post:
//     Spawns an attackbutton at each tile position in QList
//	   programs the onclick to run checkhits with the appropriate index
AttackBoard::AttackBoard(QList<Tile*> tiles)
{
	for (int i = 0; i < tiles.size();++i) {
		AttackButton* button = new AttackButton();
		int xPos = tiles.value(i)->pos().x();
		int yPos = tiles.value(i)->pos().y();
		button->setPos(xPos, yPos);
		button->setOwner(tiles.value(i));
		_buttonList.append(button);
		connect(button, &AttackButton::clicked,
			[=]() { checkHits(i); });
		game->_activeScene->addItem(button);
	}
}

// ********* Member Functions *********

// hideBoard
// hides the AttackBoard from the graphical user interface
// Pre:
//    AttackBoard must be active on scene
// Post:
//     removes the AttackButton from the _activeScene
void AttackBoard::hideBoard() {
	for (int i = 0;i < _buttonList.size();++i) {
		game->_activeScene->removeItem(_buttonList.value(i));
	}
}

// showBoard
// Shows the AttackBoard in the graphical user interface
// Pre:
//     None
// Post:
//     Scene will add AttackButton's in AttackBoard to _activeScene
void AttackBoard::showBoard() {
	for (int i = 0;i < _buttonList.size();++i) {
		game->_activeScene->addItem(_buttonList.value(i));
	}
}

// getButton
// returns list of AttackButton's
// Pre:
//     none
// Post:
//     returns a QList of AttackButton pointers in the AttackBoard _buttonList
QList<AttackButton*> AttackBoard::getButton()
{
	return _buttonList;
}


// checkHits
//	Manages the checks for hits or misses based on user input
// Pre:
//     0=<index=<100
// Post:
//     Will display hits or misses and set the next players turn and update properly
//		Will also exit and announce when win condition is met
void AttackBoard::checkHits(int index) {
	Tile* tile=_buttonList[index]->getOwner();
	//checks to see if tile is valid
	//if valid marks the ship properly, and checks win condition
	if (tile->getOccupied()) {
		tile->setHit(true);
		tile->getOwner()->healthLoss();
		bool destroyed = false;
		if (tile->getOwner()->destroyed()) {
			if (game->getWhosTurn() == "PLAYER1") {
				game->_player2ShipsLeft--;
				destroyed = true;
			}
			else {
				game->_player1ShipsLeft--;
				destroyed = true;
			}
		}

	
		if (destroyed) {
			QString dialogue = "You have sunken the enemies: " + tile->getOwner()->getName() + ".";
			QMessageBox::information(
				game,
				tr("Hit!"),
				dialogue);
		}
		else {
			QMessageBox::information(
				game,
				tr("Hit!"),
				tr("You have sucessfully hit the enemy."));
		}
		QBrush brushTile;
		brushTile.setStyle(Qt::DiagCrossPattern);
		brushTile.setColor(Qt::red);
		tile->setBrush(brushTile);
		game->_activeScene->removeItem(tile);
		game->_activeScene->addItem(tile);

		AttackButton* colorButton= _buttonList[index];
		QBrush brush;
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(Qt::green);
		colorButton->setBrush(brush);
		game->_activeScene->removeItem(colorButton);
		game->_activeScene->addItem(colorButton);

	}
	//if not occupied triggers miss dialogue
	else {
		QMessageBox::information(
			game,
			tr("Miss"),
			tr("You have missed the enemy"));	

		AttackButton* colorButton = _buttonList[index];
		QBrush brush;
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(Qt::red);
		colorButton->setBrush(brush);
		game->_activeScene->removeItem(colorButton);
		game->_activeScene->addItem(colorButton);
	}
	//checks win condition after everything has been calculated properly
	if (game->_player1ShipsLeft == 0 | game->_player2ShipsLeft == 0) {
		QMessageBox::StandardButton reply;
		QString endDialogue = game->getWhosTurn() + " has won the game.";
		QMessageBox::information(
			game,
			tr("You Win!!!"),
			endDialogue);
		game->close();

	}
	//if win condition is not met runs the gameTurnManager
	else {
		game->gameTurnManager();
	}
}

