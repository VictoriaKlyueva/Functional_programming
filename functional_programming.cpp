#include <iostream>
#include <vector>
using namespace std;


struct Card {
  int quantity;
  int type;
  int color;
  int filling;
};

struct Answer {
  int numberOfSets;
  vector<vector<int>> SETs;

  Answer(int receivedNumber, vector<vector<int>> receivedSETs) {
    numberOfSets = receivedNumber;
    SETs = receivedSETs;
  }
};

bool isEqualCards(Card card1, Card card2, Card card3) {
  return card1.quantity == card2.quantity && card1.quantity == card3.quantity
      && card1.type == card2.type && card1.type == card3.type
      && card1.color == card2.color && card1.color == card3.color
      && card1.filling == card2.filling && card1.filling == card3.filling;
}

bool isSET(Card card1, Card card2, Card card3) {
  return !isEqualCards(card1, card2, card3)
      && ((card1.quantity == card2.quantity && card2.quantity == card3.quantity) 
       || (card1.quantity != card2.quantity && card2.quantity != card3.quantity))
      && ((card1.type == card2.type && card2.type == card3.type)
       || (card1.type != card2.type && card2.type != card3.type))
      && ((card1.color == card2.color && card2.color == card3.color)
       || (card1.color != card2.color && card2.color != card3.color))
      && ((card1.filling == card2.filling && card2.filling == card3.filling)
       || (card1.filling != card2.filling && card2.filling != card3.filling));
}

Answer SETGame(vector<Card> cards, 
               vector<vector<int>> SETs=vector<vector<int>>(220, vector<int>()), 
               int currentIndex=0, int i=0, int j=1, int k=2) {
  vector<vector<int>> newSETs = SETs;
  bool found = 0;
  
  if (isSET(cards[i], cards[j], cards[k])) {
    newSETs[currentIndex] = {i + 1, j + 1, k + 1};
    found = 1;
  }
  
  return 
  i == 9 ?
    j == 10 ? 
      k == 11 ?
        Answer(currentIndex, newSETs) :
      SETGame(cards, SETs, currentIndex + found, i, j, k + 1) : 
    SETGame(cards, SETs, currentIndex + found, i, j + 1, j + 2) : 
  SETGame(cards, SETs, currentIndex + found, i + 1, i + 2, i + 3);
}

Card readCard() {
  Card card;
  cin >> card.quantity  >> card.type >> card.color >> card.filling;
  return card;
}

vector<Card> getCards(vector<Card> cards=vector<Card>(12), int i=0) {
  if (i == 12) return cards;
  cards[i] = readCard();
  return getCards(cards, i + 1); 
}

void printSET(vector<int> SET) {
  cout << SET[0] << " " << SET[1] << " " << SET[2] << endl;
}

void printSETs(Answer answer, int currentIndex=0) {
  if (currentIndex == answer.numberOfSets) return;
  printSET(answer.SETs[currentIndex]);
  printSETs(answer, currentIndex + 1);
}

int main() {
  printSETs(SETGame(getCards()));
}