//
//  deck2.cpp
//  Game of War
//
//  Created by Mark Austin L. Pagarigan on 23/01/2019.
//  Copyright © 2019 Mark Austin L. Pagarigan. All rights reserved.
//
#include "deck2.h"
#include <QTimer>
#include "game.h"
#include <stdlib.h>
#include <QDebug>

extern Game * game;

Deck2::Deck2(QGraphicsPixmapItem *parent)
{
    flag = game->gamesys->getDeckFlag();
    if(game->card->getPlayer2Deck())
    {
    if(flag == 1)
    {
        setPos(490,70);
        addImage(15,0);
        QTimer * timer = new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(move()));
        timer->start(40);
        QTimer * delet = new QTimer(this);
        connect(delet,SIGNAL(timeout()),this,SLOT(remove()));
        delet->start(300);
    }
    if(flag == 2)
    {
        setPos(340,70);
        addImage(15,0);
        QTimer * exist = new QTimer(this);
        connect(exist,SIGNAL(timeout()),this,SLOT(remove2()));
        exist->start(100);
    }
    if(flag == 3)
    {
        WMFlag = game->gamesys->getWarFlag();
        setPos(340,70);
        addImage(15,0);
        WarM = new QTimer();
        connect(WarM,SIGNAL(timeout()),this,SLOT(WarMove()));
        WarM->start(20);
        WarMP = new QTimer();
        connect(WarMP,SIGNAL(timeout()),this,SLOT(WarMoveMP()));
        WarMP->start(20);
    }
    }
}

void Deck2::move()
{
    if(pos().x() > 340)
        setPos(x()-10,y());
}

void Deck2::remove()
{
    if(pos().x() <= 340)
        delete this;
}

void Deck2::remove2()
{
    existence = game->gamesys->getNextFlag();
    if(existence == 2)
    {
        delete this;
    }
}

void Deck2::WarMove()
{
    if(WMFlag == 1)
    {
        if(pos().y() < 240)
        {
            setPos(x()-4.375,y()+10);
        }
        if(pos().y() >= 240)
        {
            qDebug() << "x = " << pos().x() << "y = " << pos().y();
            WarM->disconnect();
        }
    }
    if(WMFlag == 2)
    {
        if(pos().y() < 240)
        {
            setPos(x()-5,y()+10);
        }
        if(pos().y() >= 240)
        {
            qDebug() << "x = " << pos().x() << "y = " << pos().y();
            WarM->disconnect();
        }
    }
    if(WMFlag == 3)
    {
        if(pos().y() < 240)
        {
            setPos(x()-5.625,y()+10);
        }
        if(pos().y() >= 240)
        {
            qDebug() << "x = " << pos().x() << "y = " << pos().y();
            WarM->disconnect();
        }
    }
}
void Deck2::WarMoveMP()
{
    int victor = game->gamesys->getWarVictor();
    if(victor == 1)
    {
        if(WMFlag == 1)
        {
            if(pos().y() < 400)
            {
                setPos(x()-4.7265625,y()+10);
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
                setPos(x()-4.0625,y()+10);
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
                setPos(x()-3.3984375,y()+10);
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
                setPos(x()+14.0234375,y()-10.625);
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
                setPos(x()+14.7875,y()-10.625);
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
                setPos(x()+15.3515625,y()-10.625);
            }
            if(pos().y() <= 70)
            {
                WarMP->disconnect();
            }
        }
    }
}


