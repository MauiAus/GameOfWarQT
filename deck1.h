#ifndef DECK1_H
#define DECK1_H

#include <QObject>
#include <QTimer>
#include "card.h"

class Deck1: public QObject, public Card
        //this is inheritance
        //this means that Deck1 now has access to all the public functions of QObject and the Card Class
        //QObject and Card are the parents/base and Deck1 is the child/derived class
{
    Q_OBJECT
    //in order to use QObject you need to put this
    //QObject allows the communication between classes(signals and slots)
    //below you will see the public slots:
    //it is the reciver of the whatever signal and they will run whenever the signal is ran
public:
    Deck1(QGraphicsPixmapItem *parent=nullptr);
    //each and everytime you would use anything derived from the QGraphicsItem function like this one
    //and you want to create several copies of it you need to input that parameter
    //([The QGraphcisItem derivation that you are using in this case pixmapitem] * parent=nullptr)
    void setxpos(int x);
    int getxpos();
    //this allows you to create a pointer to the QTimer class that can be accessed throughout the different
    //functions in the program
    //remember if you do not set the variable in either the public or private members and type them inside
    //the .cpp of your class function then any variable you set there will be comepletely unique
    //to that function(meaning you wont access it outside the function)
    //in this case you use it because you will need to disconnect these pointers later
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
#endif // DECK1_H
