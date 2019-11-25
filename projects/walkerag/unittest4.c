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
// Nextplayer only has one card in deck
// No cards in discard pile
// card in deck is feast
//////////////////////////////////////////////////
memset(&G, 23, sizeof(struct gameState)); 
memset(&G, 23, sizeof(struct gameState)); 
int r = initializeGame(3, k, seed, &G);
assert(0,r,"initialize Game");

//make testing changes to gamestate
G.deck[G.whoseTurn+1][0] = 9; //feast added to deck count action card
G.deckCount[G.whoseTurn+1] = 1; //deckcount dropped to one card

//copy inital gamestate
memcpy(&preG, &G, sizeof(G));
int returnVal;
int array[2];


//returnVal = tributeEffect(&G, G.whoseTurn+1, G.whoseTurn);
returnVal = cardTribute(G.whoseTurn, G.whoseTurn+1, array, &G, 0, 0, 0);
//printGameState(preG);
//printGameState(G);

//Test results for expected outcome
printf("TEST 1 RESULTS: Next player has 1 feast in deck\n");
assert( 0, returnVal, "Return Value" );
assert( preG.handCount[0], G.handCount[0], "number of cards in players hand");
assert( preG.coins, G.coins, "number of coins");
assert( preG.numActions+2, G.numActions, "number of actions");
 

////////////////////////////////////////////////// 
//Test 2 - 
// Next player only has one card between deck and discard
// it is village in discard pile
////////////////////////////////////////////////////
memset(&G, 23, sizeof(struct gameState)); 
memset(&G, 23, sizeof(struct gameState)); 
r = initializeGame(3, k, seed, &G);
assert(0,r,"initialize Game");

//make testing changes to gamestate
G.discard[G.whoseTurn+1][0] = 14 ; //village added to deck count action card
G.discardCount[G.whoseTurn+1] = 1;
G.deckCount[G.whoseTurn+1] = 0; //deckcount dropped to one card

//copy inital gamestate
memcpy(&preG, &G, sizeof(G));

//returnVal = tributeEffect(&G, G.whoseTurn+1, G.whoseTurn);
returnVal = cardTribute(G.whoseTurn, G.whoseTurn+1, array, &G, 0, 0, 0);

//printGameState(preG);
//printGameState(G);

//Test results for expected outcome
printf("TEST 2 RESULTS: Next player has 1 village in discard pile\n");
assert( 0, returnVal, "Return Value" );
assert( preG.handCount[0], G.handCount[0], "number of cards in players hand");
assert( preG.coins, G.coins, "number of coins");
assert( preG.numActions+2, G.numActions, "number of actions");
 

/////////////////////////////////////////////////
//Test 3 - 
// 2 cards in discard pile of next player
// the cards are both action cards (baron)
////////////////////////////////////////////////
memset(&G, 23, sizeof(struct gameState)); 
memset(&G, 23, sizeof(struct gameState)); 
r = initializeGame(3, k, seed, &G);
assert(0,r,"initialize Game");

//make testing changes to gamestate
G.discard[G.whoseTurn+1][0] = 15 ; //village added to deck count action card
G.discard[G.whoseTurn+1][1] = 15 ;
G.discardCount[G.whoseTurn+1] = 2;
G.deckCount[G.whoseTurn+1] = 0; //deckcount dropped to one card

//copy inital gamestate
memcpy(&preG, &G, sizeof(G));

//returnVal = tributeEffect(&G, G.whoseTurn+1, G.whoseTurn);
returnVal = cardTribute(G.whoseTurn, G.whoseTurn+1, array, &G, 0, 0, 0);

//printGameState(preG);
//printGameState(G);

//Test results for expected outcome
printf("TEST 3 RESULTS: Next player has 2 barons in discard pile\n");
assert( 0, returnVal, "Return Value" );
assert( preG.handCount[0], G.handCount[0], "number of cards in players hand");
assert( preG.coins, G.coins, "number of coins");
assert( preG.numActions+2, G.numActions, "number of actions");
 
return 0;
}
