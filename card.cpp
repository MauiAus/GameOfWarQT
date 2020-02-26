//
//  card.cpp
//  Game of War
//
//  Created by Mark Austin L. Pagarigan on 23/01/2019.
//  Copyright © 2019 Mark Austin L. Pagarigan. All rights reserved.
//
#include "card.h"
#include "QDebug"
#include <algorithm>
#include <QGraphicsScene>

Card::Card(QGraphicsPixmapItem *parent)
{
    //parent allows the duplication of cards
}

void Card::addCardvalue()
{
    //this function adds a cardnumber to the Cards[] array
    //basically it sorts things like
    //Card[i] = 1
    //Card[i] = 2
    //...and so on
    int value = 1;
    int ctr = 4;
    int i;
    addCardSuit();
    for(i = 0; i < 52; i++)
    {
        if(ctr != 0)
        {
            Cards[i] = value;
            ctr = ctr - 1;
        }
        if(ctr == 0)
        {
            ctr = 4;
            value++;
        }
    }
    //this is just a debugger to identify if the cards and suits are arranged correctly
    //this will show on your console
    for(i = 0; i < 52; i++)
    {
        qDebug() << "Card" << i << ": " << Cards[i] << Suits[i];
    }
}

void Card::shuffleCards()
{
    //the random_shuffle function is taken from class <algorithm>
    //this rearranges the Card[] array in a completely random order while retaining their
    //stored data
    //also note that I placed in the Cards and Suits array. Why?
    //it is because random_shuffle rearranges the array in a uniform way
    //that means as long as the arrangement of two arrays are the same they will be rearranged
    //in the exact same order
    std::random_shuffle(&Cards[0], &Cards[52]);
    std::random_shuffle(&Suits[0], &Suits[52]);
    //std::random_shuffle(&Suits[0], &Suits[52]);
        qDebug() << "After shuffle";
    int i;
    for(i = 0; i < 52; i++)
    {
        qDebug() << "Card" << i << ": " << Cards[i] << Suits[i];
    }
}

void Card::addCardSuit()
{
    //this function adds a suit assignment for the Suit[] array
    //this means that this will assign a suit every four counts
    //visualization:
    //1
    //1
    //1
    //1
    //2
    //2
    //...and so on
    int i;
    int suitNo = 1;
    int ctr = 4;
    for(i = 0; i < 52; i++)
    {
        if(ctr != 0)
        {
            Suits[i] = suitNo;
            suitNo++;
            ctr = ctr - 1;
        }
        if(ctr == 0)
        {
            ctr = 4;
            suitNo = 1;
        }
    }
}

int * Card::sortPlayer1Deck()
{
    //this arranges the player1deck
    //making Deck1Card[] array equal to the first 26 cards of Card[] array
   for(int i = 0; i < 26; i++)
   {
       Deck1Card[i] = Cards[i];
   }
   //this returns the Deck1Cardarray, but it cannot be accessed without the getter
   return Deck1Card;
}

int * Card::sortPlayer2Deck()
{
   //this is similar to arranging player2deck with the exception of
   //the Cards[] array to start at the 27th card(imagine cutting a deck in half)
   int s = 26;
   for(int i = 0; i < 26; i++)
   {
       Deck2Card[i] = Cards[s];
       s++;
   }
   return Deck2Card;
}

int *Card::sortPlayer1DeckSuit()
{
    //notice that this is a pointer function because this returns Deck1suit array
    //that means that in order to get a specific element from the array you would need
    //a pointer which will return the stored data instead of the entire array
    //and yes the same properties of this apply to the other sort functions
    for(int i = 0; i < 26; i++)
    {
        Deck1Suit[i] = Suits[i];
    }
    return Deck1Suit;
}

int *Card::sortPLayer2DeckSuit()
{
    //if you read the top I think you'd understand this by now
    int s = 26;
    //int x = 0;
    for(int i = 0; i < 26; i++)
    {
        Deck2Suit[i] = Suits[s];
        s++;
      //  qDebug() << Suits[s] << " " << x++;
    }
    return Deck2Suit;
}

