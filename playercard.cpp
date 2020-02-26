//
//  playercard.cpp
//  Game of War
//
//  Created by Mark Austin L. Pagarigan on 23/01/2019.
//  Copyright © 2019 Mark Austin L. Pagarigan. All rights reserved.
//
#include "playercard.h"
#include "enemycard.h"
#include "game.h"
#include "card.h"
#include <QTimer>
#include <QDebug>

extern Game * game;

PlayerCard::PlayerCard(QGraphicsPixmapItem * parent)
{
    if(game->card->getPlayer1Deck())
    {
    setPos(340,400);
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
void PlayerCard::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    //if you are familiar with the QTimer connect
    //this is basically that except you do it manually
    //each time you click on whatever your item is you
    //activate these functions
    game->gamesys->setTurnFlag(1);
    game->gamesys->setEnemyMoveFlag(1);
    game->gamesys->spawnDeck();
    //qDebug() << "click" << game->gamesys->getCompareFlag();
}
void PlayerCard::movetoCenter()
{
    TurnFlag = game->gamesys->getTurnFlag();
    if(TurnFlag == 1)
    {
    if(pos().y() > 240)
        setPos(x()+5,y()-10);
    if(pos().y() <= 240)
    {
        i = game->card->getPlayer1Deck();
        j = game->card->getPlayer1Suit();
        int x = game->card->getPlayer1Deck();
        int y = game->card->getPlayer2Deck();
        qDebug() << "CardSelectPlayer: " << game->card->getCardSelectPlayer();
        qDebug() << "CardSelectEnemy: " << game->card->getCardSelectEnemy();
        qDebug() << "Center Ecard: " << y << "Center Pcard: " << x;
        //qDebug() << "x = " << pos().x() << "y = " << pos().y();
        game->gamesys->compareCards(x,y);
        game->gamesys->setTurnFlag(2);
        move->disconnect();
    }
    }
}
void PlayerCard::change()
{
    addImage(i,j);
}

void PlayerCard::movetoPile()
{
    TurnFlag = game->gamesys->getTurnFlag();
    PlayFlag = game->gamesys->getPlayFlag();
    if(TurnFlag == 2)
    {
        movepile->start(15);
        CompFlag = game->gamesys->getCompareFlag();
        if(CompFlag == 1)
        {
            if(pos().y() <= 400)
            {
            setPos(x()-46,y()+32);
            //ticks = 8
            }
            if(pos().y() >= 400)
            {
                movepile->disconnect();
                costume->disconnect();
                if(PlayFlag == 0)
                game->gamesys->setNextFlag(1);
            }
        }
        else if(CompFlag == 2)
        {
            if(pos().y() >= 70)
            {
            setPos(x()+14,y()-34);
            //ticks = 7
            }
            if(pos().y() <= 70)
            {
                movepile->disconnect();
                costume->disconnect();
                if(PlayFlag == 0)
                game->gamesys->setNextFlag(1);
            }
        }
        else if(CompFlag == 3)
        {
            costume->disconnect();
            movepile->disconnect();
            game->gamesys->setNextFlag(1);
            WarVictor = 1;
        }
    }
}

void PlayerCard::WarmovetoPile()
{
    if(WarVictor == 1)
    {
        int victor = game->gamesys->getWarVictor();
        if(victor == 1)
        {
            if(pos().y() <= 400)
            {
            setPos(x()-46,y()+32);
            //ticks = 8
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
            setPos(x()+14,y()-34);
            //ticks = 7
            }
            if(pos().y() <= 70)
            {
                war->disconnect();
            }
        }
    }
}
