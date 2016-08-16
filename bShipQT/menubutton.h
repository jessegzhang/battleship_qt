// menubutton.h
// Jesse Zhang
// March 10th 2016
//
// For CS 372 Fall 2016
// Header for the MenuButton class
#ifndef MENUBUTTON_H
#define MENUBUTTON_H
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

// *********************************************************************
// class Game - Class Deceleration
// *********************************************************************

// class Game
// Class that handles the general flow of the game 
// includes main menu and turn managers
// Invariants:
//		Game manages which scene is active and interacts with all classes
//		to generate the graphical user interface
class MenuButton : public QObject, public QGraphicsRectItem {
	Q_OBJECT
public:
	//constructors
	MenuButton(QString name, QGraphicsItem* parent = NULL);

	//public methods (events)
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
	void clicked();

private:
	QGraphicsTextItem* _text;
};

#endif