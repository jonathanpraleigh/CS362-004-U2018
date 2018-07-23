#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>

int main()
{
	int numPlayers = 2;
	int kingdomCards[10] = { adventurer, smithy, embargo, sea_hag, cutpurse, remodel, salvager, mine, baron, tribute };
	int randomSeed = 250;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int handPos = 0;
	int bonus = 0;
	int currentPlayer = 0;
	int i;
	int failIfZero = 1;
	struct gameState state;
	struct gameState originalState;

	initializeGame(numPlayers, kingdomCards, randomSeed, &state);

	state.hand[currentPlayer][0] = cutpurse; // sets first card to Cutpurse for testing purposes.

	originalState = state; //copies original state of game for comparison purposes in testing.

	cardEffect(cutpurse, choice1, choice2, choice3, &state, handPos, &bonus);

/*
 * test player 1's hand is plus 2 coins. state.coins
 * test top of player 2's discard (handsize -1) for copper.
 *		if yes, test player 2's hand to make sure -1 size.
 *			if not, fail.
 *		if not, test player 2's hand for copper.
 *			if yes, fail.
 *	test top of player 1's discard pile (handize -1) for cutpurse.
 *		if not, fail.
 *	test player 1's handsize is -1.
 */


	if (state.coins != originalState.coins + 2)
	{
		failIfZero = 0;
		printf("\nExpected coins %d. Coin amount %d", originalState.coins + 2, state.coins);
	}
	
	if (state.discard[1][state.discardCount[1] -1] == copper)
	{
		if (state.handCount[1] != originalState.handCount[1] - 1)
		{
			failIfZero = 0;
			printf("\nExpected hand count %d. Hand count %d\n", originalState.handCount[1] - 1, state.handCount[1]);
		}

	}
	else
	{
		for (i=0; i < state.handCount[1]; i++)
		{
			if (state.hand[1][i] == copper)
			{
				failIfZero = 0;
				printf("\nExpected no copper. Found copper.\n");
			}
		}
	}
	if (state.playedCards[state.playedCardCount - 1] != cutpurse)
	{
		failIfZero = 0;
		printf("\nExpected to find cut purse in played card pile. Did not.\n");
	}
	if (state.handCount[0] != originalState.handCount[0] - 1)
	{
		failIfZero = 0;
		printf("\nExpected hand count to be one less than original hand count.\n");
	}
	
	if (state.deckCount[1] != originalState.deckCount[1] || state.handCount[1] != originalState.handCount[1]) failIfZero = 0;
	for (i = 1; i <7; i++)
	{
		if (state.supplyCount[i] != originalState.supplyCount[i]) failIfZero = 0;
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