#include "randomtest.h"
#include "dominion.h"
#include <time.h>
#include "dominion_helpers.h"
#include <stdlib.h>

// Random # generator. Nothing special. 

int returnRandom(int low, int high)
{
	srand(time(NULL));

	int randValue = 0;

	randValue = rand() % (high + 1 - low) + low;

	return randValue;
}

/**********************************************************************************************
 * Function Name: compareHand
 * Input: gameState struct s & t, current player #.
 * Output: Integer difference between hand count in different test states.
 * Description: Subtracts one hand count from another and returns difference.
 **********************************************************************************************/

int compareHand(struct gameState* s, struct gameState* t, int player)
{
	return s->handCount[player] - t->handCount[player];
}

/**********************************************************************************************
* Function Name: compareDeck
* Input: gameState struct s & t, current player #.
* Output: Integer difference between deck count in different test states.
* Description: Subtracts one deck count from another and returns difference.
**********************************************************************************************/
int compareDeck(struct gameState* s, struct gameState* t, int player)
{
	return s->deckCount[player] - t->deckCount[player];
}

/**********************************************************************************************
* Function Name: compareDiscard
* Input: gameState struct s & t, current player #.
* Output: Integer difference between discard count in different test states.
* Description: Subtracts one discard pile count from another and returns the difference.
**********************************************************************************************/
int compareDiscard(struct gameState* s, struct gameState* t, int player)
{
	return s->discardCount[player] - t->discardCount[player];
}

/**********************************************************************************************
* Function Name: compareTotalCards
* Input: gameState struct s & t, current player #.
* Output: Integer difference between total card count in pre and post test states.
* Description: 
**********************************************************************************************/
int compareTotalCards(struct gameState* s, struct gameState* t, int player)
{
	return s->handCount[player] + s->deckCount[player] + s->discardCount[player] - (t->handCount[player] + t->deckCount[player] + t->discardCount[player]);
}

/**********************************************************************************************
* Function Name: isValidCard
* Input: gameState struct s, current player #.
* Output: 0 on success. -1 on failure.
* Description: Tests the card arrays to make sure all cards present are valid.
**********************************************************************************************/
int isValidCard(struct gameState* s, int player)
{
	for (i = 0; i < s->discardCount[player]; i++)
	{
		if (s->discard[player][i] < 0 || s->discard[player][i] > 26)
		{
			return -1;
		}
	}

	for (i = 0; i < s->handCount[player]; i++)
	{
		if (s->hand[player][i] < 0 || s->hand[player][i] > 26)
		{
			return -1;
		}
	}

	for (i = 0; i < s->deckCount[player]; i++)
	{
		if (s->deck[player][i] < 0 || s->deck[player][i] > 26)
		{
			return -1;
		}
	}

	return 0;
}

/**********************************************************************************************
* Function Name: stateInit
* Input: gameState struct s & t, card # that we're tesing.
* Output: 0. Left non-void for possible specific error return.
* Description: Initializes gameState struct with random values. 
**********************************************************************************************/
int stateInit(struct gameState * x, int cardTested)
{
	playerCount = returnRandom(2, 4); // random player number.
	randSeed = returnRandom(0, 1000); //random # to seed initialize game.
	//struct gameState emptyState; //empty gamestate.
	
	int cardNumber = 7;

	for (i = 0; i < 20; i++) {
		
		cardOptions[i] = cardNumber;
		cardNumber++;
	}
								 //following randomly populates 
	for (i = 0; i <26; i++)
	{
		if (cardOptions[i] == cardTested)
		{
			cardOptions[i] = 0;
		}
	}

	cardOptions[0] = cardTested;

	for (i = 1; i < 10; i++)
	{
		cardChosen = 0;

		while (cardChosen == 0)
		{
			cardSelected = returnRandom(7, 26);
			if (cardOptions[cardSelected] != 0)
			{
				cardChosen = cardSelected;
				actionsCards[i] = cardChosen;
				cardOptions[cardSelected] = 0;
			}
		}

	}

	initializeGame(playerCount, cardOptions, randSeed, x);

	for (i = 1; i <= playerCount; i++)
	{
		for (j = 0; j < 4; j++)
		{
			drawCard(i, x);
		}

		gainCard(cardTested, x, 2, i);
	}
	return 0;
}
