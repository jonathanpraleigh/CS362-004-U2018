/************************************************************************************
* Author: Jon Raleigh
* Class: CS362
* Date: 8/5/18
* Description: Random test generator for Smithy card.
************************************************************************************/
#include "randomtest.h"
#include "dominion_helpers.h"
#include "dominion.h"
#include <stdio.h>

int main()
{
	for (runs = 0; runs < TESTS_TO_RUN; runs++)
	{
		struct gameState state;
		struct gameState preTestState;

		stateInit(&state, remodel);
		currentplayer = returnRandom(1, state.numPlayers);

		preTestState = state;

		smithyEffect(&state, currentplayer, state.handCount[currentplayer] - 1);

		printf("Smithy Card test run # %d.\n", runs);

		//Smithy increases the hand size by 3, but then discards the smithy, netting 2. 

		if (compareHand(&state, &preTestState, currentplayer) != 2)
		{
			printf("Difference of %d total cards in hand between pre and post test states. 2 required. Test failed.\n", compareHand(&state, &preTestState, currentplayer));
		}

		//Smithy increases the discard pile by 1. 

		if (compareDiscard(&state, &preTestState, currentplayer) != 1)
		{
			printf("Difference of %d cards in discard between pre and post test states. 1 required. Test failed.\n", compareDiscard(&state, &preTestState, currentplayer));
		}


		if (compareTotalCards(&preTestState, &state, currentplayer) != 0)
		{
			printf("Differnce of %d cards total cards in play between pre and post test states. Expected 0. Test failed.\n", compareTotalCards(&preTestState, &state, currentplayer));
		}

		// Testing to make sure all cards in play are valid cards. Testing to make sure that any possible memory errors are caught. 

		if (isValidCard(&state, currentplayer) == -1)
		{
			printf("Invalid card detected in play. Test failed.\n");
		}
	}
}
