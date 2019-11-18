#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int printGameState(struct gameState G);
void randomizer(struct gameState *preG, struct gameState *postG);
void testResults(struct gameState preG, struct gameState G, int choice1, int trialNum);
int assert(int expected, int testval , char* string, struct gameState preG, struct gameState postG, int TrialNum );
 



int assert(int expected, int testval , char* string, struct gameState preG, struct gameState postG, int trialNum )
{ 
	if(expected==testval)
	{	return 0;}
	else if(expected > testval)
	{
		printf("\n\nERROR: Trial Number: %d\n", trialNum);
		printf("ASSERT FAILED: (%d-expected)(%d-value present) for %s\n", expected, testval, string);
//		printf("------Preconditions:------\n");
//		printGameState(preG);
//		printf("------Postconditions:------\n");
//		printGameState(postG);
	} 
	else if(expected < testval)
	{
		printf("\n\nERROR: Trial Number: %d\n", trialNum);
		printf("ASSERT FAILED: (%d-expected)(%d-value present) for %s\n", expected, testval, string);
//		printf("------Preconditions:------\n");
//		printGameState(preG);
//		printf("------Postconditions:------\n");
//		printGameState(postG);
	

	} 

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
printf("Current Cards in hand: \n");
int a = 0, b = 0 ;

for(b=0; b < G.numPlayers; b++)
{
	printf("Player %d Cards: \n", b+1);
	printf("Current Cards in hand: ");
	for(a=0; a < G.handCount[b]; a++)
		{
		printf("%d ", G.hand[b][a]);
		}
	printf("\n");
	printf("Current Cards in deck: ");
	for(a=0; a < G.deckCount[b]; a++)
		{
		printf("%d ", G.deck[b][a]);
		}
	printf("\n");
	printf("Current Cards in discard ");
	for(a=0; a < G.discardCount[b]; a++)
		{
		printf("%d ", G.discard[b][a]);
		}
	printf("\n");
}
printf("Cards numbers in supply ");

for(a=0; a < 26; a++)
	{
	printf("%d ", G.supplyCount[a]);
	}
printf("\n");

return 0;
}


void randomizer(struct gameState *preG, struct gameState *postG)
{
	int cardsIn = 20; 
	int a, playr, randCard;
	postG->numPlayers = (rand() % 3)+2; 		//number of players
	postG->whoseTurn = rand() % postG->numPlayers; // whose turn it is
	postG->coins = rand() % 72 ; //Max treasure in game
	postG->numBuys = rand() % 20; //Number of Buys
	postG->supplyCount[estate] = rand() % 13; //Number of supplys

	for (playr = 0;playr< postG->numPlayers; playr++)	
	   {
		//Set up player hands discard and decks
		postG->handCount[playr] = (rand() % cardsIn)+1; //Number of cards in player's hand
		postG->deckCount[playr] = (rand() % cardsIn); //Number of cards in player's deck
		postG->discardCount[playr] = (rand() % cardsIn); //Number of cards in player's discard count
	
		for(a=0;a<postG->handCount[playr];a++) //randomize cards in hand
		{
			randCard = rand() % (treasure_map+1); 
			postG->hand[playr][a] = randCard;
		}
		for(a=0;a<postG->deckCount[playr];a++) //randomize cards in hand
		{
			randCard = rand() % (treasure_map+1); 
			postG->deck[playr][a] = randCard;
		}
		for(a=0;a<postG->discardCount[playr];a++) //randomize cards in hand
		{
			randCard = rand() % (treasure_map+1); 
			postG->discard[playr][a] = randCard;
		}
	
	    }

	//make sure minion is in hand of current player
	int foundMinion = 0;
	for(a=0 ; a < postG->handCount[postG->whoseTurn] ; a++)
	  {
		if( postG->hand[postG->whoseTurn][a] == minion)
		{	foundMinion = 1;} 
	  }
	if (foundMinion == 0)
  	  {
		//add baron to a random card in players hand
		postG->hand[postG->whoseTurn][rand() % postG->handCount[postG->whoseTurn]] = minion; 
	  }		

}




void testResults(struct gameState preG, struct gameState G, int choice, int trialNum)
{
	//Test results for expected outcome

	assert( preG.numActions + 1, G.numActions , "Number of Actions should have increased by 1", preG, G, trialNum); 
	int d;
	//test options 1
	//plus two treasure
	//all hands stay the same
	if(choice==0)	
	{	for(d=0; d< G.numPlayers; d++)
		{
			if(G.whoseTurn != d)
			{assert(preG.handCount[d], G.handCount[d], "Choice 0: Other Player handcount should not change", preG, G, trialNum);}	
			else
			{assert(preG.handCount[d]-1, G.handCount[d], "Choice 0: Player handcount should lose one minion card", preG, G, trialNum);}	
	
		}	
		assert(preG.coins+2, G.coins, "Choice 0: treasure should increase by 2", preG, G, trialNum);
	}
	//test option 2 
	//treasure stays the same
	//all hands with 5+ cards have 4 cards
	if(choice==1)	
	{	for(d=0; d< G.numPlayers; d++)
		{
			if(preG.handCount[d] > 4)
			assert(4, G.handCount[d], "Choice 1: Player handcount should drop to 4 if more than 5", preG, G, trialNum);	
		}	
		assert(preG.coins, G.coins, "Choice 0: treasure should not increase", preG, G, trialNum);
	}
	

return;
}




int main()
{
   int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

   struct gameState postG;
   struct gameState preG;

   unsigned seed;
   seed = time(0);
   srand(seed);

   int c, numOfTrials = 3000;
   for(c = 0;c< numOfTrials;c++)
   {
	memset(&preG, 23, sizeof(struct gameState)); 
	memset(&postG, 23, sizeof(struct gameState)); 
	int r = initializeGame(2, k, seed, &postG);
	assert(0,r,"initialize Game", preG, postG, c);

	//determine how card is played
	int choice1 = rand() % 2;
	int choice2 = 1 - choice1;  
	int handpos, e;

	//randomize hands and decks
	randomizer(&preG, &postG);
	for(e=0; e < postG.handCount[postG.whoseTurn]; e++)
	{
		if (postG.hand[postG.whoseTurn][e] == 17)
		{
			handpos = e; break;
		} 
	}

	//Copy to pre gamestate
	memcpy(&preG, &postG, sizeof(postG));
//	printGameState(preG);
//	printGameState(postG);
	r = minionEffect(choice1, choice2, &postG,handpos , postG.whoseTurn);
	assert(0,r,"minionEffect Return Value", preG, postG, c);
	testResults(preG, postG, choice2, c);

   }
return 0;
}


