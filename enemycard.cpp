//
//  enemycard.cpp
//  Game of War
//
//  Created by Mark Austin L. Pagarigan on 23/01/2019.
//  Copyright © 2019 Mark Austin L. Pagarigan. All rights reserved.
//
#include "enemycard.h"
#include "game.h"
#include "card.h"
#include <QTimer>
#include <QDebug>

extern Game * game;

EnemyCard::EnemyCard(QGraphicsPixmapItem * parent)
{
    if(game->card->getPlayer2Deck())
    {
    setPos(340,70);
    costume = new QTimer();
    connect(costume,SIGNAL(timeout()),this,SLOT(change()));
    costume->start(50);
    move = new QTimer();
    connect(move,SIGNAL(timeout()),this,SLOT(movetoCenter()));
    move->start(5);
    movepile = new QTimer();
    connect(movepile,SIGNAL(timeout()),this,SLOT(movetoPile()));
    movepile->start(3000);
    war = new QTimer();
    connect(war,SIGNAL(timeout()),this,SLOT(WarmovetoPile()));
    war->start(15);
    }
}
void EnemyCard::movetoCenter()
{
    MoveFlag = game->gamesys->getEnemyMoveFlag();
    if(MoveFlag == 1)
    {
    if(pos().y() < 240)
        setPos(x()-5,y()+10.625);
    if(pos().y() >= 240)
    {
        i = game->card->getPlayer2Deck();
        j = game->card->getPlayer2Suit();
        move->disconnect();
        qDebug() << "Center ECard: " << i << " " << j;
        //qDebug() << "x = " << pos().x() << "y = " << pos().y();
        //qDebug() << "Deck: " << game->card->getPlayer2Deck();
        //qDebug() << "Suit: " << game->card->getPlayer2Suit();
    }
    }

}
void EnemyCard::change()
{
    addImage(i,j);
}

void EnemyCard::movetoPile()
{
    MoveFlag = game->gamesys->getTurnFlag();
    if(MoveFlag == 2)
    {
        movepile->start(15);
        CompFlag = game->gamesys->getCompareFlag();
        if(CompFlag == 1)
        {
            if(pos().y() <= 400)
            {
            setPos(x()-14,y()+32);
            //qDebug() << "Ticks: " << m++;
            }
            if(pos().y() >= 400)
            {
                movepile->disconnect();
                costume->disconnect();
                //qDebug() << "x = " << pos().x() << "y = " << pos().y();
            }
        }
        else if(CompFlag == 2)
        {
            if(pos().y() >= 70)
            {
            setPos(x()+46,y()-34);
            //qDebug() << "Ticks: " << m++;
            }
            if(pos().y() <= 70)
            {
            movepile->disconnect();
            costume->disconnect();
            //qDebug() << "x = " << pos().x() << "y = " << pos().y();
            }
        }
    }
}

void EnemyCard::WarmovetoPile()
{
    if(WarVictor == 1)
    {
        int victor = game->gamesys->getWarVictor();
        if(victor == 1)
        {
            if(pos().y() <= 400)
            {
            setPos(x()-14,y()+32);
            //qDebug() << "Ticks: " << m++;
            }
            if(pos().y() >= 400)
            {
                war->disconnect();
            }
        }
        else if(victor == 2)
        {
            if(pos().y() >= 70)
            {
            setPos(x()+46,y()-34);
            //qDebug() << "Ticks: " << m++;
            }
            if(pos().y() <= 70)
            {
                war->disconnect();
            }
        }
    }
}
