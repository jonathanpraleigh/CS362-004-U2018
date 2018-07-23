#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>

int main()
{
	int numPlayers = 2;
	int kingdomCards[10] = {adventurer, smithy, embargo, sea_hag, cutpurse, remodel, salvager, mine, baron, tribute};
	int randomSeed = 250;
	int handPos = 0;
	int currentPlayer = 0;
	int failIfZero = 1;
	struct gameState state;
	struct gameState originalState;

	initializeGame(numPlayers, kingdomCards, randomSeed, &state);

	originalState = state; //copies original state of game for comparison purposes in testing.

	//test trash flag 0

	discardCard(handPos, currentPlayer, &state, 0);

	if (state.playedCardCount <= originalState.playedCardCount)
	{
		failIfZero = 0;
		printf("\nExpected played card count to be higher than original played card count. Was not.\n");
	}

	//resetting to original state and testing trash flag 1. 

	state = originalState;

	// with trash flag 1, replacing village as last card in hand.

	state.hand[currentPlayer][state.handCount[currentPlayer] - 1] = village;

	handPos = state.handCount[currentPlayer] - 1;

	discardCard(handPos, currentPlayer, &state, 1);

	//test for presence in played pile

	if (state.playedCards[state.playedCardCount - 1] == village)
	{
		failIfZero = 0;
		printf("\nExpected last played card to be village. Was not.\n");
	}

	//testing for playedCardCount increase
	
	if (state.playedCardCount > originalState.playedCardCount)
	{
		failIfZero = 0;
		printf("\nExpected played card count to be higher. Was not\n");
	}

	//testing for village remaining as last card in hand.

	if (state.hand[currentPlayer][state.handCount[currentPlayer] - 1] == village)
	{
		failIfZero = 0;
		printf("\nExpected village to no longer be in hand. It was.\n");
	}

	//testing for handcount reduction.

	if (state.handCount[currentPlayer] >= originalState.handCount[currentPlayer])
	{
		failIfZero = 0;
		printf("\nExpected handcount to be lower. It was the same or higher.\n");
	}

	//resetting and testing village as first card in hand. 

	state = originalState;

	state.hand[currentPlayer][0] = village;

	discardCard(0, currentPlayer, &state, 1);

	//test hand size reduced

	if (state.handCount[currentPlayer] >= originalState.handCount[currentPlayer])
	{
		failIfZero = 0;
		printf("\nExpected the hand count to be lower. It was the same or higher.\n");
	}

	//test displaced card replaced with previously last card.

	if (state.hand[currentPlayer][0] != originalState.hand[currentPlayer][originalState.handCount[currentPlayer] -1])
	{
		failIfZero = 0;
		printf("\nExpected the first card of the hand to be the previous last card of the hand.\n");
	}

	//resetting to original state and setting up a hand of one card with only village. 

	state = originalState;

	state.handCount[currentPlayer] = 1;
	state.hand[currentPlayer][0] = village;

	discardCard(0, currentPlayer, &state, 1);

	if (state.handCount[currentPlayer] != 0) failIfZero = 0;

	//error messaging
	
	if (failIfZero == 0)
	{
		printf("\nTEST FAILED.\n");
	}
	else
	{
		printf("\nTEST SUCCESSFULLY COMPLETED.\n");
	}
}