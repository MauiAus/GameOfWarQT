//
//  main.cpp
//  Game of War
//
//  Created by Mark Austin L. Pagarigan on 23/01/2019.
//  Copyright © 2019 Mark Austin L. Pagarigan. All rights reserved.
//
#include <QApplication>
#include "game.h"

Game * game;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    game->show();
    return a.exec();
}