void Card::deal()
{
    //deal is a combination of all previous functions
    //first it adds a cardvalue and a card suit to the Card[] array
    addCardvalue();
    addCardSuit();
    //srand is a random seed generator, if you were to take it out then it would
    //generate a specific seed
    //meaning that it will be uniformly random, meaning that you can always input
    //the same set of cards by taking this out
    srand(time(NULL));
    //if you remove srand the shuffle is not completely random anymore
    //try changing %1000 to any number you want and you will notice that the set of cards
    //will always have the same order
    int shuffle = rand() % 1000; //2000 = war
    for(int i = 0; i < shuffle; i++)
    {
        shuffleCards();
    }
    sortPlayer1Deck();
    sortPlayer2Deck();
    sortPlayer1DeckSuit();
    sortPLayer2DeckSuit();
    for(int j = 0; j < 26; j++)
    {
        qDebug() << j << ". " << "Player: " << getPlayer1Deck() << " " << getPlayer1Suit()
                      << " | " << "Enemy: " << getPlayer2Deck() << " " << getPlayer2Suit();
        CardSelectPlayer++;
        CardSelectEnemy++;
    }
    CardSelectEnemy = 0;
    CardSelectPlayer = 0;
}

int Card::getPlayer1Deck()
{
    //the next several functions are getters
    //these allow you to call each and every private variable in the class Card
    //notice that the deck getters return a pointer
    //that is because these pointers point to different arrays
    //and remember if you want to get the data stored in an array you need a pointer
    int * p;
    p = sortPlayer1Deck();
    return *(p + CardSelectPlayer);
}

int Card::getPlayer2Deck()
{
    int * p;
    p = sortPlayer2Deck();
    return *(p + CardSelectEnemy);
}

int Card::getPlayer1Suit()
{
    int * p;
    p = sortPlayer1DeckSuit();
    return *(p + CardSelectPlayer);
}

int Card::getPlayer2Suit()
{
    int * p;
    p = sortPLayer2DeckSuit();
    return *(p + CardSelectEnemy);
}

void Card::setCardSelectPlayer(int x)
{
    //the Cardselect pointers allow you to choose which card youd want to take it from
    //this is connected to the getcard pointers and whichver you input will affect
    //what the getcard pointers return
    CardSelectPlayer = x;
}

void Card::setCardSelectEnemy(int x)
{
    CardSelectEnemy = x;
}

int Card::getCardSelectEnemy()
{
    return CardSelectEnemy;
}

int Card::getCardSelectPlayer()
{
    return CardSelectPlayer;
}


