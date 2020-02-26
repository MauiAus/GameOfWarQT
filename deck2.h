#ifndef DECK2_H
#define DECK2_H

#include <QObject>
#include "card.h"
#include <QTimer>

class Deck2: public QObject, public Card
{
    Q_OBJECT
public:
    Deck2(QGraphicsPixmapItem *parent=nullptr);
    void setxpos(int x);
    int getxpos();
    QTimer * WarM;
    QTimer * WarMP;
public slots:
    void move();
    void remove();
    void remove2();
    void WarMove();
    void WarMoveMP();
private:
    int xpos=280;
    int flag;
    int existence;
    int WMFlag = 0;
};
#endif // DECK2_H
