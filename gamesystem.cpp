//
//  gamesystem.cpp
//  Game of War
//
//  Created by Mark Austin L. Pagarigan on 23/01/2019.
//  Copyright © 2019 Mark Austin L. Pagarigan. All rights reserved.
//
#include "gamesystem.h"
#include "deck1.h"
#include "deck2.h"
#include "playercard.h"
#include "enemycard.h"
#include "game.h"
#include <QDebug>

extern Game * game;

GameSystem::GameSystem(QGraphicsRectItem * parent)
{
    timer = new QTimer();
    QTimer * phase = new QTimer();
    connect(phase,SIGNAL(timeout()),this,SLOT(gamePhase()));
    phase->start(100);
}

void GameSystem::spawnDeckTime()
{
    connect(timer,SIGNAL(timeout()),this,SLOT(spawnDeck()));
    timer->start(100);
}

void GameSystem::spawnPlayerCard()
{
    PlayerCard * pcard = new PlayerCard();
    scene()->addItem(pcard);
}

void GameSystem::spawnEnemyCard()
{
    EnemyCard * ecard = new EnemyCard();
    scene()->addItem(ecard);
}

int GameSystem::getDeckFlag()
{
    return Deckflag;
}

void GameSystem::setEnemyMoveFlag(int x)
{
    EnemyMoveFlag = x;
}

int GameSystem::getEnemyMoveFlag()
{
    return EnemyMoveFlag;
}

void GameSystem::setTurnFlag(int x)
{
    TurnFlag = x;
}

int GameSystem::getTurnFlag()
{
    return TurnFlag;
}

int GameSystem::getCompareFlag()
{
    return compareFlag;
}

void GameSystem::setNextFlag(int x)
{
    NextFlag = x;
}

int GameSystem::getNextFlag()
{
    return NextFlag;
}

int GameSystem::getWarFlag()
{
    return WarFlag;
}

int GameSystem::getPlayFlag()
{
    return PlayFlag;
}

int GameSystem::getWarVictor()
{
    return WarVictor;
}

void GameSystem::setWarVictor(int x)
{
    WarVictor = x;
}

void GameSystem::compareCards(int x, int y)
{
    PCard = x;
    ECard = y;
    qDebug() << "Ecard: " << ECard << "Pcard: " << PCard;
    if(PCard == 1)
        PCard = 14;
    if(ECard == 1)
        ECard = 14;
    if(PCard > ECard)
    {
        if(WarPhase == 2)
        {
            WarVictor = 1;
        }
        compareFlag = 1;
        playerPile();
    }
    else if(PCard < ECard)
    {
        if(WarPhase == 2)
        {
            WarVictor = 2;
        }
        compareFlag = 2;
        enemyPile();
    }
    else if(PCard == ECard)
    {
        compareFlag = 3;
        WarPhaseOne();
    }
}

void GameSystem::playerPile()
{
    int PlayersCard = game->card->getPlayer1Deck();
    int PlayersSuit = game->card->getPlayer1Suit();
    int EnemysCard = game->card->getPlayer2Deck();
    int EnemysSuit = game->card->getPlayer2Suit();
    if(WarPhase == 2)
    {
        for(int i = 0; i < WarPrize; i++)
        {
            PPile[PCardNum] = WarPD[i];
            PPileSuit[PCardNum] = WarPS[i];
            PCardNum++;
            PPile[PCardNum] = WarPD[i];
            PPileSuit[PCardNum] = WarPS[i];
            PCardNum++;
        }
        warend = new QTimer();
        connect(warend,SIGNAL(timeout()),this,SLOT(WarEnd()));
        warend->start(5000);
        WarPhase = 0;
    }
    qDebug() << "Ecard1: " << ECardNum << "Pcard1: " << PCardNum;
    PPile[PCardNum] = PlayersCard;
    PPileSuit[PCardNum] = PlayersSuit;
    PCardNum++;
    qDebug() << "Ecard2: " << ECardNum << "Pcard2: " << PCardNum;
    PPile[PCardNum] = EnemysCard;
    PPileSuit[PCardNum] = EnemysSuit;
    PCardNum++;
}