void Card::addImage(int x,int y)
{
    //this is the image function which will determine what image to display
    int cCard = x;
    int cSuit = y;
    if(cCard == 1 && cSuit == 1)
        setPixmap(QPixmap(":new/images/Cards/ACECLUBS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 2 && cSuit == 1)
        setPixmap(QPixmap(":new/images/Cards/2CLUBS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 3 && cSuit == 1)
        setPixmap(QPixmap(":new/images/Cards/3CLUBS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 4 && cSuit == 1)
        setPixmap(QPixmap(":new/images/Cards/4CLUBS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 5 && cSuit == 1)
        setPixmap(QPixmap(":new/images/Cards/5CLUBS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 6 && cSuit == 1)
        setPixmap(QPixmap(":new/images/Cards/6CLUBS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 7 && cSuit == 1)
        setPixmap(QPixmap(":new/images/Cards/7CLUBS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 8 && cSuit == 1)
        setPixmap(QPixmap(":new/images/Cards/8CLUBS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 9 && cSuit == 1)
        setPixmap(QPixmap(":new/images/Cards/9CLUBS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 10 && cSuit == 1)
        setPixmap(QPixmap(":new/images/Cards/10CLUBS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 11 && cSuit == 1)
        setPixmap(QPixmap(":new/images/Cards/JACKCLUBS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 12 && cSuit == 1)
        setPixmap(QPixmap(":new/images/Cards/QUEENCLUBS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 13 && cSuit == 1)
        setPixmap(QPixmap(":new/images/Cards/KINGCLUBS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 1 && cSuit == 2)
        setPixmap(QPixmap(":new/images/Cards/ACESPADES.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 2 && cSuit == 2)
        setPixmap(QPixmap(":new/images/Cards/2SPADES.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 3 && cSuit == 2)
        setPixmap(QPixmap(":new/images/Cards/3SPADES.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 4 && cSuit == 2)
        setPixmap(QPixmap(":new/images/Cards/4SPADES.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 5 && cSuit == 2)
        setPixmap(QPixmap(":new/images/Cards/5SPADES.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 6 && cSuit == 2)
        setPixmap(QPixmap(":new/images/Cards/6SPADES.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 7 && cSuit == 2)
        setPixmap(QPixmap(":new/images/Cards/7SPADES.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 8 && cSuit == 2)
        setPixmap(QPixmap(":new/images/Cards/8SPADES.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 9 && cSuit == 2)
        setPixmap(QPixmap(":new/images/Cards/9SPADES.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 10 && cSuit == 2)
        setPixmap(QPixmap(":new/images/Cards/10SPADES.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 11 && cSuit == 2)
        setPixmap(QPixmap(":new/images/Cards/JACKSPADES.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 12 && cSuit == 2)
        setPixmap(QPixmap(":new/images/Cards/QUEENSPADES.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 13 && cSuit == 2)
        setPixmap(QPixmap(":new/images/Cards/KINGSPADES.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 1 && cSuit == 3)
        setPixmap(QPixmap(":new/images/Cards/ACEHEARTS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 2 && cSuit == 3)
        setPixmap(QPixmap(":new/images/Cards/2HEARTS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 3 && cSuit == 3)
        setPixmap(QPixmap(":new/images/Cards/3HEARTS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 4 && cSuit == 3)
        setPixmap(QPixmap(":new/images/Cards/4HEARTS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 5 && cSuit == 3)
        setPixmap(QPixmap(":new/images/Cards/5HEARTS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 6 && cSuit == 3)
        setPixmap(QPixmap(":new/images/Cards/6HEARTS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 7 && cSuit == 3)
        setPixmap(QPixmap(":new/images/Cards/7HEARTS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 8 && cSuit == 3)
        setPixmap(QPixmap(":new/images/Cards/8HEARTS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 9 && cSuit == 3)
        setPixmap(QPixmap(":new/images/Cards/9HEARTS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 10 && cSuit == 3)
        setPixmap(QPixmap(":new/images/Cards/10HEARTS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 11 && cSuit == 3)
        setPixmap(QPixmap(":new/images/Cards/JACKHEARTS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 12 && cSuit == 3)
        setPixmap(QPixmap(":new/images/Cards/QUEENHEARTS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 13 && cSuit == 3)
        setPixmap(QPixmap(":new/images/Cards/KINGHEARTS.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 1 && cSuit == 4)
        setPixmap(QPixmap(":new/images/Cards/ACEDIAMOND.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 2 && cSuit == 4)
        setPixmap(QPixmap(":new/images/Cards/2DIAMOND.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 3 && cSuit == 4)
        setPixmap(QPixmap(":new/images/Cards/3DIAMOND.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 4 && cSuit == 4)
        setPixmap(QPixmap(":new/images/Cards/4DIAMOND.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 5 && cSuit == 4)
        setPixmap(QPixmap(":new/images/Cards/5DIAMOND.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 6 && cSuit == 4)
        setPixmap(QPixmap(":new/images/Cards/6DIAMOND.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 7 && cSuit == 4)
        setPixmap(QPixmap(":new/images/Cards/7DIAMOND.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 8 && cSuit == 4)
        setPixmap(QPixmap(":new/images/Cards/8DIAMOND.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 9 && cSuit == 4)
        setPixmap(QPixmap(":new/images/Cards/9DIAMOND.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 10 && cSuit == 4)
        setPixmap(QPixmap(":new/images/Cards/10DIAMOND.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 11 && cSuit == 4)
        setPixmap(QPixmap(":new/images/Cards/JACKDIAMOND.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 12 && cSuit == 4)
        setPixmap(QPixmap(":new/images/Cards/QUEENDIAMOND.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 13 && cSuit == 4)
        setPixmap(QPixmap(":new/images/Cards/KINGDIAMOND.png").scaled(120,120,Qt::KeepAspectRatio));
    if(cCard == 15)
        setPixmap(QPixmap(":new/images/Cards/BackCard.png").scaled(120,120,Qt::KeepAspectRatio));
}


