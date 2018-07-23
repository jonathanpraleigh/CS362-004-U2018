#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>

int main()
{
	int numPlayers = 2;
	int kingdomCards[10] = { adventurer, smithy, embargo, sea_hag, cutpurse, remodel, salvager, mine, baron, tribute };
	int randomSeed = 250;
	int i;
	int failIfZero = 1;
	int gameOverState;
	struct gameState state;
	struct gameState originalState;

	initializeGame(numPlayers, kingdomCards, randomSeed, &state);

	originalState = state;

	//testing two states. Game over and game not over.

	//game not over state
	//using original initialized game, so by definition will not be over.

	gameOverState = isGameOver(&state);
	if (gameOverState == 1) failIfZero = 0;

	//not resetting to original state due to no change in state from isGameOver function.

	//testing province card game over state. Changing supply count of province to 0

	state.supplyCount[province] = 0;

	gameOverState = isGameOver(&state);
	if (gameOverState != 1) failIfZero = 0;

	//resetting original state
	//setting the supply count of the first two piles to 0 and testing.

	state = originalState;

	for (i=0; i<2; i++)
	{
		state.supplyCount[i] = 0;
	}

	gameOverState = isGameOver(&state);
	if (gameOverState != 0) failIfZero = 0;

	//setting the supply count of the third pile to 0 and testing. 

	state.supplyCount[2] = 0;
	gameOverState = isGameOver(&state);
	if (gameOverState != 1) failIfZero = 0;

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