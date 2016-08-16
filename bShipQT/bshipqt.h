// bshipqt.h
// Jesse Zhang
// March 10th 2016
//
// For CS 372 Fall 2016
// Header for the BShipQT
// This is QT's main header to run gui resources
#ifndef BSHIPQT_H
#define BSHIPQT_H

#include <QtWidgets/QMainWindow>
#include "ui_bshipqt.h"
// *********************************************************************
// class BShipQT - Class Deceleration
// *********************************************************************

// class BShipQT
// Class involving the functions nescessary to generate gui
class BShipQT : public QMainWindow
{
	Q_OBJECT

public:
	BShipQT(QWidget *parent = 0);
	~BShipQT();

private:
	Ui::BShipQTClass ui;

public slots:
	void on_exitButton_clicked();
	void on_startGame_clicked();
};

#endif // BSHIPQT_H
