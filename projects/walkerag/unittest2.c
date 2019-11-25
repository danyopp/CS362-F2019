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
//Minion chooses +2
//No changes to hands
/////////////////////////////////////////////////
memset(&G, 23, sizeof(struct gameState)); 
memset(&G, 23, sizeof(struct gameState)); 
int r = initializeGame(3, k, seed, &G);
assert(0,r,"initialize Game");

//make testing changes to gamestate
G.hand[G.whoseTurn][0] = 17; //add minion to hand

//copy inital gamestate
memcpy(&preG, &G, sizeof(G));

//currentPlayer state handpos
cardMinion(G.whoseTurn, &G, 0, 1, 0);
//minionEffect(1, 0, &G, 0, G.whoseTurn);

//printGameState(preG);
//printGameState(G);

//Test results for expected outcome
printf("TEST 1 RESULTS: play minion card, action +1/treasure +2, no change in hands\n");
assert( preG.coins+2 , G.coins , "Number of treasure\n");
assert( preG.numActions +1, G.numActions, "Number of actions\n");
int b;
for(b=0;b < 5;b++)
{
	assert(preG.handCount[0]-1, G.handCount[0], "Cards in player zero deck changed\n");
	assert(preG.deck[1][b], G.deck[1][b], "Cards in player one deck changed\n");
	assert(preG.deck[2][b], G.deck[2][b], "Cards in player two deck changed\n");
}

////////////////////////////////////////////////// 
//Test 2 - 
//Player chooses to discard hand,-> draws 4 cards
// Player 2 has 5 cards-> discards and draws 4
// Player 3 has 4 cards-> no effect
//////////////////////////////////////////////////
memset(&G, 23, sizeof(struct gameState)); 
memset(&G, 23, sizeof(struct gameState)); 
r = initializeGame(3, k, seed, &G);
assert(0,r,"initialize Game");

//make testing changes to gamestate
for(b=0; b<5; b++)
{
	G.hand[0][b] =  0;
	G.hand[1][b] =  0; // G.deck[1][b+5];
	G.hand[2][b] =  0; // G.deck[2][b+5];
}
//G.deckCount[1] = 5;
//G.deckCount[2] = 5;
G.handCount[1] = 5;
G.handCount[2] = 4;
G.hand[G.whoseTurn][0] = 17; //add minion to hand


//copy inital gamestate
memcpy(&preG, &G, sizeof(G));

//minionEffect(0, 1, &G, 0, G.whoseTurn);
cardMinion(G.whoseTurn, &G, 0, 0, 1);

//printGameState(preG);
//printGameState(G);

//Test results for expected outcome
printf("TEST 2 RESULTS: play minion, action +1, no change in hands\n");
assert( preG.coins , G.coins , "Number of treasure\n");
assert( preG.numActions +1, G.numActions, "Number of actions\n");
for(b=0;b < 4;b++)
{
	falseAssert(0, G.hand[0][b], "Cards in player zero deck changed\n");
	falseAssert(0, G.hand[1][b], "Cards in player one deck changed\n");
	assert(preG.hand[2][b], G.hand[2][b], "Cards in player two deck changed\n");
}
assert(4, G.handCount[0] , "Player zero hand count\n");
assert(4, G.handCount[1] , "Player one count\n");
assert(4, G.handCount[2] , "Player two count\n");
assert(5, G.discardCount[0] , "Player zero discard count\n" ); 
assert(5, G.discardCount[1] , "Player one discard count\n" ); 
assert(0, G.discardCount[1] , "Player two discard count\n" ); 





return 0;
}
