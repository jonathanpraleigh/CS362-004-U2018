/************************************************************************************
* Author: Jon Raleigh
* Class: CS362
* Date: 8/5/18
* Description: Random test generator for Adventurer card.
************************************************************************************/

#include "randomtest.h"
#include "dominion_helpers.h"
#include <stdio.h>

int main()
{
	for (runs = 0; runs < TESTS_TO_RUN; runs++)
	{
		struct gameState state;
		struct gameState preTestState;

		stateInit(&state, adventurer);
		currentplayer = returnRandom(1, state.numPlayers);

		preTestState = state;

		adventurerEffect(&state, currentplayer);

		printf("Adventure Card test run # %d.\n", runs);

		// Adventurer does not change the total number of cards, but shifts cards prior to the next two treasures to the discard pile. 
		// The total number of cards will remain unchanged. This text print

		if (compareTotalCards(&preTestState, &state, currentplayer) != 0)
		{
			printf("Differnce of %d cards between pre and post test states. Test failed.\n", compareTotalCards(&preTestState, &state, currentplayer));
		}

		//Adventurer does not call discardCard, so we are expecting the hand to include two additional treasure cards.  

		if (compareHand(&state, &preTestState, currentplayer) != 2)
		{
			printf("Differnce of %d cards between pre and post test states. 2 required. Test failed.\n", compareTotalCards(&state, &preTestState, currentplayer));
		}

		// Testing to make sure all cards in play are valid cards. Testing to make sure that any possible memory errors are caught. 

		if (isValidCard(&state, currentplayer) == -1)
		{
			printf("Invalid card detected in play. Test failed.\n");
		}

		// Did not modularize this test because it only applies to the this particular card. Testing for 2 treasure cards on the top of the player's hand.

		for (i = 1; i < 3; i++)
		{
			if (state.hand[currentplayer][state.handCount[currentplayer] - i] < 4 || state.hand[currentplayer][state.handCount[currentplayer] - i] > 6)
			{
				printf("Non-treasure card detected at top of the hand. %d in the enum table. Test failed.\n", state.hand[currentplayer][state.handCount[currentplayer] - i]);
			}
		}

	}
}
