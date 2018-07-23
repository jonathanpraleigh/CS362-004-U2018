#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>

int main()
{
	int numPlayers = 2;
	int kingdomCards[10] = { adventurer, smithy, embargo, sea_hag, cutpurse, remodel, salvager, mine, baron, tribute };
	int randomSeed = 250;
	int currentPlayer = 0;
	int failIfZero = 1;
	int result; 
	struct gameState state;
	struct gameState originalState;

	initializeGame(numPlayers, kingdomCards, randomSeed, &state);

	originalState = state; //copies original state of game for comparison purposes in testing.

	//test for empty. set curse card count to 0. 
	
	state.supplyCount[curse] = 0;
	result = gainCard(curse, &state, 0, currentPlayer);

	if (result != -1) failIfZero = 0;

	//test for flag 1, deckcount. 
		//test deckcount minus one for card.
		//test deck size
		//test deck size of other player.

	//resetting original state.

	state = originalState;

	gainCard(copper, &state, 1, 0);
	
	if (state.deck[currentPlayer][state.deckCount[currentPlayer] - 1] != copper) failIfZero = 0;
	if (state.deckCount[0] != originalState.deckCount[0] + 1) failIfZero = 0;
	if (state.deckCount[1] != originalState.deckCount[1]) failIfZero = 0;
	if (state.supplyCount[copper] >= originalState.supplyCount[copper]) failIfZero = 0;
	
	//test for flag 2
		//test handcount minus one for card.
		//test hand size
		//test hand size of other player.

	state = originalState;

	gainCard(copper, &state, 2, 0);

	if (state.hand[currentPlayer][state.handCount[currentPlayer] - 1] != copper) failIfZero = 0;
	if (state.handCount[0] != originalState.handCount[0] + 1) failIfZero = 0;
	if (state.handCount[1] != originalState.handCount[1]) failIfZero = 0;
	if (state.supplyCount[copper] >= originalState.supplyCount[copper]) failIfZero = 0;
	
	//test for flag 0
		//test discard minus one for card.
		//test discard pile size
		//test discard pile size of other player. 

	state = originalState;

	gainCard(copper, &state, 0, 0);

	if (state.discard[currentPlayer][state.discardCount[currentPlayer] - 1] != copper) failIfZero = 0;
	if (state.discardCount[0] != originalState.discardCount[0] + 1) failIfZero = 0;
	if (state.discardCount[1] != originalState.discardCount[1]) failIfZero = 0;
	if (state.supplyCount[copper] >= originalState.supplyCount[copper]) failIfZero = 0;

	//error messaging.
	
	if (failIfZero == 0)
	{
		printf("\nTEST FAILED.\n");
	}
	else
	{
		printf("\nTEST SUCCESSFULLY COMPLETED.\n");
	}
}