// attackbutton.cpp
// Jesse Zhang
// 11 March 2016
//
// For CS 372
// Spring 2016
// Project 1
//
// Contains function declerations for AttackButton Class
#include "attackButton.h"

#include <QBrush>
#include <QGraphicsTextItem>

// ********* AttackButton ctor *********

// ctor
// Pre:
//     none
// Post:
//     generates a button that is unclicked.
AttackButton::AttackButton(QGraphicsItem *parent) : QGraphicsRectItem(parent) {


	//draw the rect
	setRect(0, 0, 41, 41);
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::white);
	setBrush(brush);

	_clicked = false;
	//allow responding to hover events
	setAcceptHoverEvents(true);
}

// ********* Member Functions *********
// mousePressEvent
// triggers mouse event when clicked on a button
// Pre:
//     none
// Post:
//     if not clicked will trigger the clickButton in attackBoard and mark it
void AttackButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	if (!getClicked()) {
		registerClick();
		emit clicked();
	}
}

// hoverEnterEvent
// When hovering over a clickable button, it turns red
// Pre:
//     none
// Post:
//     If the tile is clickable it will turn red on hover
void AttackButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
	if (!getClicked()) {
		//change color to red
		QBrush brush;
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(Qt::darkRed);
		setBrush(brush);
	}
}

// hoverLeaveEvent
// when button is not hovered over will return the button to its default color
// Pre:
//     none
// Post:
//     sets button back to a default color if it hasn't been clicked
void AttackButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
	if (!getClicked()) {
		QBrush brush;
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(Qt::white);
		setBrush(brush);
	}
}

// AttackButton
// Sets a pointer in AttackButton to the Tile it is hovering over
// Pre:
//     give a valid tile that is a board
// Post:
//     _owner now points to Tile* owner
void AttackButton::setOwner(Tile * owner)
{
	_owner = owner;
}
