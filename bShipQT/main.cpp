
#include "bshipqt.h"
#include <QtWidgets/QApplication>
#include <QSplashScreen>
#include <QTimer>
#include "game.h"


Game* game;


// Standard C/C++ main entry point
int main(int argc, char * argv[]) {
		QApplication app(argc, argv);
		game = new Game();
		game->show();
		game->displayMainMenu();
		return app.exec();

}

