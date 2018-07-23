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

	state.hand[currentPlayer][0] = remodel;

	originalState = state; //copies original state of game for comparison purposes in testing.

	cardEffect(remodel, choice1, choice2, choice3, &state, handPos, &bonus);

	/*	test that hand size is the same.
		test that new card is worth < +2 than top card on played card pile
		test that 2nd card in played card pile is remodel card. 
		test that player 2 has same hand and played card number.
		test victory and kingdom card pile size.
	*/

	if (state.handCount[currentPlayer] != originalState.handCount[currentPlayer] -1) failIfZero = 0;
	//if (getCost(state.hand[0][state.handCount[0] - 1]) > getCost(state.playedCards[state.playedCardCount - 1]) + 2) failIfZero = 0;
	//remove above line because trashed card does not is not stored in the current code, so nothing to compare to.
	if (state.playedCards[state.playedCardCount - 1] != remodel)
	{
		failIfZero = 0;
		printf("\nExpected top card to be Remodel. Was not.\n");
	}
	if (state.deckCount[1] != originalState.deckCount[1] || state.handCount[1] != originalState.handCount[1]) failIfZero = 0;
	for (i = 1; i <7; i++)
	{
		if (state.supplyCount[i] != originalState.supplyCount[i])
		{
			failIfZero = 0;
			printf("\nExpected supply count to be the same. Was not.\n");
		}
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