void GameSystem::enemyPile()
{
    int PlayersCard = game->card->getPlayer1Deck();
    int PlayersSuit = game->card->getPlayer1Suit();
    int EnemysCard = game->card->getPlayer2Deck();
    int EnemysSuit = game->card->getPlayer2Suit();
    if(WarPhase == 2)
    {
        for(int i = 0; i < WarPrize; i++)
        {
            EPile[ECardNum] = WarPD[i];
            EPileSuit[ECardNum] = WarPS[i];
            ECardNum++;
            EPile[ECardNum] = WarPD[i];
            EPileSuit[ECardNum] = WarPS[i];
            ECardNum++;
        }
        warend = new QTimer();
        connect(warend,SIGNAL(timeout()),this,SLOT(WarEnd()));
        warend->start(5000);
        WarPhase = 0;
    }
    qDebug() << "Ecard1: " << ECardNum << "Pcard1: " << PCardNum;
    EPile[ECardNum] = PlayersCard;
    EPileSuit[ECardNum] = PlayersSuit;
    ECardNum++;
    qDebug() << "Ecard2: " << ECardNum << "Pcard2: " << PCardNum;
    EPile[ECardNum] = EnemysCard;
    EPileSuit[ECardNum] = EnemysSuit;
    ECardNum++;
}

void GameSystem::nextCard()
{
    NextCard++;
    game->card->setCardSelectPlayer(NextCard);
    game->card->setCardSelectEnemy(NextCard);
    if(WarPhase == 2)
    {
        int PlayersCard = game->card->getPlayer1Deck();
        int PlayersSuit = game->card->getPlayer1Suit();
        int EnemysCard = game->card->getPlayer2Deck();
        int EnemysSuit = game->card->getPlayer2Suit();
        WarPD[Wari] = PlayersCard;
        WarPS[Wari] = PlayersSuit;
        Wari++;
        WarPD[Wari] = EnemysCard;
        WarPS[Wari] = EnemysSuit;
        Wari++;
    }
}

void GameSystem::WarPhaseOne()
{
    Deckflag = 3;
    WarPhase = 2;
    for(int i = 0; i < 6; i++)
    {
        nextCard();
    }
    for(WarFlag = 1; WarFlag < 4; WarFlag++)
    {
        spawnDeck();
        WarPrize++;
    }
    Deckflag = 2;
    WarFlag = 0;
}

void GameSystem::spawnDeck()
{
    Deck1 * deck1 = new Deck1();
    scene()->addItem(deck1);
    Deck2 * deck2 = new Deck2();
    scene()->addItem(deck2);
    if(Deckflag == 1)
    {
        CardCtr++;
        CardCtr++;

    if(CardCtr >=52)
    {
        timer->disconnect();
        spawnPlayerCard();
        spawnEnemyCard();
        Deckflag = 2;
    }

    //qDebug() << "Card Count: " << CardCtr;
    }
}

void GameSystem::gamePhase()
{
    if(NextFlag == 1)
    {
        int PlayerNull = game->card->getPlayer1Deck();
        int EnemyNull = game->card->getPlayer2Deck();
        if(PlayerNull != NULL)
        {
        spawnPlayerCard();
        }
        else {
            qDebug() << "NULL";
        }
        if(EnemyNull != NULL)
        {
        spawnEnemyCard();
        }
        else {
            qDebug() << "NULL";
        }
        setTurnFlag(0);
        setEnemyMoveFlag(0);
        setNextFlag(2);
        pseudo = new QTimer();
        connect(pseudo,SIGNAL(timeout()),this,SLOT(PseudoRemover()));
        pseudo->start(10);
        nextCard();
        Turns++;
        qDebug() << "Plays: " << Turns;
    }
}

void GameSystem::PseudoRemover()
{
    if(NextFlag == 2)
    {
        setNextFlag(0);
        pseudo->disconnect();
    }
}

void GameSystem::WarEnd()
{
    setWarVictor(0);
    warend->disconnect();
}
