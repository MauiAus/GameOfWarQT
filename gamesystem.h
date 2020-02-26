#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

class GameSystem: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    GameSystem(QGraphicsRectItem * parent=nullptr);
    //spawners
    void spawnDeckTime();
    void spawnPlayerCard();
    void spawnEnemyCard();
    //setters and getters
    int getDeckFlag();
    void setEnemyMoveFlag(int x);
    int getEnemyMoveFlag();
    void setTurnFlag(int x);
    int getTurnFlag();
    int getCompareFlag();
    void setNextFlag(int x);
    int getNextFlag();
    int getWarFlag();
    int getPlayFlag();
    int getWarVictor();
    void setWarVictor(int x);
    //systems
    void compareCards(int x, int y);
    void playerPile();
    void enemyPile();
    void nextCard();
    void WarPhaseOne();
    QTimer * timer;
    QTimer * pseudo;
    QTimer * warend;

public slots:
    void spawnDeck();
    void gamePhase();
    void PseudoRemover();
    void WarEnd();
private:
    int CardCtr = 0;
    int Deckflag = 1;
    int EnemyMoveFlag = 0;
    int compareFlag = 0;
    int TurnFlag = 0;
    int NextFlag = 0;
    int PCard;
    int ECard;
    int PPile[52];
    int PPileSuit[52];
    int PCardNum = 0;
    int EPile[52];
    int EPileSuit[52];
    int ECardNum = 0;
    int NextCard = 0;
    int Turns = 0;
    int WarFlag = 0;
    int WarPhase = 0;
    int PlayFlag = 0;
    int WarVictor = 0;
    int WarPrize = 0;
    int WarPD[52];
    int WarPS[52];
    int Wari = 0;
};

#endif // GAMESYSTEM_H
