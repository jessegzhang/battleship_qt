/*
 *  Created by Phil on 20/05/2011.
 *  Copyright 2011 Two Blue Cubes Ltd. All rights reserved.
 *
 *  Distributed under the Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
 // catch_default_main.hpp
 // Jesse Zhang
 // 11 March 2016
 //
 // For CS 372
 // Spring 2016
 // Project 1
 //
 // Contains main function for CATCH framework and QT GUI
#ifndef TWOBLUECUBES_CATCH_DEFAULT_MAIN_HPP_INCLUDED
#define TWOBLUECUBES_CATCH_DEFAULT_MAIN_HPP_INCLUDED
#include "bshipqt.h"
#include <QtWidgets/QApplication>
#include <QSplashScreen>
#include <QTimer>
#include "game.h"

#ifndef __OBJC__
Game* game;
QApplication *app;


// Standard C/C++ main entry point
int main (int argc, char * argv[]) {
	app = new QApplication(argc, argv);
	if (Catch::Session().run(argc, argv) == 0) {
		game = new Game();
		game->show();
		game->displayMainMenu();
		return app->exec();
	}
	else {
		return 1;
	}


}

#else // __OBJC__

// Objective-C entry point
int main (int argc, char * const argv[]) {
#if !CATCH_ARC_ENABLED
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
#endif

    Catch::registerTestMethods();
    int result = Catch::Session().run( argc, (char* const*)argv );

#if !CATCH_ARC_ENABLED
    [pool drain];
#endif

    return result;
}

#endif // __OBJC__

#endif // TWOBLUECUBES_CATCH_DEFAULT_MAIN_HPP_INCLUDED
