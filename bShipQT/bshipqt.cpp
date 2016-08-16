// bshipqt.cpp
// Jesse Zhang
// 11 March 2016
//
// For CS 372
// Spring 2016
// Project 1
//
// Contains function declerations for BShipQT class
// essentially main function for the gui
#include "bshipqt.h"
#include <QTCore>
#include <QTGui>
//setups ui
BShipQT::BShipQT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

BShipQT::~BShipQT()
{

}

//
void BShipQT::on_exitButton_clicked() {
	qApp->quit();
}

void BShipQT::on_startGame_clicked() {
	qApp->quit();
}