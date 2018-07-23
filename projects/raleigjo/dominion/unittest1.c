#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>

int main()
{
	int numPlayers = 2;
	int kingdomCards[10] = { adventurer, smithy, embargo, sea_hag, cutpurse, remodel, salvager, mine, baron, tribute };
	int randomSeed = 250;
	int currentPlayer = 0;
	int i;
	int failIfZero = 1;
	int count;
	struct gameState state;
	struct gameState originalState;

	initializeGame(numPlayers, kingdomCards, randomSeed, &state);

	originalState = state;

	//testing with count of 0. 
	//using village since not included in the kingdom cards declaration above.

	count = fullDeckCount(currentPlayer, village, &state);
	if (count != 0) failIfZero = 0;

	//testing with count of 1
	//resetting state to original state
	//adding village to hand position 0.

	state = originalState;
	state.hand[currentPlayer][0] = village;

	count = fullDeckCount(currentPlayer, village, &state);
	if (count != 1) failIfZero = 0;

	//testing with full hand of villages.
	//adding village to all hand positions.

	state = originalState;

	for (i=0; i < state.handCount[currentPlayer]; i++)
	{
		state.hand[currentPlayer][i] = village;
	}

	count = fullDeckCount(currentPlayer, village, &state);
	if (count != state.handCount[currentPlayer]) failIfZero = 0;
	
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