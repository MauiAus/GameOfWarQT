#ifndef PLAYERCARD_H
#define PLAYERCARD_H
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include "card.h"

class PlayerCard: public QObject, public Card
{
    Q_OBJECT
public:
    PlayerCard(QGraphicsPixmapItem *parent=nullptr);
    //you must follow the bottom uniformly in order to make a function that
    //can be clicked, just change the body of the function
    //see the cpp for explanation
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    QTimer * costume;
    QTimer * move;
    QTimer * movepile;
    QTimer * war;
public slots:
    void movetoCenter();
    void change();
    void movetoPile();
    void WarmovetoPile();
private:
    int ImageFlag = 0;
    int TurnFlag = 0;
    int CompFlag = 0;
    int PlayFlag = 0;
    int i=15;
    int j=0;
    int WarVictor = 0;
};
#endif // PLAYERCARD_H
