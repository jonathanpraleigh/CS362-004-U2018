#ifndef RANDOMTEST_H
#define RANDOMTEST_H

#define TESTS_TO_RUN 20
#include "dominion.h"
#include "dominion_helpers.h"

int playerCount;
int randSeed;
int i;
int j;
int cardSelected;
int cardChosen;
int cardOptions[20];
int actionsCards[10];
int currentplayer; 
int cardCountDifference;
int handChoice;
int runs;


int stateInit(struct gameState*, int);
int returnRandom(int, int);
int compareHand(struct gameState*, struct gameState*, int);
int compareDeck(struct gameState*, struct gameState*, int);
int compareDiscard(struct gameState*, struct gameState*, int);
int compareTotalCards(struct gameState*, struct gameState*, int);
int isValidCard(struct gameState*, int);

#endif
