/************************************************************************************
 * Author: Jon Raleigh
 * Class: CS362
 * Date: 8/5/18
 * Description: Random test generator for Salvager card.
 ************************************************************************************/
#include "randomtest.h"
#include "dominion_helpers.h"
#include "dominion.h"
#include <stdio.h>

int main()
{
	for (runs = 0; runs < 20; runs++)
	{
		struct gameState state;
		struct gameState preTestState;

		stateInit(&state, salvager);
		if (state.numPlayers < 2) state.numPlayers = 2;
		currentplayer = returnRandom(1, state.numPlayers);

		preTestState = state;

		handChoice = returnRandom(1, state.handCount[currentplayer] - 1);

		salvagerEffect(&state, handChoice, currentplayer, state.handCount[currentplayer] - 1);

		printf("Salvager Card test run # %d\n", runs);

		// Test for an increase in the number of buys. Did not modularize due to this being specific to the salvager card.

		if (preTestState.numBuys >= state.numBuys)
		{
			printf("The Buys number was not increased. Test failed.\n");
		}

		// Test for an increase in coins. Did not modularize due to this being specific to the salvager card. 

		if (preTestState.coins >= state.coins)
		{
			printf("Coins count did not increase. Test failed.\n");
		}

		// Tests to make sure total cards in play for player is the same, as one card is purchased, one is discarded to the discard deck
		// and one is trashed. 

		if (compareHand(&state, &preTestState, currentplayer) != 0)
		{
			printf("Differnce of %d cards between pre and post test states. 0 required. Test failed.\n", compareTotalCards(&state, &preTestState, currentplayer));
		}

		// Testing to make sure all cards in play are valid cards. Testing to make sure that any possible memory errors are caught. 

		if (isValidCard(&state, currentplayer) == -1)
		{
			printf("Invalid card detected in play. Test failed.\n");
		}
	}
}
