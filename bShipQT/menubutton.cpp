// menubutton.cpp
// Jesse Zhang
// 11 March 2016
//
// For CS 372
// Spring 2016
// Project 1
//
// Contains function declerations for MenuButton Class
#include "menubutton.h"
#include <QBrush>
#include <QGraphicsTextItem>

// ********* MenuButton ctor *********
MenuButton::MenuButton(QString name, QGraphicsItem *parent) : QGraphicsRectItem(parent) {
	
	
	//draw the rect
	setRect(0, 0, 200, 50);
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::darkCyan);
	setBrush(brush);

	//draw the text
	_text = new QGraphicsTextItem(name, this);
	int xPos = rect().width() / 2 - _text->boundingRect().width() / 2;
	int yPos = rect().height() / 2 - _text->boundingRect().height() / 2;
	_text->setPos(xPos, yPos);

	//allow responding to hover events
	setAcceptHoverEvents(true);
}

// ********* Member Functions *********

void MenuButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	emit clicked();
}

void MenuButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
	//change color to cyan
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::cyan);
	setBrush(brush);
}

void MenuButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
	//change color to dark cyan
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::darkCyan);
	setBrush(brush);
}