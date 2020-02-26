#ifndef ENEMYCARD_H
#define ENEMYCARD_H
#include <QObject>
#include "card.h"

class EnemyCard: public QObject, public Card
{
    Q_OBJECT
public:
    EnemyCard(QGraphicsPixmapItem *parent=nullptr);
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
    int MoveFlag = 0;
    int CompFlag = 0;
    int ImageFlag = 0;
    int PlayFlag = 0;
    int i=15;
    int j=0;
    int m = 0;
    int WarVictor = 0;
};
#endif // ENEMYCARD_H
