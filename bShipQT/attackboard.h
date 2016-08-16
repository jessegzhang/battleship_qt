// attackboard.h
// Jesse Zhang
// March 10th 2016
//
// For CS 372 Fall 2016
// Header for the class AttackBoard

#ifndef ATTACKBOARD_H
#define ATTACKBOARD_H
#include <QList>
#include <QObject>
#include <QMouseEvent>
#include "attackbutton.h"

// *********************************************************************
// class AttackBoard - Class Deceleration
// *********************************************************************

// class AttackBoard
// Class holding the buttons for doing attacks on the board
// Invariants:
//		Attackboard will spawn a QList of tiles, it will contain
//		100 tiles of AttackButton
class AttackBoard: public QObject {
	Q_OBJECT
public:
	//constructors
	AttackBoard() {};
	AttackBoard(QList<Tile*> tiles);

	//getters
	QList<AttackButton*> getButton();

	//setters
	void hideBoard();
	void showBoard();

//slots are for QT button calls
private slots:
	void checkHits(int index);
	

//public methods
private:
	QList<AttackButton*> _buttonList;

};

#endif 