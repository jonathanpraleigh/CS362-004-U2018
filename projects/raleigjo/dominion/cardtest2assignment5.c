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

	state.hand[currentPlayer][0] = adventurer; //sets first card to Adventurer for test purposes.

	originalState = state; //copies original state of game for comparison purposes in testing.

	cardEffect(adventurer, choice1, choice2, choice3, &state, handPos, &bonus);

	/*	test that currentplayer has 2 more treasure cards than before.
	 *	test that the top two cards of player's hand are treasure -- since we're testing from a fresh state, this will be the case. In later gameplay, it is possible that the player will only have one treasure per the Dominion wiki.
		test that current hand + pile + discard = original hand + pile + discard.
		test that player 2 has same hand and pile and discard card number.
		test victory and kingdom card pile size.
	*/

	if (state.handCount[currentPlayer] != originalState.handCount[currentPlayer] + 2) 
	{
		failIfZero = 0;
		printf("\nExpected handcount to be 2 higher\n");
	}
	
	if (state.hand[currentPlayer][state.handCount[currentPlayer] - 1] > 6 || state.hand[currentPlayer][state.handCount[currentPlayer] - 1] < 4) 
	{
		failIfZero = 0;
		printf("\nExpected a treasure to be in discard.\n");
	}
	if (state.hand[currentPlayer][state.handCount[currentPlayer] - 2] > 6 || state.hand[currentPlayer][state.handCount[currentPlayer] - 2] < 4) 
	{
		failIfZero = 0;
		printf("\nExpected a treasure to be in discard.\n");
	} 
	if (state.handCount[currentPlayer] + state.deckCount[currentPlayer] + state.discardCount[currentPlayer] != originalState.handCount[currentPlayer] + originalState.deckCount[currentPlayer] + originalState.discardCount[currentPlayer]) 
	{
		failIfZero = 0;
		printf("\nExpected total cards in play to match.\n");
	}
	if (state.deckCount[1] != originalState.deckCount[1] || state.handCount[1] != originalState.handCount[1]) 
	{
		failIfZero = 0;
		printf("\nExpected deck and hand counts to match original state.");
	}
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
