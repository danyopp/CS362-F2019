#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int assert(int expected, int testval , char* string)
{
	if(expected==testval)
	{return 0;}
	else if(expected > testval)
	{printf("ASSERT FAILED: (%d-expected)(%d-value present) for %s\n", expected, testval, string);} 
	else if(expected < testval)
	{printf("ASSERT FAILED: (%d-expected)(%d-value present) for %s\n", expected, testval, string);} 
	return 1;
}

int falseAssert(int NotExpected, int testval , char* string)
{
	if(NotExpected!=testval)
	{return 0;}
	else 	{printf("FALSE-ASSERT FAILED: (%d-NotAllowed ) and (%d-value present) for %s\n", NotExpected, testval, string);} 
	return 1;
}


int printGameState(struct gameState G)
{
printf("numPlayers: %d\n", G.numPlayers);
printf("Whose turn: %d\n", G.whoseTurn);
printf("Number of buys: %d\n", G.numBuys);
printf("Number of coins: %d\n", G.coins);
printf("Number of actions: %d\n", G.numActions);
printf("Current player Handcount: %d\n", G.handCount[G.whoseTurn]);
printf("Current player DeckCount: %d\n", G.deckCount[G.whoseTurn]);
printf("Current player Discard Count: %d\n", G.discardCount[G.whoseTurn]);
printf("Current player Cards in hand: ");
int a = 0;
for(a=0; a < G.handCount[G.whoseTurn]; a++)
	{
	printf("%d ", G.hand[G.whoseTurn][a]);
	}
printf("\n");
printf("Current player Cards in deck: ");
for(a=0; a < G.deckCount[G.whoseTurn]; a++)
	{
	printf("%d ", G.deck[G.whoseTurn][a]);
	}
printf("\n");
printf("Current player Cards in discard ");
for(a=0; a < G.discardCount[G.whoseTurn]; a++)
	{
	printf("%d ", G.discard[G.whoseTurn][a]);
	}
printf("\n");
printf("Next player Cards in hand: ");
for(a=0; a < G.handCount[G.whoseTurn+1]; a++)
	{
	printf("%d ", G.hand[G.whoseTurn+1][a]);
	}
printf("\n");

printf("Next player Cards in deck: ");
for(a=0; a < G.deckCount[G.whoseTurn+1]; a++)
	{
	printf("%d ", G.deck[G.whoseTurn+1][a]);
	}
printf("\n");
printf("Next player Cards in discard ");
for(a=0; a < G.discardCount[G.whoseTurn+1]; a++)
	{
	printf("%d ", G.discard[G.whoseTurn+1][a]);
	}
printf("\n");
printf("Last player Cards in hand: ");
for(a=0; a < G.handCount[G.whoseTurn+2]; a++)
	{
	printf("%d ", G.hand[G.whoseTurn+2][a]);
	}
printf("\n");

printf("Last player Cards in deck: ");
for(a=0; a < G.deckCount[G.whoseTurn+2]; a++)
	{
	printf("%d ", G.deck[G.whoseTurn+2][a]);
	}
printf("\n");
printf("Last player Cards in discard ");
for(a=0; a < G.discardCount[G.whoseTurn+2]; a++)
	{
	printf("%d ", G.discard[G.whoseTurn+2][a]);
	}
printf("\n");

printf("Card numbers in supply ");

for(a=0; a < 26; a++)
	{
	printf("%d ", G.supplyCount[a]);
	}
printf("\n");

return 0;
}




//Declare Gamestate
int main()
{
int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

struct gameState G;
struct gameState preG;

unsigned seed;
seed = time(0);
srand(seed);

//int coppers[MAX_HAND];
//int silvers[MAX_HAND];
//int golds[MAX_HAND];

//////////////////////////////////////////////////
//Begin test 1
// Try to upgrade a smithy to gold
//////////////////////////////////////////////////
memset(&G, 23, sizeof(struct gameState)); 
memset(&G, 23, sizeof(struct gameState)); 
int r = initializeGame(3, k, seed, &G);
assert(0,r,"initialize Game");

//make testing changes to gamestate
G.hand[G.whoseTurn][0] = 11; //mine added to deck 
G.hand[G.whoseTurn][1] = 13; //smithy added to deck 

//copy inital gamestate
memcpy(&preG, &G, sizeof(G));
int returnVal;

returnVal = mineEffect(1, 6, &G, 0, G.whoseTurn);

//printGameState(preG);
//printGameState(G);

//Test results for expected outcome
printf("TEST 1 RESULTS: upgrade a smithy to gold\n");
assert( 0, returnVal, "Return Value" );
assert( 13, G.hand[0][1], "smithy still in hand");


////////////////////////////////////////////////// 
//Test 2 - 
// trade a silver for gold 
////////////////////////////////////////////////////
memset(&G, 23, sizeof(struct gameState)); 
memset(&G, 23, sizeof(struct gameState)); 
r = initializeGame(3, k, seed, &G);
assert(0,r,"initialize Game");

//make testing changes to gamestate
G.hand[G.whoseTurn][0] = 11; //mine added to deck 
G.hand[G.whoseTurn][1] = 5; //silver added to deck 

//copy inital gamestate
memcpy(&preG, &G, sizeof(G));

returnVal = mineEffect(1, 6, &G, 0, G.whoseTurn);

//printGameState(preG);
//printGameState(G);

//Test results for expected outcome
printf("TEST 2 RESULTS: upgrade a smithy to gold\n");
assert( 0, returnVal, "Return Value" );
assert( 4, G.hand[0][0], "gold in hand");

////////////////////////////////////////////////
//Test 3 - 
// trade for a copper to council room
////////////////////////////////////////////////
memset(&G, 23, sizeof(struct gameState)); 
memset(&G, 23, sizeof(struct gameState)); 
r = initializeGame(3, k, seed, &G);
assert(0,r,"initialize Game");

//make testing changes to gamestate
G.hand[G.whoseTurn][0] = 11; //mine added to deck 
G.hand[G.whoseTurn][1] = 4; //silver added to deck 

//copy inital gamestate
memcpy(&preG, &G, sizeof(G));

returnVal = mineEffect(1, 8, &G, 0, G.whoseTurn); //councilroom requested

//printGameState(preG);
//printGameState(G);

//Test results for expected outcome
printf("TEST 3 RESULTS: upgrade a smithy to gold\n");
assert( -2, returnVal, "Return Value" );
assert( 8, G.hand[0][0], "councilroom in hand");
return 0;
}
