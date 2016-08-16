// attackbutton.h
// Jesse Zhang
// March 10th 2016
//
// For CS 372 Fall 2016
// Header for the class AttackButton
#ifndef ATTACKBUTTON_H
#define ATTACKBUTTON_H
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <tile.h>

// *********************************************************************
// class AttackButton - Class Deceleration
// *********************************************************************

// class AttackButton
// Class which involves each individual button to be on the board
// Invariants:
//		AttackButton involves hovering and click events once spawned into
//		into the scene

class AttackButton : public QObject, public QGraphicsRectItem {
	Q_OBJECT
public:
	//constructors
	AttackButton(QGraphicsItem* parent = NULL);

	//public methods (events)
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

	Tile* getOwner() { return _owner; }
	void setOwner(Tile* owner);

	//setters
	void registerClick() { _clicked = true;	}
	
	//getters
	bool getClicked() { return _clicked; }
	
signals:
	void clicked();


private:
	Tile* _owner;
	bool _clicked;
};

#endif