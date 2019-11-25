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




int printGameState(struct gameState G)
{
printf("numPlayers: %d\n", G.numPlayers);
printf("Whose turn: %d\n", G.whoseTurn);
printf("Number of buys: %d\n", G.numBuys);
printf("Number of coins: %d\n", G.coins);
printf("Current player Handcount: %d\n", G.handCount[G.whoseTurn]);
printf("Current player DeckCount: %d\n", G.deckCount[G.whoseTurn]);
printf("Current player Discard Count: %d\n", G.discardCount[G.whoseTurn]);
printf("Current Cards in hand: ");
int a = 0;
for(a=0; a < G.handCount[G.whoseTurn]; a++)
	{
	printf("%d ", G.hand[G.whoseTurn][a]);
	}
printf("\n");
printf("Current Cards in deck: ");
for(a=0; a < G.deckCount[G.whoseTurn]; a++)
	{
	printf("%d ", G.deck[G.whoseTurn][a]);
	}
printf("\n");
printf("Current Cards in discard ");
for(a=0; a < G.discardCount[G.whoseTurn]; a++)
	{
	printf("%d ", G.discard[G.whoseTurn][a]);
	}
printf("\n");

printf("Cards numbers in supply ");

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
//Baron should increase Buys by 1
//Baron will elect not to discard estate even though one is present 
//Player Should have one estate added to discard pile
/////////////////////////////////////////////////
memset(&G, 23, sizeof(struct gameState)); 
memset(&G, 23, sizeof(struct gameState)); 
int r = initializeGame(2, k, seed, &G);
assert(0,r,"initialize Game");

//make testing changes to gamestate
G.hand[G.whoseTurn][0] = 15; //add baron to hand
G.hand[G.whoseTurn][1] = 1; //add estate to hand
G.hand[G.whoseTurn][2] = 4; //add copper to hand
G.hand[G.whoseTurn][3] = 4; //add copper to hand
G.hand[G.whoseTurn][4] = 4; //add copper to hand

//copy inital gamestate
memcpy(&preG, &G, sizeof(G));

//call function to test
//printGameState(preG); 
//printGameState(G);
//curretplayer Gamestate handpos choice
cardBaron(G.whoseTurn, &G, 0, 0);
//baronEffect(0, &G,   G.whoseTurn);

//printGameState(preG);
//printGameState(G);

//Test results for expected outcome
printf("TEST 1 RESULTS: Buys increase, no discard of estate for +4 so gain estate \n");
assert( preG.numBuys + 1, G.numBuys , "Number of Buys"); 
assert( preG.supplyCount[1] , G.supplyCount[1], "Number of Estates in supply");
assert( estate, G.discard[0][0], "Estate was added to Discard");
assert( preG.coins , G.coins , "Number of treasure");

////////////////////////////////////////////////// 
//Test 2 - 
// discard estate
// +1 buy 
// +4 treasure
//////////////////////////////////////////////////
memset(&G, 23, sizeof(struct gameState)); 
memset(&G, 23, sizeof(struct gameState)); 
r = initializeGame(2, k, seed, &G);
assert(0,r,"initialize Game");

//make testing changes to gamestate
G.hand[G.whoseTurn][0] = 15; //add baron to hand
G.hand[G.whoseTurn][1] = 1; //add estate to hand
G.hand[G.whoseTurn][2] = 4; //add copper to hand
G.hand[G.whoseTurn][3] = 4; //add copper to hand
G.hand[G.whoseTurn][4] = 4; //add copper to hand

//copy inital gamestate
memcpy(&preG, &G, sizeof(G));

//call function to test
//printGameState(preG); 
//printGameState(G);
//currentplay, gamestate, handpos, choice1
cardBaron(G.whoseTurn, &G, 0, 1);
//baronEffect(1, &G, G.whoseTurn);

//printGameState(preG);
//printGameState(G);

//Test results for expected outcome
printf("TEST 2 RESULTS - Typical Baron play, Discard estate, gain +4 \n");
assert( preG.numBuys + 1, G.numBuys , "Number of Buys"); 
assert( preG.coins + 4 , G.coins , "Number of treasure");
assert( estate, G.discard[0][0], "Estate was added to Discard");
assert( preG.supplyCount[1], G.supplyCount[1], "Estate supply count");

//////////////////////////////////////////////////////////////
//TEST 3	
// 4 coppers in hand, 1 baron in hand
// Try to play +4 treasure no estante in hand
// only 1 estate in supply  	
// Result should be no additional treasure and also no estate
//////////////////////////////////////////////////////////////
memset(&G, 23, sizeof(struct gameState)); 
memset(&G, 23, sizeof(struct gameState)); 
r = initializeGame(2, k, seed, &G);
assert(0,r,"initialize Game");

//make testing changes to gamestate
G.hand[G.whoseTurn][0] = 15; //add baron to hand
G.hand[G.whoseTurn][1] = 4; //add copper to hand
G.hand[G.whoseTurn][2] = 4; //add copper to hand
G.hand[G.whoseTurn][3] = 4; //add copper to hand
G.hand[G.whoseTurn][4] = 4; //add copper to hand
G.supplyCount[1] = 1; //only a single estate in supply
G.discard[G.whoseTurn][0] = -5; //clear garbage out of discard
//copy inital gamestate
memcpy(&preG, &G, sizeof(G));

//call function to test
//printGameState(preG); 
//printGameState(G);
cardBaron(G.whoseTurn, &G, 0, 1);
//baronEffect(1, &G, G.whoseTurn);

//printGameState(preG);
//printGameState(G);

//Test results for expected outcome
printf("TEST 3 RESULTS - No estate in hand,just barron and coppers, still try to gain +4 \n");
assert( preG.numBuys + 1, G.numBuys , "Number of Buys"); 
assert( preG.coins , G.coins , "Number of treasure");
assert( preG.supplyCount[1]-1, G.supplyCount[1], "Estate supply count");
assert( estate, G.discard[0][0], "Estate was added to Discard");

/////////////////////////////////////////////////////////////
//Test 4
// All curses in hand 
// Try to still play estate for +4 treasure
/////////////////////////////////////////////////////////////
memset(&G, 23, sizeof(struct gameState)); 
memset(&G, 23, sizeof(struct gameState)); 
r = initializeGame(2, k, seed, &G);
assert(0,r,"initialize Game");

//make testing changes to gamestate
G.hand[G.whoseTurn][0] = 0; //add baron to hand
G.hand[G.whoseTurn][1] = 0; //add curse to hand
G.hand[G.whoseTurn][2] = 0; //add curse to hand
G.hand[G.whoseTurn][3] = 0; //add curse to hand
G.hand[G.whoseTurn][4] = 0; //add curse to hand
G.discard[G.whoseTurn][0] = -999; //clear garbage out of discard

//copy inital gamestate
memcpy(&preG, &G, sizeof(G));

//call function to test
//printGameState(preG); 
//printGameState(G);
cardBaron(G.whoseTurn, &G, -1, 1);
//baronEffect(1, &G, G.whoseTurn);

//printGameState(preG);
//printGameState(G);

//Test results for expected outcome
printf("TEST 4 RESULTS - No estate in hand, only baron and curses, still try to gain +4 \n");
assert( preG.numBuys + 1, G.numBuys , "Number of Buys"); 
assert( preG.coins , G.coins , "Number of treasure");
assert( preG.supplyCount[1], G.supplyCount[1], "Estate supply count");
assert( estate, G.discard[0][0], "Estate was added to Discard");



return 0;
}
