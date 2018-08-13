#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>

// This program tests the Smithy card via the cardEffect function in dominion.c

int main()
{
	int numPlayers = 2;
	int kingdomCards[10] = { adventurer, smithy, embargo, sea_hag, cutpurse, remodel, salvager, mine, baron, tribute };
	int randomSeed = 250;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int bonus = 0;
	int currentPlayer = 0;
	int failIfZero = 1;
	int i;
	struct gameState state;
	struct gameState originalState;

	initializeGame(numPlayers, kingdomCards, randomSeed, &state); //using dominion.c function to initialize random game.

	state.hand[currentPlayer][0] = smithy; //sets first card to Smithy for test purposes.

	originalState = state; //copies original state of game for comparison purposes in testing.

	cardEffect(smithy, choice1, choice2, choice3, &state, 0, &bonus);
	
	/*	Test that currentplayer hand has 2 more cards (+3 new cards -1 smithy card). 
		test that currentplayer deck has 2 fewer cards.
		test that player 2 has same hand and pile card number.
		test victory and kingdom card pile size.
	*/

	if (state.handCount[currentPlayer] != originalState.handCount[currentPlayer] + 2)
	{
		failIfZero = 0; 
		printf("\nExpected the hand to be 2 cards larger. Was not.\n");
	}
	if (state.deckCount[currentPlayer] != originalState.deckCount[currentPlayer] - 3) 
	{
		failIfZero = 0;
		printf("\nExpected the deck count to be 3 cards lower. Was not.\n");
	}
	if (state.discardCount[currentPlayer] != originalState.discardCount[currentPlayer] + 1) failIfZero = 0;
	if (state.deckCount[1] != originalState.deckCount[1] || state.handCount[1] != originalState.handCount[1]) failIfZero = 0;
	for (i=1; i <7; i++)
	{
		if (state.supplyCount[i] != originalState.supplyCount[i]) failIfZero = 0;
	}
	
	if (state.discard[currentPlayer][state.discardCount[currentPlayer]-1] != smithy)
	{	
		printf("\nExpected top card of discard to be Smithy. Was not.\n");
		failIfZero = 0; //This section added 8/12/18 for Assignment 5 to look at discarded cards.
	}

	if (failIfZero == 0)
	{
		printf("\nTEST FAILED.\n");
	}
	else
	{
		printf("\nTEST SUCCESSFULLY COMPLETED.\n");
	}

}
