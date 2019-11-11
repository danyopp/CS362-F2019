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
// Ambassador 
// reveal card, return 3 copies to supply, everyone else gets one
// return value should kick back error 
/////////////////////////////////////////////////
memset(&G, 23, sizeof(struct gameState)); 
memset(&G, 23, sizeof(struct gameState)); 
int r = initializeGame(3, k, seed, &G);
assert(0,r,"initialize Game");

//make testing changes to gamestate
G.hand[G.whoseTurn][0] = 20; //add minion to hand
G.hand[G.whoseTurn][1] = 0; 
G.hand[G.whoseTurn][2] = 0; 
G.hand[G.whoseTurn][3] = 0; 
G.hand[G.whoseTurn][4] = 4; 


//copy inital gamestate
memcpy(&preG, &G, sizeof(G));
int returnVal;

returnVal = ambassadorEffect(G.whoseTurn, 0, 3, &G, 0);

//printGameState(preG);
//printGameState(G);

//Test results for expected outcome
printf("TEST 1 RESULTS: Discard 3 copies of curse from hand\n");
assert( -1, returnVal, "Return Value" );
assert( preG.supplyCount[0] , G.supplyCount[0] , "Number of curses in supply\n");
assert( preG.handCount[0], G.handCount[0], "number of cards in players hand");
assert( preG.handCount[1], G.handCount[1], "number of cards in players hand");
assert( preG.handCount[2], G.handCount[2], "number of cards in players hand");
 

////////////////////////////////////////////////// 
//Test 2 - 
//Don't have enough cards to return to supply
//////////////////////////////////////////////////



memset(&G, 23, sizeof(struct gameState)); 
memset(&G, 23, sizeof(struct gameState)); 
r = initializeGame(3, k, seed, &G);
assert(0,r,"initialize Game");

//make testing changes to gamestate
G.hand[G.whoseTurn][0] = 20; //add minion to hand
G.hand[G.whoseTurn][1] = 0; 
G.hand[G.whoseTurn][2] = 4; 
G.hand[G.whoseTurn][3] = 4; 
G.hand[G.whoseTurn][4] = 4; 


//copy inital gamestate
memcpy(&preG, &G, sizeof(G));
returnVal = ambassadorEffect(G.whoseTurn, 1, 2, &G, 0);

//printGameState(preG);
//printGameState(G);

//Test results for expected outcome
printf("TEST 2 RESULTS: Discard 2 copies of curse (only one curse in hand)\n");
assert( -1, returnVal, "Return Value" );
assert( preG.supplyCount[0] , G.supplyCount[0] , "Number of curses in supply\n");
assert( preG.handCount[0], G.handCount[0], "number of cards in players hand");
assert( preG.handCount[1], G.handCount[1], "number of cards in players hand");
assert( preG.handCount[2], G.handCount[2], "number of cards in players hand");
 


/////////////////////////////////////////////////
//Test 3 - 
//Return 1 curses to supply
////////////////////////////////////////////////



memset(&G, 23, sizeof(struct gameState)); 
memset(&G, 23, sizeof(struct gameState)); 
r = initializeGame(3, k, seed, &G);
assert(0,r,"initialize Game");

//make testing changes to gamestate
G.hand[G.whoseTurn][0] = 20; //add ambassador to hand
G.hand[G.whoseTurn][1] = 4; //copper
G.hand[G.whoseTurn][2] = 4; //copper
G.hand[G.whoseTurn][3] = 4; //copper
G.hand[G.whoseTurn][4] = 0; //curse


//copy inital gamestate
memcpy(&preG, &G, sizeof(G));
returnVal = ambassadorEffect(G.whoseTurn, 4, 1, &G, 0);

//printGameState(preG);
//printGameState(G);

//Test results for expected outcome
printf("TEST 3 RESULTS: Discard 1 copy of curse (only one curse in hand)\n");
assert( 0, returnVal, "Return Value" );
assert( preG.supplyCount[0] , G.supplyCount[0]+1 , "Number of curses in supply\n");
assert( preG.handCount[0]-1, G.handCount[0], "number of cards in players hand");
assert( preG.discardCount[1]+1, G.discardCount[1], "number of cards in players hand");
assert( preG.discardCount[2]+1, G.discardCount[2], "number of cards in players hand");
 

return 0;
}
