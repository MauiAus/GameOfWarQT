#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QObject>
#include "card.h"
#include "gamesystem.h"

class Game: public QGraphicsView
{
public:
    Game(QWidget * parent=nullptr);
    QGraphicsScene * scene;
    Card * card;
    GameSystem * gamesys;
};

#endif // GAME_H
