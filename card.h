#ifndef CARD_H
#define CARD_H
#include <QGraphicsPixmapItem>


class Card: public QGraphicsPixmapItem
{
public:
    Card(QGraphicsPixmapItem * parent=nullptr);
    void addCardvalue();
    void shuffleCards();
    void addCardSuit();
    int * sortPlayer1Deck();
    int * sortPlayer2Deck();
    int * sortPlayer1DeckSuit();
    int * sortPLayer2DeckSuit();
    void deal();
    //setters and getters
    int getPlayer1Deck();
    int getPlayer2Deck();
    int getPlayer1Suit();
    int getPlayer2Suit();
    void setCardSelectPlayer(int x);
    void setCardSelectEnemy(int x);
    int getCardSelectEnemy();
    int getCardSelectPlayer();
    //costume
    void addImage(int x,int y);

private:
    int Cards[52];
    int Suits[52];
    int Deck1Card[52];
    int Deck2Card[52];
    int Deck1Suit[52];
    int Deck2Suit[52];
    int CardSelect = 0;
    int CardSelectPlayer = 0;
    int CardSelectEnemy = 0;
};

#endif // CARD_H
