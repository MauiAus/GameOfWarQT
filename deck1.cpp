//
//  deck1.cpp
//  Game of War
//
//  Created by Mark Austin L. Pagarigan on 23/01/2019.
//  Copyright © 2019 Mark Austin L. Pagarigan. All rights reserved.
//
#include "deck1.h"
#include <QTimer>
#include "game.h"
#include <stdlib.h>
#include <QDebug>

//extern Game * game allows you to access the data from the Game class without the need of creating a new deep copy
//accessing this is called SOFT COPY
//because we are not making a new copy of that class in the HEAP but we are accessing the same set of data
//throughout the program
//you will see this extern Game * game in every other class because it is essential to make the objects interact
extern Game * game;

Deck1::Deck1(QGraphicsPixmapItem *parent)
{
    //the reason why there are flags in this function is because the deck1 spawner in gamesystem.cpp is
    //the same, so everytime it is called it spawns this class
    //putting the flags allow a specific type of Deck1 to spawn
    //flag 1 spawns the shuffling of the deck unto the table
    //flag 2 spawns a fake card after clicking the card, if the getcardDeck array is null(exceeds what you inputted also garbage data)
    //       then it does not appear
    //flag 3 spawns three cards which will stay on the table until the player or the enemy wins war
    //deck1 and deck2 are completely the same the only exception between them is that they move differently
    //the moving that you see is the result of QTimer
    //QTimer allows you to access the timeout function which is visually basically a clock
    //you can set how fast that clock ticks and everytime it reaches midnight it runs a signal that runs a function
    flag = game->gamesys->getDeckFlag();
    //game->gamesys->getDeckFlag()
    //this is an example of accessing the data stored on class game without the need of making a deep copy
    //we can do this because we set extern Game * game at the top so we have global access to this throughout the program
    //game->
    //      is the pointer of the Game class you can name it whatever you want
    //game->gamesys
    //             this means you are accessing another class stored in the game class
    //             this class is the Gamesystem and gamesys is the pointer to that
    //game->gamesys->getDeckFlag()
    //                            this is you accessing the getDeckFlag() function under the GameSystem() class
    if(flag == 1)
    {
        setPos(190,400);
        addImage(15,0);
        //this for example is Qtimer
        //I've set a pointer pointing towards QTimer and it is called timer
        //if you would like to visualize this then imagine a car
        //the car is duplicated, making the 2 cars the same as they possess the same functions
        //the only difference is that the drivers are different and what happens to the other
        //does not affect the other
        //this is called a DEEP COPY
        //we use new QTimer to form a deep copy of this
        //this is called a dynamic variable/object because it was instantiated(made) while the program is ran
        //note that if you were to make these dynamic objects you will always need a destructor(delete)
        //or the RAM/HEAP of your computer will continue to be taken up until it crashes
        //that is what a destructor is for
        //in order to prevent this from happening
        //the format for this is
        //connect([your time pointer],SIGNAL(timeout()),[the pointer of your reciver/slot | this(if it is in the class],SLOT([function()])
        //[your time pointer]->start([how fast you want the clock to move])
        QTimer * timer = new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(move()));
        timer->start(40);
        QTimer * delet = new QTimer(this);
        connect(delet,SIGNAL(timeout()),this,SLOT(remove()));
        delet->start(300);
    }
    if(flag == 2)
    {
        setPos(340,400);
        addImage(15,0);
        QTimer * exist = new QTimer(this);
        connect(exist,SIGNAL(timeout()),this,SLOT(remove2()));
        exist->start(100);
    }
    if(flag == 3)
    {
        WMFlag = game->gamesys->getWarFlag();
        setPos(340,400);
        addImage(15,0);
        WarM = new QTimer();
        connect(WarM,SIGNAL(timeout()),this,SLOT(WarMove()));
        WarM->start(20);
        WarMP = new QTimer();
        connect(WarMP,SIGNAL(timeout()),this,SLOT(WarMoveMP()));
        WarMP->start(20);
    }
}

void Deck1::move()
{
    if(pos().x() < 340)
        setPos(x()+10,y());
}

void Deck1::remove()
{
    if(flag == 1)
    {
    if(pos().x() >= 340)
    delete this;
    }
}

void Deck1::remove2()
{
    existence = game->gamesys->getNextFlag();
    if(existence == 2)
    {
        delete this;
        qDebug() << "delete successful";
    }
}

void Deck1::WarMove()
{
    if(WMFlag == 1)
    {
        if(pos().y() > 240)
        {
            setPos(x()+4.375,y()-10);
        }
        if(pos().y() <= 240)
        {
            qDebug() << "x = " << pos().x() << "y = " << pos().y();
            //this is the disconnect
            //you run this if you want the clock to stop moving entirely throughout the execution of the program
            WarM->disconnect();
        }
    }
    if(WMFlag == 2)
    {
        if(pos().y() > 240)
        {
            setPos(x()+5,y()-10);
        }
        if(pos().y() <= 240)
        {
            qDebug() << "x = " << pos().x() << "y = " << pos().y();
            WarM->disconnect();
        }
    }
    if(WMFlag == 3)
    {
        if(pos().y() > 240)
        {
            setPos(x()+5.625,y()-10);
        }
        if(pos().y() <= 240)
        {
            qDebug() << "x = " << pos().x() << "y = " << pos().y();
            WarM->disconnect();
        }
    }
}

void Deck1::WarMoveMP()
{
    int victor = game->gamesys->getWarVictor();
    if(victor == 1)
    {
        if(WMFlag == 1)
        {
            if(pos().y() < 400)
            {
                setPos(x()-13.75,y()+10);
            }
            if(pos().y() >= 400)
            {
                WarMP->disconnect();
            }
        }
        if(WMFlag == 2)
        {
            if(pos().y() < 400)
            {
                setPos(x()-14.375,y()+10);
            }
            if(pos().y() >= 400)
            {
                WarMP->disconnect();
            }
        }
        if(WMFlag == 3)
        {
            if(pos().y() < 400)
            {
                setPos(x()-15,y()+10);
            }
            if(pos().y() >= 400)
            {
                WarMP->disconnect();
            }
        }
    }
    if(victor == 2)
    {
        if(WMFlag == 1)
        {
            if(pos().y() > 70)
            {
                setPos(x()+5,y()-10.625);
            }
            if(pos().y() <= 70)
            {
                WarMP->disconnect();
            }
        }
        if(WMFlag == 2)
        {
            if(pos().y() > 70)
            {
                setPos(x()+4.375,y()-10.625);
            }
            if(pos().y() <= 70)
            {
                WarMP->disconnect();
            }
        }
        if(WMFlag == 3)
        {
            if(pos().y() > 70)
            {
                setPos(x()+3.75,y()-10.625);
            }
            if(pos().y() <= 70)
            {
                WarMP->disconnect();
            }
        }
    }
}

