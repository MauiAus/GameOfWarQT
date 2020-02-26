#include "game.h"
#include <QDebug>
#include <QImage>

Game::Game(QWidget * parent)
{
    //add the scene
    //the scene is basically the tab of your program
    //in this case it is the entire interface of QT
    //without the scene you will not be able to see anything
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    scene->setBackgroundBrush(QImage(":new/background/Large_0348615.jpg"));
    setScene(scene);

    //initiate the cards
    card = new Card();
    card->deal();
    qDebug() << "Cards " << card->getPlayer1Deck() << " " << card->getPlayer2Deck() << endl
             << "Suits " << card->getPlayer1Suit() << " " << card->getPlayer2Suit();

    //spawn the Decks
    gamesys = new GameSystem();
    gamesys->spawnDeckTime();
    scene->addItem(gamesys);
    //each time you are to add something into the scene
    //you will need to use this function
    //the parameters inside basically addItem(pointer) is the pointer to a class
}
